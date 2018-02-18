#include <stdio.h>
#include <stdlib.h>

int main(){


/*unsigned short test = 12345;*/
/*unsigned short ptr = (unsigned)&test;*/

/*printf("test: %u, &test: %p\n", test, &test);*/

/*ptr = (ptr<<14)>>14;*/

/*printf("ptr: %x\n", ptr);*/

char *test[5];

int i = 0;

for (i=0; i<5; i++){
	test[i] = (char*) malloc(10);
}

test[0] = "No ";
test[1] = "Love ";
test[2] = "For ";
test[3] = "A ";
test[4] = "Liar ";

for (i =0; i<5; i++){
	printf("%s", test[i]);
}
printf("\n");

}
