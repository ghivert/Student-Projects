#include <Basic_block.h>


//static
void Basic_block::show_dependances(Instruction *i1, Instruction *i2){
   
   if(i1->is_dep_RAW1(i2)) 
      cout<<"Dependance i"<<i1->get_index()<<"->i"<<i2->get_index()<<": RAW1"<<endl; 
   if(i1->is_dep_RAW2(i2)) 
      cout<<"Dependance i"<<i1->get_index()<<"->i"<<i2->get_index()<<": RAW2"<<endl;
   
   if(i1->is_dep_WAR(i2)) 
      cout<<"Dependance i"<<i1->get_index()<<"->i"<<i2->get_index()<<": WAR"<<endl;
   
   if(i1->is_dep_WAW(i2)) 
      cout<<"Dependance i"<<i1->get_index()<<"->i"<<i2->get_index()<<": WAW"<<endl;
   
   if(i1->is_dep_MEM(i2)) 
      cout<<"Dependance i"<<i1->get_index()<<"->i"<<i2->get_index()<<": MEM"<<endl;
   
}

Basic_block::Basic_block():
  Use(vector<bool>(NB_REG, false)),
  LiveIn(vector<bool>(NB_REG, false)),
  LiveOut(vector<bool>(NB_REG, false)), 
  Def(vector<bool>(NB_REG, false)),
  DefLiveOut(vector<int>(NB_REG, -1)), 
  Domin(vector<bool>(NB_MAX_BB, true)){
   _head = NULL;
   _end = NULL;
   _branch = NULL;
   _index = 0;
   _nb_instr = 0;
   _firstInst=NULL;
   _lastInst=NULL;
   dep_done = false;
   use_def_done = false;
}


Basic_block::~Basic_block(){}


void Basic_block::set_index(int i){
   _index = i;
}

int Basic_block::get_index(){
   return _index;
}

void Basic_block::set_head(Line *head){
   _head = head;
}

void Basic_block::set_end(Line *end){
   _end = end;
}

Line* Basic_block::get_head(){
   return _head;
}

Line* Basic_block::get_end(){
   return _end;
}

void Basic_block::set_successor1(Basic_block *BB){
   _succ.push_front(BB);
}

Basic_block *Basic_block::get_successor1(){
   if (_succ.size()>0)
      return _succ.front();
   else 
      return NULL;
}

void Basic_block::set_successor2(Basic_block *BB){	
   _succ.push_back(BB);
}

Basic_block *Basic_block::get_successor2(){
   if (_succ.size()> 1)
      return _succ.back();
   else 
      return NULL;
}

void Basic_block::set_predecessor(Basic_block *BB){
   _pred.push_back(BB);
}

Basic_block *Basic_block::get_predecessor(int index){

   list<Basic_block*>::iterator it;
   it=_pred.begin();
   int size=(int)_pred.size();
   if(index< size){
      for (int i=0; i<index; i++, it++);
      return *it;	
   }
   else cout<<"Error: index is bigger than the size of the list"<<endl; 	
   return _pred.back();
	
}

int Basic_block::get_nb_succ() {
  return _succ.size();
}

int Basic_block::get_nb_pred(){
   return _pred.size();
}

void Basic_block::set_branch(Line* br){
   _branch=br;
}

Line* Basic_block::get_branch(){
   return _branch;
}

void Basic_block::display(){
   cout<<"Begin BB"<<endl;
   Line* element = _head;
   int i=0;
   if(element == _end)	
      cout << _head->get_content() <<endl;
  
   while(element != _end->get_next()){
      if(element->isInst()){
	 cout<<"i"<<i<<" ";
	 i++;
      }
      if(!element->isDirective())
	 cout <<element->get_content() <<endl;
      
      element = element->get_next();
   }
   cout<<"End BB"<<endl;
}

string Basic_block::get_content(){
   string rt = "";
   Line* element = _head;
  
   
   while(element != _end->get_next()){
     if(element->isInst()){
	rt = rt + element->get_content() + "\\l" ;	 	
     }
     else if(element->isLabel())
       rt = rt + element->get_content() + "\\l" ;
      
      element = element->get_next();
   }
  
   return rt ;
}

