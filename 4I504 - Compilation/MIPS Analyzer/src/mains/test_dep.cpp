#include <iostream>
#include <Program.h>
#include <Basic_block.h>
#include <Function.h>


int main(int argc, char * argv[]){

	if (argc < 2) {
	  cout << "erreur : pas de fichier assembleur" << endl;
	}	  
	Program prog(argv[1]);
	Function* functmp;
	list <Function*> myfunc; 
	list <Basic_block*> myBB;

	cout<<"Le programme a "<<prog.size()<<" lignes\n"<<endl;

	prog.comput_function();
	cout<<"nombre de fonctions : "<<prog.nbr_func()<<endl;

	list<Function*>::iterator itfct;
	list<Basic_block*>::iterator itbb;
	Basic_block *bb;
	int i, j;
	list<int> frees;
	Dfg *d;
	Cfg *c;
	
	std::ostringstream *oss ;
	for(itfct=prog.function_list_begin(), i=0;
	    itfct!=prog.function_list_end(); itfct++, i++){
	   functmp=*itfct;
	    cout<<"------------Function DISPLAY----------\n" <<endl;
	    functmp->display();
	   functmp->comput_basic_block();
	   functmp->comput_label();
	   functmp->comput_succ_pred_BB();
	   
	   oss=new std::ostringstream;
	   
	   (*oss)<<"./tmp/func_"<<i<<".dot";
	   c=new Cfg(functmp->get_BB(0), functmp->nbr_BB());
	   c->restitution(NULL, oss->str());
	   
	   cout<<"========== Function "<<i<<"==========="<<endl;
	   cout<<"============================"<<endl;
	   
	   functmp ->compute_live_var();
	   j=0;
	   for(itbb=functmp->bb_list_begin(); 
	       itbb!=functmp->bb_list_end(); itbb++, j++){
	      bb=*itbb;
	      cout<<"----------BB "<<j<<"-----------"<<endl;
	      bb->display();
	      bb->link_instructions();
	      bb->comput_pred_succ_dep();

	      cout<<"---nb_cycles : "<<bb->nb_cycles()<<"-----------"<<endl;
	      d = new Dfg(bb);
	      cout<<"comput critical path"<<endl;
	      string str;
	      stringstream sstm;
	      sstm << "./tmp/dfg_bb" << bb->get_index() <<".dot";
	      str = sstm.str();
	      d->restitute(NULL, str, true);
	      d->comput_critical_path();
	      cout<<"critical path "<<d->get_critical_path()<<endl;
	      d->scheduling(false);
	      //cout<<"----  new scheduling: -----"<<endl;
	      //d->display_sheduled_instr();
	      //d->apply_scheduling();
	      cout<<"---- BB with new scheduling: -----"<<endl;
	      bb->display();
	      cout<<"---nb_cycles : "<<bb->nb_cycles()<<"-----------"<<endl;
	      // liste de registres pour le renommage
	      // avec des registres passéees en paramètre 
	      /*
	      frees.clear();
	      for(int k=32; k<64; k++){
	      	 frees.push_back(k);
	      }
	      */
	      /* renommage en utilisant des registres n'existant pas */
	      
	      //  bb->reg_rename(&frees);

	      /* renommage utilisant les registres disponibles dans le bloc */
	      /*  ne pas faire les 2 */
	      /* il faut recalculer les informations de vivacité et de def-use 
	         pour pouvoir le faire 2 fois de suite !!
	      */
	      bb->reg_rename();
	      cout<<"----- apres renommage ------"<<endl;
	      bb->display();
	      // il faut annuler le calcul des dépendances et le refaire
	      bb->reset_pred_succ_dep();
	      bb->comput_pred_succ_dep();
	      cout<<"---nb_cycles--"<<bb->nb_cycles()<<"-----------"<<endl;

	      d= new Dfg(bb);
	      cout<<"comput critical path"<<endl;
	      //d->restitute(NULL, "./tmp/graph_dfg1.dot", true);
	      d->comput_critical_path();
	      cout<<"critical path "<<d->get_critical_path()<<endl;
	      stringstream sstm2;
	      sstm2 << "./tmp/dfg_bb" << bb->get_index() <<"_renamed.dot";
	      string str2 = sstm2.str();
	      cout << str2 << endl;
	      d->restitute(NULL, str2, true);
	      d->scheduling(false);
	      //cout<<"----  new scheduling: -----"<<endl;
	      //d->display_sheduled_instr();
	      d->apply_scheduling();
	      cout<<"---- BB with new scheduling: -----"<<endl;
	      bb->display();
	     
	      cout<<"----nb_cycles--"<<bb->nb_cycles()<<"-----------"<<endl;
	      //return 0;
	   }
	}
	    
	
	

	
}
