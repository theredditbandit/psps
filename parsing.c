#include "mpc.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <string.h>

static char buffer[2048];
/*Fake readline function*/
char *readline(char *prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char *cpy = malloc(strlen(buffer) + 1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy) - 1] = '\0';
  return cpy;
}
/*Fake add history function*/
void add_history(char *unused) {}
#else
// Install editline with `sudo apt-get install libedit-dev`
#include <editline/history.h>
#include <editline/readline.h>
#endif

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  /* Print version and exit information */
  puts("psps(lisp) Version 0.0.1");
  puts("Press Ctrl+c to Exit\n");

  mpc_parser_t *Number = mpc_new("number");
  mpc_parser_t *Operator = mpc_new("operator");
  mpc_parser_t *Expr = mpc_new("expr");
  mpc_parser_t *Lispy = mpc_new("lispy");

  mpca_lang(
      MPCA_LANG_DEFAULT,
      "                                                                                         \
    number   : /-?[0-9]+\\.?[0-9]*/ ;                                                           \
    operator : '+' | '-' | '*' | '/' | '%'| \"add\" | \"sub\" | \"mul\" | \"div\" | \"mod\";    \
    expr     : <number> | '(' <operator> <expr>+ ')' ;                                          \
    lispy    : /^/ <operator> <expr>+ /$/ ;                                                     \
  ",
      Number, Operator, Expr, Lispy);

  // REPL
  while (1) {
    char *input = readline("psps 🐱 >");
    add_history(input);

    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Lispy, &r)) {
      /* on success , print AST*/
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      // print error
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    free(input);
  }
  mpc_cleanup(4, Number, Operator, Expr, Lispy);
  return 0;
}
