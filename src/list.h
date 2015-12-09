#ifndef list_H
#define list_H

#include "huffman.h"
#include "utilities.h"
#include "memory.h"
#include <string.h>

/* Defining as -2 to avoid confusion with EOF */
#define EMPTY -2

typedef struct nodeList {
   letter_t* start;
   letter_t* end;
   int notTagged;
} list_t;

void initList(list_t* list);
letter_t* initListNode(letter_t* prev, letter_t* next);
void addToList(list_t* list, char letter);
letter_t* addListNode(letter_t* end);
void reverseList(list_t* list);
void reverseNexts(letter_t* end);
void reversePrevs(letter_t* start);
void removeFromList(list_t* list, letter_t* word);
list_t duplicateList(list_t* list);
void removeWordsNotLength(int length, list_t* list);
void insertSorted(list_t* list, letter_t* letter);
void insertBefore(letter_t* beforeThis, letter_t* item, list_t* list);
void insertAtEnd(letter_t* item, list_t* list);
int listIsEmpty(list_t* list);


#endif
