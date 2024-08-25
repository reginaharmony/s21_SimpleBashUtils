# # ======================= GLOSSARY ⊂(｡•́‿•̀｡⊃)

# Define flags and target name
GCC = gcc -Wall -Werror -Wextra -pedantic -std=c11 -g
CLANG = clang-format -style=Google

# Variabliees
UTIL = grep
TARGET = s21_$(UTIL)
TESTS = tests/

# Define all the source files
SRCS = $(patsubst %.c,%.o,$(wildcard *.c))

# # ======================= TARGETS ⊂(｡•́‿•̀｡⊃)

all: $(TARGET)

$(TARGET): $(SRCS)
	$(GCC) $(SRCS) -o $(TARGET)

%.o: %.c
	$(GCC) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf *.o $(TARGET) *.log && cd $(TESTS) && rm -rf *.log $(TARGET)

# # ======================= CHECKS ⊂(｡•́‿•̀｡⊃)

TESTRUN = cp $(TARGET) $(TESTS) && bash
TESTF = $(TESTS)test_$(UTIL).sh
TESTV = $(TESTS)test_$(UTIL)_valgrind.sh

style:
	$(CLANG) -n *.c *.h && $(CLANG) -i *.c *.h

test: clean all
	$(TESTRUN) $(TESTF) 

valgrind: all
	$(TESTRUN) $(TESTV) 