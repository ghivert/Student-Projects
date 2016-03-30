#include <Basic_block.h>

namespace Basic_block {

  // static
  void show_dependances(Instruction *i1, Instruction *i2) {
    if (i1->is_dep_RAW1(i2))
    cout << "Dependance i" << i1->get_index() << "->i" << i2->get_index() << ": RAW1" << endl;
    if (i1->is_dep_RAW2(i2))
    cout << "Dependance i" << i1->get_index() << "->i" << i2->get_index() << ": RAW2" << endl;

    if (i1->is_dep_WAR(i2))
    cout << "Dependance i" << i1->get_index() << "->i" << i2->get_index() << ": WAR" << endl;
    if (i1->is_dep_WAW(i2))
    cout << "Dependance i" << i1->get_index() << "->i" << i2->get_index() << ": WAW" << endl;

    if (i1->is_dep_MEM(i2))
    cout << "Dependance i" << i1->get_index() << "->i" << i2->get_index() << ": MEM"<<endl;
  }

  Basic_block():
  DefLiveOut(vector<int> (NB_REG,    -1)),
  Use       (vector<bool>(NB_REG,    false)),
  LiveIn    (vector<bool>(NB_REG,    false)),
  LiveOut   (vector<bool>(NB_REG,    false)),
  Def       (vector<bool>(NB_REG,    false)),
  Domin     (vector<bool>(NB_MAX_BB, true)) {
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


  ~Basic_block() { }

  void set_index(int i) {
    _index = i;
  }

  int get_index() {
    return _index;
  }

  void set_head(Line *head) {
    _head = head;
  }

  void set_end(Line *end) {
    _end = end;
  }

  Line *get_head() {
    return _head;
  }

  Line *get_end() {
    return _end;
  }

  void set_successor1(Basic_block *BB) {
    _succ.push_front(BB);
  }

  Basic_block *get_successor1() {
    if (_succ.size() > 0)
      return _succ.front();
    else
      return NULL;
  }

  void set_successor2(Basic_block *BB) {
    _succ.push_back(BB);
  }

  Basic_block *get_successor2() {
    if (_succ.size() > 1)
      return _succ.back();
    else
      return NULL;
  }

  void set_predecessor(Basic_block *BB) {
    _pred.push_back(BB);
  }

  Basic_block *get_predecessor(int index) {
    list<Basic_block*>::iterator it;
    it = _pred.begin();
    int size = (int) _pred.size();
    if (index < size) {
      for (int i = 0; i < index; i++, it++)
        ; // Nope.
      return *it;
    }
    else cout<<"Error: index is bigger than the size of the list"<<endl;
    return _pred.back();

  }

  int get_nb_succ() {
    return _succ.size();
  }

  int get_nb_pred(){
    return _pred.size();
  }

  void set_branch(Line* br){
    _branch=br;
  }

  Line* get_branch(){
    return _branch;
  }

  void display(){
    cout<<"Begin BB"<<endl;
    Line* element = _head;
    int i=0;
    if(element == _end)
    cout << _head->get_content() <<endl;

    while(element != _end->get_next()) {
      if(element->isInst()) {
        cout<<"i"<<i<<" ";
        i++;
      }
      if(!element->isDirective())
      cout <<element->get_content() <<endl;

      element = element->get_next();
    }
    cout<<"End BB"<<endl;
  }

  string get_content(){
    string rt = "";
    Line* element = _head;


    while(element != _end->get_next()) {
      if(element->isInst()) {
        rt = rt + element->get_content() + "\\l";
      }
      else if(element->isLabel())
      rt = rt + element->get_content() + "\\l";

      element = element->get_next();
    }

    return rt;
  }

  int size(){
    Line* element = _head;
    int lenght=0;
    while(element != _end) {
      lenght++;
      if(element->get_next()==_end)
      break;
      else
      element = element->get_next();
    }
    return lenght;
  }


  void restitution(string const filename){
    Line* element = _head;
    ofstream monflux(filename.c_str(), ios::app);
    if(monflux) {
      monflux<<"Begin BB"<<endl;
      if(element == _end)
      monflux << _head->get_content() <<endl;
      while(element != _end)
      {
        if(element->isInst())
        monflux<<"\t";
        if(!element->isDirective())
        monflux << element->get_content()<<endl;

        if(element->get_next()==_end) {
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

  bool is_labeled(){
    if (_head->isLabel()) {
      return true;
    }
    else return false;
  }

  int get_nb_inst(){
    if (_nb_instr == 0)
    link_instructions();
    return _nb_instr;

  }

  Instruction* get_instruction_at_index(int index){
    Instruction *inst;

    if(index >= get_nb_inst()) {
      return NULL;
    }

    inst=get_first_instruction();

    for(int i=0; i<index; i++, inst=inst->get_next());

    return inst;
  }

  Line* get_first_line_instruction(){

    Line *current = _head;
    while(!current->isInst()) {
      current=current->get_next();
      if(current==_end)
      return NULL;
    }
    return current;
  }

  Instruction* get_first_instruction(){
    if(_firstInst==NULL) {
      _firstInst= getInst(this->get_first_line_instruction());
      this->link_instructions();
    }
    return _firstInst;
  }

  Instruction* get_last_instruction(){
    if(_lastInst==NULL)
    this->link_instructions();
    return _lastInst;
  }


  /* link_instructions  num�rote les instructions du bloc */
  /* remplit le champ nb d'instructions du bloc (_nb_instr) */
  /* remplit le champ derniere instruction du bloc (_lastInst) */
  void link_instructions(){

    int index=0;
    Line *current, *next;
    current=get_first_line_instruction();
    next=current->get_next();

    Instruction *i1 = getInst(current);

    i1->set_index(index);
    index++;
    Instruction *i2;

    //Calcul des successeurs
    while(current != _end) {

      while(!next->isInst()) {
        next=next->get_next();
        if(next==_end) {
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

  bool is_delayed_slot(Instruction *i){
    if (get_branch()== NULL)
    return false;
    int j = (getInst(get_branch()))->get_index();
    return (j < i->get_index());

  }

  /* set_link_succ_pred : ajoute succ comme successeur de this et ajoute this comme pr�d�cesseur de succ
  */

  void set_link_succ_pred(Basic_block* succ){
    _succ.push_back(succ);
    succ->set_predecessor(this);
  }

  /* add_dep_link ajoute la d�pendance avec pred � la liste des dependances pr�c�desseurs de succ */
  /* ajoute la dependance avec succ � la liste des d�pendances successeurs de pred */

  /* dep est une structure de donn�es contenant une instruction et  un type de d�pendance */

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


  /* calcul des d�pendances entre les instructions dans le bloc  */
  /* une instruction a au plus 1 reg dest et 2 reg sources */
  /* Attention le reg source peut �tre 2 fois le m�me */
  /* Utiliser les m�thodes is_dep_RAW1, is_dep_RAW2, is_dep_WAR, is_dep_WAW, is_dep_MEM pour d�terminer les d�pendances */

  /* ne pas oublier les d�pendances de controle avec le branchement s'il y en a un */

  /* utiliser la fonction add_dep_link ci-dessus qui ajoute � la liste des d�pendances pred et succ une dependance entre 2 instructions */


  void comput_pred_succ_dep(){


    link_instructions();
    if (dep_done) return;
    Instruction *i_current;
    Instruction *itmp;

    /* A REMPLIR */

    // NE PAS ENLEVER : cette fonction ne doit �tre appel�e qu'une seule fois
    dep_done = true;
    return;
  }

  void reset_pred_succ_dep(){

    Instruction *ic=get_first_instruction();
    while (ic) {
      ic->reset_pred_succ_dep();
      ic = ic->get_next();
    }
    dep_done = false;
    return;
  }

  /* calcul le nb de cycles pour executer le BB, on suppose qu'une instruction peut sortir du pipeline � chaque cycle, il faut trouver les cycles de gel induit par les d�pendances */

  int nb_cycles(){

    Instruction *ic=get_first_instruction();

    /* tableau pour savoir pour chaque instruction quand elle sort pour en d�duire les cycles qu'elle peut induire avec les instructions qui en d�pendent */

    vector<int> inst_cycle(get_nb_inst());
    for (int i=0; i< get_nb_inst(); i++ ) {
      inst_cycle[i] = 0;
    }
    comput_pred_succ_dep();



    /* A REMPLIR */



    return 0;
  }

  /*
  calcule DEF et USE pour l'analyse de registre vivant
  � la fin on doit avoir
  USE[i] vaut 1 si $i est utilis� dans le bloc avant d'�tre potentiellement d�fini dans le bloc
  DEF[i] vaut 1 si $i est d�fini dans le bloc
  ******************/

  void compute_use_def(void){
    Instruction * inst = get_first_instruction();
    if (use_def_done) return;

    /* A REMPLIR */

    #ifdef DEBUG
    cout << "****** BB " << get_index() << "************" << endl;
    cout << "USE : ";
    for(int i=0; i<NB_REG; i++) {
      if (Use[i])
      cout << "$"<< i << " ";
    }
    cout << endl;
    cout << "DEF : ";
    for(int i=0; i<NB_REG; i++) {
      if (Def[i])
      cout << "$"<< i << " ";
    }
    cout << endl;
    #endif

    return;
  }

  /**** compute_def_liveout
  � la fin de la fonction on doit avoir
  DefLiveOut[i] vaut l'index de l'instruction du bloc qui d�finit $i si $i vivant en sortie seulement
  Si $i est d�fini plusieurs fois c'est l'instruction avec l'index le plus grand
  *****/
  void compute_def_liveout(){

    Instruction * inst = get_first_instruction();

    /* A REMPLIR */

    #ifdef DEBUG
    cout << "DEF LIVE OUT: ";
    for(int i=0; i<NB_REG; i++) {
      if (DefLiveOut[i] != -1)
      cout << "$"<< i << " definit par i" << DefLiveOut[i] << endl;
    }

    #endif

  }



  /**** renomme les registres renommables : ceux qui sont d�finis et utilis�s dans le bloc et dont la d�finition n'est pas vivante en sortie
  Utilise comme registres disponibles ceux dont le num�ro est dans la liste param�tre
  *****/
  void reg_rename(list<int> *frees){
    Instruction * inst = get_first_instruction();
    int newr;
    compute_def_liveout();


    /* A REMPLIR */

  }


  /**** renomme les registres renommables : ceux qui sont d�finis et utilis�s dans le bloc et dont la d�finition n'est pas vivante en sortie
  Utilise comme registres disponibles ceux dont le num�ro est dans la liste param�tre
  *****/
  void reg_rename(){
    Instruction * inst = get_first_instruction();
    int newr;
    list<int> *frees, lfree;


    /* A REMPLIR */
  }

  void apply_scheduling(list <Node_dfg*> *new_order){
    list <Node_dfg*>::iterator it=new_order->begin();
    Instruction *inst=(*it)->get_instruction();
    Line *n=_head, *prevn=NULL;
    Line *end_next = _end->get_next();
    if(!n) {
      cout<<"wrong bb : cannot apply"<<endl;
      return;
    }

    while(!n->isInst()) {
      prevn=n;
      n=n->get_next();
      if(n==_end) {
        cout<<"wrong bb : cannot apply"<<endl;
        return;
      }
    }

    //y'a des instructions, on sait pas si c'est le bon BB, mais on va supposer que oui
    inst->set_index(0);
    inst->set_prev(NULL);
    _firstInst = inst;
    n = inst;

    if(prevn) {
      prevn->set_next(n);
      n->set_prev(prevn);
    }
    else{
      set_head(n);
    }

    int i;
    it++;
    for(i=1; it!=new_order->end(); it++, i++) {

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

  /* permet de tester des choses sur un bloc de base, par exemple la construction d'un DFG, � venir ... l� ne fait rien qu'afficher le BB */
  void test(){
    cout << "test du BB " << get_index() << endl;
    display();
    cout << "nb de successeur : " << get_nb_succ() << endl;
    int nbsucc = get_nb_succ();
    if (nbsucc >= 1 && get_successor1())
    cout << "succ1 : " << get_successor1()->get_index();
    if (nbsucc >= 2 && get_successor2())
    cout << " succ2 : " << get_successor2()->get_index();
    cout << endl << "nb de predecesseurs : " << get_nb_pred() << endl;

    int size=(int)_pred.size();
    for (int i = 0; i < size; i++) {
      if (get_predecessor(i) != NULL)
      cout << "pred "<< i <<  " : " << get_predecessor(i)->get_index() << "; ";
    }
    cout << endl;
  }
}
