%{

// Include header for atoi.
#include <stdlib.h>

// Include header by bison.
#include "ast.h"

%}

number     [0-9]
integer    {number}+
whites     [ \n\t]+
ident      [a-zA-Z]+

%%

"true"    { return TRUE;  }
"false"   { return FALSE; }
"Nil"     { return NIL;   }

"fun"     { return TOK_FUN;   }
"->"      { return TOK_ARROW; }
"if"      { return TOK_IF;    }
"then"    { return TOK_THEN;  }
"else"    { return TOK_ELSE;  }
"let"     { return TOK_LET;   }
"rec"     { return TOK_REC;   }
"in"      { return TOK_IN;    }
"match"   { return TOK_MATCH; }
"with"    { return TOK_WITH;  }

"::"      { return TOK_CONS; }
"<="      { return TOK_LEQ;  }
">="      { return TOK_GEQ;  }


{whites}  { /* Just ignore it. */ }
{ident}   { yylval.name  = strdup(yytext); return IDENT; }
{integer} { yylval.value = atoi(yytext);   return INT;   }

.         { return yytext[0]; }
