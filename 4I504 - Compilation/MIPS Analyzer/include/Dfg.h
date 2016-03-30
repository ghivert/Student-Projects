#ifndef _Dfg_H
#define _Dfg_H

/**	\file	Dfg.h
	\brief	Dfg class
*/


#include <Node_dfg.h>
#include <Instruction.h>
#include <Enum_type.h>
#include <fstream>
#include <list>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/astar_search.hpp>

class Basic_block;
class Node_dfg;

/**	\class	Dfg
	\brief	class representing a Dfg of a Basic block, a data flow graph
	that is to be used to calculate the critical path and schedule code
*/


class Dfg{

public:


	/**	\brief	Constructor of Dfg given a basic block
*/
	Dfg(Basic_block *);

	/**	\brief	Destructor of Dfg
*/
	~Dfg();

	/**	\brief	Build the Dfg, 
		when you call this method you have to affect the fisrt parameter to NULL and the 
		second to true
*/
	void build_dfg(Node_dfg*,bool);

	/**	\brief	Display the Dfg, 
		when you call this method you have to affect the fisrt parameter to NULL and the 
		second to true
*/
	void display(Node_dfg * ,bool);

	/**	\brief	restitute the Dfg, 
		when you call this method you have to affect the fisrt parameter to NULL and the 
		third to true
*/
	void restitute(Node_dfg * ,string const, bool );

	/**	\brief	tests if all node have been read
*/
	bool read_test();

	/**	\brief	comput the node weight needed for critical path computation of the Dfg
*/
	void comput_critical_path();

	void compute_nb_descendant();
	/**	\brief	order the instructions in the basic block according to an algorithm list
*/
	void scheduling(bool);


	void apply_scheduling();

/**	\brief	returns the highest weigth of nodes
*/
	int get_critical_path();
	void display_sheduled_instr();

private:
	Basic_block *_bb;
	list <Node_dfg*> list_node_dfg;
	list <Node_dfg*> _roots;
	list <Node_dfg*> _delayed_slot;
	
	list <Node_dfg*> _inst_ready;
	list <Node_dfg*> new_order;

	int _nb_arc;
	int _length;
	int *_read; 
	int _index_branch;
};

#endif

