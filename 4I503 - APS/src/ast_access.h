#ifndef __AST_ACCESS__
#define __AST_ACCESS__

#include <string.h>
#include <stdio.h>

#include "ast.h"

int get_command_type(Command *cmd);
int get_declaration_type(Declaration *decl);
int get_stat_type(Stat *stat);
int get_type_expression_type(TypeExpression *t_expr);
int get_expression_type(Expression *expr);
int get_int_value(Expression *expr);
int get_function_type(Function *fun);
int get_unary_operation_type(UnaryOperation *un_op);
int get_binary_operation_type(BinaryOperation *bin_op);

char *get_declaration_name(Declaration *decl);
char *get_set_ident(Stat *set);
char *get_ident_value(Expression *expr);

bool get_bool_value(Expression *expr);

Program *get_if_right(Stat *fi);
Program *get_if_wrong(Stat *fi);
Program *get_while_body(Stat *loop);

Commands *get_prog_content(Program *prog);
Commands *get_commands(Commands *cmds);
Command  *get_command(Commands *cmds);

Stat *get_stat(Command *cmd);
Function *get_function_value(Expression *expr);
Declaration *get_declaration(Command *cmd);
TypeExpression *get_declaration_type_expression(Declaration *decl);
UnaryOperation *get_unary_operation(Function *fun);
BinaryOperation *get_binary_operation(Function *fun);

Expression *get_declaration_expression(Declaration *decl);
Expression *get_set_expression(Stat *set);
Expression *get_if_cond(Stat *fi);
Expression *get_while_cond(Stat *loop);
Expression *get_unary_operation_expression(UnaryOperation *un_op);
Expression *get_binary_operation_first(BinaryOperation *bin_op);
Expression *get_binary_operation_second(BinaryOperation *bin_op);

char *replace_str(char *str, char *orig, char *rep);

#endif
