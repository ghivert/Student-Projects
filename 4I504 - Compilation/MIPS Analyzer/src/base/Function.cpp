#include <Function.h>

Function::Function() {
  _head = NULL;
  _end = NULL;
  BB_computed = false;
  BB_pred_succ = false;
  dom_computed = false;
}

Function::~Function() {}

void Function::set_head(Line *head) {
  _head = head;
}

void Function::set_end(Line *end) {
  _end = end;
}

Line *Function::get_head() {
  return _head;
}

Basic_block *Function::get_firstBB() {
  return _myBB.front();
}

Line *Function::get_end() {
  return _end;
}

void Function::display() {
  cout << "Begin Function" << endl;
  Line *element = _head;

  if (element == _end)	
    cout << _head->get_content() << endl;

  while (element != _end) {
    cout << element->get_content() << endl;
		
    if (element->get_next() == _end) {
      cout << element->get_next()->get_content() << endl;
      break;
    } else 
      element = element->get_next();
  }
  cout << "End Function\n\n" << endl;
}

int Function::size() {
  Line *element = _head;
  int length = 0;
  while (element != _end) {
    length++;
    if (element->get_next() == _end)
      break;
    else
      element = element->get_next();
  }
  return length;
}	

void Function::restitution(string const filename) {
  Line *element = _head;
  ofstream monflux(filename.c_str(), ios::app);

  if (monflux) {
    monflux << "Begin" << endl;
    if (element == _end)	
      monflux << _head->get_content() <<endl;
    while (element != _end) {
      if (element->isInst() || element->isDirective()) 
	monflux << "\t";
      monflux << element->get_content() ;
	
      if (element->get_content().compare("nop")) 
	monflux << endl;
		
      if (element->get_next()==_end) {
	if (element->get_next()->isInst() || element->get_next()->isDirective())
	  monflux << "\t";
	monflux << element->get_next()->get_content() << endl;
	break;
      } else
	element = element->get_next();
    }
    monflux << "End\n\n" << endl;
  } else {
    cout << "Error cannot open the file" << endl;
  }

  monflux.close();
}

void Function::comput_label() {
  Line *element = _head;

  if (element == _end && element->isLabel())	
    _list_lab.push_back(getLabel(element));
  while (element != _end) {
    if (element->isLabel())	
      _list_lab.push_back(getLabel(element));
    
    if (element->get_next() == _end) {
      if (element->isLabel())
	_list_lab.push_back(getLabel(element));
      break;
    } else 
      element = element->get_next();
  }
}

int Function::nbr_label() {
  return _list_lab.size();
}

Label* Function::get_label(int index) {
  list<Label*>::iterator it;
  it = _list_lab.begin();

  int size = (int) _list_lab.size();
  if (index < size) {
    for (int i = 0; i < index; i++) it++;
    return *it;	
  } else 
    cout << "Error get_label : index is bigger than the size of the list" << endl;
	
  return _list_lab.back();
}

Basic_block* Function::find_label_BB(OPLabel *label) {
  int size = (int) _myBB.size();
  string str;
   
  for (int i = 0; i < size; i++)
    if (get_BB(i)->is_labeled()) {
       
      str = get_BB(i)->get_head()->get_content();
      if (!str.compare(0, (str.size() - 1), label->get_op()))
	return get_BB(i);
    }
   
  return NULL;
}


/* ajoute nouveau BB à la liste de BB de la fonction en le creant */

void Function::add_BB(Line *debut, Line* fin, Line *br, int index) {
  Basic_block *b = new Basic_block();
  b->set_head(debut);
  b->set_end(fin);
  b->set_index(index);
  b->set_branch(br);
  _myBB.push_back(b);
}


/* Calcule la liste des blocs de base : il faut délimiter les BB, 
   en parcourant la liste des lignes/instructions à partir de la 
   premiere, il faut s'arreter à chaque branchement (et prendre 
   en compte le delayed slot qui appartient au meme BB, c'est 
   l'instruction qui suit tout branchement) ou à chaque label 
   (on estime que tout label est utilisé par un saut et donc 
   correspond bien à une entete de BB). */

