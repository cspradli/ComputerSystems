CC=gcc
Cflags=
Lflags=

all: pipe_demo

pipe_demo: pipe_demo.c
	$(CC) $(Cflags) $(Lflags) -o pipe_demo pipe_demo.c

sem_demo: sem_demo.c
	$(CC) $(Cflags) $(Lflags) -o sem_demo sem_demo.c


test: pipe_demo
	./pipe_demo 1234567890
