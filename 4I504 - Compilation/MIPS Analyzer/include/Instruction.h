#ifndef _Instruction_H
#define _Instruction_H

/**	\file	Instruction.h
	\brief	Instruction class
*/

#include <Operand.h>
#include <string>
#include <OPExpression.h>
#include <OPImmediate.h>
#include <OPLabel.h>
#include <Line.h>
#include <OPRegister.h>
#include <Enum_type.h>
#include <list>

using namespace std;

/**	\class	Instruction
	\brief	class representing an instruction which herited by Line
*/

class Instruction;

typedef struct{
   Instruction *inst;
   t_Dep type;
}dep;

class Instruction :public Line{
   static string form[5];
   static string typ[5];

private:
   t_Operator _op;
   t_Inst _type;
   Operand *_op1;
   Operand *_op2;
   Operand *_op3;
   int _nbOp;
   int _index;

   Instruction *_next_inst;
   Instruction *_prev_inst;

   list <dep*> _succ_dep; // liste des dépendances & inst avec les instructions qui suivent dans un bloc
   list <dep*> _pred_dep; // liste des dépedances & inst avec les instructions qui précédent dans un bloc


public:

	
/**	\brief	Constructor of the class instruction
 */
   Instruction(string, t_Operator, t_Inst, Operand *, Operand *, Operand *);

/**	\brief	Constructor with 3 Operands of the class instruction */
   Instruction(t_Operator, Operand *, Operand *, Operand *);
/**	\brief	Constructor with 2 Operands of the class instruction */
   Instruction(t_Operator, Operand *, Operand *);
/**	\brief	Constructor with 1 Operand of the class instruction */
   Instruction(t_Operator, Operand *);
/**	\brief	Constructor without Operands of the class instruction */
   Instruction(t_Operator);

/**	\brief	Destructor of the class instruction
 */
   virtual ~Instruction();

/**	\brief	Get the first operand value
	accessor of the operand
*/
   Operand* get_op1();

/**	\brief	set the first operand value
	setter of the operand
*/
   void set_op1(Operand * o);

/**	\brief	Get the second operand value
	accessor of the operand
*/
   Operand* get_op2();

/**	\brief	set the second operand value
	setter of the operand
*/
   void set_op2(Operand * o);

/**	\brief	Get the third operand value
	accessor of the operand
*/
   Operand* get_op3();

/**	\brief	set the third operand value
	setter of the operand
*/
   void set_op3(Operand * o);

/**	\brief	get the Opcode value
	accessor of the opcode
*/
   t_Operator get_opcode();

/**	\brief	get the string Opcode value
	accessor of the string opcode
*/
   string string_opcode();


/**	\brief	set the opcode value
	setter of the opcode
*/
   void set_opcode(t_Operator newop);

/**	\brief	get the format of the Instruction
	accessor of the format
*/


   t_Format get_format();

/**	\brief	get the Type of the Instruction
	accessor of the Type
*/
   virtual t_Inst  get_type();


   /**	\brief	get the type of the line
    */
   virtual t_Line type_line();

   /**	\brief	get the name string instruction
    */
   virtual string to_string();

   /**	\brief	get the string  of the instruction
    */
   virtual string get_content();

   /**	\brief	set the string of the instruction
    */
   virtual void set_content(string);




/**	\brief	set the string format
 */
   string string_form();

/**	\brief	set the string Type of instruction
 */
   string string_type();

/**	\brief	get the index of instruction
 */
   int get_index();

/**	\brief	set the index of instruction
 */
   void set_index(int);

/**	\brief	test if the instruction is a branch
 */
   bool is_branch();

/**	\brief	test if the instruction is a call
 */

   bool is_call();
/**	\brief	test if the instruction is a conditionnal branch
 */

   bool is_cond_branch();


/**	\brief	test if the instruction a branch and the target adress is in a register
 */	

   bool is_indirect_branch();

/**	\brief	test if the instruction a branch and the target adress is in a register
 */	

   bool is_nop();


/**	\brief	test if the instruction is a memory access 
 */
   
   bool is_mem();
/**	\brief	test if the instruction is a memory access that reads a value
 */
   bool is_mem_load();

/**	\brief	test if the instruction is a memory access that writes a value
 */
   bool is_mem_store();

