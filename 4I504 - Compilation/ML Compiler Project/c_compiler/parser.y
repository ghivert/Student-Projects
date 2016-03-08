%{
  // Debug purposes.
  #define  YYDEBUG 0
  // Includes.
  #include <stdio.h>
  #include <stdlib.h>

  #include "ast.h"

  // To avoid warnings.
  int yylex();
  void yyerror(const char *string);

  // To read from CLI.
  extern FILE *yyin;
  FILE *yyout;

  // To store the AST.
  ast_t *program;
%}

%union {
  int    value;
  char  *name;
  ast_t *prog;
}

// Keywords.
%token TOK_FUN     TOK_WITH
%token TOK_ARROW   TOK_MATCH
%token TOK_IF      TOK_IN
%token TOK_THEN    TOK_REC
%token TOK_ELSE    TOK_LET

// Operators.
%token TOK_CONS
%token TOK_LEQ
%token TOK_GEQ

// Natives.
%token TRUE
%token FALSE
%token NIL

// Constants.
%token <name>  IDENT
%token <value> INT

%type <prog>  _Expression
%type <prog>  _List

%start _Entry

%%

_Entry: _Expression      { program = $1; }

_Expression:
    TOK_FUN IDENT TOK_ARROW _Expression                           { $$ = new_function($2, $4); }
  | TOK_LET IDENT '=' _Expression TOK_IN _Expression              { $$ = new_let($2, $4, $6);  }
  | TOK_LET TOK_REC IDENT '=' _Expression TOK_IN _Expression      { $$ = new_let($3, $5, $7);  }
  | _Expression _Expression                                       { $$ = new_apply($1, $2);    }
  | _Expression TOK_CONS _Expression                              { $$ = new_cons($1, $3);     }
  | TOK_MATCH _Expression TOK_WITH _List                          { $$ = new_match($2, $4);    }
  | TOK_IF _Expression TOK_THEN _Expression TOK_ELSE _Expression  { $$ = new_cond($2, $4, $6); }
  | _Primitives
  | _BinaryOperation

_Primitives:
    NIL     { $$ =  new_nil();    }
  | TRUE    { $$ = new_true();    }
  | FALSE   { $$ = new_false();   }
  | IDENT   { $$ = new_ident($1); }
  | INT     { $$ = new_num($1);   }

_BinaryOperation:
    _Expression     '+'     _Expression   { $$ = new_bin(TYPE_ADD, $1, $3); }
  | _Expression     '*'     _Expression   { $$ = new_bin(TYPE_MUL, $1, $3); }
  | _Expression     '-'     _Expression   { $$ = new_bin(TYPE_SUB, $1, $3); }
  | _Expression   TOK_LEQ   _Expression   { $$ = new_bin(TYPE_LEQ, $1, $3); }
  | _Expression   TOK_GEQ   _Expression   { $$ = new_bin(TYPE_GEQ, $1, $3); }

_List:
    '|' NIL TOK_ARROW _Expression '|' IDENT TOK_CONS IDENT TOK_ARROW _Expression {}
  | NIL TOK_ARROW _Expression {}
  | IDENT TOK_CONS IDENT TOK_ARROW _Expression {}

%%

// Handling errors, just in case...
void yyerror(const char *string) {
  printf("Error... %s\n", string);
}

int main(int argc, char *argv[]) {
  // Debug purposes.
  yydebug = 0;

  // Changing input to read from argument.
  for (int i = 1; i < argc; i++) {
    // Parsing.
    yyin = fopen(argv[i], "r");
    yyparse();
    fclose(yyin);

    // Writing to output.
    yyout = fopen(replace_str(argv[i], ".mpp", ".out"), "w");
    fprintf(yyout, "prog(");
    print_program(yyout, program);
    fprintf(yyout, ")");
    fclose(yyout);

    free_program(program);
  }
  return EXIT_SUCCESS;
}
