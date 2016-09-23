/*
 * Heaplist uses a STATIC var to store the lists in.
 * Not freeing the list after each test can mess up
 * subsequent tests
 */

#include <gtest/gtest.h>

extern "C" {
#include "memory.h"
#include "utilities.h"
}

TEST(Heaplist, ToHeapListFirstTime)
{
   int* pointer1 = (int*)allocOfflist(sizeof(int));
   int* pointer2 = (int*)allocOfflist(sizeof(int));
   int* pointer3 = (int*)allocOfflist(sizeof(int));

   toHeapList(pointer1);
   toHeapList(pointer2);
   toHeapList(pointer3);

   heapList_t* list = getHeapList();
   EXPECT_EQ(pointer3, list->pnt);
   EXPECT_EQ(pointer2, list->prev->pnt);
   EXPECT_EQ(pointer1, list->prev->prev->pnt);

   freeHeapList();

}


TEST(HeapList, AfterNewListCantFindOldList)
{
   int* pointer1 = (int*)allocOfflist(sizeof(int));
   int* pointer2 = (int*)allocOfflist(sizeof(int));
   int* pointer3 = (int*)allocOfflist(sizeof(int));
   heapList_t* list = NULL;
   toHeapList(pointer1);
   toHeapList(pointer2);
   toHeapList(pointer3);
   list = getHeapList();

   EXPECT_NE((void*)NULL, list->pnt);
   newHeapList();
   list = getHeapList();


   EXPECT_EQ((void*)NULL, list->pnt);
   EXPECT_EQ((void*)NULL, list->prev);
   freeHeapList();
}

TEST(HeapList, AfterNewListCanFindNewList)
{
   int* pointer1 = (int*)allocOfflist(sizeof(int));
   int* pointer2 = (int*)allocOfflist(sizeof(int));
   int* pointer3 = (int*)allocOfflist(sizeof(int));

   int* pointer4 = (int*)allocOfflist(sizeof(int));
   int* pointer5 = (int*)allocOfflist(sizeof(int));
   int* pointer6 = (int*)allocOfflist(sizeof(int));

   toHeapList(pointer1);
   toHeapList(pointer2);
   toHeapList(pointer3);

   newHeapList();

   toHeapList(pointer4);
   toHeapList(pointer5);
   toHeapList(pointer6);

   heapList_t* list = getHeapList();
   EXPECT_EQ(pointer6, list->pnt);
   EXPECT_EQ(pointer5, list->prev->pnt);
   EXPECT_EQ(pointer4, list->prev->prev->pnt);
   freeHeapList();
}

TEST(HeapList, AfterNewListCanFindFirstListInOldList)
{
   int* pointer1 = (int*)allocOfflist(sizeof(int));
   int* pointer2 = (int*)allocOfflist(sizeof(int));
   int* pointer3 = (int*)allocOfflist(sizeof(int));

   int* pointer4 = (int*)allocOfflist(sizeof(int));
   int* pointer5 = (int*)allocOfflist(sizeof(int));
   int* pointer6 = (int*)allocOfflist(sizeof(int));

   toHeapList(pointer1);
   toHeapList(pointer2);
   toHeapList(pointer3);

   newHeapList();

   toHeapList(pointer4);
   toHeapList(pointer5);
   toHeapList(pointer6);

   heapList_t* list = getHeapList();
   EXPECT_EQ(pointer3, list->lastList->pnt);
   EXPECT_EQ(pointer2, list->lastList->prev->pnt);
   EXPECT_EQ(pointer1, list->lastList->prev->prev->pnt);
   freeHeapList();

}

TEST(HeapList, FreeHeapListReturnsMeToTopOfOldList)
{
   int* pointer1 = (int*)allocOfflist(sizeof(int));
   int* pointer2 = (int*)allocOfflist(sizeof(int));
   int* pointer3 = (int*)allocOfflist(sizeof(int));

   int* pointer4 = (int*)allocOfflist(sizeof(int));
   int* pointer5 = (int*)allocOfflist(sizeof(int));
   int* pointer6 = (int*)allocOfflist(sizeof(int));

   toHeapList(pointer1);
   toHeapList(pointer2);
   toHeapList(pointer3);

   newHeapList();

   toHeapList(pointer4);
   toHeapList(pointer5);
   toHeapList(pointer6);

   freeHeapList();

   heapList_t* list = getHeapList();

   EXPECT_EQ(pointer3, list->pnt);
   EXPECT_EQ(pointer2, list->prev->pnt);
   EXPECT_EQ(pointer1, list->prev->prev->pnt);

}

TEST(HeapList, CanNowFreeListTwiceWithoutExploding)
{
   int* pointer1 = (int*)allocOfflist(sizeof(int));
   int* pointer2 = (int*)allocOfflist(sizeof(int));
   int* pointer3 = (int*)allocOfflist(sizeof(int));

   int* pointer4 = (int*)allocOfflist(sizeof(int));
   int* pointer5 = (int*)allocOfflist(sizeof(int));
   int* pointer6 = (int*)allocOfflist(sizeof(int));

   toHeapList(pointer1);
   toHeapList(pointer2);
   toHeapList(pointer3);

   newHeapList();

   toHeapList(pointer4);
   toHeapList(pointer5);
   toHeapList(pointer6);

   freeHeapList();


   heapList_t* list = getHeapList();

   EXPECT_EQ(pointer3, list->pnt);
   EXPECT_EQ(pointer2, list->prev->pnt);
   EXPECT_EQ(pointer1, list->prev->prev->pnt);

   freeHeapList();

}
