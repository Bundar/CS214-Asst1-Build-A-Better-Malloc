//memgrind.c
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int i;
	//array for the mean times for the six test cases, A-F
	long* meanTime = (long*) malloc(6*sizeof(long));
	for (i = 0; i<6; i++){
		meanTime[i] = 0;
	}
	
	//100 iterations of workloads
	i = 0;
	for (i = 0; i<100; i++){
		
		int j;
		struct timeval start, end;
		//workload A
		j = 0;
		gettimeofday(&start, NULL); //start time 
		for (j = 0; j<150; j++){ //150 iterations
			char* a = (char*) malloc(1); //mallocs 1 byte
			free(a); //immediately frees
		}
		gettimeofday(&end, NULL); //end time
		meanTime+=(end.tv_sec-start.tv_sec)*1000000 + end.tv_usec-start.tv_usec;

		//workload B
		j = 0;
		char* b[150] = {NULL}; //static array 150 pointers long
		gettimeofday(&start, NULL); //start time
		for (j = 0; j<150; j++){ //150 iterations
			b[j] = (char*) malloc(1); //mallocs 1 byte
		}
		for (j = 0; j<150; j++){ //150 iterations
			free(b[j]);
		}
		gettimeofday(&end, NULL); //end time
		meanTime+=(end.tv_sec-start.tv_sec)*1000000 + end.tv_usec-start.tv_usec;
		
		
		
	}
	
	
	
return 0;
}


