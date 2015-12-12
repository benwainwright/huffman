#include "unity.h"
#include "huffman.h"
#include "memory.h"
#include "utilities.h"
#include "list.h"
#include "dummyTree.c"

void testBuildAsciiGramCreatesCorrectCounts(void)
{
   letter_t* asciiGram = NULL;
   makeFileAsciiGram("testFile1.txt", &asciiGram);
   TEST_ASSERT_NOT_NULL(asciiGram);
   TEST_ASSERT_EQUAL_INT(7, asciiGram['T'].freq);
   TEST_ASSERT_EQUAL_INT(8, asciiGram['I'].freq);
   TEST_ASSERT_EQUAL_INT(6, asciiGram['A'].freq);
   TEST_ASSERT_EQUAL_INT(0, asciiGram[' '].freq);
   TEST_ASSERT_EQUAL_INT(0, asciiGram['.'].freq);
}

void testCreateSubTreet(void)
{
   letter_t* letter1 = (letter_t*)malloc(sizeof(letter_t));
   letter1->freq = 4;
   letter_t* letter2 = (letter_t*)malloc(sizeof(letter_t));
   letter2->freq = 7;
   letter_t* parent = NULL;
   parent = createSubTree(letter1, letter2);
   TEST_ASSERT_NOT_NULL(parent);
   TEST_ASSERT_EQUAL_INT(letter1->freq, parent->left->freq);
   TEST_ASSERT_EQUAL_INT(letter2->freq, parent->right->freq);
   TEST_ASSERT_EQUAL_INT(11, parent->freq);
}



void testMakeHuffTree(void)
{
   tree_t* tree = makeHuffTree("shortTest.txt");
   TEST_ASSERT_NOT_NULL(tree);
   TEST_ASSERT_NOT_NULL(tree->root);
   TEST_ASSERT_EQUAL_INT(12, tree->root->freq);
}
