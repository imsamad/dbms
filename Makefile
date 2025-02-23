flags = -Wall -O2 -std=c2x

ldflags=

all: clear tree

tree: tree.o
	cc ${flags} $^ -o $@ ${ldflags}

tree.o: tree.c
	cc ${flags} -c $^

clear:
	rm *.o
