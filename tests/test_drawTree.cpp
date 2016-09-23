#include <gtest/gtest.h>

extern "C" {
#include "drawTree.h"
#include "shared/dummyTree.h"
#include "types.h"
#include "queue.h"
#include "memory.h"
#include "utilities.h"
#include "list.h"
#include "huffman.h"
#include "benSDL.h"
#include "neillsdl2.h"
}


TEST(DrawTree, TreeDepth)
{
   letter_t* tree1 = dummyTree();
   letter_t* tree2 = dummyTree2();
   EXPECT_EQ(6, treeDepth(tree1));
   EXPECT_EQ(5, treeDepth(tree2));
}

TEST(DrawTree, QueueLeaves)
{
   letter_t* tree = dummyTree();
   list_t* list = (list_t*)malloc(sizeof(list_t));
   initList(list);

   ASSERT_NE((letter_t*)NULL, tree);
   addLeavesToList(tree, list);

   EXPECT_EQ(2, list->length);
   EXPECT_EQ(tree->left, list->start);
   EXPECT_EQ(tree->right, list->end);
}

TEST(DrawTree, LevelArrayBuildsCorrectly)
{
   letter_t* tree = dummyTree();
   list_t** levelArray = NULL;
   createLevelArray(tree, &levelArray);
   ASSERT_NE((list_t**)NULL, levelArray);
   ASSERT_NE((list_t*)NULL, levelArray[0]);
   EXPECT_EQ(1, levelArray[0]->length);
   EXPECT_EQ(tree, levelArray[0]->start);

   ASSERT_NE((list_t*)NULL, levelArray[1]);
   EXPECT_EQ(2, levelArray[1]->length);
   EXPECT_EQ(tree->left, levelArray[1]->start);
   EXPECT_EQ(tree->right, levelArray[1]->end);

   ASSERT_NE((list_t*)NULL, levelArray[2]);
   EXPECT_EQ(3, levelArray[2]->length);
   EXPECT_EQ(tree->left->right, levelArray[2]->start);
   EXPECT_EQ(tree->right->left, levelArray[2]->start->next);
   EXPECT_EQ(tree->right->right, levelArray[2]->end);

   ASSERT_NE((list_t*)NULL, levelArray[3]);
   EXPECT_EQ(1, levelArray[3]->length);
   EXPECT_EQ(tree->right->left->left, levelArray[3]->start);

   EXPECT_EQ(1, levelArray[3]->length);

}
