#include <stdbool.h>

typedef struct _program           Program;
typedef struct _commands          Commands;
typedef struct _command           Command;
typedef struct _declaration       Declaration;
typedef struct _type_expression   TypeExpression;
typedef struct _stat              Stat;
typedef struct _unary_operation   UnaryOperation;
typedef struct _binary_operation  BinaryOperation;
typedef struct _expression        Expression;
typedef struct _function          Function;

// Function for easy creation of AST.
Program  *new_prog(Commands *content);
Commands *new_commands(Command *content, Commands *next);
Command  *new_declaration(Declaration *decl);
Command  *new_stat(Stat *stat);

Declaration *new_const(char *name, Expression *content);
Declaration *new_var(char *name, TypeExpression *content);

TypeExpression *new_type_expression(int type);

Stat *new_set(char *ident, Expression *expr);
Stat *new_cond(Expression *cond, Program *right, Program *wrong);
Stat *new_loop(Expression *cond, Program *body);

UnaryOperation  *new_un_op(Expression *expr);
BinaryOperation *new_bin_op(int type, Expression *first, Expression *second);

Expression *new_bool(bool value);
Expression *new_int(int value);
Expression *new_ident(char *name);
Expression *new_function(Function *fun);

Function *new_un_fun(UnaryOperation *un_op);
Function *new_bin_fun(BinaryOperation *bin_op);

// Function for easy free of AST.
void free_fun(Function *fun);
void free_expression(Expression *expr);
void free_bin_op(BinaryOperation *bin_op);
void free_un_op(UnaryOperation *un_op);
void free_stat(Stat *stat);
void free_type_expression(TypeExpression *t_expr);
void free_declaration(Declaration *decl);
void free_command(Command *command);
void free_commands(Commands *commands);
void free_program(Program *prog);

struct _function {
  int token;
  union {
    UnaryOperation*  un_op;
    BinaryOperation* bin_op;
  } content;
};

struct _expression {
  int token;
  union {
    bool bvalue;
    int  ivalue;
    char *name;
    Function *fun;
  } content;
};

struct _binary_operation {
  int token;
  Expression *expr_first;
  Expression *expr_second;
};

struct _unary_operation {
  int token;
  Expression *expr;
};

struct _stat {
  int token;
  union {
    struct {
      char *ident;
      Expression *expr;
    } set;
    struct {
      Expression *cond;
      Program *right;
      Program *wrong;
    } fi;
    struct {
      Expression *cond;
      Program *body;
    } loop;
  } content;
};

struct _type_expression {
  int token;
};

struct _declaration {
  int token;
  char *name;
  union {
    Expression *expr;
    TypeExpression *t_expr;
  } content;
};

struct _command {
  int token;
  union {
    Declaration *decl;
    Stat *stat;
  } content;
};

struct _commands {
  Command *content;
  struct _commands *next;
};

struct _program {
  Commands *content;
};
