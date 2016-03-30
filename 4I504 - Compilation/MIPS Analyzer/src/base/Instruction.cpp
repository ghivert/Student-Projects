#include <Instruction.h>
#include <Enum_type.h>
#include <stdlib.h> //pour atoi

 Instruction* getInst(Line* l){
	   if (l->isInst())
	     return (dynamic_cast< Instruction * > (l));
	   else return NULL;
	}


/* retourne le délai induit par une dépendance RAW i1 -> i2 avec i1 de type t1 et i2 de type t2 */

int delai(t_Inst t1, t_Inst t2){
  return t_delay[t1][t2];
}


static int getNbDiffNull(Operand *Op1, Operand *Op2, Operand *Op3){
   int i=0;
   if(Op1!=NULL)
      i++;
   if(Op2!=NULL)
      i++;
   if(Op3!=NULL)
      i++;
   return i;
}

Instruction::Instruction(string instr, t_Operator oper, t_Inst type, 
			 Operand *Op1, Operand *Op2, Operand *Op3){
   
   _line= instr;
   _op= oper;
    _type=op_profile[_op].type;
   _type= type;
   _op1= Op1;
   _op2= Op2;
   _op3= Op3;
   _index = 0;
   _next=NULL;
   _prev=NULL;
   _next_inst=NULL;
   _prev_inst=NULL;
   _nbOp=getNbDiffNull(Op1,Op2,Op3);
}

Instruction::Instruction(t_Operator oper, Operand *Op1, Operand *Op2, Operand *Op3){
   _op= oper;
    _type=op_profile[_op].type;
   _op1= Op1;
   _op2= Op2;
   _op3= Op3;
   _index = 0;
   _next=NULL;
   _prev=NULL;
   _next_inst=NULL;
   _prev_inst=NULL;
   _nbOp=getNbDiffNull(Op1,Op2,Op3);
}

Instruction::Instruction(t_Operator oper, Operand *Op1, Operand *Op2){
   _op= oper;
    _type=op_profile[_op].type;
   _op1= Op1;
   _op2= Op2;
   _op3= NULL;
   _index = 0;
   _next=NULL;
   _prev=NULL;
 _next_inst=NULL;
   _prev_inst=NULL;
   _nbOp=getNbDiffNull(Op1, Op2, NULL);
}

Instruction::Instruction(t_Operator oper, Operand *Op1){
   _op= oper;
   _op1= Op1;
   _op2= NULL;
   _op3= NULL;
   _index = 0;
   _next=NULL;
   _prev=NULL;
   _next_inst=NULL;
   _prev_inst=NULL;
    _type=op_profile[_op].type;
   if(Op1!=NULL)
      _nbOp=1;
   else 
      _nbOp=0;

}

Instruction::Instruction(t_Operator oper){
   _op= oper;
    _type=op_profile[_op].type;
   _op1= NULL;
   _op2= NULL;
   _op3= NULL;
   _nbOp=0;
   _index = 0;
   _next=NULL;
   _prev=NULL;
   _next_inst=NULL;
   _prev_inst=NULL;
}

Instruction::~Instruction(){}

Operand* Instruction::get_op1(){
   return _op1;
}

void Instruction::set_op1(Operand * o){
   if (_op1 == NULL)
      _nbOp++;
   _op1=o;
}

Operand* Instruction::get_op2(){
   return _op2;
}

void Instruction::set_op2(Operand * o){
   if (_op2 == NULL)
      _nbOp++;
   _op2=o;
}

Operand* Instruction::get_op3(){
   return _op3;
}

void Instruction::set_op3(Operand * o){
   if (_op3 == NULL)
      _nbOp++;
   _op3 =o;
}

int Instruction::get_nbOp(){
   return _nbOp;
}

t_Operator Instruction::get_opcode(){
   return _op;
}

void Instruction::set_opcode(t_Operator newop){
   _op = newop;
}

string Instruction::string_opcode(){
   return op_profile[_op].nom;
}


t_Format Instruction::get_format(){
   return op_profile[_op].format;
}

//static
string Instruction::form[5]={"J", "I", "R", "O", "B"};

string Instruction::string_form(){
   return form[get_format()];
}

t_Inst  Instruction::get_type(){
  
   return _type;

}

string Instruction::to_string(){
   return get_content();

}

t_Line Instruction::type_line(){
   return line_Instru;
}

string Instruction::get_content(){

   string rt ;

   rt= string_opcode()+ " ";

   if(get_type()==MEM){
      if (_op1!=NULL){
	 rt = rt+ _op1->get_op();
	 if (_op2!=NULL){
	    if(_op2->get_op_type()!=Reg)
	       rt = rt+ "," + _op2->get_op();
	    else	
	       rt = rt+ ",(" + _op2->get_op()+")";
	 }
			
	 if(_op3!=NULL && _op2==NULL){
	    rt =rt+",("+ _op3->get_op()+")";	
	 }
	 else if(_op3!=NULL && _op2!=NULL){
	    rt =rt+"("+ _op3->get_op()+")";	
	 }		
      }
   }
   else{
      if (_op1!=NULL){
	 rt = rt+ _op1->get_op();
	 if (_op2!=NULL){
	    rt = rt+ "," + _op2->get_op();
	    if(_op3!=NULL){
	       rt =rt+","+ _op3->get_op();
	    }
	 }
      }
   }	
   return rt;
}

