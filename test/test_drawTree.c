#include "unity.h"
#include "drawTree.h"
#include "dummyTree.c"
#include "types.h"
#include "queue.h"
#include "memory.h"
#include "utilities.h"
#include "list.h"
#include "huffman.h"


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


void testDrawTree(void)
{
   tree_t* tree = initTree(dummyTree(), 0, 0, 0, 0);

   SDL_Renderer* ren = NULL;
   SDL_Window* win = loadSDLwindow("Test Window");
   setTreeDims(tree, 600, 100, 600, 1024);
   calcTreeCoords(tree);
   if (tree != NULL) {
      drawTree(win, tree);
      SDL_Delay(10000);
   }
}

void testLevelsAreCorrectlySpaced(void)
{
   tree_t* tree = makeHuffTree("shortTest.txt");
   int x = 100;
   int y = 100;
   int height = 800;
   int width = 600;
   int correctSpacing = height / 3;
   setTreeDims(tree, x, y, height, width);
   calcTreeCoords(tree);
   TEST_ASSERT_EQUAL_INT(correctSpacing, tree->root->left->pos.y - tree->root->pos.y);
   TEST_ASSERT_EQUAL_INT(correctSpacing, tree->root->left->right->pos.y - tree->root->left->pos.y);
}

void testCalcCoordsCorrect(void)
{
   tree_t* tree = initTree(dummyTree2(), 0, 0, 0, 0);
   int x = 100;
   int y = 100;
   int height = 800;
   int width = 600;
   int correctSpacing = height / 3;
   setTreeDims(tree, x, y, height, width);
   calcTreeCoords(tree);
   TEST_ASSERT_EQUAL_INT(correctSpacing, tree->root->left->pos.y - tree->root->pos.y);
   TEST_ASSERT_EQUAL_INT(correctSpacing, tree->root->left->right->pos.y - tree->root->left->pos.y);
}

void testTreeDepth(void)
{
   letter_t* tree1 = dummyTree();
   letter_t* tree2 = dummyTree2();
   TEST_ASSERT_EQUAL_INT(6, treeDepth(tree1));
   TEST_ASSERT_EQUAL_INT(5, treeDepth(tree2));
}

void testQueueLeaves(void)
{
   letter_t* tree = dummyTree();
   list_t* list = (list_t*)malloc(sizeof(list_t));
   initList(list);

   TEST_ASSERT_NOT_NULL(tree);
   addLeavesToList(tree, list);

   TEST_ASSERT_EQUAL_INT(2, list->length);
   TEST_ASSERT_EQUAL_PTR(tree->left, list->start);
   TEST_ASSERT_EQUAL_PTR(tree->right, list->end);


}

void testLevelArrayBuildsCorrectly(void)
{
   letter_t* tree = dummyTree();
   list_t** levelArray = NULL;
   createLevelArray(tree, &levelArray);
   TEST_ASSERT_NOT_NULL(levelArray);
   TEST_ASSERT_NOT_NULL(levelArray[0]);
   TEST_ASSERT_EQUAL_INT(1, levelArray[0]->length);
   TEST_ASSERT_EQUAL_PTR(tree, levelArray[0]->start);

   TEST_ASSERT_NOT_NULL(levelArray[1]);
   TEST_ASSERT_EQUAL_INT(2, levelArray[1]->length);
   TEST_ASSERT_EQUAL_PTR(tree->left, levelArray[1]->start);
   TEST_ASSERT_EQUAL_PTR(tree->right, levelArray[1]->end);

   TEST_ASSERT_NOT_NULL(levelArray[2]);
   TEST_ASSERT_EQUAL_INT(3, levelArray[2]->length);
   TEST_ASSERT_EQUAL_PTR(tree->left->right, levelArray[2]->start);
   TEST_ASSERT_EQUAL_PTR(tree->right->left, levelArray[2]->start->next);
   TEST_ASSERT_EQUAL_PTR(tree->right->right, levelArray[2]->end);

   TEST_ASSERT_NOT_NULL(levelArray[3]);
   TEST_ASSERT_EQUAL_INT(1, levelArray[3]->length);
   TEST_ASSERT_EQUAL_PTR(tree->right->left->left, levelArray[3]->start);

   TEST_ASSERT_EQUAL_INT(1, levelArray[3]->length);
}
