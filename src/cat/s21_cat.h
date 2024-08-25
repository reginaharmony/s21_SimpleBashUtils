#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int T;
  int E;
} opt;

void reader(char *argv[], opt *options, char *name_file);
void flagger(int argc, char *argv[], opt *options);

//========================================================= reader block

#define DEL 127
#define RETURN 13
#define BACKSPACE 8
#define NONPRINT 64

#define ARG_CHECK       \
  if (c == EOF) return; \
  if (options->s && c == '\n' && *last == '\n' && *cnt_none >= 1) return;

#define ERR_OPT "%s: Invalid options pointer\n"
#define ERR_NAME "%s: No file name provided\n"
#define ERR_FILE "%s: %s: No such file or directory\n"

#define ERR_CALL(ERR_MSG) fprintf(stderr, ERR_MSG, argv[0]), exit(EXIT_FAILURE)

#endif  // S21_CAT_H
