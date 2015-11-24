#ifndef huffman_H
#define huffman_H

#include <stdlib.h>
#include <stdio.h>
typedef struct letter {
   char letter;
   int freq;
} letter_t;

int getCharFreq(char* string, char c);
void insertSorted(letter_t* letters, int length, letter_t letter);
void insertInArray(letter_t** array, letter_t item, int pos, int length);


#endif
