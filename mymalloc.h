#ifndef _MY_MALLOC_H
#define _MY_MALLOC_H

#define malloc(x) mymalloc(x,__FILE__,__LINE__)
#define free(x) myfree(x,__FILE__,__LINE__)
//prototype defs
void* mymalloc(size_t size,char* file,int line);
void* myfree(void* ptr,char* file,int line);
//Typedef for the MemNode type.
typedef struct _MemNode{
  unsigned short active;//2-bytes value of address.
  unsigned short prev;//2-bytes number of bytes before current ptr til previous node.
  unsigned short next;//2-bytes number of bytes after current ptr til next node.
}MemNode;
#endif
