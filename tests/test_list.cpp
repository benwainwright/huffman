#include <gtest/gtest.h>

extern "C" {
#include "list.h"
#include "utilities.h"
#include "memory.h"
#include "shared/dummyList.h"
}

int listLength(list_t list);
letter_t* copyLLIntoArray(list_t list);

TEST(List, InitWordList)
{
   list_t list;
   initList(&list);
   EXPECT_EQ(list.start, list.end);
   ASSERT_EQ((letter_t*)NULL, list.start->next);
}

TEST(List, InsertBeforeEndOfList)
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
   ASSERT_NE((letter_t*)NULL,list.end->prev);
   ASSERT_NE((letter_t*)NULL,list.end->prev->prev);
   ASSERT_NE((letter_t*)NULL,list.end->prev->prev->prev);
   EXPECT_EQ('l', list.end->prev->letter);
   EXPECT_EQ(oldstart, list.start);
   ASSERT_NE((letter_t*)NULL,list.start->next);
   ASSERT_NE((letter_t*)NULL,list.start->next->next);

}

TEST(List, AddToWordList)
{
   list_t list;
   initList(&list);
   addToList(&list, 'a');
   ASSERT_NE((letter_t*)NULL,list.end);
   EXPECT_EQ('a', list.end->letter);

   addToList(&list, 'c');
   EXPECT_EQ('c', list.end->letter);

   addToList(&list, 'b');
   EXPECT_EQ('b', list.end->letter);
   EXPECT_EQ('c', list.end->prev->letter);
}

TEST(List, RemoveFromListRewiresListItems)
{
   list_t list = dummyList();
   letter_t* wordToRemove = list.start->next->next;
   letter_t* before = list.start->next;
   letter_t* after = list.start->next->next->next;
   removeFromList(&list, wordToRemove);
   EXPECT_EQ(before, after->prev);
   EXPECT_EQ(after, before->next);
   EXPECT_EQ((letter_t*)NULL,wordToRemove->next);
   EXPECT_EQ((letter_t*)NULL,wordToRemove->prev);
}

TEST(List, RemoveFromListRewiresStart)
{
   list_t list = dummyList();
   letter_t* wordToRemove = list.start;
   letter_t* after = list.start->next;

   removeFromList(&list, wordToRemove);
   EXPECT_EQ(after, list.start);
}

TEST(List, RemoveFromListRewiresEnd)
{
   list_t list = dummyList();
   letter_t* wordToRemove = list.start->next->next->next->next->next->next->next;
   letter_t* before = list.start->next->next->next->next->next->next;
   removeFromList(&list, wordToRemove);
   EXPECT_EQ(before, list.end);
}


TEST(List, InsertSortSortsList)
{
   list_t list = dummyList();
   int length = listLength(list);
   letter_t* array = copyLLIntoArray(list);

   list_t newList = insertionSort(array, length);
   ASSERT_NE((letter_t*)NULL,newList.start);
   ASSERT_NE((letter_t*)NULL,newList.end);
   EXPECT_EQ('a', newList.start->letter);
   EXPECT_EQ('g', newList.start->next->letter);
   EXPECT_EQ('o', newList.start->next->next->letter);
   EXPECT_EQ('j', newList.end->letter);
}


void testInsertBeforeInsertsInList(void)
{
   list_t list = dummyList();
   letter_t insertLetter;
   insertLetter.freq = 28;
   insertLetter.letter = 'l';

   insertBefore(list.start->next, &insertLetter, &list);
   EXPECT_EQ('l', list.start->next->letter);
   EXPECT_EQ('f', list.start->letter);
   ASSERT_NE((letter_t*)NULL,list.start->next->next);
   EXPECT_EQ('s', list.start->next->next->letter);
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

TEST(List, InsertBeforeInsertsStartOfListCorrectly)
{
   list_t list = dummyList();
   letter_t insertLetter;
   insertLetter.freq = 28;
   insertLetter.letter = 'l';
   insertBefore(list.start, &insertLetter, &list);
   EXPECT_EQ('l', list.start->letter);
   ASSERT_NE((letter_t*)NULL,list.start->next);
   EXPECT_EQ('f', list.start->next->letter);
}


TEST(List, ListLengthWorksProperly)
{
   list_t list;
   initList(&list);
   letter_t i1, i2, i3, i4, i5, i6, i7;
   EXPECT_EQ(0, list.length);

   insertBefore(list.start, &i1, &list);
   EXPECT_EQ(1, list.length);

   i2.freq = i3.freq = i4.freq = 0;
   i5.freq = i6.freq = i7.freq = 1;

   addToList(&list, 'l');
   addToList(&list, 'n');
   addToList(&list, 'f');
   EXPECT_EQ(4, list.length);
}

TEST(List, InsertAtEndPutsItemAtEndOfList)
{
   list_t list = dummyList();
   letter_t insertLetter;
   insertLetter.freq = 28;
   insertLetter.letter = 'r';
   insertAtEnd(&insertLetter, &list);
   ASSERT_NE((letter_t*)NULL,list.end);
   EXPECT_EQ('r', list.end->letter);
   EXPECT_EQ('r', list.start->next->next->next->next->next->next->next->next->letter);
}

TEST(List, InsertAtEndPutsItemInEmptyListCorrectly)
{
   list_t list;
   initList(&list);
   letter_t insertLetter;
   insertLetter.freq = 28;
   insertLetter.letter = 'r';
   insertAtEnd(&insertLetter, &list);
   EXPECT_EQ('r', list.end->letter);
   EXPECT_EQ('r', list.start->letter);
   EXPECT_EQ(list.start, list.end);
}


TEST(List, InsertSortedInsertsInRightPlace)
{
   list_t list;
   initList(&list);

   letter_t firstLetter;
   firstLetter.freq = 4;
   firstLetter.letter = 'a';

   letter_t secondLetter;
   secondLetter.freq = 2;
   secondLetter.letter = 'b';

   letter_t thirdLetter;
   thirdLetter.freq = 7;
   thirdLetter.letter = 'f';

   letter_t fourthLetter;
   fourthLetter.freq = 1;
   fourthLetter.letter = 'z';

   insertSorted(&list, &firstLetter);

   EXPECT_EQ('a', list.end->letter);
   insertSorted(&list, &secondLetter);

   EXPECT_EQ('b', list.start->letter);
   EXPECT_EQ('a', list.start->next->letter);
   insertSorted(&list, &thirdLetter);

   EXPECT_EQ('f', list.end->letter);
   insertSorted(&list, &fourthLetter);

   EXPECT_EQ('z', list.start->letter);
   ASSERT_NE((letter_t*)NULL,list.start);
   EXPECT_EQ('a', list.start->next->next->letter);
   EXPECT_EQ('z', list.start->letter);
   EXPECT_EQ('b', list.start->next->letter);
   EXPECT_EQ('a', list.start->next->next->letter);
   ASSERT_NE((letter_t*)NULL,list.start->next->next->next);

   EXPECT_EQ('f', list.end->letter);
   EXPECT_EQ('f', list.start->next->next->next->letter);
}
