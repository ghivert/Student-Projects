%{
  #include <stdio.h>
  #include <stdlib.h>
%}

%union {
  int value;
  char *name;
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

// Booleans.
%token TRUE
%token FALSE

// Constants.
%token <name>  IDENT
%token <value> INT

%start Program

%%

Program:
  '[' Commands ']'
;

Commands:
    Command
  | Command ';' Commands
;

Command:
    Declaration
  | Stat
;

Declaration:
    TOK_CONST   IDENT   Expression       { printf("TOK_CONST, %s, ", $2); }
  | TOK_VAR     IDENT   TypeExpression   { printf("TOK_VAR, %s, ", $2); }
;

TypeExpression:
    TYPE_BOOL { printf(" TYPE_BOOL "); }
  | TYPE_INT  { printf(" TYPE_INT ");  }
;

Stat:
    TOK_SET     IDENT       Expression { printf(" TOK_SET "); }
  | TOK_IF      Expression  Program     Program {printf(" TOK_IF "); }
  | TOK_WHILE   Expression  Program { printf(" TOK_WHILE "); }
;

UnaryOperation:
    '(' TOK_NOT Expression ')' { printf(" TOK_NOT "); }
;

BinaryOperation:
    '(' TOK_AND   Expression   Expression ')' { printf(" TOK_AND "); }
  | '(' TOK_OR    Expression   Expression ')' { printf(" TOK_OR "); }
  | '(' TOK_ADD   Expression   Expression ')' { printf(" TOK_ADD "); }
  | '(' TOK_SUB   Expression   Expression ')' { printf(" TOK_SUB "); }
  | '(' TOK_MUL   Expression   Expression ')' { printf(" TOK_MUL "); }
  | '(' TOK_DIV   Expression   Expression ')' { printf(" TOK_DIV "); }
;

Expression:
    TRUE { printf(" TRUE "); }
  | FALSE { printf(" FALSE "); }
  | INT { printf(" INT %d ", $1); }
  | IDENT { printf(" IDENT %s ", $1); }
  | UnaryOperation
  | BinaryOperation
;

%%

int main(int argc, char *argv[]) {
  yyparse();
}
