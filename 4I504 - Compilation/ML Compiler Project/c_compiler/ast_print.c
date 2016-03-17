#include "ast_print.h"

void print_tab(FILE *out, int tab) {
  for (int i = 0; i < tab; i++)
    fprintf(out, " ");
}

void print_program(FILE *yyout, ast_t *program, int tab, bool print) {
  switch (program->type) {
    case TYPE_NIL:
    if (print) print_tab(yyout, tab);
    printf("Nil\n");
    break;
    case TYPE_BOOL:
    if (print) print_tab(yyout, tab);
    if (program->boolean.value) fprintf(yyout, "true\n");
    else fprintf(yyout, "false\n");
    break;
    case TYPE_NUM:
    if (print) print_tab(yyout, tab);
    fprintf(yyout, "%d\n", program->num.value);
    break;
    case TYPE_VAR:
    if (print) print_tab(yyout, tab);
    fprintf(yyout, "%s\n", program->var.name);
    break;
    case TYPE_FUN:
    if (print) print_tab(yyout, tab);
    fprintf(yyout, "function %s ->\n", program->fun.args);
    print_program(yyout, program->fun.body, tab + 2, true);
    break;
    case TYPE_APPLY:
    print_program(yyout, program->apply.fun, tab, true);
    print_program(yyout, program->apply.arg, tab, false);
    break;
    case TYPE_COND:
    if (print) print_tab(yyout, tab);
    fprintf(yyout, "if ");
    print_program(yyout, program->cond.cond, tab, false);
    print_program(yyout, program->cond.then, tab + 2, true);
    fprintf(yyout, "else ");
    print_program(yyout, program->cond.elsse, tab + 2, true);
    break;
    case TYPE_MATCH:
    
    break;
    case TYPE_CONS:

    break;
    case TYPE_ADD:

    break;
    case TYPE_MUL:

    break;
    case TYPE_SUB:

    break;
    case TYPE_LEQ:

    break;
    case TYPE_GEQ:

    break;
    case TYPE_LET:

    break;
    case TYPE_LET_R:

    break;
    case TYPE_NIL_L:

    break;
    case TYPE_CONS_L:

    break;
    case TYPE_FULL_L:

    break;
  }
}
