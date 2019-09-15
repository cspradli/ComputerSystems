#
# Makefile for Linked List assignment
# 

CC = gcc
CFLAGS = -O -Wall
LFLAGS = 

all: myls


myls: main.c linked_list.c linked_list.h directory.c directory.h
	$(CC) $(CFLAGS) -c -o linked_list.o linked_list.c
	$(CC) $(CLFAGS) -c -o main.o main.c
	$(CC) $(LFLAGS) -c -o directory.o directory.c
	$(CC) $(LFLAGS) -o myls main.o linked_list.o directory.o


clean:
	rm -f linked_list.o main.o directory.o myls