#include "unity.h"
#include "printTree.h"
#include "dummyTree.c"
#include "memory.h"
#include "utilities.h"

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


void testCreate2DarrayDoesntSetsAPointer(void)
{
   char** array = NULL;
   create2Darray(&array , 4, 4);
   TEST_ASSERT_NOT_NULL(array);
   TEST_ASSERT_NOT_NULL(array[0]);
   array[3][2] = 'a';
   TEST_ASSERT_EQUAL_INT('a', array[3][2]);
}
