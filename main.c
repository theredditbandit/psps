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

  while (1) {
    char *input = readline("psps 🐱 >");
    add_history(input);

    /*Echo the input back */
    printf("No you're a %s\n", input);

    free(input);
  }
  return 0;
}
