#ifndef _OPRegister_H
#define _OPRegister_H

/**	\file	OPRegister.h
	\brief	OPRegister class
	\author	Hajjem
*/

#include <iostream>
#include <string>
#include <Operand.h>
#include <Enum_type.h>
using namespace std;

/**	\class	OPRegister
	\brief	class representing a Register herited by Operand
*/

class OPRegister: public Operand{

private :
	int _reg;
	t_Src_Dst _type;

public	:

/**	\brief	Constructor of the Register class
*/
	OPRegister(string, t_Src_Dst);

/**	\brief	Constructor of the Register class
*/
	OPRegister(string, int, t_Src_Dst);
	
	OPRegister(int, t_Src_Dst);

/**	\brief	Destructor of the Register class
*/
	virtual ~OPRegister();


/**	\brief	Get the Register value
	\return return the number of the Register
*/
	int get_reg();

/**	\brief	set the Register value
	setter of the Register
*/
	void set_reg( int);

/**	\brief	Get the operand value
	\return return the string of the register
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

/**	\brief	set the type of the register
	setter of the register type
*/
	void set_type(t_Src_Dst );

/**	\brief	get the type of the register
	getter of the register type
*/
	t_Src_Dst get_type( );


};

/**	\brief	returns the OPRegister associated to the Operand if it is an OPRegister, otherwise returns NULL*/
OPRegister* getOPRegister(Operand *);

#endif

