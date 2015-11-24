#include "huffman.h"
#include "unity.h"




void testFindFreqInString(void)

{

   UnityAssertEqualNumber((_U_SINT)((5)), (_U_SINT)((getCharFreq("This string has 5 s characters", 's'))), (((void *)0)), (_U_UINT)7, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((2)), (_U_SINT)((getCharFreq("I'm on the top", 't'))), (((void *)0)), (_U_UINT)8, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((getCharFreq("Of the world", 'o'))), (((void *)0)), (_U_UINT)9, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((1)), (_U_SINT)((getCharFreq("One two three", 'w'))), (((void *)0)), (_U_UINT)10, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((getCharFreq("One two three", 'z'))), (((void *)0)), (_U_UINT)11, UNITY_DISPLAY_STYLE_INT);

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





   UnityAssertEqualNumber((_U_SINT)(('h')), (_U_SINT)((letters[1].letter)), (((void *)0)), (_U_UINT)51, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(('a')), (_U_SINT)((letters[0].letter)), (((void *)0)), (_U_UINT)52, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(('z')), (_U_SINT)((letters[2].letter)), (((void *)0)), (_U_UINT)53, UNITY_DISPLAY_STYLE_INT);

   UnityAssertEqualNumber((_U_SINT)(('g')), (_U_SINT)((letters[3].letter)), (((void *)0)), (_U_UINT)54, UNITY_DISPLAY_STYLE_INT);





}
