#include "unity.h"
#include "list.h"
#include "utilities.h"
#include "memory.h"
#include "dummyList.h"


void testInitWordList(void)
{
   list_t list;
   initList(&list);
   TEST_ASSERT_EQUAL_PTR(list.start, list.end);
   TEST_ASSERT_NULL(list.start->next);

}


void testDuplicateList(void)
{
   list_t list1 = dummyList();
   list_t list2 = duplicateList(&list1);
   if(list2.start != NULL) {
      TEST_ASSERT_EQUAL_INT(list1.start->letter, list2.start->letter);
      TEST_ASSERT_EQUAL_INT(list1.start->next->letter, list2.start->next->letter);
      TEST_ASSERT_EQUAL_INT(list1.start->next->next->letter, list2.start->next->next->letter);
      TEST_ASSERT_EQUAL_INT(list1.start->next->next->next->next->next->next->letter, list2.start->next->next->next->next->next->next->letter);
      TEST_ASSERT_EQUAL_INT(list1.start->next->next->next->next->next->next->next->letter, list2.start->next->next->next->next->next->next->next->letter);
      TEST_ASSERT_EQUAL_INT(list1.end->letter, list2.end->letter);
   }
   else {
      TEST_FAIL();
   }
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

void testReverseList(void)
{
   list_t list = dummyList();
   reverseList(&list);
   TEST_ASSERT_EQUAL_INT('j', list.start->letter);
   TEST_ASSERT_EQUAL_INT('i', list.start->next->letter);
   TEST_ASSERT_EQUAL_INT('a', list.start->next->next->letter);
   TEST_ASSERT_EQUAL_INT('j', list.start->next->prev->letter);
   TEST_ASSERT_EQUAL_INT('i', list.start->next->next->prev->letter);
   TEST_ASSERT_NULL(list.start->prev);
   TEST_ASSERT_NULL(list.end->next);
}

void testInsertSortSortsList(void)
{


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
   TEST_ASSERT_EQUAL_INT('a', list.end->letter);

   insertSorted(&list, &thirdLetter);
   TEST_ASSERT_EQUAL_INT('b', list.start->letter);
   TEST_ASSERT_EQUAL_INT('a', list.start->next->letter);
   TEST_ASSERT_EQUAL_INT('f', list.start->next->next->letter);
   TEST_ASSERT_EQUAL_INT('f', list.end->letter);

   insertSorted(&list, &fourthLetter);
   TEST_ASSERT_EQUAL_INT('z', list.start->letter);
   TEST_ASSERT_EQUAL_INT('b', list.start->next->letter);
   TEST_ASSERT_EQUAL_INT('a', list.start->next->next->letter);
   TEST_ASSERT_EQUAL_INT('f', list.start->next->next->next->letter);
   TEST_ASSERT_EQUAL_INT('f', list.end->letter);
}
