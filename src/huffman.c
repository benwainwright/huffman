#include "huffman.h"


int getCharFreq(char* string, char c)
{
   int count = 0;
   char* pos = string;
   while(*pos != '\0') {
      if(*pos++ == c) {
         count++;
      }
   }
   return count;
}

void insertSorted(letter_t* letters, int length, letter_t letter)
{
   int i;
   for(i = 0; i < length; i++) {
      if(i != length - 1 && letters[i + 1].freq < letter.freq) {
         insertInArray(&letters, letter, i, length);
      }
   }
}

void insertInArray(letter_t** array, letter_t item, int pos, int length)
{
   int i;
   if((*array = (letter_t*)realloc(*array, sizeof(letter_t) * length)) == NULL) {
      fprintf(stderr, "Memory allocation error");
   }

   for(i = length; i > pos && i > 0; i--) {
      (*array)[i] = (*array)[i - 1];
   }
    (*array)[i] = item;
}
