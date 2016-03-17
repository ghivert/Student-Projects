#pragma once

#include <stdio.h>

#include "ast.h"

void print_program(FILE *yyout, ast_t *program, int tab, bool print);