void Function::comput_basic_block() {
  cout << "comput BB" << endl;
  
#ifdef DEBUG
  cout << "head :" << _head->get_content() << endl;
  cout << "tail :" <<  _end->get_content() << endl;
#endif
  
  // Function have to be called once. If not, just skip.
  if (!BB_computed) {
    int ind = 0;
    Line *current = _head, *beg = NULL;
    
    while(current != _end->get_next()) {
      if (current->isLabel()) {
	if (beg)
	  add_BB(beg, current->get_prev(), NULL, ind++);
	beg = current;
      } else if (current->isInst()) {
	if (getInst(current)->is_branch()) {
	  if (beg)
	    add_BB(beg, current->get_next(), current, ind++);
	  else
	    add_BB(current, current->get_next(), current, ind++);
	  current = current->get_next();
	  beg = NULL;
	} else
	  if (!beg) beg = current;
      } else if (current->isDirective()) {
	// Just a directive, uninteresting. Skip it bro.
      } else {
	if (beg) {
	  add_BB(beg, current->get_prev(), NULL, ind++);
	  beg = NULL;
	}
      }
      
      // Next !
      current = current->get_next();
    }
  
#ifdef DEBUG
    cout << "end comput Basic Block" << endl;
#endif
  
    BB_computed = true;
  }
}

int Function::nbr_BB() {
  return _myBB.size();
}

Basic_block *Function::get_BB(int index) {

  list<Basic_block*>::iterator it;
  it=_myBB.begin();
  int size=(int)_myBB.size();
  
  if (index< size) {
    for (int i = 0; i < index; i++) it++;
    return *it;	
  } else 
    return NULL;
}

list<Basic_block*>::iterator Function::bb_list_begin() {
  return _myBB.begin();
}

list<Basic_block*>::iterator Function::bb_list_end() {
  return _myBB.end();
}

/* Calcule les successeurs et prédécesseurs des BB. 
   Pour cela, il faut commencer par les successeurs et itérer sur tous 
   les BB d'une fonction. Il faut determiner si un BB a un ou deux
   successeurs : dépend de la présence d'un saut à la fin ou non.
   Pas de saut, saut incontionnel ou appel de fonction : 1 successeur (lequel ?).
   Branchement conditionnel : 2 successeurs. 
   Le dernier bloc n'a pas de successeurs - celui qui se termine par jr R31.
   Les sauts indirects n'ont pas de successeur. */
void Function::comput_succ_pred_BB() {
  Basic_block *current = NULL;
  Instruction *instr;
  
  // Function have to be called once. If it's called more, skip it.
  if (!BB_pred_succ) {
      
    for (int i = 0; i < nbr_BB(); i++) {
      current = get_BB(i);
      instr = getInst(get_BB(i)->get_end()->get_prev());
      if (instr->is_branch()) {
	if (instr->is_cond_branch()) {
	  current->set_link_succ_pred(find_label_BB(instr->get_op_label()));
	  if (get_BB(i + 1) != NULL) {
	    current->set_link_succ_pred(get_BB(i + 1));
	  }
	  cout << current->get_nb_succ();
	} else if (!instr->is_cond_branch()) {
	  if (instr->get_opcode() == jr) {
	    if (((OPRegister *) instr->get_op1())->get_reg() != 31)
	      current->set_link_succ_pred(find_label_BB(instr->get_op_label()));
	  }
	  if (instr->get_opcode() == j) {
	    current->set_link_succ_pred(find_label_BB(instr->get_op_label()));
	  }
	  if (instr->get_opcode() == jal) {
	    if (get_BB(i + 1) != NULL) {
	      current->set_link_succ_pred(get_BB(i + 1));
	    }
	  }
	}
      } else if (instr->is_call()) {
	if (get_BB(i + 1))
	  current->set_link_succ_pred(get_BB(i + 1));
      } else if (instr->is_indirect_branch()) {
	// Nope.
      } else {
	if (get_BB(i + 1))
	  current->set_link_succ_pred(get_BB(i + 1));
      }
    }

    BB_pred_succ = true;
    }
}

