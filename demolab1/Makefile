#
# Makefile for the C demo project
# Author: Caleb Spradlin
#
#

CC = gcc
CFLAGS = -O -Wall
LFLAGS = 

all: demo

#the below title should be the same as the executable
demo: main.c student.h student.c
	# -c says to stop at -o	
	$(CC) $(CFLAGS) -c -o student.o student.c
	$(CC) $(CFLAGS) -c -o main.o main.c
	# This is the linker line
	$(CC) $(LFLAGS) -o demo main.o student.o

clean:
	rm -f student.o main.o demo
