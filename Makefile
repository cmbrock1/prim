#   Makefile
#   Cameron Brock
#   Programming Assignment 2 prim
#
#   This program is entirely my own work
CC=gcc
CFLAGS=-Wall -Wextra -g -std=c99 -c
OBJECTS=scanner.o node.o Fatal.o vertex.o cdll.o binheap.o graph.o queue.o
TESTOBJECTS=scanner.o node.o Fatal.o vertex.o cdll.o binheap.o graph.o

all: prim

prim: prim.o ${OBJECTS}
	${CC} -Wall -Wextra -std=c99 -g -o prim prim.o ${OBJECTS} -lm

test: prim.o testing.o ${TESTOBJECTS}
	${CC} -Wall -Wextra -std=c99 -g -o testing testing.o ${TESTOBJECTS} -lm
	./testing data1

testing.o: testing.c cdll.h vertex.h node.h binheap.h scanner.h graph.h Fatal.h
	${CC} ${CFLAGS} testing.c

vertex.o: vertex.c vertex.h Fatal.h node.h
	${CC} ${CFLAGS} vertex.c

prim.o: prim.c cdll.h vertex.h node.h binheap.h scanner.h graph.h Fatal.h
	${CC} ${CFLAGS} prim.c

node.o: node.c node.h Fatal.h vertex.h
	${CC} ${CFLAGS} node.c

cdll.o: cdll.c cdll.h Fatal.h node.h
	${CC} ${CFLAGS} cdll.c

binheap.o: binheap.c binheap.h node.h Fatal.h cdll.h
	${CC} ${CFLAGS} binheap.c

graph.o: graph.c graph.h vertex.h Fatal.h
	${CC} ${CFLAGS} graph.c

queue.o: queue.c queue.h node.h Fatal.h
	${CC} ${CFLAGS} queue.c

Fatal.o: Fatal.c Fatal.h
	${CC} ${CFLAGS} Fatal.c

scanner.o: scanner.c scanner.h
	${CC} ${CFLAGS} scanner.c

clean:
	rm ${OBJECTS}
	if [ -f "testing" ]; then rm testing; fi
	if [ -f "prim" ]; then rm prim; fi
