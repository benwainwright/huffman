#ifndef list_H
#define list_H
#define ASCIILETTERS 128
#include "huffman.h"
#include "utilities.h"
#include "memory.h"
#include "types.h"
#include <string.h>
#include <assert.h>

/* Defining as -2 to avoid confusion with EOF */
#define EMPTY -2

void initList(list_t* list);
letter_t* initListNode(letter_t* prev, letter_t* next);
void addToList(list_t* list, char letter);
letter_t* addListNode(letter_t* end);
void reverseList(list_t* list);
void reverseNexts(letter_t* end);
void reversePrevs(letter_t* start);
void removeFromList(list_t* list, letter_t* letter);
void removeWordsNotLength(int length, list_t* list);
void insertSorted(list_t* list, letter_t* letter);
void insertBefore(letter_t* beforeThis, letter_t* item, list_t* list);
void insertAtEnd(letter_t* item, list_t* list);
int listIsEmpty(list_t* list);
list_t insertionSort(letter_t* asciiGram, int length);
void duplicateLetter(letter_t** dest, letter_t* source);
void deleteZerosFromList(list_t* list);


#endif
