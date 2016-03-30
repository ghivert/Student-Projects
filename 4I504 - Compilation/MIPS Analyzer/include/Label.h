#ifndef _Label_H
#define _Label_H
/**	\file	Label.h
	\brief	Label class
	\author	Hajjem
*/

#include <iostream>
#include <string>
#include <Enum_type.h>
#include <Line.h>
using namespace std;

/**	\class	Label
	\brief	class representing an Label herited by Line
*/

class Label : public Line{


public	:

		/**	\brief	Constructor of the Label
*/
	Label(string);

		/**	\brief	Destructor of the Label
*/
	virtual ~Label();

		/**	\brief	get the type of the line
*/
	virtual t_Line type_line();

	/**	\brief	get the string of Label
*/	
	virtual string to_string();

	/**	\brief	get the string  of the Label
*/	
	virtual string get_content();

	/**	\brief	set the string of the Label
*/	
	virtual void set_content(string);


	/**	\brief	return the type of the instruction
*/
	virtual t_Inst  get_type();




};


/**	\brief	returns the Label associated to the line if the line is a label, NULL otherwise
*/
	 Label* getLabel(Line *l);


#endif