int Basic_block::size(){
   Line* element = _head;
   int lenght=0;
   while(element != _end){
      lenght++;
      if(element->get_next()==_end)	
	 break;
      else 
	 element = element->get_next();
   }
   return lenght;
}	


void Basic_block::restitution(string const filename){	
   Line* element = _head;
   ofstream monflux(filename.c_str(), ios::app);
   if(monflux){
      monflux<<"Begin BB"<<endl;
      if(element == _end)	
	monflux << _head->get_content() <<endl;
      while(element != _end)
      {
	 if(element->isInst()) 
	    monflux<<"\t";
	 if(!element->isDirective())
	    monflux << element->get_content()<<endl ;
		
	 if(element->get_next()==_end){
	    if(element->get_next()->isInst()) 
	       monflux<<"\t";
	    if(!element->isDirective())
	       monflux << element->get_next()->get_content()<<endl;
	    break;
	 }
	 else element = element->get_next();
      }
      monflux<<"End BB\n\n"<<endl;		
   }
   else {
      cout<<"Error cannot open the file"<<endl;
   }
   monflux.close();

}

bool Basic_block::is_labeled(){
   if (_head->isLabel()){
      return true;
   }
   else return false;
}

int Basic_block::get_nb_inst(){   
   if (_nb_instr == 0)
      link_instructions();
   return _nb_instr;
    
}

Instruction* Basic_block::get_instruction_at_index(int index){
   Instruction *inst;
   
   if(index >= get_nb_inst()){
      return NULL;
   }
   
   inst=get_first_instruction();

   for(int i=0; i<index; i++, inst=inst->get_next());

   return inst;
}

Line* Basic_block::get_first_line_instruction(){
   
   Line *current = _head;
   while(!current->isInst()){
      current=current->get_next();
      if(current==_end)
	 return NULL;
   }
   return current;
}

Instruction* Basic_block::get_first_instruction(){
  if(_firstInst==NULL){
      _firstInst= getInst(this->get_first_line_instruction());
      this->link_instructions();
  }
   return _firstInst;
}

Instruction* Basic_block::get_last_instruction(){
   if(_lastInst==NULL)
      this->link_instructions();
   return _lastInst;
}


/* link_instructions  numérote les instructions du bloc */
/* remplit le champ nb d'instructions du bloc (_nb_instr) */
/* remplit le champ derniere instruction du bloc (_lastInst) */
void Basic_block::link_instructions(){

   int index=0;
   Line *current, *next;
   current=get_first_line_instruction();
   next=current->get_next();

   Instruction *i1 = getInst(current);

   i1->set_index(index);
   index++;
   Instruction *i2;
   
//Calcul des successeurs
   while(current != _end){
   
      while(!next->isInst()){
	 next=next->get_next();
	 if(next==_end){
	    if(next->isInst())
	       break;
	    else{
	       _lastInst = i1;
	       _nb_instr = index;
	       return;
	    }
	 }
      }
      
      i2 = getInst(next);
      i2->set_index(index);
      index++;
      i1->set_link_succ_pred(i2);
      
      i1=i2;
      current=next;
      next=next->get_next();
   }
   _lastInst = i1;
   _nb_instr = index;
}

bool Basic_block::is_delayed_slot(Instruction *i){
   if (get_branch()== NULL)
      return false;
   int j = (getInst(get_branch()))->get_index();
   return (j < i-> get_index());

}

/* set_link_succ_pred : ajoute succ comme successeur de this et ajoute this comme prédécesseur de succ
 */

void Basic_block::set_link_succ_pred(Basic_block* succ){
  _succ.push_back(succ);
  succ->set_predecessor(this);
}

/* add_dep_link ajoute la dépendance avec pred à la liste des dependances précédesseurs de succ */
/* ajoute la dependance avec succ à la liste des dépendances successeurs de pred */

/* dep est une structure de données contenant une instruction et  un type de dépendance */

void add_dep_link(Instruction *pred, Instruction* succ, t_Dep type){
   dep *d;
   d=(dep*)malloc(sizeof(dep));
   d->inst=succ;
   d->type=type;
   pred->add_succ_dep(d);
   
   d=(dep*)malloc(sizeof(dep));
   d->inst=pred;
   d->type=type;
   succ->add_pred_dep(d);
}


