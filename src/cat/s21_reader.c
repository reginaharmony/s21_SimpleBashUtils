#include "s21_cat.h"

void handle_errors(char *argv[], opt *options, char *name_file) {
  if (!options) ERR_CALL(ERR_OPT);
  if (!name_file) ERR_CALL(ERR_NAME);
  FILE *fp = fopen(name_file, "r");
  if (!fp) fprintf(stderr, ERR_FILE, argv[0], name_file), exit(EXIT_FAILURE);
  fclose(fp);
}

void initialize_variables(int *last, int *c, int *cnt_str, int *cnt_none) {
  *last = '\n';
  *c = 0;
  *cnt_str = 0;
  *cnt_none = 0;
}

void process_chars(int c, int *last, int *cnt_none, opt *options, int *cnt_str) {
  ARG_CHECK
  *cnt_none = 0;
  if (*last == '\n' && ((options->b && c != '\n') || options->n))
    printf("%6d\t", ++(*cnt_str));
  if (options->s && c == '\n' && *last == '\n') (*cnt_none)++;
  if (options->e && c == '\n') printf("$");
  if (options->t && c == '\t') printf("^"), c = 'I';
  if (options->v && c == DEL) printf("^"), c -= NONPRINT;
  if (options->v && c < ' ' && c != '\t' && c != '\n')
    printf("^"), c += NONPRINT;

  printf("%c", c);
  *last = c;
}

void reader(char *argv[], opt *options, char *name_file) {
  handle_errors(argv, options, name_file);
  int last, c, cnt_str, cnt_none;
  initialize_variables(&last, &c, &cnt_str, &cnt_none);
  FILE *fp = fopen(name_file, "r");
  while (!feof(fp)) {
    c = fgetc(fp);
    process_chars(c, &last, &cnt_none, options, &cnt_str);
  }
  fclose(fp);
}
