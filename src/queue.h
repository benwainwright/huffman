#ifndef queue_H
#define queue_H

#include <stdlib.h>
#include "types.h"
#include "memory.h"
#include "utilities.h"

void initQueue(queue_t* queue);
void addToQueue(queue_t* queue, letter_t* letter);
letter_t* getFromQueue(queue_t* queue);


#endif
