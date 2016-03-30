#include <OPImmediate.h>
#include <sstream>

OPImmediate::OPImmediate(string op){
    _oper = op;
}

OPImmediate::OPImmediate(int imm){
	std::ostringstream oss ;
	oss << imm ;
    _oper = oss.str() ;
}

OPImmediate::~OPImmediate(){}

string OPImmediate::get_op(){

    return _oper;
}


t_OpType OPImmediate::get_op_type(){
    return Imm;
}


string OPImmediate::to_string(){
    return _oper;
}

void OPImmediate::set_op( string op){
    _oper=op;
   }

