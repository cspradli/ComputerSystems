#
# Makefile for my-pi
# 

CC = gcc
CFLAGS = -O -Wall
LFLAGS = 

all: my-pi


my-pi: main.c simulation.c simulation.h
	$(CC) $(CFLAGS) -c -o simulation.o simulation.c
	$(CC) $(CLFAGS) -c -o main.o main.c
	$(CC) $(LFLAGS) -o my-pi main.o simulation.o


clean:
	rm -f simulation.o main.o my-pi
