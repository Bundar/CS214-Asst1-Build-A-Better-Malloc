/*
CS:214
Dunbar Paul Birnie IV && Prad Rao
Assignment 1: Build A Better Malloc
2/12/18
mymalloc.c
-------------------------------------
immplements our version of malloc
*/
#include <stdio.h>
#include "mymalloc.h"

static char myblock[5000];

static int errorCount = 0;

/*
Function: mymalloc
-------------------------------------
computes address of allocatable space in the array myblock of 5000 bytes by treating it as a linked list of MemNodes which store basic meta data.
size: amount of space requested to be dynamically allocated.
file: file name of file being ran.
line: line number of current function call.
returns: The pointer to the head of the memory with size equal to or greater than the ammount requested.
*/
void* mymalloc(size_t size, char* file, int line)
{
	if (size == 0){
		printf("%s:%d error: no requested memory\n",file,line);
      		return NULL;
	}
  //treats the first addess of mem as if it was a MemNode.
  MemNode* p = (MemNode*) myblock;
  //sets previous 
  //check if any memory has been allocated already by checking if p->prev is set to current address.
  if(p->prev != *((unsigned short *)&p))
  {
  	//printf("%p",myblock);
    //check if you are trying to allocate more than 4988 bytes
    if(size>(5000-(2*sizeof(MemNode))))
    {
      printf("%s:%d error: not enough addressable memory.\n",file,line);
      return NULL;
    }
    //create first node and second node to manage the tail.
    p->prev = *((unsigned short *)&p);
    p->next = size+sizeof(MemNode);
    p->active = p->prev;
    MemNode* nextNode = (MemNode*)(((char*)p)+(p->next));
    nextNode->prev = p->next;
    nextNode->next = 5000 - (nextNode->prev);
    //printf("size of remaining space %d\n", nextNode->next);
    //printf("head %u\n",p->active);
    return (void*)(p+1);
  }
  //if first node is alreay allocated, run until memory is found that is not intentionally placed or used and there is enough space.
  //while: node is active OR theres not enough space to return a safe pointer to
  while((p->active == *((unsigned short *)&p)) || (p->next-sizeof(MemNode)<size))
  {
    //checks if requested memory will fit in remaining space.
    if((((char*)(p+1))+size) > (myblock+5000))
    {
      printf("%s:%d error: no remaining addressable memory.\n",file,line);
      return NULL;
    }
    p=(MemNode*)(((char*)p)+(p->next));
  }
  //once loop finds open node or empty space: 
  //first check if adding to end of LL
    //printf("size of space after available node %d\n", p->next);
  if(((char*)p)+p->next == myblock+5000)
  {  
    MemNode* newTail = (MemNode*)((char*)p + size+ sizeof(MemNode));
    newTail->next = (myblock+5000) - ((char*)newTail);
    newTail->prev = size + sizeof(MemNode);
    p->active = *((unsigned short *)&p);
    p->next = size + sizeof(MemNode);
    //printf("last %u\n",p->active);
    return (void*)(p+1);    
  }
  //then deal with if adding in middle
  //checks if there is more than enough space
  //printf("size %d and space available %d\n", size, p->next-sizeof(MemNode));
  if((size+sizeof(MemNode))<(p->next-sizeof(MemNode)))
  {
    MemNode* newNode = (MemNode*)((char*)p + size + sizeof(MemNode));
    newNode->next = (p->next) - (size + sizeof(MemNode));
    newNode->prev = size + sizeof(MemNode);
    newNode->active = 0;
    p->active = *((unsigned short *)&p);
    p->next = size + sizeof(MemNode);
    //printf("middle space optim %u\n",p->active);
    return (void*)(p+1);
  }
  
  //if there is just enough space or not enough space for the new node and the size
  //returns pointer to memory allocated right after meta data.
  p->active = *((unsigned short *)&p);
  //printf("middle %u\n",p->active);
  return (void*)(p+1);
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
void* myfree(void* ptrv, char* file, int line)
{

	char* ptr = (char*) ptrv;
	//printf("%u\n", ((MemNode*)(ptr-sizeof(MemNode)))->active);
  //checks if ptr points to a place NOT in the array of 5000 chars
  if(ptr-sizeof(MemNode) < myblock || ptr-sizeof(MemNode) > myblock+5000)
  {
    printf("%s:%d error: out of bounds of addressable memory.\n",file,line);
    return NULL;
  }
  //finds MemNode that manages given memory
  MemNode* node = (MemNode*)(ptr-sizeof(MemNode));
  //checks if node points to a valid previously allocated memory address
  if(node->active != *((unsigned short *)&node))
  {
  	errorCount++;
  	printf("%s:%d error: %d: Pointer does not point to valid allocated memory address.\n",file,line, errorCount);
  	return NULL;
  }
  //if given a valid ptr continue from here.
  /*
  set node to inactive then:
  cases:
  1.) freeing head.
    - if next is free:
      - node->next += nextNode->next
      - if nextNode != tail:
        - nextnextNode->prev += nextNode->prev
  2.) freeing node with prev node already freed.
    - prevNode->next += node->next
    - if last node:
      - return
    - else:
      - nextNode->prev += node->prev
      - set node to prevNode and continue to case 3.
  3.) freeing node with next node already freed.
    - node->next += nextNode->next
    - if nextNode != tail:
      - nextnextNode->prev += nextNode->prev      
  */
  else
  {
    //set node to inactive no matter which case.
    node->active = 0;
    //Case 1:
    MemNode* nextNode = (MemNode*)(((char*)node)+node->next);
    //if head
    if(node->prev == *((unsigned short *)&node))
    {
      //if next is also free
      if(nextNode->active != *((unsigned short *)&nextNode))
      {
        node->next += nextNode->next;
        //if next is not tail node
        if(((char*)nextNode)+nextNode->next != myblock+5000)
        {
          MemNode* nextnextNode = (MemNode*)(((char*)nextNode)+nextNode->next);
          nextnextNode->prev += nextNode->prev;
        }
      }
      return (void*)(node+1);
    }
    //Case 2:
    MemNode* prevNode = (MemNode*)(((char*)node)-node->prev);
    //if prev is free
    if(prevNode->active != *((unsigned short *)&prevNode))
    {
      prevNode->next += node->next;
      //if next is tail
      if(((char*)nextNode)+nextNode->next == myblock+5000)
      {
      	prevNode->next+=nextNode->next;
        return (void*)(node+1);
      }
      nextNode->prev += node->prev;
      node = prevNode;
    }
    //Case 3:
    nextNode = (MemNode*)(((char*)node)+node->next);
    if(nextNode->active != *((unsigned short *)&nextNode))
    {
      node->next += nextNode->next;
      if(((char*)nextNode)+nextNode->next != myblock+5000)
      {
        MemNode* nextnextNode = (MemNode*)(((char*)nextNode)+nextNode->next);
        nextnextNode->prev += nextNode->prev;
      }
    }
    return (void*)(node+1);
  }
}
