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
	   int total1 = 0, total2 = 0, total3 = 0, total4 = 0;
	   for(itbb=functmp->bb_list_begin(); 
	       itbb!=functmp->bb_list_end(); itbb++, j++){
	      bb=*itbb;
	      bb->link_instructions();
	      bb->comput_pred_succ_dep();

	      total1 += bb->nb_cycles();
	      d = new Dfg(bb);
	      d->scheduling(false);
	      d->apply_scheduling();
	      total2 += bb->nb_cycles();

	      bb->reg_rename();
	      // il faut annuler le calcul des dépendances et le refaire
	      bb->reset_pred_succ_dep();
	      bb->comput_pred_succ_dep();
	      total3 += bb->nb_cycles();

	      d= new Dfg(bb);
	      d->scheduling(false);
	      d->apply_scheduling();

	      total4 += bb->nb_cycles();
	      //return 0;
	   }
	   printf("Nombres de cycles : \n");
	   printf(" BASIC  | SCHEDULED | RENAMED | RE-SCHEDULED\n");
	   printf("   %d   |    %d     |    %d   |     %d      \n", total1, total2, total3, total4);
	}
	    
	
	

	
}
