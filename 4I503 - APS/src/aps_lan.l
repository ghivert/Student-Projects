%{

// Include header for atoi.
#include <stdlib.h>

// Include header by bison.
#include "aps_lan.tab.h"

%}

number     [0-9]
integer    {number}+
whites     [ \n\t]+
ident      [a-z]+

%%

"CONST"   { return CONST; }
"VAR"     { return VAR;   }
"SET"     { return SET;   }
"IF"      { return IF;    }
"WHILE"   { return WHILE; }

"bool"    { return BOOL_TYPE; }
"int"     { return INT_TYPE;  }

"not"     { return NOT; }
"and"     { return AND; }
"or"      { return OR;  }
"add"     { return ADD; }
"sub"     { return SUB; }
"mul"     { return MUL; }
"div"     { return DIV; }

"true"    { return TRUE;  }
"false"   { return FALSE; }

{whites}  { /* Just ignore it. */ }
{ident}   { yylval.name  = strdup(yytext); return IDENT; }
{integer} { yylval.value = atoi(yytext); return INT;     }

.         { return yytext[0]; }