void Instruction::set_content(string line){
   _line =line;

}


//static
string Instruction::typ[5]={"ALU", "MEM", "BR", "OTHER","BAD"};

string Instruction::string_type(){
   return typ[get_type()];
}


// ------------------ RAW ----------------------

bool Instruction::is_dep_RAW1(Instruction *i2){
   return (this->get_reg_dst() != NULL && 
	   i2->get_reg_src1() != NULL && 
	   !(this->get_reg_dst()->get_op().compare(i2->get_reg_src1()-> get_op())));
}

bool Instruction::is_dep_RAW2(Instruction *i2){
   return (this->get_reg_dst() != NULL && 
	   i2->get_reg_src2() != NULL && 
	   !(this->get_reg_dst()-> get_op().compare(i2->get_reg_src2()-> get_op())));  
}
//this write, i2 read
bool Instruction::is_dep_RAW(Instruction *i2){
   return this->is_dep_RAW1(i2) || this->is_dep_RAW2(i2) ;
}

// ------------------ WAR ----------------------

bool Instruction::is_dep_WAR1(Instruction *i2){
  return (i2->get_reg_dst() != NULL && 
	  this->get_reg_src1() != NULL && 
	  !(i2->get_reg_dst()-> get_op().compare(this->get_reg_src1()-> get_op())));
}

bool Instruction::is_dep_WAR2(Instruction *i2){
  return  (i2->get_reg_dst() != NULL &&
	   this->get_reg_src2() != NULL && 
	   !(i2->get_reg_dst()-> get_op().compare(this->get_reg_src2()-> get_op())));
}

//this read, i2 write
bool Instruction::is_dep_WAR(Instruction *i2){
   return this->is_dep_WAR1(i2) || this->is_dep_WAR2(i2);
}

bool Instruction::is_dep_WAW(Instruction *i2){
  return (i2->get_reg_dst() != NULL && get_reg_dst()!= NULL &&  
	  !(i2->get_reg_dst()->get_op().compare(this->get_reg_dst()->get_op())));
}

// ------------------ MEM ----------------------

bool Instruction::is_mem(){
   return _type==MEM;
}

bool Instruction::is_mem_load(){
  return (_type==MEM && 
	  ( _op==lb || _op==lbu || _op==lh || _op==lhu 
	    || _op==lw || _op==lwl || _op==lwr 
	    || _op==ll || _op==pref));
}

bool Instruction::is_mem_store(){
  return (_type==MEM && (_op==	sw ||_op == sb || _op== sh));
}

bool Instruction::is_dep_MEM(Instruction *i2){
   
   if(!( this->get_type()==MEM 
	 && i2->get_type()==MEM))
      return false;
   
   Instruction *loader= NULL, *storer=NULL, *storer2=NULL;

   if (is_mem_load() && i2->is_mem_store()){
      loader=this;
      storer=i2;
   }
   else if (i2->is_mem_load() && is_mem_store()){
      loader=i2;
      storer=this;
   }
   else if ((i2->is_mem_store() && is_mem_store())){
      storer=this;
      storer2=i2;
   }
   else{
      //2 loads -> WAW possible, mais pas de conflit mem !
      return false;
   }
   
   if(storer2==NULL
      && loader->get_reg_src1()-> get_op().compare(storer->get_reg_src2()-> get_op()))
	 return true;
   
   if(storer2!=NULL
      && storer->get_reg_src2()-> get_op().compare(storer2->get_reg_src2()-> get_op()))
      	 return true;

   //this.op3 == i2.op3
   string str=this->get_op2()->get_op();
   int imm=atoi( str.c_str() );
   str=i2 ->get_op2()->get_op();
   int imm_i2=atoi( str.c_str() );
   
   if (imm-imm_i2>=4
       || imm_i2-imm>=4)
      return false;
       
   return true;
}


t_Dep Instruction::is_dependant(Instruction *i2){

   if(is_dep_RAW(i2)) 
      return RAW;
   if(is_dep_WAR(i2)) 
      return WAR;
   if(is_dep_WAW(i2)) 
      return WAW;
   if(is_dep_MEM(i2)) 
      return MEMDEP;
   return NONE;

}


OPRegister* Instruction::get_reg_dst(){
   OPRegister *op1 = dynamic_cast< OPRegister * > (_op1);
   
   if(_op1!=NULL && _op1->get_op_type()==Reg 
      && op1->get_type() == Dst && _op1->get_op().compare("$0"))
      return op1;

   return NULL;
}

OPRegister* Instruction::get_reg_src1(){
   OPRegister *op1 = dynamic_cast< OPRegister * > (_op1);
   OPRegister *op2 = dynamic_cast< OPRegister * > (_op2);
   OPRegister *op3 = dynamic_cast< OPRegister * > (_op3);

   if(_op1!=NULL) 
      if(_op1->get_op_type()==Reg && op1->get_type() == Src)
	 return op1;
   if(_op2!=NULL) 
      if(_op2->get_op_type()==Reg && op2->get_type() == Src)
	 return op2;
   if(_op3!=NULL) 
      if(_op3->get_op_type()==Reg && op3->get_type() == Src)
	 return op3;
   return NULL;
}