void Function::compute_dom() {
  list<Basic_block*>::iterator it;
  list<Basic_block*> workingList;
  Basic_block *current, *pred;
  int size = (int)_myBB.size();
  
  if (!dom_computed) {
    comput_succ_pred_BB();
  
    // Add all blocks without preds.
    it = _myBB.begin();
    for (int j = 0; j < size; j++) {
      current = *it;
      if (current->get_nb_pred() == 0) {
	for (int i = 0; i < NB_MAX_BB; i++)
	  current->Domin[i] = false;
	current->Domin[current->get_index()] = true;
	workingList.push_back(current);
      }
      it++;
    }
  
    while (!workingList.empty()) {
      current = workingList.front();
      workingList.pop_front(); 
    
      std::vector<bool> past(current->Domin);
    
      if (current->get_nb_pred() != 0) {
	for (int j = 0; j < current->get_nb_pred(); j++) {
	  pred = current->get_predecessor(j);
	  for (int i = 0; i < NB_MAX_BB; i++)
	    current->Domin[i] = current->Domin[i] & pred->Domin[i];
	}
	current->Domin[current->get_index()] = true;
      }
    
      bool same = true;
      for (int i = 0; i < NB_MAX_BB; i++) {
	if (current->Domin[i] != past[i]) {
	  same = false;
	  break;
	}
      }
    
      if (!same || current->get_nb_pred() == 0)
	switch(current->get_nb_succ()) {
	case 2: workingList.push_back(current->get_successor2());
	case 1: workingList.push_back(current->get_successor1());
	}
    }
  
  
    // Affichage du résultat.
    it = _myBB.begin();

    for (int j = 0; j < size; j++) {
      current = *it;
      cout << "Dominants pour BB" << current->get_index() << " : ";
      for (int i = 0; i < nbr_BB(); i++)
	if (current->Domin[i]) 
	  cout << " BB" << i;
      cout << endl;
      it++;
    }
  }
  
  dom_computed = true;
}


void Function::compute_live_var() {
  fflush(stdout);
  list<Basic_block*>::iterator it, it2;
  list<Basic_block*> workinglist;
  Basic_block *current, *bb, *pred;
  bool change = true;
  int size= (int) _myBB.size();
  it=_myBB.begin();

  vector<bool> computed(size, 0);

  for (int i = 0; i < size; i++) {
    if ((*it)->get_nb_succ() == 0) workinglist.push_back(*it);
    (*it++)->compute_use_def();
  }

  while (!workinglist.empty()) {
    current = workinglist.front();
    workinglist.pop_front();
    computed[current->get_index()] = 1;

    // Calcul de LiveOut
    if (current->get_nb_succ() != 0) {
      for (int i = 0; i < NB_REG; i++) {
        if (bb = current->get_successor1())
          current->LiveOut[i] = current->LiveOut[i] || bb->LiveIn[i];
        if (bb = current->get_successor2())
          current->LiveOut[i] = current->LiveOut[i] || bb->LiveIn[i];
      }
    } else {
      if (current->get_branch())
        current->LiveOut[2] = 1;
    }

    // Calcul de LiveIn
    for (int i = 0; i < NB_REG; i++) 
      current->LiveIn[i] = current->Use[i] || (current->LiveOut[i] && !current->Def[i]);

    // actualisation de la working list
    for (int i = 0; i < current->get_nb_pred(); i++) {
      pred = current->get_predecessor(i);
      if (! computed[pred->get_index()])
        workinglist.push_back(pred);
    }
  }
  
  /* AFFICHAGE DU RESULTAT */
  it2=_myBB.begin();
  for (int j=0; j<size; j++){
    bb = *it2;
    cout << "********* bb " << bb->get_index() << "***********" << endl;
    cout << "LIVE_OUT : " ;
    for(int i=0; i<NB_REG; i++){
      if (bb->LiveOut[i]){
	cout << "$"<< i << " "; 
      }
    }
    cout << endl;
    cout << "LIVE_IN :  " ;
    for(int i=0; i<NB_REG; i++){
      if (bb->LiveIn[i]){
	cout << "$"<< i << " "; 
      }}
    cout << endl;
    it2++;
  }
  return;
}
     



/* en implementant la fonction test de la classe BB, permet de tester des 
   choses sur tous les blocs de base d'une fonction par exemple l'affichage 
   de tous les BB d'une fonction ou l'affichage des succ/pred des BBs comme 
   c'est le cas -- voir la classe Basic_block et la méthode test 
*/
void Function::test(){
  int size=(int)_myBB.size();
  for(int i=0;i<size; i++){
    get_BB(i)->test();
  }
  return;
}
