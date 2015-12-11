/*
  Files controlling the initialisation and management of the queue
  initially created in the wordladder assignment, this version is
  adapted for the Huffman code coursework
*/

#include "queue.h"

void initQueue(queue_t* queue)
{
   queue->front = NULL;
   queue->back = NULL;
   queue->length = 0;
}


void addToQueue(queue_t* queue, letter_t* word)
{
   letter_t* oldBack = queue->back;
   queue->back = word;
   word->next = oldBack;
   if(oldBack != NULL) {
      oldBack->prev = word;
   }
   else {
      queue->front = word;
   }

   /* TODO test for intiger overflow */
   queue->length++;
}

letter_t* getFromQueue(queue_t* queue)
{
   letter_t* front = queue->front;
   if(queue->back == queue->front) {
      queue->front = NULL;
      queue->back = NULL;
   }
   else {
      queue->front = queue->front->prev;
   }
   if (queue->length > 0) {
      queue->length--;
   }
   return front;
}
