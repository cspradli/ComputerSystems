#
# Makefile for Linked List assignment
# 

CC = gcc
CFLAGS = -O -Wall
LFLAGS = 

all: linked_list


linked_list: main.c linked_list.c linked_list.h
	$(CC) $(CFLAGS) -c -o linked_list.o linked_list.c
	$(CC) $(CLFAGS) -c -o main.o main.c
	$(CC) $(LFLAGS) -o linked_list main.o linked_list.o


clean:
	rm -f linked_list.o main.o linked_list
