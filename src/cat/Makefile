# # ======================= GLOSSARY ⊂(｡•́‿•̀｡⊃)

# Define flags and target name
GCC = gcc -Wall -Werror -Wextra -pedantic -std=c11 -g
CLANG = clang-format -style=Google

# Variabliees 
TARGET = s21_cat
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
	rm -rf *.o $(TARGET) && cd $(TESTS) && rm -rf *.log $(TARGET)

# # ======================= CHECKS ⊂(｡•́‿•̀｡⊃)

TESTRUN = cp $(TARGET) $(TESTS) && bash
TESTF = $(TESTS)test_cat.sh
TESTV = $(TESTS)test_cat_valgrind.sh

style:
	$(CLANG) -n *.c *.h && $(CLANG) -i *.c *.h

test: all
	$(TESTRUN) $(TESTF) 

valgrind: all
	$(TESTRUN) $(TESTV) 