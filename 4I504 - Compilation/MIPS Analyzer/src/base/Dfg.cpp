#include <Dfg.h>


Arc_t* new_arc(int del, t_Dep d, Node_dfg *n){
   Arc_t *arc = new Arc_t;
   arc->delai=del;
   arc->dep=d;
   arc->next=n;
   
   return arc;
}

int get_delay(t_Dep dep, Instruction *from, Instruction *to){
   switch(dep){
   case WAW:
      return WAW_DELAY;
   case WAR:
      return WAR_DELAY;
   case MEMDEP:
      return MEMDEP_DELAY;
   case CONTROL:
      return 0;
   case NONE:
      return 0;
   case RAW:
      int ret=t_delay[from->get_type()][to->get_type()];
      if(ret<1)
	 return 1;
      return ret;
   }
   
   return 0;
}

Dfg::Dfg(Basic_block *bb){
   _bb=bb;
   Instruction *itmp;
   int icurr=0, inxt, nb_inst, del, need_new_arc;
   list<Arc_t*>::iterator ita;
   _index_branch=-1;

   nb_inst=bb->get_nb_inst();
   bb->comput_pred_succ_dep();

   Node_dfg **nodeTab= new Node_dfg*[nb_inst];
   
   for(int i=0; i<nb_inst; i++)
      nodeTab[i]=NULL;
   
   Arc_t *arc;
  
   itmp=bb->get_first_instruction();
   _nb_arc=0;

   while(itmp!=NULL){
     // creation d'un noeud si non existant déjà
      if(nodeTab[icurr]==NULL){
	 nodeTab[icurr]=new Node_dfg(itmp);
      }
     
      //ajoute noeud à la liste des noeuds
      list_node_dfg.push_back(nodeTab[icurr]);
      
     
      //si pas de prédécesseur, ajout à la racine
      if(itmp->get_nb_pred()==0){
	 _roots.push_back(nodeTab[icurr]);
      }

      list<dep*>::iterator itd;
      need_new_arc=1;

      //parcours des instructions qui dependent de l'instruction courante
      for(itd=itmp->succ_begin(); itd!=itmp->succ_end(); itd++){
	inxt=(*itd)->inst->get_index();
	 del=get_delay((*itd)->type, itmp, (*itd)->inst);
#ifdef DEBUG2
	 cout << "inst " << itmp->to_string() << "->" << (*itd)->type<< "->" << (*itd)->inst->to_string();
	 cout << "delai " << del << endl;
#endif
	 need_new_arc=1;   
	 //creation noeud pour l'instruction dependante si non existant 
	 if(nodeTab[inxt]==NULL){
	    nodeTab[inxt]=new Node_dfg((*itd)->inst);
	 }
	 else{
	   // à commenter si on  veut  toutes les dépendances entre 2 instructions
	   //par défaut on les met toutes ce qui ne change pas les calculs ensuite.
	   

	   //on cherche s'il existe déjà un arc entre les 2 instructions
	   // si oui on regarde s'il faut mettre à jour le type de l'arc
	   // en considérant le délai comme critère de mise à jour 
	   // RAW prend le pas sur WAR et WAW et MEM 
	   // penser à mettre le délai le plus long
	   
	   /*for (ita= nodeTab[icurr]->arcs_begin(); ita!=nodeTab[icurr]->arcs_end(); ita++){
	      if( (*ita)->next->get_instruction()==(*itd)->inst){
		if(del>(*ita)->delai){
		  (*ita)->delai=del;
		  (*ita)->dep=(*itd)->type;
		  }
		  if((*itd)->type==RAW){// RAW == vrai dépendance, elle prend le pas
		  (*ita)->delai=del; // sur toute autre dépendance
		  (*ita)->dep=RAW;
		  } 
		  need_new_arc=0;
		  break;
		  }
		  }*/
	   ;
	 }
	 
	 if(need_new_arc){
	    arc = new_arc(del, (*itd)->type, nodeTab[inxt]);
	    nodeTab[icurr]->add_successeur(arc);
	    nodeTab[inxt]->add_predecesseur(nodeTab[icurr]);
	    _nb_arc++;
	 }
	 
      }
      if(itmp->is_branch()){
	 _index_branch=itmp->get_index();
	 itmp=itmp->get_next();//on saute par dessus le delayed slot
	 icurr++;
         //dans notre cas le seul delayed slot potentiel 
	 //est la dernière instr si l'avant dernière est un saut

	 nodeTab[icurr]=new Node_dfg(itmp);
	 _delayed_slot.push_back(nodeTab[icurr]);
	 
      }

      itmp=itmp->get_next();
      icurr++;
   }
   
   _length=nb_inst;
   _read= new int[nb_inst];
   free(nodeTab);
}