   static bool is_writed_between(int dst, Instruction *i1, Instruction *i2exclu);
/**	\brief	get the dependance between the current instruction and i2
	\return return "RAW", "WAR", "WAW", "MEMDEP" or "not dependant" in format enum
*/
   t_Dep is_dependant(Instruction *i2);


/**	\brief	return if there is dependance RAW between the current instruction and the first source operand of i2	
	\return return true if there is a RAW dependance between the current instruction and the first source operand of i2 

*/	bool is_dep_RAW1(Instruction *i2);

/**	\brief	return if there is dependance RAW between the current instruction and the second  source operand of i2	
	\return return true if there is a RAW dependance between the current instruction and the second source register operand of i2 

*/	bool is_dep_RAW2(Instruction *i2);


/**	\brief	get the information if there is dependance RAW between the current instruction and i2	
	\return return true if there is a RAW dependance
*/
   bool is_dep_RAW(Instruction *i2);


/**	\brief	test if there is dependance WAR between the first source operande of the current instruction if any and the destination register operande i2 if any	
	\return return true if there is a WAR dependance between the first source operande of the current instruction if any and the destination register operande i2 if any	 	
*/
	bool is_dep_WAR1(Instruction *i2);

/**   	\brief	test if there is dependance WAR between the second source operande of the current instruction if any and the destination register operande i2 if any	
	\return return true if there is a WAR dependance between the second source operande of the current instruction if any and the destination register operande i2 if any
*/     	bool is_dep_WAR2(Instruction *i2);


/**	\brief	get the information if there is dependance WAR between the current instruction and i2	
	\return return true if there is a WAR dependance
*/
   bool is_dep_WAR(Instruction *i2);

/**	\brief	get the information if there is dependance WAW between the current instruction and i2	
	\return return true if there is a WAW dependance
*/
   bool is_dep_WAW(Instruction *i2);

/**	\brief	test if there is dependance MEMDEP between the current instruction and i2	
	\return return true if there is a MEMDEP dependance
*/
   bool is_dep_MEM(Instruction *i2);

/**	\brief	get the number of operand	
	\return return the number of operand
*/
   int get_nbOp();


/**	\brief	set the number of operand*/
   void set_number_oper(int);

   /**	\brief	get the regiter destination of the instruction
    */
   OPRegister* get_reg_dst();

   /**	\brief	get the first register source of the instruction
    */
   OPRegister* get_reg_src1();
	
   /**	\brief	get the second register source of the instruction
    */
   OPRegister* get_reg_src2();

 /**	\brief	get the label operand of the instruction, if any
    */
   OPLabel* get_op_label();

/**	\brief	get the successor of the Instruction
 */



   void set_next(Instruction*);

/**     \brief set the parameter as successor and this as predecessor of the parameter
 */
   void set_link_succ_pred(Instruction*);

/**	\brief	get the successor of the Instruction
 */
   Instruction* get_next();

/**	\brief	setter of the predecessor of the Instruction
 */
   void set_prev(Instruction *);

/**	\brief	get the predecessor of the Instruction
 */
   Instruction* get_prev();

/**	\brief	add a dependance with a predecessor instruction to the dependance type list
 */
   void add_pred_dep(dep*);

/**	\brief	get the dependance type with the ith predecessor instruction of the current instruction
 */
   dep* get_pred_dep(int i);

/**	\brief	add a dependance with a successor  to list of the dependance type of successors
 */
   void add_succ_dep(dep*);

/** \brief reset succ and pred dependances of this */
   void reset_pred_succ_dep();
   
   list<dep*>::iterator succ_begin();
   list<dep*>::iterator succ_end();

/**	\brief	get the ieme dependance type with successors from successor dependance type list  of the current instruction
 */
   dep* get_succ_dep(int i);


/**	\brief	get the number of successor of the Instruction
 */
   int get_nb_succ();

/**	\brief	get the number of predecessor of the Instruction
 */
   int get_nb_pred();

   /** \brief return the latency of the instruction */

   int get_latency();


   /** \brief print the dependance of this with instructions denoted by their index and the dependance type */
   void print_succ_dep();

};



/**	\brief	returns the instruction associated to the line, if the line is an instruction, NULL otherwise
*/
Instruction* getInst(Line* l);

/** \brief retourne le délai induit par une dépendance RAW i1 -> i2 avec i1 de type t1 et i2 de type t2

 */
int delai(t_Inst t1, t_Inst t2);


#endif
