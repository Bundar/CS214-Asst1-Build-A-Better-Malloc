all: mymalloc memgrind
mymalloc: mymalloc.c
	gcc -g -Wall -c mymalloc.c
memgrind: memgrind.c
	gcc -g -Wall -o memgrind memgrind.c mymalloc.o
clean:
	rm -rf mymalloc.o memgrind	
