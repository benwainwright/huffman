#include "huffman.h"

letter_t* makeHuffTree(char* fileName)
{
   letter_t* asciiGram = NULL, *parent = NULL, *left = NULL, *right = NULL;
   list_t sortedList;

   makeFileAsciiGram(fileName, &asciiGram);
   sortedList = insertionSort(asciiGram, ASCIILETTERS);
   deleteZerosFromList(&sortedList);

   while(sortedList.length > 1) {
      removeFromList(&sortedList, left = sortedList.start);
      removeFromList(&sortedList, right = sortedList.start);
      parent = createSubTree(left, right);
      if(sortedList.length > 0) {
         insertSorted(&sortedList, parent);
      }
   }
   return parent;
}

void makeFileAsciiGram(char* file, letter_t** asciiGram)
{
   int c;
   FILE* fh = openFile(file, "r");
   *asciiGram = (letter_t*)callocate(ASCIILETTERS, sizeof(letter_t));
   initAsciigram(*asciiGram);
   do {
      c = toupper(getc(fh));
      if(isalpha(c) && c != EOF) {
         (*asciiGram)[c].freq++;
      }
   } while(!feof(fh) && !ferror(fh));
   fclose(fh);
}

void initAsciigram(letter_t* asciiGram)
{
   int i;
   for(i = 0; i < ASCIILETTERS; i++) {
      asciiGram[i].prev = NULL;
      asciiGram[i].next = NULL;
      asciiGram[i].freq = 0;
      asciiGram[i].letter = i;
   }
}

letter_t* createSubTree(letter_t* left, letter_t* right)
{
   letter_t* parent = (letter_t*)allocate(sizeof(letter_t));
   parent->freq = left->freq + right->freq;
   parent->letter = 0;
   parent->left = allocNode(left->freq, left->left,
                            left->right, left->letter);
   parent->right = allocNode(right->freq, right->left,
                             right->right, right->letter);
   return parent;
}

letter_t* allocNode(int freq, letter_t* left, letter_t* right, char c)
{
   letter_t* returnVal = (letter_t*)allocate(sizeof(letter_t));
   returnVal->freq = freq;
   returnVal->left = left;
   returnVal->right = right;
   returnVal->letter = c;
   return returnVal;
}
