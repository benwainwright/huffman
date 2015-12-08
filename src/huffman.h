#ifndef huffman_H
#define huffman_H

#include <stdlib.h>
#include <stdio.h>

#include "memory.h"
typedef struct letter {
   int letter;
   int freq;
   struct letter* prev;
   struct letter* next;
   struct letter* left;
   struct letter* right;
} letter_t;



int getCharFreq(char* string, char c);
void insertInArray(letter_t** array, letter_t item, int pos, int length);
int insertSortNoZeros(int* asciiGram, letter_t** letters);
void deleteArrayPos(letter_t** array, int i, int length);
letter_t* createSubTree(letter_t* left, letter_t* right);
void makeFileAsciiGram(char* file, int** asciiGram);
letter_t* allocNode(int freq, letter_t* left, letter_t* right, char c);
void printLetterArray(letter_t* array, int length);
letter_t* makeHuffTree(char* fileName);
void outputTree(letter_t* tree, int* asciiGram);
letter_t* printCode(letter_t* tree, char c);

#endif
