#ifndef _Operand_H
#define _Operand_H

/**	\file	Operand.h
	\brief	Operand class
	\author	Hajjem
*/

#include <iostream>
#include <string>
#include <Enum_type.h>
using namespace std;

/**	\class	Operand
	\brief	Abstract class representing an operand
*/

class Operand{


public	:

/**	\brief	Virtual destructor
*/
	virtual ~Operand(){};

/**	\brief	Get the operand value
	virtual accessor of the operand
*/
	virtual string get_op()=0;

/**	\brief	set the operand value
	virtual setter of the operand
*/
	virtual void set_op(string)=0;

/**	\brief	get the operator type
	virtual accessor of accessor
	\return return the Operand type as enum	
*/
	virtual  t_OpType get_op_type()=0;


/**	\brief	virtual tostring
	\return	return the Object as string
*/
	virtual string to_string()=0;



	bool isOPLabel(){return get_op_type() == Lab;};

	bool isOPRegister(){return get_op_type() == Reg;};

	bool isOPImmediate(){return get_op_type() == Imm;};
protected :
	string _oper;
};


#endif	
