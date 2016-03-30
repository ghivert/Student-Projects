#ifndef _OPLabel_H
#define _OPLabel_H
/**	\file	OPLabel.h
	\brief	OPLabel class
	\author	Hajjem
*/

#include <iostream>
#include <Operand.h>
#include <Enum_type.h>
#include <string>
using namespace std;

/**	\class	OPLabel
	\brief	class representing a Label herited by Operand
*/

class OPLabel: public Operand{

public	:

/**	\brief	Constructor of the Label Class
*/
	OPLabel(string);

/**	\brief	Destructor of the Label Class
*/
	virtual ~OPLabel();

/**	\brief	Get the string of the operand
	accessor of the operand
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

/**	\brief	set the operand value
	setter of the operand
*/
	virtual void set_op( string);



};

/**	\brief	returns the OPLabel associated to the Operand if it is an OPLabel, otherwise returns NULL*/
OPLabel* getOPLabel(Operand *);

#endif

