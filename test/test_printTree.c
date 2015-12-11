#include "unity.h"
#include "printTree.h"
#include "dummyTree.c"

void testNumOfRightsReturnsCorrectNum(void)
{
   letter_t* tree = dummyTree();
   letter_t* tree2 = dummyTree2();

   TEST_ASSERT_EQUAL_INT(3, numOfRights(tree));
   TEST_ASSERT_EQUAL_INT(4, numOfRights(tree2));

}

void testNumOfRightsReturnsZeroWhenGivenNull(void)
{
   TEST_ASSERT_EQUAL_INT(0, numOfRights(NULL));
}

void testLeftDepthReturnsCorrectNum(void)
{
   letter_t* tree = dummyTree();
   letter_t* tree2 = dummyTree2();
   TEST_ASSERT_EQUAL_INT(5, leftDepth(tree));
   TEST_ASSERT_EQUAL_INT(4, leftDepth(tree2));


}

void testLeftDepthReturnsZeroWhenGivenNull(void)
{
   TEST_ASSERT_EQUAL_INT(0, leftDepth(NULL));
}
