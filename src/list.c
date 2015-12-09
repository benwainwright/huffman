/*
 * Word Ladders assignment
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
}

void removeFromList(list_t* list, letter_t* word)
{
   if(word->next != NULL) {
      word->next->prev = word->prev;
   }
   else {
      list->end = word->prev;
   }
   if(word->prev != NULL) {
      word->prev->next = word->next;
   }
   else {
      list->start = word->next;
   }
   word->next = NULL;
   word->prev = NULL;
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

void insertionSort(list_t* list)
{

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

void insertAtEnd(letter_t* item, list_t* list)
{
   if(listIsEmpty(list)) {
      list->start = item;
      item->prev = NULL;
      item->next = NULL;
   } else {
      item->prev = list->end;
   }
   list->end->next = item;
   list->end = item;
}

int listIsEmpty(list_t* list)
{
   return (list->end == list->start && list->start->letter == EMPTY);
}

void insertBefore(letter_t* beforeThis, letter_t* item, list_t* list)
{
   if(beforeThis->prev == NULL) {
      list->start = item;
   }
   else {
      beforeThis->prev->next = item;
   }
   beforeThis->prev = item;
   item->next = beforeThis;
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
   return dupeList;
}
