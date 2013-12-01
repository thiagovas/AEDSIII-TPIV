# Made by Thiago Vieira
# The option -c in gcc: Compile and assemble, but do not link
CC=gcc

all: build clearafter

build: main.o vector.o graph.o queue.o pair.o matrix3d.o utility.o solver.o
	$(CC) main.o vector.o graph.o queue.o pair.o utility.o matrix3d.o solver.o -o tp4 -lm -lpthread -O2

main.o: vector.o graph.o utility.o
	$(CC) -c main.c -o main.o -Wall

vector.o: utility.o
	$(CC) -c vector.c -o vector.o -Wall
	
graph.o: vector.o utility.o
	$(CC) -c graph.c -o graph.o -Wall

queue.o: pair.o vector.o utility.o
	$(CC) -c queue.c -o queue.o -Wall

pair.o: utility.o
	$(CC) -c pair.c -o pair.o -Wall

matrix3d.o: vector.o utility.o
	$(CC) -c matrix3d.c -o matrix3d.o -Wall

utility.o:
	$(CC) -c utility.c -o utility.o -Wall

solver.o: utility.o vector.o graph.o matrix3d.o
	$(CC) -c solver.c -o solver.o -Wall

#Clear temporary files after compiling
clearafter:
	#Option -r: Remove recursive and
	#Option -f: ignore nonexistent files, never prompt
	rm -rf *.o
	rm -rf *~ #Remove temporary files

clean: clearafter
	rm -f tp4
	rm -f output

