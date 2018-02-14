all: mymalloc.h
	gcc -o memgrind memgrind.c mymalloc.o
	memgrind
mymalloc.o: mymalloc.c
	gcc -c mymalloc.c	
