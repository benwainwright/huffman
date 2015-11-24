#include "huffman.h"

void makeHuffTree(char* fileName)
{

}

void makeFileAsciiGram(char* file, int** asciiGram)
{
   int c;
   FILE* fh = openFile(file, "r");
   *asciiGram = (int*)callocate(256, sizeof(int));
   do {
      if((c = getc(fh)) != EOF && c < 256) {
         (*asciiGram)[c]++;
      }
   } while(!feof(fh) && !ferror(fh));
   fclose(fh);
}

letter_t* createSubTree(letter_t* left, letter_t* right)
{
   letter_t* parent = (letter_t*)allocate(sizeof(letter_t));
   parent->freq = left->freq + right->freq;
   parent->left = left;
   parent->right = right;
   return parent;
}

void insertSortNoZeros(int* asciiGram, letter_t** letters)
{
   int i, arrayLength = 0;
   letter_t letter;
   for(i = 0; i < 256; i++) {
      if(asciiGram[i] > 0) {
         letter.freq = asciiGram[i];
         letter.letter = (char) i;
         insertSorted(letters, arrayLength++, letter);
      }
   }
}

void insertSorted(letter_t** letters, int length, letter_t letter)
{
   int i;
   for(i = 0; i < length; i++) {
      if(*letters != NULL && letter.freq < (*letters)[i].freq) {
         insertInArray(letters, letter, i, length);
         return;
      }
   }
   insertInArray(letters, letter, i, length);
}

void insertInArray(letter_t** array, letter_t item, int pos, int length)
{
   int i;
   if((*array = (letter_t*)realloc(*array, sizeof(letter_t) * (length + 1))) == NULL) {
      fprintf(stderr, "Memory allocation error");
   }

   for(i = length; i > pos && i > 0; i--) {
      (*array)[i] = (*array)[i - 1];
   }
   (*array)[i] = item;
}

void deleteArrayPos(letter_t** array, int pos, int length)
{
   int i;
   for(i = pos; i < length - 1; i++) {
      (*array)[i] = (*array)[i + 1];
   }
   if((*array = (letter_t*)realloc(*array, sizeof(letter_t) * (length - 1))) == NULL) {
      fprintf(stderr, "Memory allocation error");
   }
}
