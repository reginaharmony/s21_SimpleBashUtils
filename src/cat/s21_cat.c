#include "s21_cat.h"

int main(int argc, char *argv[]) {
  opt options = {0};
  flagger(argc, argv, &options);
  for (int i = 1; i < argc; i++)
    if (argv[i][0] != '-') reader(argv, &options, argv[i]);
  return 0;
}
