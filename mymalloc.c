/*
CS:214
Dunbar Paul Birnie IV && Prad Rao
Assignment 1: Build A Better Malloc
2/12/18
*/
#include <stdio.h>
#include "mymalloc.h"
/*
Function: mymalloc
-------------------------------------
computes address of allocatable space in the array mem of 5000 bytes by treating it as a linked list of MemNodes which store basic meta data.
size: ammount of space requested to be dynamically allocated.
file: file name of file being ran.
line: line number of current function call.
returns: The pointer to the head of the memory with size equal to or greater than the ammount requested.
*/
void* mymalloc(size_t size, char* file, int line)
{
  //treats the first addess of mem as if it was a MemNode.
  MemNode* p = mem;
  unsigned short i = *((unsigned short *)&p);
  //run until memory is found that is not intentionally placed or used and there is enough space.
  //while((p->active == *((unsigned short *)&p)) || ((p->next->active == *((unsigned short *)(p->next))) && (&p+sizeof(MemNode)+size) > (p->next)))
  while((p->active == *((unsigned short *)&p)) || (((p+(p->next))->active == *((unsigned short *)&(p+(p->next)))) && (p->next-sizeof(MemNode)>size)))//sorry for ugly while loop
  {
    //checks if requested memory will fit in remaining space.
    if((&p+sizeof(MemNode)+size) > (mem+5000))
    {
      printf("%s:%d error: no remaining addressable memory.\n",file,line);
      return NULL;
    }
    //increments ptr to next MemNode
    p+=p->next;
  }
  p->active = *((unsigned short *)&p);
  p->next = (unsigned short)(sizeof(MemNode) + size);
  //returns pointer to memory allocated right after meta data.
  return (void*)(&p+sizeof(MemNode));
}
/*
Function: myfree
-------------------------------------
Marks the memory that the pointer was using as addressable so it can be allocated again through mymalloc()
ptr: pointer to memory that should be returned to useable memory.
file: file name of file being ran.
line: line number of current function call.
returns: The pointer to the head of the memory that is now available.
*/
void* free(void* ptr, char* file, int line)
{
  //checks if ptr points to a place in the array of 5000 chars
  if(&ptr-sizeof(MemNode) < mem || &ptr-sizeof(MemNode) > &mem+5000)
  {
    printf("%s:%d error: out of bounds of addressable memory.\n",file,line);
    return NULL;
  }
  MemNode* node = &ptr-sizeof(MemNode);
  //checks if ptr points to a valid previously allocated memory address
  if(node->active != *((unsigned short *)&node))
  {
    printf("%s:%d error: pointer does not point to valid allocated memory address.\n",file,line);
    return NULL;
  }
  //if given a valid ptr
  else
  {
    
  }
}
