/*
CS:214
Dunbar Paul Birnie IV && Prad Rao
Assignment 1: Build A Better Malloc
2/12/18
*/
#include <stdio.h>
#include "mymalloc.h"
//mymalloc function. Returns pointer to memory allocated.
void* mymalloc(size_t size, char* file, int line)
{
  //treats the first addess of mem as if it was a MemNode.
  MemNode* p = mem;
  unsigned short i = *((unsigned short *)&p);
  //run until memory is found that is not intentionally placed or used.
  while(p->active == *((unsigned short *)&p))
  {
    //checks if requested memory will fit in remaining space.
    if((&p+sizeof(MemNode)+size) > (mem+5000))
    {
      printf("%s:%d error: no remaining addressable memory.\n",file,line);
      return NULL;
    }
    //increments ptr to next MemNode
    p=p->next;
  }
  p->active = *((unsigned short *)&p);
  p->next = &p + sizeof(MemNode) + size;
  //returns pointer to memory allocated right after meta data.
  return p+sizeof(MemNode);
}