/* calcul des dépendances entre les instructions dans le bloc  */
/* une instruction a au plus 1 reg dest et 2 reg sources */
/* Attention le reg source peut être 2 fois le même */ 
/* Utiliser les méthodes is_dep_RAW1, is_dep_RAW2, is_dep_WAR, is_dep_WAW, is_dep_MEM pour déterminer les dépendances */

/* ne pas oublier les dépendances de controle avec le branchement s'il y en a un */

/* utiliser la fonction add_dep_link ci-dessus qui ajoute à la liste des dépendances pred et succ une dependance entre 2 instructions */


void Basic_block::comput_pred_succ_dep(){
   
  
  link_instructions();
  if (!dep_done) {
    Instruction *i_current = get_last_instruction(), *itmp;
   
    while (i_current) {
      itmp = i_current->get_prev();
      int fin = 0;
      while (itmp) {
	if (itmp->is_dep_RAW1(i_current) && !(fin & 1)) {
	  add_dep_link(itmp, i_current, RAW);
	  fin |= 1;
	}
	if (itmp->is_dep_RAW2(i_current) && !(fin & 2)) {
	  add_dep_link(itmp, i_current, RAW);
	  fin |= 2;
	}
	if (itmp->is_dep_MEM(i_current) && !(fin & 4)) {
	  add_dep_link(itmp, i_current, MEMDEP);
	  fin |= 4;
	}
	if (itmp->is_dep_WAW(i_current)) {
	  add_dep_link(itmp, i_current, WAW);
	  break;
	}
	if (itmp->is_dep_WAR(i_current))
	  add_dep_link(itmp, i_current, WAR);
	itmp = itmp->get_prev();
      }
      i_current=i_current->get_prev();
    }
   
    itmp = get_last_instruction()->get_prev();
    if (itmp->is_branch()) {
      for (int i = 0; i < get_nb_inst() - 2; i++) {     
	i_current = get_instruction_at_index(i);
	if (i_current->get_nb_succ() == 0) 
	  add_dep_link(itmp, i_current, CONTROL);
      }
    }
    // NE PAS ENLEVER : cette fonction ne doit être appelée qu'une seule fois
    dep_done = true;
  }
}

void Basic_block::reset_pred_succ_dep(){

  Instruction *ic=get_first_instruction();
  while (ic){
    ic -> reset_pred_succ_dep();
    ic = ic -> get_next();
  }
  dep_done = false;
  return;
}

/* calcul le nb de cycles pour executer le BB, on suppose qu'une instruction peut sortir du pipeline à chaque cycle, il faut trouver les cycles de gel induit par les dépendances */

int Basic_block::nb_cycles() {
  /*
  Instruction *ic = get_last_instruction();
  // int instruction = 0;
  // int cycle = 1;
  vector<int> inst_cycle(get_nb_inst()); 
  for (int i = 0; i < get_nb_inst(); i++) {
    inst_cycle[i] = 0;
  }
  comput_pred_succ_dep();
  
  inst_cycle[get_nb_inst()-1] = 1;
  while (ic != get_first_instruction()) {
    
  }
   
  /*
  while (ic != NULL) {
    for (Instruction *next = ic->get_prev(); next != NULL; next = next->get_prev())
      if (ic->is_dependant(next) == RAW) {
	inst_cycle[instruction++] = cycle + delai(ic, next);
	cycle += delai(ic, next);
	break;
      }
    cycle++;
    ic = ic->get_prev();
    }
  */
  return 0;
}

/* 
calcule DEF et USE pour l'analyse de registre vivant 
à la fin on doit avoir
 USE[i] vaut 1 si $i est utilisé dans le bloc avant d'être potentiellement défini dans le bloc
 DEF[i] vaut 1 si $i est défini dans le bloc 
******************/

