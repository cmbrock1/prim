#   Makefile
#   Cameron Brock
#   Programming Assignment 2 prim
#
#   This program is entirely my own work
CC=gcc
CFLAGS=-Wall -g -std=c99 -c
OBJECTS=prim.o scanner.o node.o Fatal.o
BINARYS=prim

all: prim

prim: ${OBJECTS}
	${CC} -Wall -std=c99 -g -o prim ${OBJECTS}

test: prim

prim.o: prim.c scanner.h Fatal.h
	${CC} ${CFLAGS} prim.c

node.o: node.c node.h Fatal.h
	${CC} ${CFLAGS} node.c

Fatal.o: Fatal.c Fatal.h
	${CC} ${CFLAGS} Fatal.c

scanner.o: scanner.c scanner.h
	${CC} ${CFLAGS} scanner.c

clean:
	rm ${OBJECTS} ${BINARYS}
