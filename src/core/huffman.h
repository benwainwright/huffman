#include <ctype.h>

#ifndef huffman_H
#define huffman_H
#define NULLCHARLEN 1
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "types.h"
#include "list.h"
#include "memory.h"

int getCharFreq(char* string, char c);
void insertInArray(letter_t** array, letter_t item, int pos, int length);
int insertSortNoZeros(int* asciiGram, letter_t** letters);
void deleteArrayPos(letter_t** array, int i, int length);
letter_t* createSubTree(letter_t* left, letter_t* right);
void makeFileAsciiGram(char* file, letter_t** asciiGram);
letter_t* allocNode(int freq, letter_t* left, letter_t* right, char c);
void printLetterArray(letter_t* array, int length);
tree_t* makeHuffTree(char* fileName);
void outputTree(letter_t* tree, letter_t* asciiGram);
code_t* getCode(letter_t* tree, char c, int i);
code_t* initCode(int length, int freq);
void initAsciigram(letter_t* asciiGram);
void replaceOnlyItem(letter_t* item, list_t* list);
int numOfRights(letter_t* tree);
int leftDepth(letter_t* tree);
int getBytes(int bitCount);
tree_t* initTree(letter_t* root, int h, int w, int x, int y);

#endif
