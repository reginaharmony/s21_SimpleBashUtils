#ifndef SRC_S21_GREP_H_
#define SRC_S21_GREP_H_

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 1024

typedef struct options {
  int err;
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int files;
  int e_count;
  int reg_files;
  char pattern[BUF];
  char *files_list[BUF];
  char *reg_files_list[BUF];
} opt;

void handle_errors(int err, char text[BUF], int s);
void get_options(const int argc, char **const argv);
void read_files(const opt options, int mode);
void process_file(const opt flags, FILE **file, char filename[BUF]);

//========================================================= error handling

#define ERR_REG "Regex match failed\n"
#define ERR_USE "Usage: s21_grep [OPTION]... PATTERNS [FILE]...\n"
#define ERR_COMP "Could not compile regex\n"
#define ERR_FLAG "Wrong flags\n"
#define ERR_FILE "grep: %s: No such file or directory\n", text

#define ERR_CALL(ERR_MSG) fprintf(stderr, ERR_MSG)

#endif  // SRC_S21_GREP_H_
