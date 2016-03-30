#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "ast_access.h"
#include "aps_lan.tab.h"

struct _box {
  int type;
  union {
    bool bvalue;
    int value;
  } content;
};

typedef struct _environnement {
  TypeExpression *t_expr;
  char *name;
  struct _box value;
  bool constant;
  struct _environnement *next;
} Environnement;

void print_env();

Environnement *add_env(Environnement *env, Declaration *value);
Environnement *fetch_env(Environnement *env, const char *name);
void update_env(Environnement *env, const char *name, Expression *expr);
void free_env(Environnement *env);

void eval_program(Program *program);
void eval_command(Command *cmd);
void eval_stat(Stat *stat);
void eval_if(Expression *cond, Program *right, Program *wrong);
void eval_while(Expression *cond, Program *body);

struct _box eval_function(Function *fun);
struct _box eval_unary(UnaryOperation *un_op);
struct _box eval_binary(BinaryOperation *bin_op);
struct _box eval_expr(Expression *expr);
