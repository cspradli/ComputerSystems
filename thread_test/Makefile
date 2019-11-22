#
# Makefile 
#

CC = gcc
CFLAGS = -O -Wall 
LFLAGS = -pthread

all: tdemo

tdemo: main.c thread.c thread.h
	$(CC) $(CFLAGS) -c -o thread.o thread.c
	$(CC) $(CFLAGS) -c -o main.o main.c
	$(CC) $(LFLAGS) -o tdemo main.o thread.o

clean:
	rm -f thread.o main.o tdemo
