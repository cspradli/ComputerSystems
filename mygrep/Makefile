#
# Makefile for Linked List assignment
# 

CC = gcc
CFLAGS = -O -Wall
LFLAGS = 

all: mygrep


mygrep: main.c linked_list.c linked_list.h file_input.c file_input.h
	$(CC) $(CFLAGS) -c -o linked_list.o linked_list.c
	$(CC) $(CLFAGS) -c -o main.o main.c
	$(CC) $(LFLAGS) -c -o file_input.o file_input.c
	$(CC) $(LFLAGS) -o mygrep main.o linked_list.o file_input.o


clean:
	rm -f linked_list.o main.o file_input.o mygrep
