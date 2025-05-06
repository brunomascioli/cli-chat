CC = gcc
CFLAGS = -Wall -g

all: main

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

main: main.o
	$(CC) -o main main.o

clean:
	-rm -rf main.o main

run: main
	./main
