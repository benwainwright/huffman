#include <gtest/gtest.h>

extern "C" {
#include "printTree.h"
#include "shared/dummyTree.h"
#include "memory.h"
#include "utilities.h"
}

TEST(PrintTreee, NumOfRightsReturnsCorrectNum)
{
   letter_t* tree = dummyTree();
   letter_t* tree2 = dummyTree2();

   EXPECT_EQ(3, numOfRights(tree));
   EXPECT_EQ(4, numOfRights(tree2));
}

TEST(PrintTree, NumOfRightsReturnsZeroWhenGivenNull)
{
   EXPECT_EQ(0, numOfRights(NULL));
}

TEST(PrintTree, LeftDepthReturnsCorrectNum)
{
   letter_t* tree = dummyTree();
   letter_t* tree2 = dummyTree2();
   EXPECT_EQ(5, leftDepth(tree));
   EXPECT_EQ(4, leftDepth(tree2));
}

TEST(PrintTree, LeftDepthReturnsZeroWhenGivenNull)
{
   EXPECT_EQ(0, leftDepth(NULL));
}


TEST(PrintTree, Create2DArrayDoesntSetsAPointer)
{
   char** array = NULL;
   create2Darray(&array , 4, 4);
   ASSERT_NE((char**)NULL, array);
   ASSERT_NE((char*)NULL, array[0]);
   array[3][2] = 'a';
   EXPECT_EQ('a', array[3][2]);
}

TEST(PrintTree, Prints2DArray)
{
   char** array = NULL;
   create2Darray(&array , 4, 4);
   array[0][0] = 'a';
   array[0][1] = 'b';
   array[2][1] = 'c';
   array[2][2] = 'd';
   print2DArray(array, 4, 4);
}

TEST(PrintTree, PrintsTree)
{
   letter_t* tree = dummyTree();
   letter_t* tree1 = dummyTree2();
   printTree(tree);
   printf("\n\n");
   printTree(tree1);
}
