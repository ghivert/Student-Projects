#include "ast_print.h"

void print_tab(FILE *out, int tab) {
  for (int i = 0; i < tab; i++)
    fprintf(out, " ");
}

void print_program(FILE *yyout, ast_t *program, int tab, bool print) {
  fprintf(yyout, "(");
  switch (program->type) {
    case TYPE_NIL:
    if (print) print_tab(yyout, tab);
    printf("Nil");
    break;
    case TYPE_BOOL:
    if (print) print_tab(yyout, tab);
    if (program->boolean.value) fprintf(yyout, "true");
    else fprintf(yyout, "false");
    break;
    case TYPE_NUM:
    if (print) print_tab(yyout, tab);
    fprintf(yyout, "%d", program->num.value);
    break;
    case TYPE_VAR:
    if (print) print_tab(yyout, tab);
    fprintf(yyout, "%s", program->var.name);
    break;
    case TYPE_FUN:
    if (print) print_tab(yyout, tab);
    fprintf(yyout, "function %s ->\n", program->fun.args);
    print_tab(yyout, tab + 2);
    print_program(yyout, program->fun.body, tab + 2, false);
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
    if (print) print_tab(yyout, tab);
    fprintf(yyout, "match ");
    print_program(yyout, program->match.expr, tab, false);
    fprintf(yyout, "with\n");
    print_program(yyout, program->match.expr, tab, true);
    break;
    case TYPE_CONS:
    if (print) print_tab(yyout, tab);
    print_program(yyout, program->cons.head, tab, false);
    fprintf(yyout, " :: ");
    print_program(yyout, program->cons.tail, tab, false);
    break;
    case TYPE_ADD:
    print_program(yyout, program->bin_op.left, tab, false);
    fprintf(yyout, " + ");
    print_program(yyout, program->bin_op.right, tab, false);
    break;
    case TYPE_MUL:
    print_program(yyout, program->bin_op.left, tab, false);
    fprintf(yyout, " * ");
    print_program(yyout, program->bin_op.right, tab, false);
    break;
    case TYPE_SUB:
    print_program(yyout, program->bin_op.left, tab, false);
    fprintf(yyout, " - ");
    print_program(yyout, program->bin_op.right, tab, false);
    break;
    case TYPE_LEQ:
    print_program(yyout, program->bin_op.left, tab, false);
    fprintf(yyout, " <= ");
    print_program(yyout, program->bin_op.right, tab, false);
    break;
    case TYPE_GEQ:
    print_program(yyout, program->bin_op.left, tab, false);
    fprintf(yyout, " >= ");
    print_program(yyout, program->bin_op.right, tab, false);
    break;
    case TYPE_LET:
    fprintf(yyout, "let %s = ", program->let.name);
    print_program(yyout, program->let.value, tab + 2, false);
    print_tab(yyout, tab);
    fprintf(yyout, "\nin\n");
    print_program(yyout, program->let.body, tab, true);
    break;
    case TYPE_LET_R:
    fprintf(yyout, "let rec %s = ", program->let.name);
    print_program(yyout, program->let.value, tab + 2, false);
    print_tab(yyout, tab);
    fprintf(yyout, "\nin\n");
    print_program(yyout, program->let.body, tab, true);
    break;
    case TYPE_NIL_L:

    break;
    case TYPE_CONS_L:

    break;
    case TYPE_FULL_L:

    break;
  }
  fprintf(yyout, ")");
}
