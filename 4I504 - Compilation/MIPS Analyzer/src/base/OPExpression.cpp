#include <OPExpression.h>

OPExpression::OPExpression(string op){

    _oper = op;

    }

OPExpression::~OPExpression(){}

string OPExpression::get_op(){

    return _oper;
    }

t_OpType OPExpression::get_op_type(){
   return Exp;
    }

string OPExpression::to_string(){
    return _oper;
    }

void OPExpression::set_op( string op){
    _oper=op;
    }

