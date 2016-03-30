#ifndef _OPExpression_H
#define _OPExpression_H

/**	\file	OPExpression.h
	\brief	OPExpression class
	\author	Hajjem
*/
#include <iostream>
#include <string>
#include <Operand.h>
#include <Enum_type.h>
using namespace std;

/**	\class	OPExpression
	\brief	class representing an expression herited by Operand
*/

class OPExpression: public Operand{

public	:

/**	\brief	Constructor of the Expression class
*/
	OPExpression(string);

/**	\brief	Destructor of the Expression class
*/
	virtual ~OPExpression();

/**	\brief	Get the operand value
	\return return the string of the Expression
*/
	virtual string get_op();

/**	\brief	get the operator type
	\return	return the Operand type as enum	
*/
	virtual t_OpType get_op_type();


/**	\brief	tostring
	\return	return the Object as string
*/
	virtual string to_string();



/**	\brief	set the operand value
	setter of the operand
*/
	virtual void set_op( string);





};

#endif

