#include "ast_print.h"

// Printing functions for Prolog. Print a Prolog sequence.

void print_program(FILE *yyout, Program *prog) {
  fprintf(yyout, "[");
  print_commands(yyout, get_prog_content(prog));
  fprintf(yyout, "]");
}

void print_commands(FILE *yyout, Commands *cmds) {
  print_command(yyout, get_command(cmds));
  if (get_commands(cmds) != NULL) {
    fprintf(yyout, ",");
    print_commands(yyout, get_commands(cmds));
  }
}

void print_command(FILE *yyout, Command *cmd) {
  if (get_command_type(cmd) == DECL)
    print_declaration(yyout, get_declaration(cmd));
  else if (get_command_type(cmd) == STAT)
    print_stat(yyout, get_stat(cmd));
}

void print_declaration(FILE *yyout, Declaration *decl) {
  if (get_declaration_type(decl) == TOK_CONST) {
    fprintf(yyout, "const(%s,", get_declaration_name(decl));
    print_expression(yyout, get_declaration_expression(decl));
  } else if (get_declaration_type(decl) == TOK_VAR) {
    fprintf(yyout, "var(%s,", get_declaration_name(decl));
    print_type_expression(yyout, get_declaration_type_expression(decl));
  }
  fprintf(yyout, ")");
}

void print_stat(FILE *yyout, Stat *stat) {
  if (get_stat_type(stat) == TOK_SET) {
    fprintf(yyout, "set(%s,", get_set_ident(stat));
    print_expression(yyout, get_set_expression(stat));
  } else if (get_stat_type(stat) == TOK_IF) {
    fprintf(yyout, "if(");
    print_expression(yyout, get_if_cond(stat));
    fprintf(yyout, ",");
    print_program(yyout, get_if_right(stat));
    fprintf(yyout, ",");
    print_program(yyout, get_if_wrong(stat));
  } else if (get_stat_type(stat) == TOK_WHILE) {
    fprintf(yyout, "while(");
    print_expression(yyout, get_while_cond(stat));
    fprintf(yyout, ", ");
      print_program(yyout, get_while_body(stat));
  }
  fprintf(yyout, ")");
}

void print_expression(FILE *yyout, Expression *expr) {
  switch(get_expression_type(expr)) {
  case BOOL:
    if (get_bool_value(expr) == true)
      fprintf(yyout, "true");
    else
      fprintf(yyout, "false");
    break;
  case INT:
    fprintf(yyout, "%d", get_int_value(expr));
    break;
  case IDENT:
    fprintf(yyout, "%s", get_ident_value(expr));
    break;
  case FUN:
    print_function(yyout, get_function_value(expr));
    break;
  }
}

void print_type_expression(FILE *yyout, TypeExpression *t_expr) {
  if (get_type_expression_type(t_expr) == TYPE_BOOL)
    fprintf(yyout, "bool");
  else if (get_type_expression_type(t_expr) == TYPE_INT)
    fprintf(yyout, "int");
}

void print_function(FILE *yyout, Function *fun) {
  fprintf(yyout, "app(");
  if (get_function_type(fun) == UNARY)
    print_unary_operation(yyout, get_unary_operation(fun));
  else if (get_function_type(fun) == BINARY)
    print_binary_operation(yyout, get_binary_operation(fun));
  fprintf(yyout, ")");
}

void print_unary_operation(FILE *yyout, UnaryOperation *un_op) {
  if (get_unary_operation_type(un_op) == TOK_NOT) {
    fprintf(yyout, "not,[");
    print_expression(yyout, get_unary_operation_expression(un_op));
    fprintf(yyout, "]");
  }
}

void print_binary_operation(FILE *yyout, BinaryOperation *bin_op) {
  switch (get_binary_operation_type(bin_op)) {
  case TOK_AND:
    fprintf(yyout, "and,[");
    break;
  case TOK_OR:
    fprintf(yyout, "or,[");
    break;
  case TOK_ADD:
    fprintf(yyout, "add,[");
    break;
  case TOK_SUB:
    fprintf(yyout, "sub,[");
    break;
  case TOK_MUL:
    fprintf(yyout, "mul,[");
    break;
  case TOK_DIV:
    fprintf(yyout, "div,[");
    break;
  case TOK_EQ:
    fprintf(yyout, "eq,[");
    break;
  case TOK_LT:
    fprintf(yyout, "lt,[");
    break;
  }
  print_expression(yyout, get_binary_operation_first(bin_op));
  fprintf(yyout, ",");
  print_expression(yyout, get_binary_operation_second(bin_op));
  fprintf(yyout, "]");
}
