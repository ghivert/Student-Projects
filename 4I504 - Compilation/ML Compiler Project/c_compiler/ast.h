#pragma once

#include <stdbool.h>

typedef enum {
  TYPE_NIL,
  TYPE_BOOL,
  TYPE_NUM,
  TYPE_VAR,
  TYPE_FUN,
  TYPE_APPLY,
  TYPE_COND,
  TYPE_MATCH,
  TYPE_CONS,
  TYPE_ADD,
  TYPE_MUL,
  TYPE_SUB,
  TYPE_LEQ,
  TYPE_GEQ,
  TYPE_LET,
  TYPE_LET_R,
  TYPE_NIL_L,
  TYPE_CONS_L,
  TYPE_FULL_L
} type_t;

typedef struct boolean     bool_t;
typedef struct num         num_t;
typedef struct var         var_t;
typedef struct fun         fun_t;
typedef struct apply       apply_t;
typedef struct cond        cond_t;
typedef struct match       match_t;
typedef struct cons        cons_t;
typedef struct bin_op      bin_op_t;
typedef struct let         let_t;
typedef struct nil_list    nil_list_t;
typedef struct cons_list   cons_list_t;
typedef struct full_list   full_list_t;

struct boolean {
  int type;
  bool value;
};

struct num {
  int type;
  int value;
};

struct var {
  int type;
  char *name;
};

struct fun {
  type_t type;
  char *args;
  union ast *body;
};

struct apply {
  type_t type;
  union ast *fun;
  union ast *arg;
};

struct cond {
  type_t type;
  union ast *cond;
  union ast *then;
  union ast *elsse;
};

struct match {
  type_t type;
  union ast *expr;
  union ast *list;
};

struct cons {
  type_t type;
  union ast *head;
  union ast *tail;
};

struct bin_op {
  type_t type;
  union ast *left;
  union ast *right;
};

struct let {
  type_t type;
  char *name;
  union ast *value;
  union ast *body;
};

struct nil_list {
  type_t type;
  union ast *body;
};

struct cons_list {
  type_t type;
  union ast *cons;
  union ast *body;
};

struct full_list {
  type_t type;
  union ast *first;
  union ast *second;
};

typedef union ast {
  type_t type;
  bool_t        boolean;
  num_t         num;
  var_t         var;
  fun_t         fun;
  apply_t       apply;
  cond_t        cond;
  match_t       match;
  cons_t        cons;
  bin_op_t      bin_op;
  let_t         let;
  nil_list_t    nil_l;
  cons_list_t   cons_l;
  full_list_t   full_l;
} ast_t;
