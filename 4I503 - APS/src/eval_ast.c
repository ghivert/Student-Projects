#include "eval_ast.h"

Environnement *env = NULL;


// Gestion of environment.
// Printing function.
void print_env_sub(Environnement *env) {
  if (env) {
    printf("%s: ", env->name);
    switch (env->value.type) {
      case BOOL:
      printf("%d\n", env->value.content.bvalue);
      break;
      case INT:
      printf("%d\n", env->value.content.value);
      break;
    }
    print_env_sub(env->next);
  }
}

void print_env() {
  if (env) {
    printf("************* ENV ************\n");
    print_env_sub(env);
    printf("******************************\n\n");
  } else {
    printf("Empty environment.\n\n");
  }
}

// Add an element to the env.
Environnement *add_env(Environnement *env, Declaration *value) {
  Environnement *new_env = malloc(sizeof *new_env);
  new_env->t_expr = value->t_expr;
  new_env->name = value->name;
  new_env->value = eval_expr(value->expr);
  new_env->constant = value->token == TOK_CONST ? true : false;
  new_env->next = env;
  return new_env;
}

// Free the entire environment.
void free_env(Environnement *env) {
  if (env->next) free_env(env->next);
  free(env);
}

// Fetch a variable in the environment.
Environnement *fetch_env(Environnement *env, const char *name) {
  if (!env) {
    fprintf(stderr, "Non existent variable %s.\nExiting.\n", name);
    exit(EXIT_FAILURE);
  }

  if (strcmp(name, env->name) == 0)
    return env;
  return fetch_env(env->next, name);
}

// Update a variable in the environment.
void update_env(Environnement *env, const char *name, Expression *expr) {
  Environnement *var = fetch_env(env, name);

  struct _box value = eval_expr(expr);

  if (var->t_expr->token != value.type) {
    printf("%d %d\n", var->t_expr->token, expr->token);
    fprintf(stderr, "(update) Type not concordant.\nExiting.\n");
    exit(EXIT_FAILURE);
  }

  if (var->constant == false)
    var->value = value;
  else {
    fprintf(stderr, "Trying to modify a constant var: %s...\n", var->name);
    exit(EXIT_FAILURE);
  }
}

// Eval the program.
void eval_program(Program *program) {
  Commands *instr = get_prog_content(program);

  while (instr != NULL) {
    eval_command(get_command(instr));

    instr = get_commands(instr);
  }
}

// Eval a command.
void eval_command(Command *cmd) {
  if (get_command_type(cmd) == DECL) {
    env = add_env(env, get_declaration(cmd));
  } else if (get_command_type(cmd) == STAT)
    eval_stat(get_stat(cmd));
}

// Eval a stat.
void eval_stat(Stat *stat) {
  if (get_stat_type(stat) == TOK_SET) {
    update_env(env, get_set_ident(stat), get_set_expression(stat));
  } else if (get_stat_type(stat) == TOK_IF) {
    eval_if(get_if_cond(stat), get_if_right(stat), get_if_wrong(stat));
  } else if (get_stat_type(stat) == TOK_WHILE) {
    eval_while(get_while_cond(stat), get_while_body(stat));
  }
}

// Eval an if expression.
void eval_if(Expression *cond, Program *right, Program *wrong) {
  struct _box truth;

  switch (get_expression_type(cond)) {
  case INT:
    fprintf(stderr, "That should not happen...\n");
    exit(EXIT_FAILURE);
    break;

  case IDENT: {
    Environnement *var = fetch_env(env, get_ident_value(cond));
    if (var->t_expr->token != BOOL) {
      fprintf(stderr, "Not concordant type. Exit.\n");
      exit(EXIT_FAILURE);
    }

    truth.content.bvalue = var->value.content.bvalue;
    truth.type = BOOL;
    break;
  }
  case FUN:
    truth = eval_function(get_function_value(cond));
    break;
  }

  if (truth.type != BOOL) {
    fprintf(stderr, "AAAAAAAAAAAaaaaaaargh...\n");
    exit(EXIT_FAILURE);
  }

  if (truth.content.bvalue) {
    // printf("(if) right side.\n");
    eval_program(right);
  }
  else {
    // printf("(if) wrong side.\n");
    eval_program(wrong);
  }
}

// Eval a loop.
void eval_while(Expression *cond, Program *body) {
  struct _box truth;

  switch (get_expression_type(cond)) {
    case INT:
    fprintf(stderr, "That should not happen...\n");
    exit(EXIT_FAILURE);
    break;

    case IDENT: {
      Environnement *var = fetch_env(env, get_ident_value(cond));
      if (var->t_expr->token != BOOL) {
        fprintf(stderr, "Not concordant type. Exit.\n");
        exit(EXIT_FAILURE);
      }

      truth.content.bvalue = var->value.content.bvalue;
      truth.type = BOOL;
      break;
    }
    case FUN:
    truth = eval_function(get_function_value(cond));
    break;
  }

  if (truth.type != BOOL) {
    fprintf(stderr, "AAAAAAAAAAAaaaaaaargh...\n");
    exit(EXIT_FAILURE);
  }

  if (truth.content.bvalue) {
    eval_program(body);
    eval_while(cond, body);
  }
}