Dfg::~Dfg(){}


void Dfg::display(Node_dfg * node, bool first){
   
   
   list<Node_dfg*>::iterator it;
   it=_roots.begin();

   if(first)	
      for(int i=0; i<_length; i++)	
	 _read[i]=0;  	
   
   for (unsigned int j=0; j<_roots.size();j++ ){ 
      if(first) node = *it;	
			

      if(!_read[node->get_instruction()->get_index()]){
	 _read[node->get_instruction()->get_index()]=1;
	 cout<<"pour i"<<node->get_instruction()->get_index()<<endl;
	 cout<<"l'instruction "<<node->get_instruction()->get_content()<<endl;
			
	 //On affiche ses successeurs s'il en a
	 for(int i=0;i<node->get_nb_arcs();i++){
	    if (node->get_arc(i)){
	       cout<< " -> succ i"
		   << node->get_arc(i)->next->get_instruction()->get_index()
		   << " : "
		   << node->get_arc(i)->next->get_instruction()->get_content()
		   << endl;
	    }
	 }
	 for(int i=0;i<node->get_nb_arcs();i++){
	    if (node->get_arc(i))
	       display(node->get_arc(i)->next, false);
	 }
      }
      it++;

   }
}

#define DEP(x) ((x==NONE)?"":((x==RAW)?"RAW_":\
				   ((x==WAR)?"WAR":\
				    ((x==WAW)?"WAW": \
				     ((x==MEMDEP)?"MEM": "control")))))


//Pour générer le fichier .dot: dot -Tps graph.dot -o graph.ps
void Dfg::restitute(Node_dfg * node, string const filename, bool first){
   if(first)
      remove(filename.c_str());
   ofstream monflux(filename.c_str(), ios::app);
   list<Node_dfg*>::iterator it;
 
   if(first && _length){
     
      for(int i=0; i<_length; i++)
	 _read[i]=0;
      
      it = _delayed_slot.begin();
      
      int index_min = _length;
      
      for(unsigned int i=0; i < _delayed_slot.size(); i++){
	 _read[(*it)->get_instruction()->get_index()] = 1;
	 if (index_min > (*it)->get_instruction()->get_index())
	    index_min = (*it)->get_instruction()->get_index();
	 it++;
      }

      monflux << "digraph G1 {" << endl;
      monflux << "node [shape = ellipse];\n" ; 
     
      //for(int i=0; i<index_min; i++){
      // monflux << "i" << i <<  " [label = \"" << BB->get_content() << "\"] ;" << endl; ";"<<endl;
	 
      //}
   }	
   it=_roots.begin();
   for (unsigned int j=0; j<_roots.size();j++ ){ 		

      if(first) node = *it;
		
      if(monflux){			
	 //monflux.open(filename.c_str(), ios::app);
	 if(!_read[node->get_instruction()->get_index()]){
	    _read[node->get_instruction()->get_index()]=1;
	
	    monflux << "i" << node->get_instruction()->get_index() <<  " [label = \"" << node->get_instruction()->get_content() << "\"] ;" << endl; 
	    //On affiche ses successeurs s'il en a
	    for(int i=0; i<node->get_nb_arcs(); i++){
	       if (node->get_arc(i)){
	   
		  monflux<<"i"<<node->get_instruction()->get_index();
		  monflux<<" ->  i" << node->get_arc(i)->next->get_instruction()->get_index();

		  // monflux<<"i"<<node->get_instruction()->get_index()<<"_"<<node->get_weight();
		  // monflux<<" ->  i" << node->get_arc(i)->next->get_instruction()->get_index();
		  // monflux<<"_"<<node->get_arc(i)->next->get_weight();
		  if (node->get_arc(i)->dep == RAW)
		    monflux<<" [label= \""<< DEP(node->get_arc(i)->dep) << node->get_arc(i)->delai<<"\"];"<<endl;
		  else
		    monflux<<" [label= \""<< DEP(node->get_arc(i)->dep) <<"\"];"<<endl;
	       }
	    }
	    monflux.close();
	
	    for(int i=0;i<node->get_nb_arcs();i++){
	       if (node->get_arc(i))
		  restitute(node->get_arc(i)->next,filename.c_str(),false);	
	    }
	 }
      }
      if((j+1) < _roots.size())	monflux.open(filename.c_str(), ios::app);
      it++;
   }

   if (first && _length){
      monflux.open(filename.c_str(), ios::app);
      monflux<<"}"<<endl;
      monflux.close();
   }
   return;
 
}

