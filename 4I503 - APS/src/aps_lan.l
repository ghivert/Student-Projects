%{

// Include header for atoi.
#include <stdlib.h>

// Include header by bison.
#include "ast.h"
#include "aps_lan.tab.h"

%}

number     [0-9]
integer    {number}+
whites     [ \n\t]+
ident      [a-z]+

%%

"CONST"   { return TOK_CONST; }
"VAR"     { return TOK_VAR;   }
"SET"     { return TOK_SET;   }
"IF"      { return TOK_IF;    }
"WHILE"   { return TOK_WHILE; }

"bool"    { return TYPE_BOOL; }
"int"     { return TYPE_INT;  }

"not"     { return TOK_NOT; }
"and"     { return TOK_AND; }
"or"      { return TOK_OR;  }
"add"     { return TOK_ADD; }
"sub"     { return TOK_SUB; }
"mul"     { return TOK_MUL; }
"div"     { return TOK_DIV; }
"eq"      { return TOK_EQ;  }
"lt"      { return TOK_LT;  }

"true"    { return TRUE;  }
"false"   { return FALSE; }

{whites}  { /* Just ignore it. */ }
{ident}   { yylval.name  = strdup(yytext); return IDENT; }
{integer} { yylval.value = atoi(yytext); return INT;     }

.         { return yytext[0]; }
