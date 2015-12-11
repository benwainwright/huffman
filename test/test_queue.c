#include "unity.h"
#include "queue.h"
#include "memory.h"
#include "utilities.h"
#include <stdlib.h>

void testinitQueueInitsBlankQueue(void)
{
   queue_t* queue;
   initQueue(&queue);
   TEST_ASSERT_NULL(queue->front);
   TEST_ASSERT_NULL(queue->back);
}

void testAddToQueueAddsPointerToQueue(void)
{
   queue_t* queue;
   letter_t* firstLetter = (letter_t*)malloc(sizeof(letter_t));
   initQueue(&queue);
   addToQueue(queue, firstLetter);
   TEST_ASSERT_EQUAL_PTR(firstLetter, queue->front);
   TEST_ASSERT_EQUAL_PTR(firstLetter, queue->back);
}

void testMultipleQueueAddsAreAddedCorrectly(void)
{
   queue_t* queue;
   letter_t* firstLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* secondLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* thirdLetter = (letter_t*)malloc(sizeof(letter_t));

   initQueue(&queue);
   addToQueue(queue, firstLetter);
   TEST_ASSERT_EQUAL_PTR(firstLetter, queue->front);
   TEST_ASSERT_EQUAL_PTR(firstLetter, queue->back);

   addToQueue(queue, secondLetter);
   TEST_ASSERT_EQUAL_PTR(firstLetter, queue->front);
   TEST_ASSERT_EQUAL_PTR(secondLetter, queue->back);

   addToQueue(queue, thirdLetter);
   TEST_ASSERT_EQUAL_PTR(firstLetter, queue->front);
   TEST_ASSERT_EQUAL_PTR(thirdLetter, queue->back);
   TEST_ASSERT_EQUAL_PTR(secondLetter, queue->back->next);
}

void testQueueLengthIsIncreasedCorrectly(void) {
   queue_t *queue;
   letter_t* firstLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* secondLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* thirdLetter = (letter_t*)malloc(sizeof(letter_t));

   initQueue(&queue);
   TEST_ASSERT_EQUAL_INT(0, queue->length);

   addToQueue(queue, firstLetter);
   TEST_ASSERT_EQUAL_INT(1, queue->length);

   addToQueue(queue, secondLetter);
   TEST_ASSERT_EQUAL_INT(2, queue->length);

   addToQueue(queue, thirdLetter);
   TEST_ASSERT_EQUAL_INT(3, queue->length);
}

void testRemoveFromQueueDecreasesLengthCorrectly(void) {
   queue_t* queue;
   letter_t* firstLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* secondLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* thirdLetter = (letter_t*)malloc(sizeof(letter_t));

   letter_t* result;
   initQueue(&queue);
   TEST_ASSERT_EQUAL_INT(0, queue->length);

   addToQueue(queue, firstLetter);
   addToQueue(queue, firstLetter);
   TEST_ASSERT_EQUAL_INT(2, queue->length);

   getFromQueue(queue);
   TEST_ASSERT_EQUAL_INT(1, queue->length);
   addToQueue(queue, firstLetter);
   TEST_ASSERT_EQUAL_INT(2, queue->length);
   getFromQueue(queue);
   getFromQueue(queue);
   TEST_ASSERT_EQUAL_INT(0, queue->length);
}

void testGetFromQueueGetsCorrectItemFirstTime(void)
{
   queue_t* queue;
   letter_t* firstLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* result;
   initQueue(&queue);
   addToQueue(queue, firstLetter);
   result = getFromQueue(queue);
   TEST_ASSERT_EQUAL_PTR(firstLetter, result);
}

void testGetFromQueueGetsCorrectItemMultipleTimes(void)
{
   queue_t* queue;
   letter_t* firstLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* secondLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* thirdLetter = (letter_t*)malloc(sizeof(letter_t));

   letter_t* result;
   initQueue(&queue);

   addToQueue(queue, firstLetter);
   addToQueue(queue, secondLetter);
   addToQueue(queue, thirdLetter);
   result = getFromQueue(queue);
   TEST_ASSERT_EQUAL_PTR(firstLetter, result);

   result = getFromQueue(queue);
   TEST_ASSERT_EQUAL_PTR(secondLetter, result);

   result = getFromQueue(queue);
   TEST_ASSERT_EQUAL_PTR(thirdLetter, result);
}


void testGetFromQueueModifiesFrontItem(void)
{
   queue_t* queue;
   letter_t* firstLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* secondLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* thirdLetter = (letter_t*)malloc(sizeof(letter_t));

   initQueue(&queue);

   addToQueue(queue, firstLetter);
   addToQueue(queue, secondLetter);
   addToQueue(queue, thirdLetter);

   TEST_ASSERT_EQUAL_PTR(queue->front, firstLetter);
   getFromQueue(queue);
   TEST_ASSERT_EQUAL_PTR(queue->front, secondLetter);
   getFromQueue(queue);
   TEST_ASSERT_EQUAL_PTR(queue->front, thirdLetter);
}

void testGetLastItemNullsContentsOfQueue(void)
{
   queue_t* queue;
   letter_t* firstLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* secondLetter = (letter_t*)malloc(sizeof(letter_t));

   initQueue(&queue);

   addToQueue(queue, firstLetter);
   addToQueue(queue, secondLetter);

   TEST_ASSERT_EQUAL_PTR(queue->front, firstLetter);
   getFromQueue(queue);
   getFromQueue(queue);
   TEST_ASSERT_NULL(queue->front);
   TEST_ASSERT_NULL(queue->back);
}

void testGetFromEmptyQueueGetsNull(void)
{
   queue_t* queue;
   letter_t* result = NULL;

   initQueue(&queue);
   result = getFromQueue(queue);
   TEST_ASSERT_NULL(result);
}
