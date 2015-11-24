#include "unity.h"
#include "huffman.h"


void testFindFreqInString(void)
{
   TEST_ASSERT_EQUAL_INT(5, getCharFreq("This string has 5 s characters", 's'));
   TEST_ASSERT_EQUAL_INT(2, getCharFreq("I'm on the top", 't'));
   TEST_ASSERT_EQUAL_INT(1, getCharFreq("Of the world", 'o'));
   TEST_ASSERT_EQUAL_INT(1, getCharFreq("One two three", 'w'));
   TEST_ASSERT_EQUAL_INT(0, getCharFreq("One two three", 'z'));
}

/*
void testInsertIntoSortedArray(void)
{
   letter_t letters[10];
   letter_t letter1 = { 'a', 2 };
   letter_t letter2 = { 'z', 1 };
   letter_t letter3 = { 'g', 4 };

   insertSorted(letters, 3, letter1);
   TEST_ASSERT_EQUAL_INT('a', letters[0].letter);

   insertSorted(letters, 3, letter2);
   TEST_ASSERT_EQUAL_INT('z', letters[0].letter);
   TEST_ASSERT_EQUAL_INT('a', letters[1].letter);

   insertSorted(letters, 3, letter3);
   TEST_ASSERT_EQUAL_INT('z', letters[0].letter);
   TEST_ASSERT_EQUAL_INT('a', letters[1].letter);
   TEST_ASSERT_EQUAL_INT('g', letters[2].letter);
}
*/

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
