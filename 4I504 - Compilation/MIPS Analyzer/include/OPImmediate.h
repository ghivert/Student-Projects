#ifndef _OPImmediate_H
#define _OPImmediate_H

/**	\file	OPImmediate.h
	\brief	OPImmediate class
	\author	Hajjem
*/

#include <iostream>
#include <string>
#include <Operand.h>
#include <Enum_type.h>
using namespace std;


/**	\class	OPImmediate
	\brief	class representing an Immediate herited by Operand
*/
class OPImmediate: public Operand{

public	:

/**	\brief	Constructor of the Immediate Class */
	OPImmediate(string);

/**	\brief	Constructor of the Immediate Class */
	OPImmediate(int);

/**	\brief	Destructor of the Immediate Class
*/
	virtual ~OPImmediate();

/**	\brief	Get the string of the operand 
	\return return the string of the Immediate
*/
	virtual string get_op();

/**	\brief	get the operator type
	\return	return the Operand type as enum	
*/
	virtual t_OpType get_op_type();


/**	\brief	tostring
	\return	return the name of the Object as string
*/
	virtual string to_string();

/**	\brief	set the string of the operand 
	setter of the operand
*/
	virtual void set_op( string);



};

#endif

