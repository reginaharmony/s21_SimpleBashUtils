#include "s21_grep.h"

int main(const int argc, char **const argv) {
  if (argc < 3) handle_errors(4, 0, 0);
  return get_options(argc, argv), 0;
}