bool Dfg::read_test(){
  for(int i=0; i<_length; i++)	if(_read[i]==0)	return true;
  return false;
}

/* rend vrai si le noeud n est déjà dans l, faux sinon */

bool contains(list<Node_dfg*>* l, Node_dfg* n){
   list<Node_dfg*>::iterator it;
   
   for(it=l->begin(); it!= l->end(); it++){
      if( (*it)==n ){
	 return true;
      }
   }
   return false;
}


void Dfg::comput_critical_path(){
   list<Node_dfg*>::iterator it;
   list<Node_dfg*>::iterator itp;
   list<Node_dfg*> leafs, grp1, grp2, *next_grp, *current_grp, *swap;
   Instruction *inst;

   // chercher les feuilles du DAG
   for(it=list_node_dfg.begin(); it!=list_node_dfg.end(); it++){
      if((*it)->get_nb_arcs()==0){ //0 successeurs
	 leafs.push_back(*it);
      }
   }   
   next_grp=&grp1;
   //traitement des feuilles en premier
   for(it=leafs.begin(); it!=leafs.end(); it++){
     inst=(*it)->get_instruction();
      
     if(inst->is_branch())
       (*it)->set_weight(2);//poids du branch + du delayed slot
     else
       (*it)->set_weight(inst->get_latency());
     
     // on ajoute tout les successeurs des feuilles dans le prochain groupe à traiter
     for(itp=(*it)->pred_begin(); itp!=(*it)->pred_end(); itp++){
       if(!contains(next_grp, *itp) ){
	 next_grp->push_back(*itp);
       }
     }
   }
   
   current_grp=next_grp;
   next_grp=&grp2;
   while(current_grp->size()>0){
      
      for(it=current_grp->begin(); it!=current_grp->end(); it++){
	int w = (*it)->compute_weight();
	 if( w==0 ){
	    // on a pas pu valuer le noeuds ce tour ci, il faudra recommencer au prochain tour
	       next_grp->push_back(*it);
	 }
	 else{
	   //le noeud a été valué, au prochain tour on étudie tout ses prédecesseurs
	   if (w == 1)
	    for(itp=(*it)->pred_begin(); itp!=(*it)->pred_end(); itp++){
	      next_grp->push_back(*itp);
	    }
	 }
      }
      current_grp->clear();
      swap=current_grp;
      current_grp=next_grp;
      next_grp=swap;
   }
  
#ifdef DEBUG2
   it=list_node_dfg.begin();
   for(unsigned int k = 0; k < list_node_dfg.size(); k++, it++){
      Node_dfg* node = *it;
      cout << "node inst " << node -> get_instruction() -> get_index();
      cout << " poids=" << node->get_weight() << " nb succ=" << node->get_nb_arcs() << endl;
   }
#endif
}

/* rend la valeur du chemin critique */
int Dfg::get_critical_path(){
   list <Node_dfg*>::iterator it= _roots.begin();
   list <Node_dfg*>::iterator it2;
   int max=0;
   
   if((*it)->get_weight()==0){
      comput_critical_path();
   }
#ifdef DEGUB2

   cout << "Poids chemin critique calculé, dans get_critical_path " << endl;
   for(it2=list_node_dfg.begin(); it2!=list_node_dfg.end(); it2++){
     cout << "i" << (*it2)->get_instruction()->get_index() << " poids" << (*it2)->get_weight() << endl;
   }
#endif    
   for(; it!=_roots.end(); it++){
      if((*it)->get_weight()>max){
	 max=(*it)->get_weight();
      }
   }
   return max;
}


