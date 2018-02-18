all: memgrind
mymalloc: mymalloc.c
	gcc -g -Wall -o mymalloc.c
memgrind: mymalloc.c memgrind.c
  gcc -g -Wall -c mymalloc.c
	gcc -g -Wall -o memgrind memgrind.c mymalloc.o
clean:
	rm -rf mymalloc.o memgrind	
