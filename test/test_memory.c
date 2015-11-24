/*
 * Heaplist uses a STATIC var to store the lists in.
 * Not freeing the list after each test can mess up
 * subsequent tests
 */

#include "unity.h"
#include "memory.h"
#include "utilities.h"

void testToHeapListFirstTime(void)
{
   int* pointer1 = allocOfflist(sizeof(int));
   int* pointer2 = allocOfflist(sizeof(int));
   int* pointer3 = allocOfflist(sizeof(int));

   toHeapList(pointer1);
   toHeapList(pointer2);
   toHeapList(pointer3);

   heapList_t* list = getHeapList();
   TEST_ASSERT_EQUAL_PTR(pointer3, list->pnt);
   TEST_ASSERT_EQUAL_PTR(pointer2, list->prev->pnt);
   TEST_ASSERT_EQUAL_PTR(pointer1, list->prev->prev->pnt);

   freeHeapList();

}


void testAfterNewListCantFindOldList(void)
{
   int* pointer1 = allocOfflist(sizeof(int));
   int* pointer2 = allocOfflist(sizeof(int));
   int* pointer3 = allocOfflist(sizeof(int));
   heapList_t* list = NULL;
   toHeapList(pointer1);
   toHeapList(pointer2);
   toHeapList(pointer3);
   list = getHeapList();

   TEST_ASSERT_NOT_NULL(list->pnt);
   newHeapList();
   list = getHeapList();


   TEST_ASSERT_NULL(list->pnt);
   TEST_ASSERT_NULL(list->prev);
   freeHeapList();
}

void testAfterNewListCanFindNewList(void)
{
   int* pointer1 = allocOfflist(sizeof(int));
   int* pointer2 = allocOfflist(sizeof(int));
   int* pointer3 = allocOfflist(sizeof(int));

   int* pointer4 = allocOfflist(sizeof(int));
   int* pointer5 = allocOfflist(sizeof(int));
   int* pointer6 = allocOfflist(sizeof(int));

   toHeapList(pointer1);
   toHeapList(pointer2);
   toHeapList(pointer3);

   newHeapList();

   toHeapList(pointer4);
   toHeapList(pointer5);
   toHeapList(pointer6);

   heapList_t* list = getHeapList();
   TEST_ASSERT_EQUAL_PTR(pointer6, list->pnt);
   TEST_ASSERT_EQUAL_PTR(pointer5, list->prev->pnt);
   TEST_ASSERT_EQUAL_PTR(pointer4, list->prev->prev->pnt);
   freeHeapList();

}

void testAfterNewListCanFindFirstListInOldList(void)
{
   int* pointer1 = allocOfflist(sizeof(int));
   int* pointer2 = allocOfflist(sizeof(int));
   int* pointer3 = allocOfflist(sizeof(int));

   int* pointer4 = allocOfflist(sizeof(int));
   int* pointer5 = allocOfflist(sizeof(int));
   int* pointer6 = allocOfflist(sizeof(int));

   toHeapList(pointer1);
   toHeapList(pointer2);
   toHeapList(pointer3);

   newHeapList();

   toHeapList(pointer4);
   toHeapList(pointer5);
   toHeapList(pointer6);

   heapList_t* list = getHeapList();
   TEST_ASSERT_EQUAL_PTR(pointer3, list->lastList->pnt);
   TEST_ASSERT_EQUAL_PTR(pointer2, list->lastList->prev->pnt);
   TEST_ASSERT_EQUAL_PTR(pointer1, list->lastList->prev->prev->pnt);
   freeHeapList();

}

void testFreeHeapListReturnsMeToTopOfOldList(void)
{
   int* pointer1 = allocOfflist(sizeof(int));
   int* pointer2 = allocOfflist(sizeof(int));
   int* pointer3 = allocOfflist(sizeof(int));

   int* pointer4 = allocOfflist(sizeof(int));
   int* pointer5 = allocOfflist(sizeof(int));
   int* pointer6 = allocOfflist(sizeof(int));

   toHeapList(pointer1);
   toHeapList(pointer2);
   toHeapList(pointer3);

   newHeapList();

   toHeapList(pointer4);
   toHeapList(pointer5);
   toHeapList(pointer6);

   freeHeapList();

   heapList_t* list = getHeapList();

   TEST_ASSERT_EQUAL_PTR(pointer3, list->pnt);
   TEST_ASSERT_EQUAL_PTR(pointer2, list->prev->pnt);
   TEST_ASSERT_EQUAL_PTR(pointer1, list->prev->prev->pnt);

}

void testCanNowFreeListTwiceWithoutExploding(void)
{
   int* pointer1 = allocOfflist(sizeof(int));
   int* pointer2 = allocOfflist(sizeof(int));
   int* pointer3 = allocOfflist(sizeof(int));

   int* pointer4 = allocOfflist(sizeof(int));
   int* pointer5 = allocOfflist(sizeof(int));
   int* pointer6 = allocOfflist(sizeof(int));

   toHeapList(pointer1);
   toHeapList(pointer2);
   toHeapList(pointer3);

   newHeapList();

   toHeapList(pointer4);
   toHeapList(pointer5);
   toHeapList(pointer6);

   freeHeapList();


   heapList_t* list = getHeapList();

   TEST_ASSERT_EQUAL_PTR(pointer3, list->pnt);
   TEST_ASSERT_EQUAL_PTR(pointer2, list->prev->pnt);
   TEST_ASSERT_EQUAL_PTR(pointer1, list->prev->prev->pnt);

   freeHeapList();

}
