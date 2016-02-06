#include "ast_access.h"

Commands *get_prog_content(Program *prog) {
  return prog->content;
}

Command *get_command(Commands *cmds) {
  return cmds->content;
}

Commands *get_commands(Commands *cmds) {
  return cmds->next;
}

int get_command_type(Command *cmd) {
  return cmd->token;
}

Declaration *get_declaration(Command *cmd) {
  return cmd->content.decl;
}

Stat *get_stat(Command *cmd) {
  return cmd->content.stat;
}

int get_declaration_type(Declaration *decl) {
  return decl->token;
}

char *get_declaration_name(Declaration *decl) {
  return decl->name;
}

Expression *get_declaration_expression(Declaration *decl) {
  return decl->content.expr;
}

TypeExpression *get_declaration_type_expression(Declaration *decl) {
  return decl->content.t_expr;
}

int get_stat_type(Stat *stat) {
  return stat->token;
}

char *get_set_ident(Stat *set) {
  return set->content.set.ident;
}

Expression *get_set_expression(Stat *set) {
  return set->content.set.expr;
}

Expression *get_if_cond(Stat *fi) {
  return fi->content.fi.cond;
}

Program *get_if_right(Stat *fi) {
  return fi->content.fi.right;
}

Program *get_if_wrong(Stat *fi) {
  return fi->content.fi.wrong;
}

Expression *get_while_cond(Stat *loop) {
  return loop->content.loop.cond;
}

Program *get_while_body(Stat *loop) {
  return loop->content.loop.body;
}

int get_type_expression_type(TypeExpression *t_expr) {
  return t_expr->token;
}

int get_expression_type(Expression *expr) {
  return expr->token;
}

bool get_bool_value(Expression *expr) {
  return expr->content.bvalue;
}

int get_int_value(Expression *expr) {
  return expr->content.ivalue;
}

char *get_ident_value(Expression *expr) {
  return expr->content.name;
}

Function *get_function_value(Expression *expr) {
  return expr->content.fun;
}

int get_function_type(Function *fun) {
  return fun->token;
}

UnaryOperation *get_unary_operation(Function *fun) {
  return fun->content.un_op;
}

BinaryOperation *get_binary_operation(Function *fun) {
  return fun->content.bin_op;
}

int get_unary_operation_type(UnaryOperation *un_op) {
  return un_op->token;
}

Expression *get_unary_operation_expression(UnaryOperation *un_op) {
  return un_op->expr;
}

int get_binary_operation_type(BinaryOperation *bin_op) {
  return bin_op->token;
}

Expression *get_binary_operation_first(BinaryOperation *bin_op) {
  return bin_op->expr_first;
}

Expression *get_binary_operation_second(BinaryOperation *bin_op) {
  return bin_op->expr_second;
}

char *replace_str(char *str, char *orig, char *rep) {
  static char buffer[4096];
  char *p;

  if (!(p = strstr(str, orig)))
    return str;

  strncpy(buffer, str, p - str);
  buffer[p - str] = '\0';
  sprintf(buffer + (p - str), "%s%s", rep, p + strlen(orig));
  return buffer;
}
