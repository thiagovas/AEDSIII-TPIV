# Made by Thiago Vieira
# The option -c in gcc: Compile and assemble, but do not link
CC=gcc

all: build clearafter

build: main.o vector.o graph.o queue.o pair.o
	$(CC) main.o vector.o graph.o queue.o pair.o -o tp4 -lm -lpthread -O2

main.o: vector.o graph.o
	$(CC) -c main.c -o main.o -Wall

vector.o:
	$(CC) -c vector.c -o vector.o -Wall
	
graph.o: vector.o
	$(CC) -c graph.c -o graph.o -Wall

queue.o: pair.o vector.o
	$(CC) -c queue.c -o queue.o -Wall

pair.o:
	$(CC) -c pair.c -o pair.o -Wall

#Clear temporary files after compiling
clearafter:
	#Option -r: Remove recursive and
	#Option -f: ignore nonexistent files, never prompt
	rm -rf *.o
	rm -rf *~ #Remove temporary files

clean: clearafter
	rm -f tp4

