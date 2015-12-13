#include <ctype.h>

#ifndef huffman_H
#define huffman_H
#define NULLCHARLEN 1
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#include "types.h"
#include "list.h"
#include "memory.h"

letter_t* createSubTree(letter_t* left, letter_t* right);
void makeFileAsciiGram(char* file, letter_t** asciiGram);
letter_t* allocNode(int freq, letter_t* left, letter_t* right, char c);
letter_t* makeHuffTree(char* fileName);
void initAsciigram(letter_t* asciiGram);
#endif
