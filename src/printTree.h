#ifndef printTree_H
#define printTree_H

#include "types.h"
#include "memory.h"
#include <stdlib.h>

int numOfRights(letter_t* tree);
int leftDepth(letter_t* tree);
void print2DArray(char** array, int h, int w);
void create2Darray(char*** array, int h, int w);


#endif
