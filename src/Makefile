CATDIR = cd cat &&
GREPDIR = cd grep &&

all: cat_test grep_test

s21_cat:
	$(CATDIR) make
cat_test:
	$(CATDIR) make test
cat_valgrind:
	$(CATDIR) make valgrind

s21_grep:
	$(GREPDIR) make
grep_test:
	$(GREPDIR) make test
grep_valgrind:
	$(GREPDIR) make valgrind	

style: 
	$(CATDIR) make style
	$(GREPDIR) make style

clean:
	$(CATDIR) make clean
	$(GREPDIR) make clean


# ==== KNOWN ISSUES ====

# THE PROJECT WAS MADE AND TESTED ON LINUX
# APPEND SOME MARGIN OF ERRORS ON OTHER SYSTEMS

# you might expect such things on mac:

#1. During cat/grep compilation:
# error: no newline at end of file
# [-Werror, -Wnewline-eof]
# ^ can be fixed by running "style" makefile target and recompiling utils

#2. During grep compilation
#	error: logical not is only applied to the left side... 
#	[Werror,-Wlogical-not-comparison]
# ^ can be fixed with adding this to the list of compile flags in Makefile: 
# " -Wno-logical-not-parenthesis "

#3. During grep test execution
# 	FAIL 55
# 	SUCCESS 290
# 	ALL 345
# ^ can be fixed by running on linux ;)

#4. Other potential issues may or may not include:

# 	grep: option requires an argument -- 'f'
# 	Usage: grep [OPTION]... PATTERNS [FILE]...
# 	Try 'grep --help' for more information.

# 	grep: -c: No such file or directory

# ^ this may happen due to the nature of the tests
# and potentially due to some flaws in original grep utility itself

# for further issue reports and support contact meeeee 
# @reginaha