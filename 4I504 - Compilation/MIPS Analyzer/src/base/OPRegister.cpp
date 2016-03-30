#include <OPRegister.h>
#include <sstream>


OPRegister::OPRegister(string op, t_Src_Dst ty){

    _oper = op;
    _type = ty;
}

OPRegister::OPRegister(string op, int reg, t_Src_Dst ty){

    _oper = op;
    _reg = reg;
    _type = ty;

    }

OPRegister::OPRegister(int reg, t_Src_Dst ty){
   std::ostringstream oss ;
   oss << "$" << reg ;
   _oper = oss.str() ;
   _reg = reg;
   _type = ty;
   
}

OPRegister::~OPRegister(){}


int OPRegister::get_reg(){
   return _reg;
}


void OPRegister::set_reg(int reg){
   _reg= reg;
   std::ostringstream oss ;
   oss << "$" << reg ;
   _oper = oss.str() ;
}

string OPRegister::get_op(){
    return _oper;
}

t_OpType OPRegister::get_op_type(){
    return Reg;
}

string OPRegister::to_string(){
   return _oper;
}

void OPRegister::set_op( string op){
    _oper=op;
}

t_Src_Dst OPRegister::get_type( ){
   return _type;
}

void OPRegister::set_type(t_Src_Dst ty){
	_type=ty;
}

OPRegister* getOPRegister(Operand *o){
  if (o->isOPRegister())
    return (dynamic_cast <OPRegister*> (o));
  return NULL;
}
