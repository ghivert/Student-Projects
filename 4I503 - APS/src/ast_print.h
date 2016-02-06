#ifndef __AST_PRINT__
#define __AST_PRINT__

#include <stdio.h>
#include <stdbool.h>

#include "ast.h"
#include "ast_access.h"
#include "aps_lan.tab.h"

void print_program(FILE *yyout, Program *prog);
void print_commands(FILE *yyout, Commands *cmds);
void print_command(FILE *yyout, Command *cmd);
void print_declaration(FILE *yyout, Declaration *decl);
void print_stat(FILE *yyout, Stat *stat);
void print_expression(FILE *yyout, Expression *expr);
void print_type_expression(FILE *yyout, TypeExpression *t_expr);
void print_function(FILE *yyout, Function *fun);
void print_unary_operation(FILE *yyout, UnaryOperation *un_op);
void print_binary_operation(FILE *yyout, BinaryOperation *bin_op);

#endif
