#include "unity.h"
#include "list.h"
#include "utilities.h"
#include "memory.h"
#include "dummyList.h"


int listLength(list_t list);
letter_t* copyLLIntoArray(list_t list);

void testInitWordList(void)
{
   list_t list;
   initList(&list);
   TEST_ASSERT_EQUAL_PTR(list.start, list.end);
   TEST_ASSERT_NULL(list.start->next);

}



void testInsertBeforeEndOfList(void)
{
   list_t list = dummyList();
   letter_t* seek = list.start;
   letter_t* oldstart = list.start;
   letter_t insertLetter;
   insertLetter.letter = 'l';
   while(seek != NULL)
   {
      if(seek->next == NULL) {
         insertBefore(seek, &insertLetter, &list);
      }
      seek = seek->next;
   }
   TEST_ASSERT_NOT_NULL(list.end->prev);
   TEST_ASSERT_NOT_NULL(list.end->prev->prev);
   TEST_ASSERT_NOT_NULL(list.end->prev->prev->prev);
   TEST_ASSERT_EQUAL_INT('l', list.end->prev->letter);
   TEST_ASSERT_EQUAL_PTR(oldstart, list.start);
   TEST_ASSERT_NOT_NULL(list.start->next);
   TEST_ASSERT_NOT_NULL(list.start->next->next);

}

void testAddToWordList(void)
{
   list_t list;
   initList(&list);
   addToList(&list, 'a');
   TEST_ASSERT_NOT_NULL(list.end);
   TEST_ASSERT_EQUAL_INT('a', list.end->letter);

   addToList(&list, 'c');
   TEST_ASSERT_EQUAL_INT('c', list.end->letter);

   addToList(&list, 'b');
   TEST_ASSERT_EQUAL_INT('b', list.end->letter);
   TEST_ASSERT_EQUAL_INT('c', list.end->prev->letter);
}

void testRemoveFromListRewiresListItems(void)
{
   list_t list = dummyList();
   letter_t* wordToRemove = list.start->next->next;
   letter_t* before = list.start->next;
   letter_t* after = list.start->next->next->next;
   removeFromList(&list, wordToRemove);
   TEST_ASSERT_EQUAL_PTR(before, after->prev);
   TEST_ASSERT_EQUAL_PTR(after, before->next);
   TEST_ASSERT_NULL(wordToRemove->next);
   TEST_ASSERT_NULL(wordToRemove->prev);
}


void testRemoveFromListRewiresStart(void)
{
   list_t list = dummyList();
   letter_t* wordToRemove = list.start;
   letter_t* after = list.start->next;

   removeFromList(&list, wordToRemove);
   TEST_ASSERT_EQUAL_PTR(after, list.start);
}

void testRemoveFromListRewiresEnd(void)
{
   list_t list = dummyList();
   letter_t* wordToRemove = list.start->next->next->next->next->next->next->next;
   letter_t* before = list.start->next->next->next->next->next->next;
   removeFromList(&list, wordToRemove);
   TEST_ASSERT_EQUAL_PTR(before, list.end);
}


void testInsertSortSortsList(void)
{
   list_t list = dummyList();
   int length = listLength(list);
   letter_t* array = copyLLIntoArray(list);

   list_t newList = insertionSort(array, length);
   TEST_ASSERT_NOT_NULL(newList.start);
   TEST_ASSERT_NOT_NULL(newList.end);
   TEST_ASSERT_EQUAL_INT('a', newList.start->letter);
   TEST_ASSERT_EQUAL_INT('g', newList.start->next->letter);
   TEST_ASSERT_EQUAL_INT('o', newList.start->next->next->letter);
   TEST_ASSERT_EQUAL_INT('j', newList.end->letter);
}


void testInsertBeforeInsertsInList(void)
{
   list_t list = dummyList();
   letter_t insertLetter;
   insertLetter.freq = 28;
   insertLetter.letter = 'l';

   insertBefore(list.start->next, &insertLetter, &list);
   TEST_ASSERT_EQUAL_INT('l', list.start->next->letter);
   TEST_ASSERT_EQUAL_INT('f', list.start->letter);
   TEST_ASSERT_NOT_NULL(list.start->next->next);
   TEST_ASSERT_EQUAL_INT('s', list.start->next->next->letter);
}

