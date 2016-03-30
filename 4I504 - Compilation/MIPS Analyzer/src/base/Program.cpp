#include <Program.h>
#include <asm_mipsyac.h>

extern	void programparse(string) ; 
extern	Program prog ;

Program::Program() {
  _head = NULL;
  _length = 0;
}


// constructeur de copie
Program::Program(Program const& otherprogram) {
  // On initialise la liste.
  _head = NULL;
  _length = 0;
  // On copie la liste.
  Line *tmp = otherprogram._head;
  while (tmp != NULL) {
    add_line(tmp);
    tmp = tmp->get_next();
  }
}

// constructeur qui vas permettre de parser un fichier
Program::Program (string const file) {
  _head = NULL;
  _length = 0;
  programparse(file);
  
  Line *tmp = prog._head;
  while (tmp != NULL) {
    add_line(tmp);
    tmp = tmp->get_next();
  }
}

Program::~Program() {
  _head = NULL;
  _length = 0;
}



void Program::add_line(Line * newline) {
  if (!_head) {
    _head = newline;
    _end = newline;
  }
  else {
    newline->set_prev(_end);
    if (_end != NULL)  
      _end->set_next(newline);
    _end = newline;
  }
  _length++;
}


void Program::del_line(int index) {
  Line *to_delete = NULL;
  Line *prec;
	
  if (index >= 0 && index < _length) {
    if (index == 0) {
      if (_length > 0) {
	// On efface le maillon.
	to_delete = _head;
	_head = _head->get_next();	
	_head->set_prev(NULL);
      }
    }
    else {	// On se place sur le prÃ©cÃ©dent.
      prec = _head;
      for (int i = 0; i < index-1; ++i) {
	prec = prec->get_next();
      }

      // On retire le maillon.
      to_delete = prec->get_next();
	 
      prec->set_next(to_delete->get_next());
      to_delete->get_next()->set_prev(prec);   
    }
    delete to_delete;
    --_length;
  }
}

int Program::add_line_at(Line *newline, int position) {
  if (position <= 0) {
    newline->set_next(_head); // newline pointe sur le premier.
    _head->set_prev(newline);
    _head = newline;         // newline est maintenant premier.
    ++_length;
    return 1;
  }

  else if (position >= _length)
    add_line(newline);

  else {
      
    Line *prec = _head;
     
    // On se place sur le precedent.
    for (int i = 0; i < position - 1; ++i){
      prec = prec->get_next();
    }

    // On ajuste les pointeurs.
    newline->set_next(prec->get_next());
    prec->set_next(newline);
    ++_length;
    return 1;
  }
  return 1;
}


void Program::display() {
  Line *element = _head;
  while (element != NULL) {
    cout << element->get_content() << endl;
		
    if (element->get_next() == NULL)	
      break;
    else 
      element = element->get_next();
  }
  if (is_empty())	
    cout << "The program is empty" << endl;
  cout << endl;
}

void Program::flush() {

  while (!is_empty()) {
    del_line(0);		
  }
}


void Program::exchange_line(int line1, int line2) {
  Line *lg1, *lg2;
	
  lg1 = find_line(line1);
  lg2 = find_line(line2);

  del_line(line1);
  add_line_at(lg2,line1);
  del_line(line2);
  add_line_at(lg1,line2);
}

Line* Program::find_line(int index) {
  int j;
  Line *e = _head;
  for (j = 0; j < _length; j++) {
    if (j == index) {
      return e;
    }
    e = e->get_next();
  }
  return NULL;
}


int Program::size() {
  return _length;
}

bool Program::is_empty() {
  if (!_head)	
    return true;
  return false;
}

void Program::in_file(string const filename) {
  Line *element = _head;
  ofstream monflux(filename.c_str());
  
  if (monflux) {
    while (element != NULL) {
      if(element->type_line() == line_Instru || 
	 element->type_line() == line_Direct) 
	monflux << "\t";
      monflux << element-> get_content();
	
      if (element->get_next() == NULL)	
	break;
      else {
	if(element->get_content().compare("nop")) 
	  monflux << endl;
	element = element->get_next();
      }			
    } 
  }
  else {
    cout << "Error cannot open the file" << endl;
  }
  
  monflux.close();
}

