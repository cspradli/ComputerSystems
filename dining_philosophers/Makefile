CC=gcc
CFLAGS=-O -Wall

all: dining_philosopher

dining_philosopher: main.c philosopher.c philosopher.h semaphore_lib.c semaphore_lib.h
	$(CC) $(CFLAGS) -c -o main.o main.c
	$(CC) $(CFLAGS) -c -o philosopher.o philosopher.c
	$(CC) $(CFLAGS) -c -o semaphore_lib.o semaphore_lib.c
	$(CC) $(LFLAGS)  -o dining_philosopher main.o philosopher.o semaphore_lib.o

clean:
	rm *.o dining_philosopher


test: dining_philosopher
	./dining_philosopher