// Eval a operation.
struct _box eval_function(Function *fun) {
  struct _box value;

  switch (get_function_type(fun)) {
    case UNARY:
    value = eval_unary(get_unary_operation(fun));
    break;
    case BINARY:
    value = eval_binary(get_binary_operation(fun));
    break;
  }
  return value;
}

// Eval unary operation.
struct _box eval_unary(UnaryOperation *un_op) {
  struct _box value;

  switch (get_unary_operation_type(un_op)) {
    case TOK_NOT:
    value = eval_expr(get_unary_operation_expression(un_op));
    if (value.type != BOOL) {
      fprintf(stderr, "AAAAAAAAAAAaaaaaaargh...\n");
      exit(EXIT_FAILURE);
    }
    value.content.bvalue = !value.content.bvalue;
  }
  return value;
}

// Eval binary operation.
struct _box eval_binary(BinaryOperation *bin_op) {
  Expression *e_first  = get_binary_operation_first(bin_op);
  Expression *e_second = get_binary_operation_second(bin_op);

  struct _box v_first  = eval_expr(e_first);
  struct _box v_second = eval_expr(e_second);

  switch (get_binary_operation_type(bin_op)) {
    case TOK_AND:
    if (v_first.type != BOOL || v_second.type != BOOL) {
      fprintf(stderr, "AAAAAAAAAAAaaaaaaargh...\n");
      exit(EXIT_FAILURE);
    }
    v_first.content.bvalue &= v_second.content.bvalue;
    break;

    case TOK_OR:
    if (v_first.type != BOOL || v_second.type != BOOL) {
      fprintf(stderr, "AAAAAAAAAAAaaaaaaargh...\n");
      exit(EXIT_FAILURE);
    }
    v_first.content.bvalue |= v_second.content.bvalue;
    break;

    case TOK_ADD:
    if (v_first.type != INT || v_second.type != INT) {
      fprintf(stderr, "AAAAAAAAAAAaaaaaaargh...\n");
      exit(EXIT_FAILURE);
    }
    v_first.content.value += v_second.content.value;
    break;

    case TOK_SUB:
    if (v_first.type != INT || v_second.type != INT) {
      fprintf(stderr, "AAAAAAAAAAAaaaaaaargh...\n");
      exit(EXIT_FAILURE);
    }
    v_first.content.value -= v_second.content.value;
    break;

    case TOK_MUL:
    if (v_first.type != INT || v_second.type != INT) {
      fprintf(stderr, "AAAAAAAAAAAaaaaaaargh...\n");
      exit(EXIT_FAILURE);
    }
    v_first.content.value *= v_second.content.value;
    break;

    case TOK_DIV:
    if (v_first.type != INT || v_second.type != INT) {
      fprintf(stderr, "AAAAAAAAAAAaaaaaaargh...\n");
      exit(EXIT_FAILURE);
    }
    v_first.content.value /= v_second.content.value;
    break;

    case TOK_EQ:
    if ((v_first.type == INT && v_second.type != INT) ||
        (v_first.type == BOOL && v_second.type != BOOL)) {
      fprintf(stderr, "AAAAAAAAAAAaaaaaaargh...\n");
      exit(EXIT_FAILURE);
    }
    switch (v_first.type) {
      case BOOL:
      v_first.content.bvalue = v_first.content.bvalue == v_second.content.bvalue ? true : false;
      break;
      case INT:
      v_first.content.bvalue = v_first.content.value == v_second.content.value ? true : false;
      v_first.type = BOOL;
      break;
    }
    break;

    case TOK_LT:
    if (v_first.type != INT || v_second.type != INT) {
      fprintf(stderr, "AAAAAAAAAAAaaaaaaargh...\n");
      exit(EXIT_FAILURE);
    }
    v_first.content.bvalue = v_first.content.value < v_second.content.value ? true : false;
    v_first.type = BOOL;
    break;
  }
  return v_first;
}

// Eval an expression.
struct _box eval_expr(Expression *expr) {
  struct _box value;

  switch (get_expression_type(expr)) {
    case BOOL:
    value.type = BOOL;
    value.content.bvalue = get_bool_value(expr);
    break;

    case IDENT: {
      Environnement *fetched = fetch_env(env, get_ident_value(expr));
      value.type = fetched->t_expr->token;
      switch(value.type) {
        case BOOL:
        value.content.bvalue = fetched->value.content.bvalue;
        break;
        case INT:
        value.content.value = fetched->value.content.value;
        break;
      }
    }
    break;

    case INT:
    value.type = INT;
    value.content.value = get_int_value(expr);
    break;

    case FUN:
    value = eval_function(get_function_value(expr));
    break;
  }

  return value;
}
