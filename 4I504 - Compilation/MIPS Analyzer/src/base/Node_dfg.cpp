#include <Node_dfg.h>

Node_dfg::Node_dfg(Instruction* i1 ){
   _inst = i1;
   _nbr_descendant=0;
   _poids = 0;
}

Node_dfg::~Node_dfg(){
}


void Node_dfg::remove_arc(int index){
  list<Arc_t*>::iterator it;
  it=_arc.begin();
   
  if(index< (int)_arc.size()){
      for (int i=0; i<index; i++ ) 
	it++;
      it = _arc.erase(it);	
   }
  return;
}


void Node_dfg::remove_pred(int index){
  list<Node_dfg*>::iterator it;
  it=_pred.begin();
   
  if(index< (int)_pred.size()){
      for (int i=0; i<index; i++ ) 
	it++;
      it = _pred.erase(it);	
   }
  return;
}

Arc_t *Node_dfg::get_arc(int index){

   list<Arc_t*>::iterator it;
   it=_arc.begin();
   
   if(index< (int)_arc.size()){
      for (int i=0; i<index; i++ ) it++;
      return *it;	
   }
   else
     return NULL;

}

//arcs = successeurs
list<Arc_t*>::iterator Node_dfg::arcs_begin(){
   return _arc.begin();
}

list<Arc_t*>::iterator Node_dfg::arcs_end(){
   return _arc.end();
}

int Node_dfg::get_nb_arcs(){
   return _arc.size();
}

Instruction *Node_dfg::get_instruction(){
   return _inst;
}

void Node_dfg::add_successeur(Arc_t* u){
   _arc.push_back(u);
}

void Node_dfg::add_predecesseur(Node_dfg*n){
   _pred.push_back(n);
}

int Node_dfg::nb_preds(){
   return (int) _pred.size();
}

list<Node_dfg*>::iterator Node_dfg::pred_begin(){
   return _pred.begin();
}

list<Node_dfg*>::iterator Node_dfg::pred_end(){
   return _pred.end();
}

void Node_dfg::set_instruction( Instruction* i1){
   _inst = i1;
}

int Node_dfg::compute_weight(){
   list<Arc_t*>::iterator it;
   int max=_poids, w_next;

   for(it=_arc.begin(); it!=_arc.end(); it++){
      w_next=(*it)->next->get_weight();
//      cout<<"next i"<<(*it)->next->get_instruction()->get_index()<<" w="<<w_next<<endl;
      
      if(w_next==0) // un des sucesseurs n'est pas encore valué, on ne peut pas valuer le poides de this
	 return 0;
      
      if( (w_next+(*it)->delai) > max ){
	 max=w_next+(*it)->delai;
      }
   }
   if (_poids != max) {
     _poids=max;
     return 1;
   }
   else 
     return -1;
}


int Node_dfg::compute_nb_descendant(int nb_instr, int* deja_comptes){
   if(!deja_comptes){
     deja_comptes = new int[nb_instr];
      for(int i=0; i<nb_instr; i++){
	 deja_comptes[i]=0;
      }
   }
   int index=get_instruction()->get_index();
   
   list<Arc_t*>::iterator it;
   int sum=0;
   for(it=_arc.begin(); it!=_arc.end(); it++){
     if(!deja_comptes[(*it)->next->get_instruction()->get_index()])
       sum+= (*it)->next->compute_nb_descendant(nb_instr, deja_comptes);
   }

   if(!deja_comptes[index]){
      sum++;
      deja_comptes[index]=1;
   }
   
   return sum;
}


void Node_dfg::set_weight( int w ){
   _poids = w;
}

int Node_dfg::get_weight( ){
   return _poids;
}

void Node_dfg::set_nb_descendant(int descent){
   _nbr_descendant=descent;
}

int Node_dfg::get_nb_descendant(){
   return _nbr_descendant;
	
}

void Node_dfg::set_tready(int t){
   _tready=t;
}

int Node_dfg::get_tready(){
   return _tready;
}