Node_dfg* heaviest_in_critical_path(list<Node_dfg*>* ready){
   list <Node_dfg*>::iterator it;
   int max=0, w, more_than_one_max=0;
   Node_dfg* heaviest=NULL;
   
   for(it=ready->begin(); it!=ready->end(); it++){
      w=(*it)->get_weight();
      if(w==max){
	 more_than_one_max++;
      }
      else if(w>max){
	 max=w;
	 heaviest=*it;
	 more_than_one_max=0;
      }
   }
   if(!more_than_one_max)
      return heaviest;
   else
      return NULL;
}

void heaviest_nodes_critical_path(list<Node_dfg*>* ready, list<Node_dfg*>* res){
   list <Node_dfg*>::iterator it;
   
   int max=0, w, more_than_one_max=0;
   Node_dfg* heaviest=NULL;
   
   for(it=ready->begin(); it!=ready->end(); it++){
      w=(*it)->get_weight();
      if(w==max){
	 more_than_one_max++;
      }
      else if(w>max){
	 max=w;
	 heaviest=*it;
	 more_than_one_max=0;
      }
   }
   if(!more_than_one_max){
     res->push_back(heaviest);
   }
   else
     for(it=ready->begin(); it!=ready->end(); it++){
       w=(*it)->get_weight();
       if(w == max){
	 res->push_back(*it);
       }
     }  
 
      return;
}

Node_dfg* first_without_freeze(list<Node_dfg*>* ready, int curTime){
   list <Node_dfg*>::iterator it;
   for(it=ready->begin(); it!=ready->end(); it++){
      if((*it)->get_tready()<=curTime)
	 return *it;
   }
   return NULL;
}

 void nodes_without_freeze(list<Node_dfg*>* ready, int curTime, list<Node_dfg*>* res){
   list <Node_dfg*>::iterator it;
   for(it=ready->begin(); it!=ready->end(); it++){
      if((*it)->get_tready()<=curTime)
	res->push_back(*it);
   }
   return;
}


 void  nodes_limiting_freeze(list<Node_dfg*>* ready, int curTime, list<Node_dfg*>* res) {

 list <Node_dfg*>::iterator it;
 int min_ready = 0;

   for(it=ready->begin(); it!=ready->end(); it++){
     if (min_ready ==0) min_ready = (*it)->get_tready();
     if ((*it)->get_tready() < min_ready)
       min_ready = (*it)->get_tready();
     
   }

   for(it=ready->begin(); it!=ready->end(); it++){
     if((*it)->get_tready()==min_ready)
       res->push_back(*it);
   }
 
   return;
 }


Node_dfg* highest_latency(list<Node_dfg*>* ready){
   list <Node_dfg*>::iterator it;
   Node_dfg* n=NULL;
   int max=0, lat, more_than_one_max=0;

   for(it=ready->begin(); it!=ready->end(); it++){
      lat=(*it)->get_instruction()->get_latency();
      if(lat==max){
	 more_than_one_max++;
      }
      else if(lat>max){
	 max=lat;
	 n=*it;
	 more_than_one_max=0;
      }
   }
   
   if(!more_than_one_max)
      return n;
   else
      return NULL;
}

 void  highest_latency_nodes(list<Node_dfg*>* ready, list<Node_dfg*>* res){
   list <Node_dfg*>::iterator it;
   Node_dfg* n=NULL;
   int max=0, lat, more_than_one_max=0;

   for(it=ready->begin(); it!=ready->end(); it++){
      lat=(*it)->get_instruction()->get_latency();
      if(lat==max){
	 more_than_one_max++;
      }
      else if(lat>max){
	 max=lat;
	 n=*it;
	 more_than_one_max=0;
      }
   }
   
   if(!more_than_one_max)
     res->push_back(n);
   else
     for(it=ready->begin(); it!=ready->end(); it++){
       lat=(*it)->get_instruction()->get_latency();
       if(lat==max){
	 res->push_back(*it);
       }
     }
   return;
}



