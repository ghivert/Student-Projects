#include <iostream>
#include <Program.h>
#include <Basic_block.h>
#include <Function.h>


/*
  ##################Programme à appeler avec le nom d'un fichier assembleur en argument###############

  -Affichage du nombre de lignes du programme, de son contenu
  - Découpage en fonctions et affichage du nombre de fonction
  - Découpage en nombre de bloc de base
  -Pour chaque fonction, calcul du decoupage en blocs de base, des successeurs et prédécesseurs des BB, construction et restitution en fichier .dot du CFG
  -Affichage du BB0 de la fonction0

*/

int main(int argc, char * argv[]){

   remove("tmp/test1.txt");
   remove("tmp/test2.txt");
   remove("./tmp/graph.dot");
   if (argc < 2) {
      cout << "erreur : pas de fichier assembleur en entree" << endl;
   }	  
   Program prog(argv[1]);
   Function* functmp;

   list <Basic_block*> myBB;

   cout<<"Le programme a "<<prog.size()<<" lignes\n"<<endl;

   cout<<"Contenu du programme:"<<endl;
   prog.display();
   
   //prog.in_file("tmp/restit.txt");

   cout<<"\n Calcul des fonctions des block de base et restitution\n"<<endl;
   prog.comput_function();
   
   cout<<"nombre de fonction: "<<prog.nbr_func()<<endl;

   Cfg *graph;
   for (int i=0; i<prog.nbr_func(); i++){
      
      functmp= prog.get_function(i);

      if(functmp==NULL){
	 cout<<"null"<<endl;
	 break;
      }
      cout << "FONCTION " << i << endl;
      //functmp -> display();
      //determine les BB de la fonction
      functmp->comput_basic_block();
      

      cout << "Affichage des blocs de base " << endl; 
      for(int j=0; j<functmp->nbr_BB(); j++){
	 functmp->get_BB(j)->display();
      }
     
      // calcul les étiquettes de la fonction
      functmp->comput_label();
      // calcul les liens entre BB 
      functmp->comput_succ_pred_BB();
      functmp->test();
      functmp->compute_dom();
      // crée un nouveau CFG pour la fonction
      // permet de le visualiser avec dotty, cf. plus bas
      graph =new Cfg(functmp->get_BB(0),
			  functmp->nbr_BB());
	
		
      cout<<"------------Function "<< (i+1) <<"/"<<prog.nbr_func()<<" DISPLAY----------\n" <<endl;
      // affichage des BB et des predecesseurs/successeurs
      // functmp->test();
      // pour afficher le CFG mais l'affichage ci-dessus donne les infos aussi
      // graph->display(NULL);

      string str="./tmp/";
      stringstream sstm;
      sstm << "tmp/cfg_graph_" << i <<".dot";
      str = sstm.str();
      cout << str << endl;
      graph->restitution(NULL,str);
   }
   // met dans une fichier une représentation du dernier CFG construit
   
  
}
