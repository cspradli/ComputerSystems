#
# Makefile 
#

CC = gcc
CFLAGS = -O -Wall 
LFLAGS = -pthread

all: sliced_thread sliced_server

sliced_thread: main.c thread.c thread.h
	$(CC) $(CFLAGS) -c -o thread.o thread.c
	$(CC) $(CFLAGS) -c -o main.o main.c
	$(CC) -o sliced_thread main.o thread.o $(LFLAGS)

sliced_server: server.c
	$(CC) $(CFLAGS) -c -o server.o server.c
	$(CC) -o sliced_server server.o $(LFLAGS)

clean:
	rm -f thread.o main.o sliced_thread
