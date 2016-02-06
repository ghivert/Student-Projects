#include <stdlib.h>

#include "ast.h"
#include "aps_lan.tab.h"

// Functions for easy manipulation of AST.

// Creates a new Program.
Program *new_prog(Commands *content) {
  Program *r_prog = malloc(sizeof *r_prog);
  r_prog->content = content;
  return r_prog;
}

// Creates a new Commands.
Commands *new_commands(Command *content, Commands *next) {
  Commands *r_commands = malloc(sizeof *r_commands);
  r_commands->content = content;
  r_commands->next = next;
  return r_commands;
}

// Creates a new Declaration.
Command *new_declaration(Declaration *decl) {
  Command *r_command = malloc(sizeof *r_command);
  r_command->token = DECL;
  r_command->content.decl = decl;
  return r_command;
}

// Creates a new Stat.
Command *new_stat(Stat *stat) {
  Command *r_command = malloc(sizeof *r_command);
  r_command->token = STAT;
  r_command->content.stat = stat;
  return r_command;
}

// Creates a new Const.
Declaration *new_const(char *name, Expression *content) {
  Declaration *r_decl = malloc(sizeof *r_decl);
  r_decl->token = TOK_CONST;
  r_decl->name = name;
  r_decl->content.expr = content;
  return r_decl;
}

// Creates a new Var.
Declaration *new_var(char *name, TypeExpression *content) {
  Declaration *r_decl = malloc(sizeof *r_decl);
  r_decl->token = TOK_VAR;
  r_decl->name = name;
  r_decl->content.t_expr = content;
  return r_decl;
}

// Creates new TypeExpression.
TypeExpression *new_type_expression(int type) {
  TypeExpression *r_texpr = malloc(sizeof *r_texpr);
  r_texpr->token = type;
  return r_texpr;
}

// Creates a new Set.
Stat *new_set(char *ident, Expression *expr) {
  Stat *r_set = malloc(sizeof *r_set);
  r_set->token = TOK_SET;
  r_set->content.set.ident = ident;
  r_set->content.set.expr = expr;
  return r_set;
}

// Creates a new Conditionnal.
Stat *new_cond(Expression *cond, Program *right, Program *wrong) {
  Stat *r_cond = malloc(sizeof *r_cond);
  r_cond->token = TOK_IF;
  r_cond->content.fi.cond = cond;
  r_cond->content.fi.right = right;
  r_cond->content.fi.wrong = wrong;
  return r_cond;
}

// Creates a new While.
Stat *new_loop(Expression *cond, Program *body) {
  Stat *r_loop = malloc(sizeof *r_loop);
  r_loop->token = TOK_WHILE;
  r_loop->content.loop.cond = cond;
  r_loop->content.loop.body = body;
  return r_loop;
}

// Creates a new UnaryOperation.
UnaryOperation *new_un_op(Expression *expr) {
  UnaryOperation *r_un_op = malloc(sizeof *r_un_op);
  r_un_op->token = TOK_NOT;
  r_un_op->expr = expr;
  return r_un_op;
}

// Creates a new BinaryOperation.
BinaryOperation *new_bin_op(int type, Expression *first, Expression *second) {
  BinaryOperation *r_bin = malloc(sizeof *r_bin);
  r_bin->token = type;
  r_bin->expr_first = first;
  r_bin->expr_second = second;
  return r_bin;
}

// Creates a new Bool.
Expression *new_bool(bool value) {
  Expression *r_bool = malloc(sizeof *r_bool);
  r_bool->token = BOOL;
  r_bool->content.bvalue = value;
  return r_bool;
}

// Creates a new Int.
Expression *new_int(int value) {
  Expression *r_int = malloc(sizeof *r_int);
  r_int->token = INT;
  r_int->content.ivalue = value;
  return r_int;
}

// Creates a new Ident.
Expression *new_ident(char *name) {
  Expression *r_ident = malloc(sizeof *r_ident);
  r_ident->token = IDENT;
  r_ident->content.name = name;
  return r_ident;
}

// Creates a new Function.
Expression *new_function(Function *fun) {
  Expression *r_fun = malloc(sizeof *r_fun);
  r_fun->token = FUN;
  r_fun->content.fun = fun;
  return r_fun;
}

// Creates a new Unary Function.
Function *new_un_fun(UnaryOperation *un_op) {
  Function *r_un_fun = malloc(sizeof *r_un_fun);
  r_un_fun->token = UNARY;
  r_un_fun->content.un_op = un_op;
  return r_un_fun;
}

// Creates a new Binary Function.
Function *new_bin_fun(BinaryOperation *bin_op) {
  Function *r_bin_fun = malloc(sizeof *r_bin_fun);
  r_bin_fun->token = BINARY;
  r_bin_fun->content.bin_op = bin_op;
  return r_bin_fun;
}

// Free functions for all types.

void free_fun(Function *fun) {
  if (fun->token == UNARY)
    free_un_op(fun->content.un_op);
  else if (fun->token == BINARY)
    free_bin_op(fun->content.bin_op);
  free(fun);
}

void free_expression(Expression *expr) {
  if (expr->token == FUN)
    free_fun(expr->content.fun);
  else if (expr->token == IDENT)
    free(expr->content.name);
  free(expr);
}

void free_bin_op(BinaryOperation *bin_op) {
  free_expression(bin_op->expr_first);
  free_expression(bin_op->expr_second);
  free(bin_op);
}

void free_un_op(UnaryOperation *un_op) {
  free_expression(un_op->expr);
  free(un_op);
}

void free_stat(Stat *stat) {
  if (stat->token == TOK_SET) {
    free(stat->content.set.ident);
    free_expression(stat->content.set.expr);
  } else if (stat->token == TOK_IF) {
    free_expression(stat->content.fi.cond);
    free_program(stat->content.fi.right);
    free_program(stat->content.fi.wrong);
  } else if (stat->token == TOK_WHILE) {
    free_expression(stat->content.loop.cond);
    free_program(stat->content.loop.body);
  }
  free(stat);
}

void free_type_expression(TypeExpression *t_expr) {
  free(t_expr);
}

void free_declaration(Declaration *decl) {
  if (decl->token == TOK_CONST)
    free_expression(decl->content.expr);
  else if (decl->token == TOK_VAR)
    free_type_expression(decl->content.t_expr);
  free(decl->name);
  free(decl);
}

void free_command(Command *command) {
  if (command->token == DECL)
    free_declaration(command->content.decl);
  else if (command->token == STAT)
    free_stat(command->content.stat);
  free(command);
}

void free_commands(Commands *commands) {
  free_command(commands->content);
  if (commands->next)
    free_commands(commands->next);
  free(commands);
}

void free_program(Program *prog) {
  free_commands(prog->content);
  free(prog);
}
