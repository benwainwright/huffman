#include <gtest/gtest.h>

extern "C" {
#include "huffman.h"
#include "memory.h"
#include "utilities.h"
#include "list.h"
#include "shared/dummyTree.h"
}

TEST(Huffman, BuildAsciiGramCreatesCorrectCounts)
{
   letter_t* asciiGram = NULL;
   makeFileAsciiGram((char*)"testResources/testFile1.txt", &asciiGram);
   ASSERT_NE((letter_t*)NULL, asciiGram);
   EXPECT_EQ(7, asciiGram['T'].freq);
   EXPECT_EQ(8, asciiGram['I'].freq);
   EXPECT_EQ(6, asciiGram['A'].freq);
   EXPECT_EQ(0, asciiGram[' '].freq);
   EXPECT_EQ(0, asciiGram['.'].freq);
}

TEST(Huffman, CreateSubTree)
{
   letter_t* letter1 = (letter_t*)malloc(sizeof(letter_t));
   letter1->freq = 4;
   letter_t* letter2 = (letter_t*)malloc(sizeof(letter_t));
   letter2->freq = 7;
   letter_t* parent = NULL;
   parent = createSubTree(letter1, letter2);
   ASSERT_NE((letter_t*)NULL, parent);
   EXPECT_EQ(letter1->freq, parent->left->freq);
   EXPECT_EQ(letter2->freq, parent->right->freq);
   EXPECT_EQ(11, parent->freq);
}

TEST(Huffman, MakeHuffTree)
{
   tree_t* tree = makeHuffTree((char*)"testResources/shortTest.txt");
   ASSERT_NE((tree_t*)NULL, tree);
   ASSERT_NE((letter_t*)NULL, tree->root);
   EXPECT_EQ(12, tree->root->freq);
}
