#include <Directive.h>

Directive::Directive( string direct)
{
	_dir= direct;
	_value = "" ;
	_isfunction = false ;
	  _next=NULL;
	  _prev=NULL;
}

Directive::Directive(string direct, string value)
{
	_dir= direct ;
	_value= value ;
	_isfunction= false ;
	  _next=NULL;
	  _prev=NULL;

}

Directive::Directive(string direct, string value, bool isfunction)
{
	_dir= direct ;
	_value= value ;
	_isfunction= isfunction ;
	_next=NULL;
	_prev=NULL;

}

Directive::~Directive(){}


string Directive::to_string(){
	return _line;

}


t_Line Directive::type_line(){
	return line_Direct;
}

string Directive::get_content(){
	return _dir + "	" + _value ;
}

void Directive::set_content(string line){
	_line =line;
}


bool Directive::is_function(){
	return _isfunction ;
}

t_Inst  Directive::get_type(){
	return OTHER;
}


Directive* getDirective(Line *l){
	   if (l->isDirective())
	     return (dynamic_cast< Directive * > (l));
	   else return NULL;
	}
