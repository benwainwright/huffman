/*
 * Word Ladders assignment
 *
 * Functions in this file handle the initialisation and management
 * of the word list
 *
 * Author: Ben Wainwright
 * Date: November 2015
 */

#include "list.h"

void initList(list_t* list)
{
   word_t* node = initListNode(NULL, NULL);
   list->start = node;
   list->end = node;
}

word_t* initListNode(word_t* prev, word_t* next)
{
   word_t* node = (word_t*)allocate(sizeof(word_t));
   node->next = next;
   node->prev = prev;
   node->parent = NULL;
   node->word = NULL;
   node->depth = 0;
   return node;
}

word_t* addListNode(word_t* end)
{
   word_t* newNode = initListNode(end, NULL);
   end->next = newNode;
   return newNode;
}

void addWordToList(list_t* list, char* word)
{
   if(list->end->word != NULL) {
      list->end = addListNode(list->end);
   }
   list->end->word = word;
}

void removeWordFromList(list_t* list, word_t* word)
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
   word_t* end = NULL;
   reverseNexts(list->end);
   reversePrevs(list->end);
   end = list->start;
   list->start = list->end;
   list->end = end;
}

void reverseNexts(word_t* end)
{
   word_t* next = end;
   while(end != NULL) {
      end = end->prev;
      next->next = end;
      next = next->next;
   }
}

void reversePrevs(word_t* start)
{
   word_t* prev = NULL;
   while(start != NULL) {
      start->prev = prev;
      prev = start;
      start = start->next;
   }
}

list_t duplicateList(list_t* list)
{
   list_t dupeList;
   word_t* seek = NULL, *newNode = NULL;

   seek = list->start;
   do {
      newNode = initListNode(newNode, NULL);
      newNode->word = seek->word;
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

void removeWordsNotLength(int length, list_t* list)
{
   word_t* seek = list->start;
   word_t* next = NULL;
   while(seek != NULL) {
      next = seek->next;
      if((int)strlen(seek->word) != length) {
         removeWordFromList(list, seek);
      }
      seek = next;
   }
}
