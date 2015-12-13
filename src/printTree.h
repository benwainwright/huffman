#ifndef printTree_H
#define printTree_H
#define R_BRANCH_INIT_LEN 2

#include "types.h"
#include "memory.h"
#include <stdlib.h>

int numOfRights(letter_t* tree);
int leftDepth(letter_t* tree);
void print2DArray(char** array, int h, int w);
void create2Darray(char*** array, int h, int w);
void printTreeRecurse(letter_t* tree, char** output, int y, int x);
void printTree(letter_t* tree);
void printLeftBranchLine(char** output, int y, int x);


#endif
