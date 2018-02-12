#ifndef _MY_MALLOC_H
#define _MY_MALLOC_H
#define malloc(x) mymalloc(x,__FILE__,__LINE__)
#define free(x) myfree(x,__FILE__,__LINE__)
//prototype defs
void* mymalloc(size_t,char*,int);
void* myfree(size_t,char*,int);
//Typedef for the MemNode type.
typedef struct _MemNode{
  char* word;
  struct _MemNode* next;
}MemNode;