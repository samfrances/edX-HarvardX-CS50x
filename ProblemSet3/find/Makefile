#
# Makefile
#
# Computer Science 50
# Problem Set 3
#

all: find generate tests

find: find.c helpers.c helpers.h
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o find find.c helpers.c -lcs50 -lm

generate: generate.c
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o generate generate.c

clean:
	rm -f *.o a.out core find generate

# Added by SF:
tests: tests.c helpers.c helpers.h
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -Wshadow tests.c helpers.c  -lcs50 -lm -o tests