#include <gtest/gtest.h>
#include <stdlib.h>

extern "C" {
#include "queue.h"
#include "memory.h"
#include "utilities.h"
}


TEST(Queue, InitQueueBlanksQueue)
{
   queue_t* queue;
   initQueue(&queue);
   EXPECT_EQ((letter_t*)NULL, queue->front);
   EXPECT_EQ((letter_t*)NULL, queue->back);
}

TEST(Queue, AddToQueueAddsPointerToQueue)
{
   queue_t* queue;
   letter_t* firstLetter = (letter_t*)malloc(sizeof(letter_t));
   initQueue(&queue);
   addToQueue(queue, firstLetter);
   EXPECT_EQ(firstLetter, queue->front);
   EXPECT_EQ(firstLetter, queue->back);
}

TEST(Queue, MultipleQueueAddsAreAddedCorrectly)
{
   queue_t* queue;
   letter_t* firstLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* secondLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* thirdLetter = (letter_t*)malloc(sizeof(letter_t));

   initQueue(&queue);
   addToQueue(queue, firstLetter);
   EXPECT_EQ(firstLetter, queue->front);
   EXPECT_EQ(firstLetter, queue->back);

   addToQueue(queue, secondLetter);
   EXPECT_EQ(firstLetter, queue->front);
   EXPECT_EQ(secondLetter, queue->back);

   addToQueue(queue, thirdLetter);
   EXPECT_EQ(firstLetter, queue->front);
   EXPECT_EQ(thirdLetter, queue->back);
   EXPECT_EQ(secondLetter, queue->back->next);
}

TEST(Queue, QueueLengthIsIncreasedCorrectly)
{
   queue_t *queue;
   letter_t* firstLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* secondLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* thirdLetter = (letter_t*)malloc(sizeof(letter_t));

   initQueue(&queue);
   EXPECT_EQ(0, queue->length);

   addToQueue(queue, firstLetter);
   EXPECT_EQ(1, queue->length);

   addToQueue(queue, secondLetter);
   EXPECT_EQ(2, queue->length);

   addToQueue(queue, thirdLetter);
   EXPECT_EQ(3, queue->length);
}

TEST(Queue, RemoveFromQueueDecreasesLengthCorrectly)
{
   queue_t* queue;
   letter_t* firstLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* secondLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* thirdLetter = (letter_t*)malloc(sizeof(letter_t));

   letter_t* result;
   initQueue(&queue);
   EXPECT_EQ(0, queue->length);

   addToQueue(queue, firstLetter);
   addToQueue(queue, firstLetter);
   EXPECT_EQ(2, queue->length);

   getFromQueue(queue);
   EXPECT_EQ(1, queue->length);
   addToQueue(queue, firstLetter);
   EXPECT_EQ(2, queue->length);
   getFromQueue(queue);
   getFromQueue(queue);
   EXPECT_EQ(0, queue->length);
}

TEST(Queue, GetFromQueueGetsCorrectItemFirstTime)
{
   queue_t* queue;
   letter_t* firstLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* result;
   initQueue(&queue);
   addToQueue(queue, firstLetter);
   result = getFromQueue(queue);
   EXPECT_EQ(firstLetter, result);
}

TEST(Queue, GetFromQueueGetsCorrectItemMultipleTimes)
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
   EXPECT_EQ(firstLetter, result);

   result = getFromQueue(queue);
   EXPECT_EQ(secondLetter, result);

   result = getFromQueue(queue);
   EXPECT_EQ(thirdLetter, result);
}


TEST(Queue, GetFromQueueModifiesFrontItem)
{
   queue_t* queue;
   letter_t* firstLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* secondLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* thirdLetter = (letter_t*)malloc(sizeof(letter_t));

   initQueue(&queue);

   addToQueue(queue, firstLetter);
   addToQueue(queue, secondLetter);
   addToQueue(queue, thirdLetter);

   EXPECT_EQ(queue->front, firstLetter);
   getFromQueue(queue);
   EXPECT_EQ(queue->front, secondLetter);
   getFromQueue(queue);
   EXPECT_EQ(queue->front, thirdLetter);
}

TEST(Queue, GetLastItemNullsContentsOfQueue)
{
   queue_t* queue;
   letter_t* firstLetter = (letter_t*)malloc(sizeof(letter_t));
   letter_t* secondLetter = (letter_t*)malloc(sizeof(letter_t));

   initQueue(&queue);

   addToQueue(queue, firstLetter);
   addToQueue(queue, secondLetter);

   EXPECT_EQ(queue->front, firstLetter);
   getFromQueue(queue);
   getFromQueue(queue);
   EXPECT_EQ((letter_t*)NULL, queue->front);
   EXPECT_EQ((letter_t*)NULL, queue->back);
}

TEST(Queue, GetFromEmptyQueueGetsNull)
{
   queue_t* queue;
   letter_t* result = NULL;

   initQueue(&queue);
   result = getFromQueue(queue);
   EXPECT_EQ((letter_t*)NULL, result);
}
