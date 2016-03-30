#ifndef _Basic_block_H
#define _Basic_block_H

/**	\file	Basic_block.h
	\brief	Basic_block class
	\author	Hajjem
*/


#include <Line.h>
#include <Instruction.h>
#include <string>
#include <stdio.h>
#include <Enum_type.h>
#include <fstream>
#include <vector>
#include <list>
#include <Dfg.h>
#include <Node_dfg.h>

#define DEBUG
class Node_dfg;


/**	\class	Basic_block
	\brief	class representing a Basic_block of a fonction
*/

class Basic_block{

public:
  
  /** \brief prints dependance between both instructions 
   */
   static void show_dependances(Instruction*, Instruction*);

/**	\brief	Constructor of a Basic Block
 */
   Basic_block();

/**	\brief	Destructor of a basic block
 */
   ~Basic_block();

   
/**	\brief	setter of the head of the basic block
 */
   void set_head(Line *);

/**	\brief	setter of the end of the basic block
 */
   void set_end(Line *);

/**	\brief	get the head of the basic block
 */
   Line* get_head();

/**	\brief	get the end of the basic block
 */
   Line* get_end();

/**	\brief	setter of line corresponding to the branch
 */
   void set_branch(Line *);

/**	\brief	get the line corresponding to the branch
 */
   Line* get_branch();

/**	\brief	Returns true if the first line of the block is a label
 */
   bool is_labeled();

/**	\brief	set the index of the basic block
 */
   void set_index(int i);

/**	\brief	get the index of the basic block
 */
   int get_index();


/**	\brief	returns the size (in nodes) of the basic block
 */
   int size();	


/**	\brief	returns/gets the number of successors of the basic block
 */
   int get_nb_succ();

/**	\brief	returns/gets the number of predecessors of the basic block
 */
   int get_nb_pred();

/**	\brief	setter of the successor of the basic block
 */
   void set_successor1(Basic_block *BB);

/**	\brief	get the successor of the basic block
 */
   Basic_block *get_successor1();

/**	\brief	setter of the successor of the basic block
 */
   void set_successor2(Basic_block *BB);

/**	\brief	get the successor of the basic block
 */
   Basic_block *get_successor2();

/**	\brief	setter of the predecessor of the basic block
 */
   void set_predecessor(Basic_block *BB);

/**	\brief	get the ith predecessor of the basic block
 */
   Basic_block *get_predecessor(int );



/**	\brief	returns the number of instructions
 */
   int get_nb_inst();

/**	\brief return the line associated with the first instruction of the basic block, NULL if any
 */
   Line* get_first_line_instruction();

/**	\brief return the first instruction of the basic block, NULL if any
 */
   Instruction* get_first_instruction();

/**	\brief return the last instruction of the basic block, NULL if any
 */
   Instruction* get_last_instruction();

/**	\brief	returns the instruction at the given index, NULL if any
 */
   Instruction* get_instruction_at_index(int);

/**	\brief	link instructions in the order they appear in the code
 */
   void link_instructions();

/**	\brief	comput dependances predecessors and successors of each instructions in the BB
 */
   void comput_pred_succ_dep();


/**	\brief	reset dependances predecessors and successors of each instructions in the BB to be able to recompute them
 */
   void reset_pred_succ_dep();


   /** \brief return a string with the basic block content */
   string get_content();


/**	\brief	display the basic block
 */
   void display();


/**	\brief	restitute the basic block in a file
 */
   void restitution(string const);	

/**     \brief set the parameter as a BB successor of this and this as a BB predecessor of the parameter
 */
   void set_link_succ_pred(Basic_block*);


/**	\brief	test if the instruction is in the delayed slots of the branch terminating the BB if any
*/
   bool is_delayed_slot(Instruction*);	
 
   /** \brief compute the number of cycles to execute the instruction of the basic bloc */  
   int nb_cycles();
   
 /** \brief change the order of instruction with the one given in the parameter list 

 */  
   void apply_scheduling(list<Node_dfg*>*);
  
/** \brief rename registers in the basic bloc using as available register numbers the ones give in the parameter list
 */  

   void reg_rename(list<int>*);
  

/** \brief rename registers in the basic bloc using  available registers according to the liveness analysis  
 */  

   void reg_rename();
  
/**	\brief	this method is to be used to test other methods
 */
   void test();

   void compute_use_def();
   void compute_def_liveout();
   vector<bool> Use;
   vector<bool> Def;
   vector<bool> LiveIn;
   vector<bool> LiveOut;

   /** \brief contient l'index de l'instruction qui définit le registre vivant en sortie
    */
   vector<int> DefLiveOut;

   vector<bool> Domin; 
private:
   
  
   Line *_head;
   Line *_end;

   Instruction *_firstInst;
   Instruction *_lastInst;

   Line *_branch;

   int _index;
   int _nb_instr;

   bool use_def_done;
   bool dep_done;
  
   list <Basic_block *> _succ;
   list <Basic_block *> _pred;
   
    
  
  
};

#endif