int listLength(list_t list)
{
   int i = 0;
   letter_t* seek = list.start;
   while(seek != NULL) {
      i++;
      seek = seek->next;
   }
   return i;
}

letter_t* copyLLIntoArray(list_t list)
{
   int i;
   int length = listLength(list);
   letter_t* array = (letter_t*)malloc(sizeof(letter_t) * length);
   letter_t* seek = list.start;
   for(i = 0; i < length; i++) {
      array[i] = *seek;
      seek = seek->next;
   }
   return array;
}



void testInsertBeforeInsertsStartOfListCorrectly(void)
{
   list_t list = dummyList();
   letter_t insertLetter;
   insertLetter.freq = 28;
   insertLetter.letter = 'l';
   insertBefore(list.start, &insertLetter, &list);
   TEST_ASSERT_EQUAL_INT('l', list.start->letter);
   TEST_ASSERT_NOT_NULL(list.start->next);
   TEST_ASSERT_EQUAL_INT('f', list.start->next->letter);
}


void testListLengthWorksProperly(void)
{
   list_t list;
   initList(&list);
   letter_t i1, i2, i3, i4, i5, i6, i7;
   TEST_ASSERT_EQUAL_INT(0, list.length);

   insertBefore(list.start, &i1, &list);
   TEST_ASSERT_EQUAL_INT(1, list.length);

   i2.freq = i3.freq = i4.freq = 0;
   i5.freq = i6.freq = i7.freq = 1;

   addToList(&list, 'l');
   addToList(&list, 'n');
   addToList(&list, 'f');
   TEST_ASSERT_EQUAL_INT(4, list.length);
}

void testInsertAtEndPutsItemAtEndOfList(void)
{
   list_t list = dummyList();
   letter_t insertLetter;
   insertLetter.freq = 28;
   insertLetter.letter = 'r';
   insertAtEnd(&insertLetter, &list);
   TEST_ASSERT_NOT_NULL(list.end);
   TEST_ASSERT_EQUAL_INT('r', list.end->letter);
   TEST_ASSERT_EQUAL_INT('r', list.start->next->next->next->next->next->next->next->next->letter);
}

void testInsertAtEndPutsItemInEmptyListCorrectly(void)
{
   list_t list;
   initList(&list);
   letter_t insertLetter;
   insertLetter.freq = 28;
   insertLetter.letter = 'r';
   insertAtEnd(&insertLetter, &list);
   TEST_ASSERT_EQUAL_INT('r', list.end->letter);
   TEST_ASSERT_EQUAL_INT('r', list.start->letter);
   TEST_ASSERT_EQUAL_PTR(list.start, list.end);
}


void testInsertSortedInsertsInRightPlace(void)
{
   list_t list;
   initList(&list);

   letter_t firstLetter = {
      .freq = 4,
      .letter = 'a'
   };

   letter_t secondLetter = {
      .freq = 2,
      .letter = 'b'
   };

   letter_t thirdLetter = {
      .freq = 7,
      .letter = 'f'
   };

   letter_t fourthLetter = {
      .freq = 1,
      .letter = 'z'
   };

   insertSorted(&list, &firstLetter);

   TEST_ASSERT_EQUAL_INT('a', list.end->letter);
   insertSorted(&list, &secondLetter);

   TEST_ASSERT_EQUAL_INT('b', list.start->letter);
   TEST_ASSERT_EQUAL_INT('a', list.start->next->letter);
   insertSorted(&list, &thirdLetter);

   TEST_ASSERT_EQUAL_INT('f', list.end->letter);
   insertSorted(&list, &fourthLetter);

   TEST_ASSERT_EQUAL_INT('z', list.start->letter);
   TEST_ASSERT_NOT_NULL(list.start);
   TEST_ASSERT_EQUAL_INT('a', list.start->next->next->letter);
   TEST_ASSERT_EQUAL_INT('z', list.start->letter);
   TEST_ASSERT_EQUAL_INT('b', list.start->next->letter);
   TEST_ASSERT_EQUAL_INT('a', list.start->next->next->letter);
   TEST_ASSERT_NOT_NULL(list.start->next->next->next);

   TEST_ASSERT_EQUAL_INT('f', list.end->letter);
   TEST_ASSERT_EQUAL_INT('f', list.start->next->next->next->letter);
}
