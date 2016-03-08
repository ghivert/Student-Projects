#pragma once

#include <stdlib.h>

#include "ast.h"

ast_t *new_function(char *args, ast_t *body);
ast_t *new_let(char *name, ast_t *value, ast_t *body);
ast_t *new_nil();
ast_t *new_true();
ast_t *new_false();
ast_t *new_var(char *name);
ast_t *new_num(int value);
ast_t *new_apply(ast_t *fun, ast_t *arg);
ast_t *new_cons(ast_t *head, ast_t *tail);
ast_t *new_match(ast_t *expr, ast_t *list);
ast_t *new_bin(type_t type, ast_t *left, ast_t *right);
ast_t *new_cond(ast_t *cond, ast_t *then, ast_t *elsse);