Node_dfg* more_succ(list<Node_dfg*>* ready){
   list <Node_dfg*>::iterator it;
   Node_dfg* n=NULL;
   int max=0, succ, more_than_one_max=0;

   for(it=ready->begin(); it!=ready->end(); it++){
      succ=(*it)->get_nb_arcs();
      if(succ==max){
	 more_than_one_max++;
      }
      else if(succ>max){
	 max=succ;
	 n=*it;
	 more_than_one_max=0;
      }
   }
   
   if(!more_than_one_max)
      return n;
   else
      return NULL;
}


 void more_succ_nodes(list<Node_dfg*>* ready,list<Node_dfg*>* res){
   list <Node_dfg*>::iterator it;
   Node_dfg* n=NULL;
   int max=0, succ, more_than_one_max=0;

   for(it=ready->begin(); it!=ready->end(); it++){
      succ=(*it)->get_nb_arcs();
      if(succ==max){
	 more_than_one_max++;
      }
      else if(succ>max){
	 max=succ;
	 n=*it;
	 more_than_one_max=0;
      }
   }
   
   if(!more_than_one_max)
     res->push_back(n);
   else
     for(it=ready->begin(); it!=ready->end(); it++){
       succ=(*it)->get_nb_arcs();
       if(succ==max){
	 res->push_back(*it);
       }
     }
     
   return;
 }


Node_dfg* more_descendants(list<Node_dfg*>* ready){
   list <Node_dfg*>::iterator it;
   Node_dfg* n=NULL;
   int max=0, desc, more_than_one_max=0;

   for(it=ready->begin(); it!=ready->end(); it++){
      desc=(*it)->get_nb_descendant();
      if(desc==max){
	 more_than_one_max++;
      }
      else if(desc>max){
	 max=desc;
	 n=*it;
	 more_than_one_max=0;
      }
   }
   
   if(!more_than_one_max)
      return n;
   else
      return NULL;
}

 void  more_descendants_nodes(list<Node_dfg*>* ready,list<Node_dfg*>* res){
   list <Node_dfg*>::iterator it;
   Node_dfg* n=NULL;
   int max=0, desc, more_than_one_max=0;

   for(it=ready->begin(); it!=ready->end(); it++){
      desc=(*it)->get_nb_descendant();
      if(desc==max){
	 more_than_one_max++;
      }
      else if(desc>max){
	 max=desc;
	 n=*it;
	 more_than_one_max=0;
      }
   }
   
   if(!more_than_one_max)
     res->push_back(n);
   else
     for(it=ready->begin(); it!=ready->end(); it++){
       desc=(*it)->get_nb_descendant();
       if(desc==max){
	 res->push_back(*it);
       }}

      return;
}

Node_dfg* lowest_index(list<Node_dfg*>* ready){
   list <Node_dfg*>::iterator it=ready->begin();
   Node_dfg* n=*it;
   int min=n->get_instruction()->get_index(), tmp;

   for(; it!=ready->end(); it++){
      tmp=(*it)->get_instruction()->get_index();
      if(min>tmp){
	 min=tmp;
	 n=*it;
      }
   }
   
   return n;
}



bool is_ready(Node_dfg* node, list<Node_dfg*>* scheduled){
   list<Node_dfg*>::iterator it;
   for(it=node->pred_begin(); it!=node->pred_end(); it++){
      if(!contains(scheduled, *it))
	 return false;
   }
   return true;
}

void print_linstr(list<Node_dfg*>* l){
   list<Node_dfg*>::iterator it;
   for(it=l->begin(); it!=l->end(); it++){
     cout<<"i"<<(*it)->get_instruction()->get_index()<<"  : " <<  (*it)->get_instruction()->to_string() << " ;" ;
   }
   cout << endl;
   return;
}

void Dfg::compute_nb_descendant(){
   list<Node_dfg*>::iterator it;
   
   int nb_instr=_bb->get_nb_inst(), nb;
   for(it=list_node_dfg.begin(); it!=list_node_dfg.end(); it++){
      nb=(*it)->compute_nb_descendant(nb_instr, NULL);
      (*it)->set_nb_descendant(nb);
   }
}


