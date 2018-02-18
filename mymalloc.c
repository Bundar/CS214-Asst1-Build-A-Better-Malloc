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
/*
Function: mymalloc
-------------------------------------
computes address of allocatable space in the array mem of 5000 bytes by treating it as a linked list of MemNodes which store basic meta data.
size: amount of space requested to be dynamically allocated.
file: file name of file being ran.
line: line number of current function call.
returns: The pointer to the head of the memory with size equal to or greater than the ammount requested.
*/
void* mymalloc(size_t size, char* file, int line)
{
  //treats the first addess of mem as if it was a MemNode.
  MemNode* p = mem;
  //sets previous 
  //check if any memory has been allocated already by checking if p->prev is 0 already.
  if(p->prev != 0)
  {
    //check if you are trying to allocate more than 4994 bytes
    if(size>(5000-sizeof(MemNode)))
    {
      printf("%s:%d error: not enough addressable memory.\n",file,line);
      return NULL;
    }
    //create first node and second node to manage the tail.
    p->prev = 0;
    p->next = size+sizeof(MemNode);
    MemNode* nextNode = (MemNode*)(((char*)p)+(p->next));
    nextNode->prev = p->next;
    nextNode->next = 5000 - (nextNode->prev + sizeof(MemNode));
    return (void*)(p+1);
  }
  //if first node is alreay allocated, run until memory is found that is not intentionally placed or used and there is enough space.
  //while: node is active OR (Node is inactive AND theres not enough space to return a safe pointer to
  while((p->active == *((unsigned short *)&p)) || ((p->active != *((unsigned short *)&p)) && (p->next-sizeof(MemNode)<size)))
  {
    //checks if requested memory will fit in remaining space.
    if((((char*)(p+1))+size) > (mem+5000))
    {
      printf("%s:%d error: no remaining addressable memory.\n",file,line);
      return NULL;
    }
    p=(MemNode*)(((char*)p)+(p->next));
  }
  //once loop finds open node or empty space: 
  //first check if adding to end of LL
  if(((char*)p)+p->next == mem+5000)
  {  
    MemNode* newTail = (MemNode*)((char*)p + size);
    newTail->next = (mem+5000) - (((char*)newTail) + sizeof(MemNode));
    newTail->prev = size;
    p->active = *((unsigned short *)&p);
    p->next = size;
    return (void*)(p+1);    
  }
  //then deal with if adding in middle
  //checks if there is more than enough space
  if((size+sizeof(MemNode)+1)<p->next)
  {
    MemNode* newNode = (MemNode*)((char*)p + p->next);
    newNode->next = (p->next) - (size + sizeof(MemNode));
    newNode->prev = size;
    p->active = *((unsigned short *)&p);
    p->next = size;
    return (void*)(p+1);
  }
  
  //if there is just enough space or not enough space for the new node and the size
  //returns pointer to memory allocated right after meta data.
  p->active = *((unsigned short *)&p);
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
void* myfree(void* ptr, char* file, int line)
{
  //checks if ptr points to a place NOT in the array of 5000 chars
  if(ptr-sizeof(MemNode) < mem || ptr-sizeof(MemNode) > mem+5000)
  {
    printf("%s:%d error: out of bounds of addressable memory.\n",file,line);
    return NULL;
  }
  //finds MemNode that manages given memory
  MemNode* node = ptr-sizeof(MemNode);
  //checks if node points to a valid previously allocated memory address
  if(node->active != *((unsigned short *)&node))
  {
    printf("%s:%d error: Pointer does not point to valid allocated memory address.\n",file,line);
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
    if(node->prev == 0)
    {
      //MemNode* nextNode = (MemNode*)(((char*)node)+node->next);
      //if next is also free
      if(nextNode->active != *((unsigned short *)&nextNode))
      {
        node->next += nextNode->next;
        //if next is not tail node
        if(((char*)nextNode)+nextNode->next != mem+5000)
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
      if(((char*)nextNode)+nextNode->next == mem+5000)
      {
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
      if(((char*)nextNode)+nextNode->next != mem+5000)
      {
        MemNode* nextnextNode = (MemNode*)(((char*)nextNode)+nextNode->next);
        nextnextNode->prev += nextNode->prev;
      }
    }
    return (void*)(node+1);
  }
}
