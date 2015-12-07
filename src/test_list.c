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
   TEST_ASSERT_NULL(list.start->word);
   TEST_ASSERT_NULL(list.start->next);
   TEST_ASSERT_NULL(list.start->parent);
}


void testDuplicateList(void)
{
   list_t list1 = dummyList();
   list_t list2 = duplicateList(&list1);
   if(list2.start != NULL) {
      TEST_ASSERT_EQUAL_PTR(list1.start->word, list2.start->word);
      TEST_ASSERT_EQUAL_PTR(list1.start->next->word, list2.start->next->word);
      TEST_ASSERT_EQUAL_PTR(list1.start->next->next->word, list2.start->next->next->word);
      TEST_ASSERT_EQUAL_PTR(list1.start->next->next->next->next->next->next->word, list2.start->next->next->next->next->next->next->word);
      TEST_ASSERT_EQUAL_PTR(list1.start->next->next->next->next->next->next->next->word, list2.start->next->next->next->next->next->next->next->word);
      TEST_ASSERT_EQUAL_PTR(list1.end->word, list2.end->word);
   }
   else {
      TEST_FAIL();
   }
}

void testAddToWordList(void)
{
   list_t list;
   initList(&list);
   addWordToList(&list, "chris");
   TEST_ASSERT_NOT_NULL(list.end);
   TEST_ASSERT_EQUAL_STRING("chris", list.end->word);

   addWordToList(&list, "james");
   TEST_ASSERT_EQUAL_STRING("james", list.end->word);

   addWordToList(&list, "jess");
   TEST_ASSERT_EQUAL_STRING("jess", list.end->word);
   TEST_ASSERT_EQUAL_STRING("james", list.end->prev->word);
}

void testRemoveFromListRewiresListItems(void)
{
   list_t list = dummyList();
   word_t* wordToRemove = list.start->next->next;
   word_t* before = list.start->next;
   word_t* after = list.start->next->next->next;
   removeWordFromList(&list, wordToRemove);
   TEST_ASSERT_EQUAL_PTR(before, after->prev);
   TEST_ASSERT_EQUAL_PTR(after, before->next);
   TEST_ASSERT_NULL(wordToRemove->next);
   TEST_ASSERT_NULL(wordToRemove->prev);
}


void testRemoveFromListRewiresStart(void)
{
   list_t list = dummyList();
   word_t* wordToRemove = list.start;
   word_t* after = list.start->next;

   removeWordFromList(&list, wordToRemove);
   TEST_ASSERT_EQUAL_PTR(after, list.start);
}

void testRemoveFromListRewiresEnd(void)
{
   list_t list = dummyList();
   word_t* wordToRemove = list.start->next->next->next->next->next->next->next;
   word_t* before = list.start->next->next->next->next->next->next;
   removeWordFromList(&list, wordToRemove);
   TEST_ASSERT_EQUAL_PTR(before, list.end);
}

void testReverseList(void)
{
   list_t list = dummyList();
   reverseList(&list);
   TEST_ASSERT_EQUAL_STRING("james", list.start->word);
   TEST_ASSERT_EQUAL_STRING("jimes", list.start->next->word);
   TEST_ASSERT_EQUAL_STRING("aames", list.start->next->next->word);
   TEST_ASSERT_EQUAL_STRING("james", list.start->next->prev->word);
   TEST_ASSERT_EQUAL_STRING("jimes", list.start->next->next->prev->word);
   TEST_ASSERT_NULL(list.start->prev);
   TEST_ASSERT_NULL(list.end->next);
}
