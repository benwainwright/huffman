#include "utilities.h"
#include "memory.h"
#include "huffman.h"
#include "unity.h"




void testInsertSort(void)

{

   int asciiGram[255] = {0};

   letter_t* letters = ((void *)0);

   asciiGram['a'] = 4;

   asciiGram['b'] = 14;

   asciiGram['h'] = 8;



   insertSortNoZeros(asciiGram, &letters);



   if ((((letters)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)17);;};

   UnityAssertEqualNumber((_U_SINT)(('a')), (_U_SINT)((letters[0].letter)), (((void *)0)), (_U_UINT)18, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((4)), (_U_SINT)((letters[0].freq)), (((void *)0)), (_U_UINT)19, UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(('h')), (_U_SINT)((letters[1].letter)), (((void *)0)), (_U_UINT)21, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((8)), (_U_SINT)((letters[1].freq)), (((void *)0)), (_U_UINT)22, UNITY_DISPLAY_STYLE_INT);



   UnityAssertEqualNumber((_U_SINT)(('b')), (_U_SINT)((letters[2].letter)), (((void *)0)), (_U_UINT)24, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((14)), (_U_SINT)((letters[2].freq)), (((void *)0)), (_U_UINT)25, UNITY_DISPLAY_STYLE_INT);

}





void testBuildAsciiGramCreatesCorrectCounts(void)

{

   int* asciiGram = ((void *)0);

   makeFileAsciiGram("testFile1.txt", &asciiGram);

   if ((((asciiGram)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)33);;};

   UnityAssertEqualNumber((_U_SINT)((7)), (_U_SINT)((asciiGram['t'])), (((void *)0)), (_U_UINT)34, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((8)), (_U_SINT)((asciiGram['i'])), (((void *)0)), (_U_UINT)35, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((asciiGram['\n'])), (((void *)0)), (_U_UINT)36, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((6)), (_U_SINT)((asciiGram['a'])), (((void *)0)), (_U_UINT)37, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((14)), (_U_SINT)((asciiGram[' '])), (((void *)0)), (_U_UINT)38, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((asciiGram['.'])), (((void *)0)), (_U_UINT)39, UNITY_DISPLAY_STYLE_INT);

}







void testInsertIntoSortedArray(void)

{

   letter_t* letters = ((void *)0);

   letter_t letter1 = { 'a', 2 };

   letter_t letter2 = { 'z', 1 };

   letter_t letter3 = { 'g', 4 };



   insertSorted(&letters, 0, letter1);

   UnityAssertEqualNumber((_U_SINT)(('a')), (_U_SINT)((letters[0].letter)), (((void *)0)), (_U_UINT)52, UNITY_DISPLAY_STYLE_INT);



   insertSorted(&letters, 1, letter2);

   UnityAssertEqualNumber((_U_SINT)(('z')), (_U_SINT)((letters[0].letter)), (((void *)0)), (_U_UINT)55, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(('a')), (_U_SINT)((letters[1].letter)), (((void *)0)), (_U_UINT)56, UNITY_DISPLAY_STYLE_INT);



   insertSorted(&letters, 2, letter3);

   UnityAssertEqualNumber((_U_SINT)(('z')), (_U_SINT)((letters[0].letter)), (((void *)0)), (_U_UINT)59, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(('a')), (_U_SINT)((letters[1].letter)), (((void *)0)), (_U_UINT)60, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(('g')), (_U_SINT)((letters[2].letter)), (((void *)0)), (_U_UINT)61, UNITY_DISPLAY_STYLE_INT);



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

   UnityAssertEqualNumber((_U_SINT)(('h')), (_U_SINT)((letters[1].letter)), (((void *)0)), (_U_UINT)78, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(('a')), (_U_SINT)((letters[0].letter)), (((void *)0)), (_U_UINT)79, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(('z')), (_U_SINT)((letters[2].letter)), (((void *)0)), (_U_UINT)80, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(('g')), (_U_SINT)((letters[3].letter)), (((void *)0)), (_U_UINT)81, UNITY_DISPLAY_STYLE_INT);

}





void testCreateSubTreet(void)

{

   letter_t* letter1 = (letter_t*)malloc(sizeof(letter_t));

   letter1->freq = 4;

   letter_t* letter2 = (letter_t*)malloc(sizeof(letter_t));

   letter2->freq = 7;

   letter_t* parent = ((void *)0);

   parent = createSubTree(letter1, letter2);

   if ((((parent)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)93);;};

   UnityAssertEqualNumber((_U_SINT)(_UP)((letter1)), (_U_SINT)(_UP)((parent->left)), (((void *)0)), (_U_UINT)94, UNITY_DISPLAY_STYLE_HEX64);

   UnityAssertEqualNumber((_U_SINT)(_UP)((letter2)), (_U_SINT)(_UP)((parent->right)), (((void *)0)), (_U_UINT)95, UNITY_DISPLAY_STYLE_HEX64);

   UnityAssertEqualNumber((_U_SINT)((11)), (_U_SINT)((parent->freq)), (((void *)0)), (_U_UINT)96, UNITY_DISPLAY_STYLE_INT);

}
