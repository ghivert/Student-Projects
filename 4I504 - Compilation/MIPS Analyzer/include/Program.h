#ifndef _Program_H
#define _Program_H

/**	\file	Program.h
	\brief	Program class
	\author	Hajjem
*/


#include <Line.h>
#include <Function.h>
#include <Basic_block.h>
#include <Instruction.h>
#include <Directive.h>
#include <Cfg.h>
#include <string>
#include <stdio.h>
#include <Enum_type.h>
#include <fstream>
#include <list>
using namespace std;


/**	\class	Program
	\brief	class representing a program as list
*/

class Program{

public:

/**	\brief	Empty constructor of a program
*/
	Program();

/**	\brief	Copy constructor of a program
*/
	Program(Program const&  otherprogram);

/**	\brief	Constructor with the input file of program
*/
	Program (string const file);

/**	\brief	Destructor of program
*/
	~Program();

/**	\brief	Add a line at the end of the program
*/
	void add_line(Line * newline);

/**	\brief	Add a line to the program with position as index
*/
	int add_line_at(Line *newline, int position);

/**	\brief	Reverse two lines which are at the index line1 and line2
*/
	void exchange_line(int line1, int line2);

/** \brief display the program
*/
	void display();


/**	\brief	Delete the line at the given index in the program
*/
	void del_line(int index);

/**	\brief	gives the line that corresponds to the index
*/
	Line * find_line(int index);

/**	\brief	get the length of the program
*/
	int size();

/**	\brief	returns the dependance betwen the two given instructions
	\return returns the dependance in the enum format
*/

/**	\brief	write the programme into a file
*/
	void in_file(string const filename);

/**	\brief	return true if the program is Empty
*/
	bool is_empty();

/**	\brief	calculate the functions of the program
*/
	void  comput_function();

/**	\brief	get the number of functions in the program
*/
	int nbr_func();

/**	\brief	returns the function of index index in the list _myfunc
*/
	Function*  get_function(int index);
	
	list<Function*>::iterator function_list_begin();

	list<Function*>::iterator function_list_end();


/**	\brief	empty the program
*/
	void flush();

/**	\brief	calculate the CFG associated with each function of the program
*/
	void  comput_CFG();


/**	\brief	returns the CFG of index index in the list _myCFG
*/
	Cfg*  get_CFG(int index);

private:
	int _length;
	Line *_head;
	Line *_end;
	list <Function *> _myfunc;
       	list <Cfg *> _myCFG;

};



#endif