/* Delimite les fonctions du programme et crée la liste des fonctions 
   Il faut parcourir les lignes composant le programme et chercher les 
   directives de début et de fin d'une fonction (voir TD). Celles-ci 
   delimitent les lignes du programme correspondant à une fonction : 
   il faut alors créer un objet de type Function* et l'ajouter à la 
   liste des fonctions du programme.

   NB1 : on peut comparer un string s à une chaine de caractère avec la 
   methode compare :  s.compare(0, 4, "test") rend 0 si le string s 
   contient la chaine test en préfixe (pour les 4 premiers caractères)

   NB2 : Etant donnée un pointeur sur ligne l = l-> isDirective() rend 
   true si l est une direction et getDirective(l) rend la Directive * associée.
   La methode get_content de la classe Line (ou Instruction ou Directive) rend 
   le contenu de la ligne (ou directive ou instruction) sous forme de string.
*/
void Program::comput_function() {
  Function *func;
  Line *element_debut = NULL;
  Line *current = _head;
   
  Directive *d = NULL;
  string direct;

  while (current != NULL) {   
    if (current->isDirective()) {
      d = getDirective(current);
      direct = d->get_content();
      if (direct.size() != 0) {
	if (direct.compare(0, 4, ".ent") == 0) {
	  element_debut=current;
	}
	if (direct.compare(0, 4, ".end") == 0) {
	  func = new Function();
	  func->set_head(element_debut);
	  func->set_end(current);
	  element_debut = NULL;
	  //func -> display();
	  _myfunc.push_back(func);
	}
      }
    }

    if (current->get_next() == NULL)	
      break;
    else 
      current = current->get_next();
  }
  if (is_empty())	
    cout << "The program is empty" << endl;
}

int Program::nbr_func() {
  return _myfunc.size();
}

Function *Program::get_function(int index) {
  list<Function*>::iterator it;
  it = _myfunc.begin();
  int size = (int) _myfunc.size();
  
  if (index < size) {
    for (int i = 0; i < index; i++) 
      it++;
    return *it;	
  }
  return NULL;	
}

list<Function*>::iterator Program::function_list_begin() {
  return _myfunc.begin();
}

list<Function*>::iterator Program::function_list_end() {
  return _myfunc.end();
}


/* Pour chaque fonction du programme, donc de la liste _myfunc, il faut créer 
   un CFG et l'ajouter à la liste _myCFG. La création d'un CFG se fait avec un 
   appel au constructeur, par exemple : Cfg * cfg = new Cfg(bb0, n); crée un 
   CFG dont le BB d'entrée est bb0 et contenant n BBs.
   Vous pouvez vous inspirer de la fonction ci-dessus pour itérer sur la liste 
   des fonctions _myfunc.
   N'oubliez pas de calculer les blocs de base des fonctions et les succ/pred
   des BB sinon le CFG n'aura qu'un bloc, le premier (meme si on dit qu'il en
   a n en paramètre)
*/
void  Program::comput_CFG() {
  list<Function*>::iterator it;
  Function *current;
  it = _myfunc.begin();
  int size = (int) _myfunc.size();
  for (int i = 0; i < size; i++) {
    current = *it; //ième fonction du programme
    
    _myCFG.push_back(new Cfg(current->get_firstBB(), current->nbr_BB()));
    
    it++; // on passe à la fonction suivante
  }
  return;
}




Cfg*  Program::get_CFG(int index) {
  list<Cfg*>::iterator it;
  it = _myCFG.begin();
  if (index < (int) _myCFG.size()) {
    for (int i = 0; i < index; i++) 
      it++;
    return *it;	
  }
  return _myCFG.back();	
}
