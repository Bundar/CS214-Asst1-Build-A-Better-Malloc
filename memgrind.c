/*
CS:214
Dunbar Paul Birnie IV && Prad Rao
Assignment 1: Build A Better Malloc
2/12/18
memgrind.c
-------------------------------------
tests our implementation of the malloc function and analyzes time complexity.
*/
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main(){
	int n = 1;
	int i, j, k, m, f;
	//array for the mean times for the six test cases, A-F
	float meanTime[6] = {0};
	for (i = 0; i<6; i++){
		meanTime[i] = 0;
	}
	
/*	char* a = (char*) malloc(1);*/
/*	char* b = (char*) malloc(1);*/
/*	char* c = (char*) malloc(1);*/
/*	printf("\n");*/
/*	free(a);*/
/*	free(b);*/
/*	free(c);*/


	//100 iterations of workloads
	i = 0;
	for (i = 0; i<n; i++){
		
		struct timeval start, end;
		
/*		//workload A*/
/*		j = 0;*/
/*		gettimeofday(&start, NULL); //start time */
/*		for (j = 0; j<150; j++){ //150 iterations*/
/*			char* a = (char*) malloc(1); //mallocs 1 byte*/
/*			free(a); //immediately frees*/
/*		}*/
/*		gettimeofday(&end, NULL); //end time*/
/*		meanTime[0]+=(end.tv_sec-start.tv_sec)*1000000 + end.tv_usec-start.tv_usec;*/
/*		*/
/*		//workload B*/
/*		j = 0;*/
/*		char* b[150]; //static array 150 pointers long*/
/*		gettimeofday(&start, NULL); //start time*/
/*		for (j = 0; j<150; j++){ //150 iterations*/
/*			b[j] = (char*) malloc(1); //mallocs 1 byte*/
/*		}*/
/*		for (j = 0; j<150; j++){ //150 iterations*/
/*			free(b[j]);*/
/*		}*/
/*		gettimeofday(&end, NULL); //end time*/
/*		meanTime[1]+=(end.tv_sec-start.tv_sec)*1000000 + end.tv_usec-start.tv_usec;*/
/*		*/
/*		//workload C*/
/*		j = 0, m = 0, f = 0;*/
/*		srand(time(0));*/
/*		char* c[150] = {NULL};*/
/*		gettimeofday(&start, NULL); //start time*/
/*		while(m+f<6){*/
/*			int rd = rand() % 50;*/
/*			if (rd<25 && m<3){*/
/*				c[j] = (char*) malloc(1);*/
/*				m++, j++;	*/
/*			}*/
/*			else if(j>0){*/
/*				f++, j--;				*/
/*				free(c[j]);*/
/*			}*/
/*		}*/
/*		gettimeofday(&end, NULL); //end time*/
/*		meanTime[2]+=(end.tv_sec-start.tv_sec)*1000000 + end.tv_usec-start.tv_usec;*/
/*		*/
/*		//workload D*/
/*		j = 0, m = 0, f = 0;*/
/*		srand(time(0));*/
/*		char* d[150] = {NULL};*/
/*		gettimeofday(&start, NULL); //start time*/
/*		while(m+f<300){*/
/*			int rd = rand() % 50;*/
/*			int sz = (rand() % 64) + 1;*/
/*			if (rd<25 && m<150){*/
/*				d[j] = (char*) malloc(sz);*/
/*				m++, j++;*/
/*			}*/
/*			else if(j>0){*/
/*				f++, j--;*/
/*				free(d[j]);*/
/*				*/
/*			}*/
/*		}*/
/*		gettimeofday(&end, NULL); //end time*/
/*		meanTime[3]+=(end.tv_sec-start.tv_sec)*1000000 + end.tv_usec-start.tv_usec;*/
		
   	 	//workload E
   	 	//char* ptr = (char*) malloc(4994);	
   	 	char* ptr2 = (char*) malloc(10);
   	 	
   	 	j = 0, m = 0, f = 0, k = 0;
		srand(time(0));
		char* e[150] = {NULL};
		
		gettimeofday(&start, NULL); //start time
		while(m+f<300){
			int rd = rand() % 50;
			if (rd<25 && m<150){
				//printf("%d malloc\n", j);
				e[j] = (char*) malloc(25);
				if (e[j]==NULL) printf("ERRRRRROROROROROR");
				//printf("%p\n",e[j]);
				m++, j++;
			}
			else if(j>0){
				int rdPtr = rand() % j;
				//printf("%d free of %d node\n", (j-1), rdPtr);
				char* test = free(e[rdPtr]);
				if (test==NULL) printf("error");
				//printf("%p\n",e[j]);
				for (k=rdPtr; k<j; k++){
					e[k] = e[k+1];
				}
				f++, j--;
				
			}
		}
/*		e[0] = (char*) malloc(200);*/
/*		e[1] = (char*) malloc(200);*/
/*		e[2] = (char*) malloc(200);*/
/*		e[3] = (char*) malloc(200);*/
/*		e[4] = (char*) malloc(200);*/
/*		e[5] = (char*) malloc(200);*/
/*		e[6] = (char*) malloc(200);*/
/*		e[7] = (char*) malloc(200);*/
/*		printf("\n");*/
/*		printf("%p\n",e[0]);*/
/*		free(e[0]);*/
/*		printf("%p\n",e[2]);*/
/*		free(e[2]);*/
/*		printf("%p\n",e[4]);*/
/*		free(e[4]);*/
/*		printf("%p\n",e[6]);*/
/*		free(e[6]);*/
/*		e[0] = (char*) malloc(200);*/
/*		e[2] = (char*) malloc(200);*/
/*		e[4] = (char*) malloc(200);*/
/*		e[6] = (char*) malloc(200);*/
/*		printf("\n");*/
/*		printf("%p\n",e[0]);*/
/*		printf("%p\n",e[2]);*/
/*		printf("%p\n",e[4]);*/
/*		printf("%p\n",e[6]);*/
		
/*		for (j=0;j<15;j++){*/
/*			e[j] = (char*) malloc(2);*/
/*			printf("%p\n",e[j]);*/
/*		}*/
/*		printf("\n");*/
/*		for (j=0;j<15;j+=2){*/
/*			free(e[j]);*/
/*			printf("%p\n",e[j]);*/
/*		}*/
/*	printf("\n");*/
/*		for (j=1;j<15;j+=2){*/
/*			free(e[j]);*/
/*			printf("%p\n",e[j]);*/
/*		}*/
/*		printf("\n");*/
/*		for (j=0;j<15;j+=2){*/
/*			e[j] = (char*) malloc(2);*/
/*			printf("%p\n",e[j]);*/
/*		}*/
/*		printf("\n");*/
/*		for (j=1;j<15;j+=2){*/
/*			e[j] = (char*) malloc(2);*/
/*			printf("%p\n",e[j]);*/
/*		}*/
/*		printf("\n");*/
/*		*/
/*		free(e[3]);*/
/*		free(e[4]);*/
/*		e[3] = (char*) malloc(2);		*/
		
		gettimeofday(&end, NULL); //end time
		meanTime[4]+=(end.tv_sec-start.tv_sec)*1000000 + end.tv_usec-start.tv_usec;
	
/*    		//workload F*/
/*    		*/
/*    		char* f[150] = {NULL};*/
/*    		*/
/*    		gettimeofday(&start, NULL); //start time*/
/*		for (j=0;j<150;j++){*/
/*			f[j] = (char*) malloc(27);*/
/*		}*/
/*		*/
/*		for (j=1; j<149;j++){*/
/*			free(f[j]);*/
/*		}*/
/*		*/
/*		f[1] = (char*) malloc(3000);*/
/*		gettimeofday(&end, NULL); //end time*/
/*		meanTime[5]+=(end.tv_sec-start.tv_sec)*1000000 + end.tv_usec-start.tv_usec;*/
	}
	
	//char* g = (char*) malloc(6000);
	
	float meanSec[6] = {0};
	
	for (i = 0; i<6; i++){
		meanTime[i]/=n;
		
		meanTime[i]=meanTime[i]/1000000;
		meanSec[i]=meanTime[i];
		meanTime[i]=0;
		while (meanSec[i]>60){
			meanSec[i]-=60;
			meanTime[i]++;
		}
	}
	
	printf("Test Case A took %f minutes and %.10f seconds.\n", meanTime[0], meanSec[0]);
	printf("Test Case B took %f minutes and %.10f seconds.\n", meanTime[1], meanSec[1]);
	printf("Test Case C took %f minutes and %.10f seconds.\n", meanTime[2], meanSec[2]);
	printf("Test Case D took %f minutes and %.10f seconds.\n", meanTime[3], meanSec[3]);
	printf("Test Case E took %f minutes and %.10f seconds.\n", meanTime[4], meanSec[4]);
	printf("Test Case F took %f minutes and %.10f seconds.\n", meanTime[5], meanSec[5]);

	
return 0;
}


