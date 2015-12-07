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
   addWordToList(&list, 'a');
   TEST_ASSERT_NOT_NULL(list.end);
   TEST_ASSERT_EQUAL_INT('a', list.end->letter);

   addWordToList(&list, 'c');
   TEST_ASSERT_EQUAL_INT('c', list.end->letter);

   addWordToList(&list, 'b');
   TEST_ASSERT_EQUAL_INT('b', list.end->letter);
   TEST_ASSERT_EQUAL_INT('c', list.end->prev->letter);
}

void testRemoveFromListRewiresListItems(void)
{
   list_t list = dummyList();
   letter_t* wordToRemove = list.start->next->next;
   letter_t* before = list.start->next;
   letter_t* after = list.start->next->next->next;
   removeWordFromList(&list, wordToRemove);
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

   removeWordFromList(&list, wordToRemove);
   TEST_ASSERT_EQUAL_PTR(after, list.start);
}

void testRemoveFromListRewiresEnd(void)
{
   list_t list = dummyList();
   letter_t* wordToRemove = list.start->next->next->next->next->next->next->next;
   letter_t* before = list.start->next->next->next->next->next->next;
   removeWordFromList(&list, wordToRemove);
   TEST_ASSERT_EQUAL_PTR(before, list.end);
}

void testReverseList(void)
{
   list_t list = dummyList();
   reverseList(&list);
   TEST_ASSERT_EQUAL_STRING("james", list.start->letter);
   TEST_ASSERT_EQUAL_STRING("jimes", list.start->next->letter);
   TEST_ASSERT_EQUAL_STRING("aames", list.start->next->next->letter);
   TEST_ASSERT_EQUAL_STRING("james", list.start->next->prev->letter);
   TEST_ASSERT_EQUAL_STRING("jimes", list.start->next->next->prev->letter);
   TEST_ASSERT_NULL(list.start->prev);
   TEST_ASSERT_NULL(list.end->next);
}
