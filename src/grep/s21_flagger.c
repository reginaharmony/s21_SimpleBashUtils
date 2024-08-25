#include "s21_grep.h"

void initialize_options(opt* options) {
  options->err = 0;
  options->e = 0;
  options->i = 0;
  options->v = 0;
  options->c = 0;
  options->l = 0;
  options->n = 0;
  options->h = 0;
  options->s = 0;
  options->f = 0;
  options->o = 0;
  options->files = 0;
  options->pattern[0] = '\0';
  options->e_count = 0;
  options->reg_files = 0;
}

void process_options(char option, opt* options, char* prev) {
  if (option == 'i')
    options->i = 1;
  else if (option == 'v')
    options->v = 1;
  else if (option == 'c')
    options->c = 1;
  else if (option == 'l')
    options->l = 1;
  else if (option == 'n')
    options->n = 1;
  else if (option == 'h')
    options->h = 1;
  else if (option == 's')
    options->s = 1;
  else if (option == 'o')
    options->o = 1;
  else if (option == 'f')
    options->f = 1, *prev = 'f';
  else if (option == 'e')
    options->e = 1, *prev = 'e';
  else
    options->err = 1;
}

void process_e(opt* options, char** argv, int index) {
  if (options->e_count != 0) strcat(options->pattern, "|");
  for (int k = 2; k < (int)strlen(argv[index]); k++) {
    char c_to_str[2];
    c_to_str[1] = '\0';
    c_to_str[0] = argv[index][k];
    strcat(options->pattern, c_to_str);
  }
  options->e_count++;
}

void process_f(opt* options, char** argv, int index) {
  char reg_filename[1024];
  reg_filename[0] = '\0';
  for (int k = 2; k < (int)strlen(argv[index]); k++) {
    char c_to_str[2];
    c_to_str[1] = '\0';
    c_to_str[0] = argv[index][k];
    strcat(reg_filename, c_to_str);
  }
  options->reg_files_list[options->reg_files] = reg_filename;
  options->reg_files++;
}

void process(opt* options, char** argv, int index, char* prev) {
  for (int j = 1; j < (int)strlen(argv[index]); j++) {
    process_options(argv[index][j], options, prev);
  }
}

void process_argument(opt* options, char** argv, int i, char* prev) {
  if ((argv[i][0] == '-' && argv[i][1] != '-') || argv[i][0] != '-' ||
      ((*prev == 'e' || *prev == 'f') && argv[i][0] == '-')) {
    if (argv[i][0] == '-' && argv[i][1] != '\0' && *prev != 'e' && *prev != 'f')
      if (argv[i][1] == 'e' && argv[i][2] != '\0') {
        process_e(options, argv, i);
      } else if (argv[i][1] == 'f' && argv[i][2] != '\0') {
        process_f(options, argv, i);
      } else
        process(options, argv, i, prev);
    else if (*prev == 'f')
      options->reg_files_list[options->reg_files] = argv[i],
      options->reg_files++, *prev = 'x';
    else if (*prev == 'e' && options->e_count > 0)
      options->e_count++, strcat(options->pattern, "|"),
          strcat(options->pattern, argv[i]), *prev = 'x';
    else if (*prev == 'e' && options->e_count == 0)
      strcat(options->pattern, argv[i]), options->e_count++, *prev = 'x';
    else
      options->files_list[options->files] = argv[i], options->files++;
  } else
    handle_errors(4, 0, options->s), exit(1);
}

void get_options(const int argc, char** const argv) {
  opt options;
  initialize_options(&options);
  char prev = 'x';
  for (int i = 1; i < argc; i++) process_argument(&options, argv, i, &prev);
  if (!options.reg_files)
    read_files(options, 1);
  else
    read_files(options, 2);
}
