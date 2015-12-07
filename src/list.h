#ifndef list_H
#define list_H

#include "types.h"
#include "utilities.h"
#include "memory.h"
#include <string.h>

void initList(list_t* list);
word_t* initListNode(word_t* prev, word_t* next);
void addWordToList(list_t* list, char* word);
word_t* addListNode(word_t* end);
void reverseList(list_t* list);
void reverseNexts(word_t* end);
void reversePrevs(word_t* start);
void removeWordFromList(list_t* list, word_t* word);
list_t duplicateList(list_t* list);
void removeWordsNotLength(int length, list_t* list);


#endif
