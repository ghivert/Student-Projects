#ifndef _Cfg_H
#define _Cfg_H

/**	\file	Cfg.h
	\brief	Cfg class
	\author	Hajjem
*/


#include <Basic_block.h>
#include <string>
#include <stdio.h>
#include <Label.h>
#include <Enum_type.h>
#include <list>
#include <fstream>
using namespace std;

/**	\class	Cfg
	\brief	class representing control flow graph
*/

class Cfg{

public:
	
/**	\brief	Constructor of Cfg
*/
	Cfg(Basic_block *, int);

/**	\brief	Destructor of Cfg
*/
	~Cfg();

/**	\brief	get the head of the cfg
*/
	Basic_block *get_head();

/**	\brief	Display cfg, when you call this method you have to affect the fisrt parameter to NULL
*/
	void display(Basic_block *);

/**	\brief	Restitut the cfg in file with DOT, when you call this method you have to affect the fisrt parameter to NULL
*/
	void restitution(Basic_block *, string const );


private:

	Basic_block * _head;
	int *_read;
	int _length;
	

	
};

#endif
