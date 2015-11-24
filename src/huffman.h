#ifndef huffman_H
#define huffman_H

#include <stdlib.h>
#include <stdio.h>

#include "memory.h"
typedef struct letter {
   char letter;
   int freq;
   struct letter* left;
   struct letter* right;
} letter_t;

int getCharFreq(char* string, char c);
void insertSorted(letter_t** letters, int length, letter_t letter);
void insertInArray(letter_t** array, letter_t item, int pos, int length);
void insertSortNoZeros(int* asciiGram, letter_t** letters);
void deleteArrayPos(letter_t** array, int i, int length);
letter_t* createSubTree(letter_t* left, letter_t* right);



#endif
