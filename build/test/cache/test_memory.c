#include "utilities.h"
#include "memory.h"
#include "unity.h"














void testToHeapListFirstTime(void)

{

   int* pointer1 = allocOfflist(sizeof(int));

   int* pointer2 = allocOfflist(sizeof(int));

   int* pointer3 = allocOfflist(sizeof(int));



   toHeapList(pointer1);

   toHeapList(pointer2);

   toHeapList(pointer3);



   heapList_t* list = getHeapList();

   UnityAssertEqualNumber((_U_SINT)(_UP)((pointer3)), (_U_SINT)(_UP)((list->pnt)), (((void *)0)), (_U_UINT)22, UNITY_DISPLAY_STYLE_HEX64);

   UnityAssertEqualNumber((_U_SINT)(_UP)((pointer2)), (_U_SINT)(_UP)((list->prev->pnt)), (((void *)0)), (_U_UINT)23, UNITY_DISPLAY_STYLE_HEX64);

   UnityAssertEqualNumber((_U_SINT)(_UP)((pointer1)), (_U_SINT)(_UP)((list->prev->prev->pnt)), (((void *)0)), (_U_UINT)24, UNITY_DISPLAY_STYLE_HEX64);



   freeHeapList();



}





void testAfterNewListCantFindOldList(void)

{

   int* pointer1 = allocOfflist(sizeof(int));

   int* pointer2 = allocOfflist(sizeof(int));

   int* pointer3 = allocOfflist(sizeof(int));

   heapList_t* list = ((void *)0);

   toHeapList(pointer1);

   toHeapList(pointer2);

   toHeapList(pointer3);

   list = getHeapList();



   if ((((list->pnt)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)42);;};

   newHeapList();

   list = getHeapList();





   if ((((list->pnt)) == ((void *)0))) {} else {UnityFail( (" Expected NULL"), (_U_UINT)(_U_UINT)(_U_UINT)47);;};

   if ((((list->prev)) == ((void *)0))) {} else {UnityFail( (" Expected NULL"), (_U_UINT)(_U_UINT)(_U_UINT)48);;};

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

   UnityAssertEqualNumber((_U_SINT)(_UP)((pointer6)), (_U_SINT)(_UP)((list->pnt)), (((void *)0)), (_U_UINT)73, UNITY_DISPLAY_STYLE_HEX64);

   UnityAssertEqualNumber((_U_SINT)(_UP)((pointer5)), (_U_SINT)(_UP)((list->prev->pnt)), (((void *)0)), (_U_UINT)74, UNITY_DISPLAY_STYLE_HEX64);

   UnityAssertEqualNumber((_U_SINT)(_UP)((pointer4)), (_U_SINT)(_UP)((list->prev->prev->pnt)), (((void *)0)), (_U_UINT)75, UNITY_DISPLAY_STYLE_HEX64);

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

   UnityAssertEqualNumber((_U_SINT)(_UP)((pointer3)), (_U_SINT)(_UP)((list->lastList->pnt)), (((void *)0)), (_U_UINT)101, UNITY_DISPLAY_STYLE_HEX64);

   UnityAssertEqualNumber((_U_SINT)(_UP)((pointer2)), (_U_SINT)(_UP)((list->lastList->prev->pnt)), (((void *)0)), (_U_UINT)102, UNITY_DISPLAY_STYLE_HEX64);

   UnityAssertEqualNumber((_U_SINT)(_UP)((pointer1)), (_U_SINT)(_UP)((list->lastList->prev->prev->pnt)), (((void *)0)), (_U_UINT)103, UNITY_DISPLAY_STYLE_HEX64);

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



   UnityAssertEqualNumber((_U_SINT)(_UP)((pointer3)), (_U_SINT)(_UP)((list->pnt)), (((void *)0)), (_U_UINT)132, UNITY_DISPLAY_STYLE_HEX64);

   UnityAssertEqualNumber((_U_SINT)(_UP)((pointer2)), (_U_SINT)(_UP)((list->prev->pnt)), (((void *)0)), (_U_UINT)133, UNITY_DISPLAY_STYLE_HEX64);

   UnityAssertEqualNumber((_U_SINT)(_UP)((pointer1)), (_U_SINT)(_UP)((list->prev->prev->pnt)), (((void *)0)), (_U_UINT)134, UNITY_DISPLAY_STYLE_HEX64);



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



   UnityAssertEqualNumber((_U_SINT)(_UP)((pointer3)), (_U_SINT)(_UP)((list->pnt)), (((void *)0)), (_U_UINT)163, UNITY_DISPLAY_STYLE_HEX64);

   UnityAssertEqualNumber((_U_SINT)(_UP)((pointer2)), (_U_SINT)(_UP)((list->prev->pnt)), (((void *)0)), (_U_UINT)164, UNITY_DISPLAY_STYLE_HEX64);

   UnityAssertEqualNumber((_U_SINT)(_UP)((pointer1)), (_U_SINT)(_UP)((list->prev->prev->pnt)), (((void *)0)), (_U_UINT)165, UNITY_DISPLAY_STYLE_HEX64);



   freeHeapList();



}
