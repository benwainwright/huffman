#include "unity.h"
#include "huffman.h"
#include "memory.h"
#include "utilities.h"


void testInsertSort(void)
{
   int asciiGram[255] = {0};
   letter_t* letters = NULL;
   asciiGram['a'] = 4;
   asciiGram['b'] = 14;
   asciiGram['h'] = 8;

   insertSortNoZeros(asciiGram, &letters);

   TEST_ASSERT_NOT_NULL(letters);
   TEST_ASSERT_EQUAL_INT('a', letters[0].letter);
   TEST_ASSERT_EQUAL_INT(4, letters[0].freq);

   TEST_ASSERT_EQUAL_INT('h', letters[1].letter);
   TEST_ASSERT_EQUAL_INT(8, letters[1].freq);

   TEST_ASSERT_EQUAL_INT('b', letters[2].letter);
   TEST_ASSERT_EQUAL_INT(14, letters[2].freq);
}


void testBuildAsciiGramCreatesCorrectCounts(void)
{
   int* asciiGram = NULL;
   makeFileAsciiGram("testFile1.txt", &asciiGram);
   TEST_ASSERT_NOT_NULL(asciiGram);
   TEST_ASSERT_EQUAL_INT(7, asciiGram['t']);
   TEST_ASSERT_EQUAL_INT(8, asciiGram['i']);
   TEST_ASSERT_EQUAL_INT(3, asciiGram['\n']);
   TEST_ASSERT_EQUAL_INT(6, asciiGram['a']);
   TEST_ASSERT_EQUAL_INT(14, asciiGram[' ']);
   TEST_ASSERT_EQUAL_INT(1, asciiGram['.']);
}



void testInsertIntoSortedArray(void)
{
   letter_t* letters = NULL;
   letter_t letter1 = { 'a', 2 };
   letter_t letter2 = { 'z', 1 };
   letter_t letter3 = { 'g', 4 };

   insertSorted(&letters, 0, letter1);
   TEST_ASSERT_EQUAL_INT('a', letters[0].letter);

   insertSorted(&letters, 1, letter2);
   TEST_ASSERT_EQUAL_INT('z', letters[0].letter);
   TEST_ASSERT_EQUAL_INT('a', letters[1].letter);

   insertSorted(&letters, 2, letter3);
   TEST_ASSERT_EQUAL_INT('z', letters[0].letter);
   TEST_ASSERT_EQUAL_INT('a', letters[1].letter);
   TEST_ASSERT_EQUAL_INT('g', letters[2].letter);

}

void testInsertInArray(void)
{
   letter_t* letters = (letter_t*)malloc(sizeof(letter_t) * 3);
   letter_t letter1 = { 'a', 2 };
   letter_t letter2 = { 'z', 1 };
   letter_t letter3 = { 'g', 4 };
   letter_t letter4 = { 'h', 7 };

   letters[0] = letter1;
   letters[1] = letter2;
   letters[2] = letter3;

   insertInArray(&letters, letter4, 1, 3);
   TEST_ASSERT_EQUAL_INT('h', letters[1].letter);
   TEST_ASSERT_EQUAL_INT('a', letters[0].letter);
   TEST_ASSERT_EQUAL_INT('z', letters[2].letter);
   TEST_ASSERT_EQUAL_INT('g', letters[3].letter);
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
   TEST_ASSERT_EQUAL_PTR(letter1, parent->left);
   TEST_ASSERT_EQUAL_PTR(letter2, parent->right);
   TEST_ASSERT_EQUAL_INT(11, parent->freq);
}
