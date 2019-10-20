#
# Makefile for the C demo program: Linked List
#

CC = gcc
CFLAGS = -O -Wall 
LFLAGS = 

all: count_secret_words

count_secret_words: main.c linked_list.h linked_list.c secret_words.c secret_words.h
	$(CC) $(CFLAGS) -c -o linked_list.o linked_list.c
	$(CC) $(CFLAGS) -c -o main.o main.c
	$(CC) $(CFLAGS) -c  -o secret_words.o secret_words.c
	$(CC) $(LFLAGS) -o count_secret_words main.o linked_list.o secret_words.o

test: count_secret_words
	./count_secret_words moby.txt

clean:
	rm -f linked_list.o main.o secret_words.o count_secret_words
