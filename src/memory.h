#ifndef _MEMORY_
#define _MEMORY_

#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
typedef struct pointerList {
  void* pnt;
  struct pointerList* lastList;
  struct pointerList* prev;
} heapList_t;

typedef struct heapListStack {
   heapList_t* list;
   struct heapListStack* prev;
} heapListStack_t;


void* reAllocate(void* ptr, int size);
heapList_t** toHeapList(void* pnt);
void newHeapList(void);
void freeHeapList(void);
void* allocate(int size);
void* callocate(int num, int size);
void* callocOffList(int num, int size);
void* allocOfflist(int size);
void* reallocate(void* ptr, size_t size);

#endif