void Basic_block::compute_use_def(void){
  Instruction * inst = get_first_instruction();
  if (use_def_done) return;
 
  /* A REMPLIR */

#ifdef DEBUG  
  cout << "****** BB " << get_index() << "************" << endl;
  cout << "USE : " ;
  for(int i=0; i<NB_REG; i++){
      if (Use[i])
      cout << "$"<< i << " "; 
  }
  cout << endl;
  cout << "DEF : " ;
  for(int i=0; i<NB_REG; i++){
      if (Def[i])
	cout << "$"<< i << " "; 
    }
  cout << endl;
#endif

    return;
}

/**** compute_def_liveout 
à la fin de la fonction on doit avoir
DefLiveOut[i] vaut l'index de l'instruction du bloc qui définit $i si $i vivant en sortie seulement
Si $i est défini plusieurs fois c'est l'instruction avec l'index le plus grand
*****/
void Basic_block::compute_def_liveout(){
  
  Instruction * inst = get_first_instruction();
 
  /* A REMPLIR */

#ifdef DEBUG
  cout << "DEF LIVE OUT: " ;
  for(int i=0; i<NB_REG; i++){
      if (DefLiveOut[i] != -1)
	cout << "$"<< i << " definit par i" << DefLiveOut[i] << endl; 
    }

#endif

}



/**** renomme les registres renommables : ceux qui sont définis et utilisés dans le bloc et dont la définition n'est pas vivante en sortie
Utilise comme registres disponibles ceux dont le numéro est dans la liste paramètre 
*****/
void Basic_block::reg_rename(list<int> *frees){
  Instruction * inst = get_first_instruction();
  int newr;
  compute_def_liveout();
 

  /* A REMPLIR */

}


/**** renomme les registres renommables : ceux qui sont définis et utilisés dans le bloc et dont la définition n'est pas vivante en sortie
Utilise comme registres disponibles ceux dont le numéro est dans la liste paramètre 
*****/
void Basic_block::reg_rename(){
  Instruction * inst = get_first_instruction();
  int newr;
  list<int> *frees, lfree;
 
  
  /* A REMPLIR */
}

void Basic_block::apply_scheduling(list <Node_dfg*> *new_order){
   list <Node_dfg*>::iterator it=new_order->begin();
   Instruction *inst=(*it)->get_instruction();
   Line *n=_head, *prevn=NULL;
   Line *end_next = _end->get_next();
   if(!n){
      cout<<"wrong bb : cannot apply"<<endl;
      return;
   }
   
   while(!n->isInst()){
     prevn=n;
     n=n->get_next();
     if(n==_end){
       cout<<"wrong bb : cannot apply"<<endl;
       return;
     }
   }
   
   //y'a des instructions, on sait pas si c'est le bon BB, mais on va supposer que oui
   inst->set_index(0);
   inst->set_prev(NULL);
   _firstInst = inst;
   n = inst;
   
   if(prevn){
     prevn->set_next(n);
     n->set_prev(prevn);
   }
   else{
     set_head(n);
   }

   int i;
   it++;
   for(i=1; it!=new_order->end(); it++, i++){

     inst->set_link_succ_pred((*it)->get_instruction());
     
     inst=(*it)->get_instruction();
     inst->set_index(i);
     prevn = n;
     n = inst;
     prevn->set_next(n);
     n->set_prev(prevn);
     }
   inst->set_next(NULL);
   _lastInst = inst;
   set_end(n);
   n->set_next(end_next);
   return;
}

/* permet de tester des choses sur un bloc de base, par exemple la construction d'un DFG, à venir ... là ne fait rien qu'afficher le BB */
void Basic_block::test(){
   cout << "test du BB " << get_index() << endl;
   display();
   cout << "nb de successeur : " << get_nb_succ() << endl;
   int nbsucc = get_nb_succ() ;
   if (nbsucc >= 1 && get_successor1())
      cout << "succ1 : " << get_successor1()-> get_index();
   if (nbsucc >= 2 && get_successor2())
      cout << " succ2 : " << get_successor2()-> get_index();
   cout << endl << "nb de predecesseurs : " << get_nb_pred() << endl ;
  
   int size=(int)_pred.size();
   for (int i = 0; i < size; i++){
      if (get_predecessor(i) != NULL)
	 cout << "pred "<< i <<  " : " << get_predecessor(i)-> get_index() << "; ";
   }
   cout << endl;
}
