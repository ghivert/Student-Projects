%{
  // Debug purposes.
  #define  YYDEBUG 1
  // Includes.
  #include <stdio.h>
  #include <stdlib.h>

  #include "ast.h"
  #include "ast_access.h"

  // To avoid warnings.
  int yylex();
  void yyerror(const char *string);

  // To read from CLI.
  extern FILE *yyin;
  FILE *yyout;
%}

%union {
  int   value;
  char *name;

  Program           *prog;
  Commands          *cmds;
  Command           *cmd;
  Declaration       *decl;
  TypeExpression    *t_expr;
  Stat              *stat;
  UnaryOperation    *un_op;
  BinaryOperation   *bin_op;
  Expression        *expr;
  Function          *fun;
}

// Keywords.
%token TOK_CONST
%token TOK_VAR
%token TOK_SET
%token TOK_IF
%token TOK_WHILE

// Type of constants.
%token TYPE_BOOL
%token TYPE_INT

// Operators.
%token TOK_NOT
%token TOK_AND
%token TOK_OR
%token TOK_ADD
%token TOK_SUB
%token TOK_MUL
%token TOK_DIV
%token TOK_EQ
%token TOK_LT

// Booleans.
%token TRUE
%token FALSE

// Constants.
%token <name>  IDENT
%token <value> INT

// For AST constructing.
%token DECL
%token STAT
%token BOOL
%token FUN
%token UNARY
%token BINARY

%type <prog>     _Program
%type <cmds>     _Commands
%type <cmd>      _Command
%type <decl>     _Declaration
%type <t_expr>   _TypeExpression
%type <stat>     _Stat
%type <un_op>    _UnaryOperation
%type <bin_op>   _BinaryOperation
%type <expr>     _Expression
%type <fun>      _Function

%start _Program

%%

_Program:
  '[' _Commands ']'   { $$ = new_prog($2); }
;

_Commands:
    _Command                 { $$ = new_commands($1, NULL); }
  | _Command ';' _Commands   { $$ = new_commands($1, $3); }
;

_Command:
    _Declaration   { $$ = new_declaration($1); }
  | _Stat          { $$ = new_stat($1); }
;

_Declaration:
    TOK_CONST   IDENT   _Expression       { $$ = new_const($2, $3); }
  | TOK_VAR     IDENT   _TypeExpression   { $$ = new_var($2, $3);   }
;

_TypeExpression:
    TYPE_BOOL   { $$ = new_type_expression(TYPE_BOOL); }
  | TYPE_INT    { $$ = new_type_expression(TYPE_INT);  }
;

_Stat:
    TOK_SET    IDENT        _Expression           { $$ = new_set($2, $3);      }
  | TOK_IF     _Expression  _Program     _Program { $$ = new_cond($2, $3, $4); }
  | TOK_WHILE  _Expression  _Program              { $$ = new_loop($2, $3);     }
;

_UnaryOperation:
    TOK_NOT _Expression   { $$ = new_un_op($2); }
;

_BinaryOperation:
    TOK_AND   _Expression   _Expression   { $$ = new_bin_op(TOK_AND, $2, $3); }
  | TOK_OR    _Expression   _Expression   { $$ = new_bin_op(TOK_OR,  $2, $3); }
  | TOK_ADD   _Expression   _Expression   { $$ = new_bin_op(TOK_ADD, $2, $3); }
  | TOK_SUB   _Expression   _Expression   { $$ = new_bin_op(TOK_SUB, $2, $3); }
  | TOK_MUL   _Expression   _Expression   { $$ = new_bin_op(TOK_MUL, $2, $3); }
  | TOK_DIV   _Expression   _Expression   { $$ = new_bin_op(TOK_DIV, $2, $3); }
  | TOK_EQ    _Expression   _Expression   { $$ = new_bin_op(TOK_EQ,  $2, $3); }
  | TOK_LT    _Expression   _Expression   { $$ = new_bin_op(TOK_LT,  $2, $3); }
;

_Function:
    _UnaryOperation    { $$ = new_un_fun($1);  }
  | _BinaryOperation   { $$ = new_bin_fun($1); }


_Expression:
    TRUE                { $$ = new_bool(true);   }
  | FALSE               { $$ = new_bool(false);  }
  | INT                 { $$ = new_int($1);      }
  | IDENT               { $$ = new_ident($1);    }
  | '(' _Function ')'   { $$ = new_function($2); }
;

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
    yyout = fopen(replace_str(argv[i], ".mps", ".out"), "w");

    fclose(yyout);
  }
  return EXIT_SUCCESS;
}