void  Dfg::scheduling(bool verbose){
   list <Node_dfg*>::iterator it;
   list <Arc_t*>::iterator ita;

   comput_critical_path();
   compute_nb_descendant();
   int curTime=1;
   Node_dfg *scheduled, *succ;
   list <Node_dfg*> res, res2;
   
   _inst_ready.clear();
   
   for(it=_roots.begin(); it!=_roots.end(); it++){
      _inst_ready.push_back(*it);
      (*it)->set_tready(1);
   }
   
   if(verbose)
      cout<<"Scheduling"<<endl;
  
   while(_inst_ready.size()>0 && _inst_ready.size() < 100 ){
     res.clear();
     res2.clear();
    
     if(verbose){
	cout<<curTime<<" : "<<endl;
	cout<<"ready : ";
	 print_linstr(&_inst_ready);
	 cout<<endl;
      }

      if(_inst_ready.size()==1){
	 if(verbose)
	    cout<<"only one : ";
	 scheduled=_inst_ready.front();
      }
      else {
	nodes_without_freeze(&_inst_ready, curTime, &res);
	if (res.size()==0)  { // tous provoquant des cycles de gel
	  // trouver les noeuds avec le min de gel 
         nodes_limiting_freeze(&_inst_ready, curTime, &res);
	}
	
	if (res.size()==1){
	  scheduled = res.front();
	  if(verbose)
	    cout<<"first without freeze :";
	}

	if (res.size()> 1){
	  res2.clear();
	  heaviest_nodes_critical_path(&res,&res2); // on garde ceux avec le plus fort poids
	  if (res2.size() == 0) cout << " aucun plus fort sur heaviest " << endl;
	  if (res2.size() == 1){
	    scheduled= res2.front();
	    if(verbose)
	      cout<<"heaviest :";
	  }
	  else {
	    res.clear();
	    highest_latency_nodes(&res2, &res);  // on garde ceux avec la plus grande latence
	  if (res.size() == 0) cout << " aucun plus fort avec latence " << endl;

	    if(res.size() == 1){
	      scheduled = res.front();
	      if(verbose)
		cout<<"highest latency :";
	    }
	    else {
	      res2.clear();
	      more_succ_nodes(&res, &res2); // on garde ceux avec le plus de successeurs
	  if (res2.size() == 0) cout << " aucun plus fort avec latence " << endl;


	      if(res2.size() == 1){
		scheduled = res2.front();
		if(verbose)
		  cout<<"more succ :";
	      }
	      else {
		res.clear();
		more_descendants_nodes(&res2, &res); // on garde ceux avec le plus de descendants
		if (res.size() == 1){
		  scheduled = res.front();
		  if(verbose)
		    cout<<"more descendants :";
		}
		else{
		  scheduled=lowest_index(&res);
		  if(verbose)
		    cout<<"lowest_index :";
		} // plus d'un avec le max de descendants
	      }// plus d'un avec le plus de successeurs
	    } // plus d'un avec la latence max
	  } // plus d'un avec poids max sur chemin critique
	} // plus d'un qui ne freeze pas
      } // plus d'un qui est prêt
      

      _inst_ready.remove(scheduled);
   
     
     
      if(verbose)
	 cout<<"i"<<scheduled->get_instruction()->get_index()<<endl;
      new_order.push_back(scheduled);
      
      for (ita=scheduled->arcs_begin(); 
	   ita!=scheduled->arcs_end();
	   ita++){
	 succ=(*ita)->next;
	 if(is_ready(succ, &new_order)){
	   
	    succ->set_tready(curTime+(*ita)->delai);
	    _inst_ready.push_back(succ);
	 }
      }
      
      curTime++;
   }
   //donc dans notre cas, le nop post jump
   if(_delayed_slot.size()!=0){
      new_order.push_back(_delayed_slot.front());
   }
   display_sheduled_instr();
   return;
}

void Dfg::apply_scheduling(){
   _bb->apply_scheduling(&new_order);
}


void Dfg::display_sheduled_instr(){
   list <Node_dfg*>::iterator it;
   Instruction *inst;
   for(it=new_order.begin(); it!=new_order.end(); it++){
      inst=(*it)->get_instruction();
      cout<<"i"<<inst->get_index()<<": "<<inst->get_content()<<endl;
   }
}
