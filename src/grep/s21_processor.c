#include "s21_grep.h"

void handle_errors(int err, char text[BUF], int s) {
  if (!s) {
    err == 1   ? ERR_CALL(ERR_FILE)
    : err == 2 ? ERR_CALL(ERR_REG)
    : err == 3 ? ERR_CALL(ERR_COMP)
    : err == 4 ? ERR_CALL(ERR_USE)
    : err == 5 ? ERR_CALL(ERR_FLAG)
               : 0;
  }
}

void print_string(const opt options, const char *filename, int line_num,
                  const char *string, regmatch_t *pmatch) {
  // Print prefix
  if (options.files > 1 && !options.h &&
      !(options.e_count == 0 && options.files == 2))
    printf("%s:", filename);
  if (options.n) printf("%d:", line_num);

  // Print string
  if (!options.o) {
    printf("%s", string);
  } else if (!options.v) {
    printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
           &string[pmatch[0].rm_so]);
  }
}

void print_line(const opt options, const char *filename, int line_num,
                const char *string, regmatch_t *pmatch) {
  if (options.l || options.c) return;
  if ((string == NULL || string[strlen(string) - 1] != '\n') && !options.o &&
      string[0] != '\0')
    printf("\n");

  print_string(options, filename, line_num, string, pmatch);
}

void print_match_count(const opt options, const char *filename,
                       int match_count) {
  if (options.l && match_count > 0) printf("%s\n", filename);
  if (options.c && !options.l) {
    if (options.files > 1 && !options.h && options.e)
      printf("%s:%d\n", filename, match_count);
    else if (options.files > 1 && options.h)
      printf("%d\n", match_count);
    else if (!options.h && !options.e)
      printf("%d\n", match_count);
  }
}

/* Function process_lines
Regex match results:
- If regex!=match && !opt.v && line !=\0, print the line and ++ the match count.
- If regex!=match && opt.v, ++ the match count.
- If regex=match && opt.v, exit early
- If regex=match !opt.v print the line and seek more matches (if opt.o) */

void process_lines(const opt options, FILE **file, const char *filename,
                   int *match_count, int *line_num, regex_t *regex,
                   regmatch_t *pmatch, size_t nmatch, char *string) {
  // Read lines from the file until EOF or exception occurs
  while (!feof(*file) && !ferror(*file)) {
    fgets(string, BUF, *file), (*line_num)++;
    int reg_res = regexec(regex, string, nmatch, pmatch, 0);
    if (reg_res || options.v) {  // Handle match results
      if (reg_res == REG_NOMATCH && options.v && !options.o &&
          string[0] != '\0')
        print_line(options, filename, *line_num, string, pmatch),
            (*match_count)++;
      else if ((reg_res == REG_NOMATCH && !options.v) ||
               (reg_res == REG_NOMATCH && options.v && options.o))
        if (options.v) (*match_count)++;
      string[0] = '\0';
      continue;
    }
    if (string[0] != '\n') (*match_count)++;  // Increment match count
    while (!reg_res && !options.v) {          // Handle no matches w/o .v
      print_line(options, filename, *line_num, string, pmatch);
      if (options.o)
        reg_res = regexec(
            regex, memmove(string, string + (pmatch[0].rm_eo), strlen(string)),
            nmatch, pmatch, 0);  // Move unmatched and repeat
      else
        reg_res = REG_NOMATCH;  // if no matches !.o &&, exit cycle
    }
    string[0] = '\0';  // Reset the string for next iteration
  }
}

void process_file(const opt options, FILE **file, char filename[BUF]) {
  regex_t regex;
  int cflags = REG_EXTENDED;
  char string[BUF];
  int match_count = 0;
  int line_num = 0;
  regmatch_t pmatch[2];
  size_t nmatch = 2;

  if (options.i) cflags += REG_ICASE;
  if (!options.o) cflags += REG_NOSUB;
  if (!regcomp(&regex, options.pattern, cflags)) {
    process_lines(options, file, filename, &match_count, &line_num, &regex,
                  pmatch, nmatch, string);
    print_match_count(options, filename, match_count);
  } else
    handle_errors(3, 0, options.s);
  regfree(&regex);
}
