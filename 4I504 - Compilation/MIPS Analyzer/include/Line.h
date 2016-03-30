#ifndef _Line_H
#define _Line_H
/**	\file	Line.h
	\brief	Line class
	
*/

#include <iostream>
#include <string>
#include <Enum_type.h>
using namespace std;

/**	\class	Line
	\brief	Abstract class representing an Line
*/

class Line{
public	:
	
	/**	\brief	Virtual destructor
*/
	virtual ~Line(){}; 

	/**	\brief	get the string  of the line
		virtual getter
*/
	virtual string get_content()=0;

	/**	\brief	set the string of the line
		virtual setter
*/
	virtual void set_content(string)=0;

	/**	\brief	get the type of the line
		virtual accessor of the type
*/
	virtual t_Line type_line()=0;

/**	\brief	get the name string 
		accessor of the type line
		
*/
	virtual string to_string()=0;


/**	\brief	return the type of the instruction
*/
	virtual t_Inst  get_type()=0;

/**	\brief	tests if the line is an instruction
*/
	bool isInst(){return type_line()==line_Instru;};

/**	\brief	tests if the line is a label
*/
	bool isLabel(){return type_line()==line_Lab;};

/**	\brief	tests if the line is a directive
*/
	bool isDirective(){return type_line()==line_Direct;};



/**	\brief	set the next line
*/
	void set_next(Line *newsuccessor){
	  _next=newsuccessor;
	};




/**	\brief	get the previous line
*/
	Line * get_prev(){
	  return _prev;
	};
	
/**	\brief	set the previous line
*/
	void set_prev(Line *newprev){
	  _prev=newprev;
	};
	
/**	\brief	get the next line
*/

	Line* get_next(){
	  return _next;
	};

protected:
	Line * _next;
	Line * _prev;
	string _line;
};

#endif	

