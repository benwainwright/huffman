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

int listIsEmpty(list_t* list)
{
   return (list->end == list->start && list->start->letter == EMPTY);
}
