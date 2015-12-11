#include "unity.h"
#include "drawTree.h"
#include "dummyTree.c"
#include "types.h"
#include "queue.h"
#include "memory.h"
#include "utilities.h"

/*

void testDisplayWindow(void)
{
   position_t position = { .x = 100, .y = 100 };
   dimension_t dimension = { .w = 1024, .h = 768 };
   rgb_t background = { .r = 230, .g = 12, .b = 12 };
   SDL_Window* win = initSDLWindow("Test window", position, dimension);
   SDL_Renderer* ren = makeRenderer(win, NOFLAGS, background);

   sleep(4);
   killWindow(win);
}
*/


void testQueueLeaves(void)
{
   letter_t* tree = dummyTree();
   queue_t* queue;
   initQueue(&queue);
   queueLeaves(tree, queue);
   TEST_ASSERT_NOT_NULL(tree);
   TEST_ASSERT_EQUAL_INT(2, queue->length);
   TEST_ASSERT_EQUAL_PTR(tree->left, queue->front);
   TEST_ASSERT_EQUAL_PTR(tree->right, queue->back);
}

void testLevelArrayBuildsCorrectly(void)
{
   letter_t* tree = dummyTree();
   queue_t** levelArray = NULL;
   createLevelArray(tree, &levelArray);
   TEST_ASSERT_NOT_NULL(levelArray);
   TEST_ASSERT_NOT_NULL(levelArray[0]);
   TEST_ASSERT_EQUAL_INT(1, levelArray[0]->length);
   TEST_ASSERT_EQUAL_PTR(tree, levelArray[0]->front);

   TEST_ASSERT_NOT_NULL(levelArray[1]);
   TEST_ASSERT_EQUAL_INT(2, levelArray[1]->length);
   TEST_ASSERT_EQUAL_PTR(tree->left, levelArray[1]->front);
   TEST_ASSERT_EQUAL_PTR(tree->right, levelArray[1]->back);

   TEST_ASSERT_NOT_NULL(levelArray[2]);
   TEST_ASSERT_EQUAL_INT(3, levelArray[2]->length);
   TEST_ASSERT_EQUAL_PTR(tree->left->right, levelArray[2]->front);
   TEST_ASSERT_EQUAL_PTR(tree->right->left, levelArray[2]->front->prev);
   TEST_ASSERT_EQUAL_PTR(tree->right->right, levelArray[2]->back);

   TEST_ASSERT_NOT_NULL(levelArray[3]);
   TEST_ASSERT_EQUAL_INT(1, levelArray[3]->length);
   TEST_ASSERT_EQUAL_PTR(tree->right->left->left, levelArray[3]->back);

   TEST_ASSERT_EQUAL_INT(1, levelArray[4]->length);
}
