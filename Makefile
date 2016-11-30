#   Makefile
#   Cameron Brock
#   Programming Assignment 2 prim
#
#   This program is entirely my own work
CC=gcc
CFLAGS=-Wall -Wextra -g -std=c99 -c
OBJECTS=prim.o scanner.o node.o Fatal.o vertex.o cdll.o binheap.o graph.o queue.o

all: prim

prim: ${OBJECTS}
	${CC} -Wall -Wextra -std=c99 -g -o prim ${OBJECTS} -lm

tester: prim
	./prim ./graphs/graph1.txt > ./results/res1
	./prim ./graphs/graph2.txt > ./results/res2
	./prim ./graphs/graph3.txt > ./results/res3
	./prim ./graphs/graph4.txt > ./results/res4
	./prim ./graphs/graph5.txt > ./results/res5
	./prim ./graphs/graph6.txt > ./results/res6
	./prim ./graphs/graph7.txt > ./results/res7
	./prim ./graphs/graph8.txt > ./results/res8
	./prim ./graphs/graph9.txt > ./results/res9
	./prim ./graphs/graph10.txt > ./results/res10
	diff ./outputs/output1.txt ./results/res1
	diff ./outputs/output2.txt ./results/res2
	diff ./outputs/output3.txt ./results/res3
	diff ./outputs/output4.txt ./results/res4
	diff ./outputs/output5.txt ./results/res5
	diff ./outputs/output6.txt ./results/res6
	diff ./outputs/output7.txt ./results/res7
	diff ./outputs/output8.txt ./results/res8
	diff ./outputs/output9.txt ./results/res9
	diff ./outputs/output10.txt ./results/res10

vertex.o: vertex.c vertex.h Fatal.h node.h
	${CC} ${CFLAGS} vertex.c

prim.o: prim.c cdll.h vertex.h node.h binheap.h scanner.h graph.h Fatal.h
	${CC} ${CFLAGS} prim.c

node.o: node.c node.h Fatal.h vertex.h
	${CC} ${CFLAGS} node.c

cdll.o: cdll.c cdll.h Fatal.h node.h
	${CC} ${CFLAGS} cdll.c

binheap.o: binheap.c binheap.h node.h cdll.h Fatal.h
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
	if [ -f "prim" ]; then rm prim; fi
	if [ -d "prim.dSYM" ]; then rm -r prim.dSYM; fi
