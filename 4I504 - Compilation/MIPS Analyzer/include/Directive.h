#ifndef _Directive_H
#define _Directive_H
/**	\file	Directive.h
	\brief	Directive class
	\author	Hajjem
*/

#include <iostream>
#include <string>
#include <Enum_type.h>
#include <Line.h>
using namespace std;

/**	\class	Directive
	\brief	class representing an Directive herited by Line
*/

class Directive : public Line{


public	:
	string	_dir ;
	string	_value ;
	bool	_isfunction ;

		/**	\brief	Constructor of the Directive*/	
	Directive(string);
		
	/**	\brief	Constructor of the Directive with directive, content and an boolean*/
	
	Directive(string,string);
	/**	\brief	Constructor of the Directive with directive, content and an boolean*/
	Directive(string,string,bool);

		/**	\brief	Destructor of the Directive
*/
	virtual ~Directive();

	 
		/**	\brief	get the type of the line
*/
	virtual t_Line type_line();

	/**	\brief	get the string of the Directive
*/	
	virtual string to_string();

	/**	\brief	get the string  of the Directive
*/
	virtual string get_content();

	/**	\brief	set the string of the Directive
*/	
	virtual void set_content(string);

	/**	\brief	return true if the directive indicate a function
*/
	bool is_function();

	/**	\brief	return the type of the instruction
*/
	virtual t_Inst  get_type();



};


/**	\brief	returns the Directive associated to the line, if the line is a directive, NULL otherwise
*/
Directive* getDirective(Line *l);

#endif