OPRegister* Instruction::get_reg_src2(){
   OPRegister *op1 = dynamic_cast< OPRegister * > (_op1);
   OPRegister *op3 = dynamic_cast< OPRegister * > (_op3);
   OPRegister *op2 = dynamic_cast< OPRegister * > (_op2);

   if (op1 != NULL && op1->get_type() == Dst){ 
      if(op2 && op2->get_type() == Src)
	 if (op3  && op3->get_type() == Src)
	    return op3;
      return NULL;
   }
   if (op1 != NULL && op1->get_type() == Src){ 
      if( op2 && op2->get_type() == Src)
	 return op2;
      else
	 if (op3  && op3->get_type() == Src)
	    return op3;
      return NULL;
   }
   return NULL;
}



OPLabel* Instruction::get_op_label(){
   OPLabel *op1 = dynamic_cast< OPLabel * > (_op1);
   OPLabel *op3 = dynamic_cast< OPLabel * > (_op3);
   OPLabel *op2 = dynamic_cast< OPLabel * > (_op2);

   if (op1 != NULL)
     return op1;
   if (op2 != NULL)
     return op2;
   if (op3 != NULL)
     return op3;
    
   return NULL;
}

void Instruction::set_next(Instruction *inst){	
   _next_inst=inst;
}

Instruction *Instruction::get_next(){
   return _next_inst;
}

void Instruction::set_prev(Instruction *inst){
   _prev_inst=inst;
}

void Instruction::set_link_succ_pred(Instruction *succ){
   _next_inst=succ;
   succ->set_prev(this);
}

Instruction *Instruction::get_prev(){
   return _prev_inst;	
}

void Instruction::add_pred_dep(dep *d){
   _pred_dep.push_back(d);
}

void Instruction::add_succ_dep(dep *d){
   _succ_dep.push_back(d);
}

list<dep*>::iterator Instruction::succ_begin(){
   return _succ_dep.begin();
}
list<dep*>::iterator Instruction::succ_end(){
   return _succ_dep.end();
}


dep* Instruction::get_pred_dep(int index){
	list<dep*>::iterator it;
	it=_pred_dep.begin();

  	if(index< (int)_pred_dep.size()){
	  for (int i=0; i<index;i++ ) it++;
	  return *it;	
	}
	else cout<<"Error: index is bigger than the size of the list"<<endl; 
	
	return NULL;

}
dep* Instruction::get_succ_dep(int index){
	list<dep*>::iterator it;
	it=_succ_dep.begin();

  	if(index< (int)_succ_dep.size()){
	  for (int i=0; i<index;i++ ) it++;
	  return *it;	
	}
	else cout<<"Error: index is bigger than the size of the list"<<endl; 
	return NULL;

}


int Instruction::get_nb_succ(){
   return _succ_dep.size();
}

int Instruction::get_nb_pred(){
   return _pred_dep.size();
}

int Instruction::get_index(){
   return _index;
}

void Instruction::set_index(int id){
   _index = id;
}

bool Instruction::is_branch(){
  return _type == BR;
}

bool Instruction::is_nop(){
  OPRegister *op1 = dynamic_cast< OPRegister * > (_op1);
   
  if(_op1!=NULL && _op1->get_op_type()==Reg 
     && op1->get_type() == Dst && (_op1->get_op().compare("$0")==0))
      return true;

  return (get_content().compare(0,3,"nop")==0);
}

bool Instruction::is_call(){
   return _op == jal;
}
bool Instruction::is_cond_branch(){
   return (get_content().compare(0,1,"b")==0);
}
bool Instruction::is_indirect_branch(){
   return ( get_opcode() == jr ||  get_opcode() == jalr);
}

int Instruction::get_latency(){
  // 1 pour tout le monde
    return 1;
}

string str_t_dep(t_Dep td){
   string str[6]={ "None", "RAW", "WAR", "WAW", "MEMDEP", "CONTROL" };
   
   return str[td];
}

void Instruction::print_succ_dep(){
   list<dep*>::iterator it;
   int size=(int) _succ_dep.size();
   it=_succ_dep.begin();

   for (int i=0; i<size; i++ ){
      cout<< "i"<<_index<<" -> i"<<(*it)->inst->get_index()<<" : "<<str_t_dep((*it)->type)<<endl;
      it++;
   }
}


void Instruction::reset_pred_succ_dep(){
  
  list<dep*>::iterator it;
  int size=(int) _succ_dep.size();
   dep * d;
   it=_succ_dep.begin();
  
   for (int i=0; i<size; i++ ){
     d = *it; 
     free(d);
     it++;
   }
   _succ_dep.clear();
   size = (int) _pred_dep.size();
   it = _pred_dep.begin();
   for (int i=0; i<size; i++ ){
     d = *it; 
     free(d);
     it++;
   }
   _pred_dep.clear();
   return;
}
