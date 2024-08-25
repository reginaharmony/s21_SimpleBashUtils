#include "s21_grep.h"

void read_mode_single(opt options) {
  int i = 0;
  if (options.e_count == 0) strcat(options.pattern, options.files_list[0]), i++;
  for (; i < options.files; i++) {
    FILE *file;
    file = fopen(options.files_list[i], "r");
    if (file != NULL) {
      if (!options.err)
        process_file(options, &file, options.files_list[i]);
      else
        handle_errors(5, options.files_list[i], options.s);
      fclose(file);
    } else
      handle_errors(1, options.files_list[i], options.s);
  }
}

void read_mode_mult(opt options) {
  char string[BUF];
  for (int i = 0; i < options.reg_files; i++) {
    FILE *reg_file = fopen(options.reg_files_list[i], "r");
    if (reg_file == NULL) {
      handle_errors(1, options.reg_files_list[i], options.s);
      continue;
    }
    if (ferror(reg_file)) handle_errors(5, options.files_list[i], options.s);
    while (fgets(string, BUF, reg_file) && !feof(reg_file)) {
      string[strcspn(string, "\n")] = 0;
      if (options.e_count == 0)
        strcat(options.pattern, string);
      else
        strcat(options.pattern, "|"), strcat(options.pattern, string);
      options.e_count++;
    }
    fclose(reg_file);
  }
  read_mode_single(options);
}

void read_files(opt options, int mode) {
  if (mode == 1) read_mode_single(options);
  if (mode == 2) read_mode_mult(options);
}
