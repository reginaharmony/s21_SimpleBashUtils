#include "s21_cat.h"

// Define a function pointer type for the option handlers
typedef void (*option_handler)(opt *options);

// Define the option handlers
void handle_b(opt *options) { options->b = 1; }
void handle_n(opt *options) { options->n = 1; }
void handle_s(opt *options) { options->s = 1; }
void handle_E(opt *options) { options->e = 1; }
void handle_T(opt *options) { options->t = 1; }
void handle_v(opt *options) { options->v = 1; }
void handle_t(opt *options) {
  options->t = 1;
  options->v = 1;
}
void handle_e(opt *options) {
  options->e = 1;
  options->v = 1;
}

option_handler option_handlers[] = {
    [0] = NULL,  // for no option
    ['b'] = handle_b, ['e'] = handle_e, ['n'] = handle_n, ['s'] = handle_s,
    ['t'] = handle_t, ['E'] = handle_E, ['T'] = handle_T, ['v'] = handle_v};

static struct option long_opt[] = {
    {"number-nonblank", 0, 0, 'b'},
    {"number", 0, 0, 'n'},
    {"squeeze-blank", 0, 0, 's'},
    {0, 0, 0, 0},
};

void flagger(int argc, char *argv[], opt *options) {
  int opt;
  while ((opt = getopt_long(argc, argv, "+benstvTE", long_opt, NULL)) != -1) {
    if (option_handlers[opt])
      option_handlers[opt](options);
    else
      fprintf(stderr, "Usage: ./s21_cat  [-benstvET] [file ...]\n");
  }
  if (options->b && options->n) options->n = 0;
}
