#include <OPLabel.h>

OPLabel::OPLabel(string op){

    _oper = op;

    }

OPLabel::~OPLabel(){}

 string OPLabel::get_op(){

    return _oper;
    }

t_OpType OPLabel::get_op_type(){
   return Lab;
    }


 string OPLabel::to_string(){
   return _oper;
    }

 void OPLabel::set_op( string op){
    _oper=op;
    }

OPLabel* getOPLabel(Operand *o){
  if (o->isOPLabel())
    return (dynamic_cast <OPLabel*> (o));
  return NULL;
}
