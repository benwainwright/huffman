/*
 * Huffman assignment
 *
 * Functions in this file handle the initialisation and management
 * of the word list. Adapted and expanded from word ladder assignment
 *
 * Author: Ben Wainwright
 * Date: November 2015
 */

#include "list.h"

void initList(list_t* list)
{
   letter_t* node = initListNode(NULL, NULL);
   list->start = node;
   list->end = node;
   list->start->letter = EMPTY;
   list->start->freq = 0;
   list->length = 0;
}

letter_t* initListNode(letter_t* prev, letter_t* next)
{
   letter_t* node = (letter_t*)allocate(sizeof(letter_t));
   node->next = next;
   node->prev = prev;
   node->left = NULL;
   node->right = NULL;
   return node;
}

void deleteZerosFromList(list_t* list)
{
   letter_t* seek = list->start;
   letter_t* next = NULL;
   while(seek != NULL)
   {
      next = seek->next;
      if(seek->freq == 0) {
         removeFromList(list, seek);
      }
      seek = next;
   }
}

void removeFromList(list_t* list, letter_t* letter)
{
   if(letter->next != NULL) {
      letter->next->prev = letter->prev;
   }
   else {
      list->end = letter->prev;
   }
   if(letter->prev != NULL) {
      letter->prev->next = letter->next;
   }
   else {
      list->start = letter->next;
   }
   letter->next = NULL;
   letter->prev = NULL;
   list->length--;
}



letter_t* addListNode(letter_t* end)
{
   letter_t* newNode = initListNode(end, NULL);
   end->next = newNode;
   return newNode;
}

void addToList(list_t* list, char letter)
{
   if(list->end->letter != EMPTY) {
      list->end = addListNode(list->end);
   }
   list->end->letter = letter;
   list->length++;
}


void reverseList(list_t* list)
{
   letter_t* end = NULL;
   reverseNexts(list->end);
   reversePrevs(list->end);
   end = list->start;
   list->start = list->end;
   list->end = end;
}

void reverseNexts(letter_t* end)
{
   letter_t* next = end;
   while(end != NULL) {
      end = end->prev;
      next->next = end;
      next = next->next;
   }
}

list_t insertionSort(letter_t* asciiGram, int length)
{

   int i;
   list_t newList;
   initList(&newList);

   for(i = 0; i < length; i++) {
      insertSorted(&newList, &asciiGram[i]);
   }
   return newList;

}

void duplicateLetter(letter_t** dest, letter_t* source)
{
   *dest = initListNode(source->prev, source->next);
   (*dest)->freq = source->freq;
   (*dest)->letter = source->letter;
}

void insertSorted(list_t* list, letter_t* letter)
{
   int i = 0;
   letter_t* seek = list->start;
   while(seek != NULL) {
      if (letter->freq < seek->freq) {
         insertBefore(seek, letter, list);
         return;
      }
      seek = seek->next;
   }
   insertAtEnd(letter, list);
}
void insertBefore(letter_t* beforeThis, letter_t* item, list_t* list)
{
   if(listIsEmpty(list)) {
      replaceOnlyItem(item, list);
   }
   else {
      if(beforeThis->prev == NULL) {
            list->start = item;
      }
      else {
         beforeThis->prev->next = item;
      }
      item->next = beforeThis;
      item->prev = beforeThis->prev;
      beforeThis->prev = item;
   }
   list->length++;
}


void replaceOnlyItem(letter_t* item, list_t* list)
{
   list->start = item;
   list->end = item;
   item->prev = NULL;
   item->next = NULL;

}
void insertAtEnd(letter_t* item, list_t* list)
{
   if(listIsEmpty(list)) {
      replaceOnlyItem(item, list);
   } else {
      item->next = NULL;
      item->prev = list->end;
      list->end->next = item;
      list->end = item;
   }
   list->length++;
}


void printList(list_t list)
{
   letter_t* seek = list.start;
   int character = 0;

   while(seek != NULL)
   {
      if (isprint(seek->letter)) {
         character = seek->letter;
      }
      else {
         character = 'x';
      }
      printf("%c(%d) ", character, seek->freq);
      seek = seek->next;
   }
}
int listIsEmpty(list_t* list)
{
   return (list->end == list->start && list->start->letter == EMPTY);
}



void reversePrevs(letter_t* start)
{
   letter_t* prev = NULL;
   while(start != NULL) {
      start->prev = prev;
      prev = start;
      start = start->next;
   }
}

list_t duplicateList(list_t* list)
{
   list_t dupeList;
   letter_t* seek = NULL, *newNode = NULL;

   seek = list->start;
   do {
      newNode = initListNode(newNode, NULL);
      newNode->letter = seek->letter;
      if(newNode->prev == NULL) {
         dupeList.start = newNode;
      }
      else {
         newNode->prev->next = newNode;
      }
      seek = seek->next;
   } while(seek != NULL);
   newNode->prev->next = newNode;
   dupeList.end = newNode;
   dupeList.length = list->length;
   return dupeList;
}
