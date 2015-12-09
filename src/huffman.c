#include "huffman.h"

letter_t* printCode(letter_t* tree, char c)
{
   letter_t* node = NULL;
   if(tree == NULL) {
      return NULL;
   }
   if(tree->letter == c) {
      return tree;
   }
   if((node = printCode(tree->left, c)) != NULL) {
      putchar('0');
      return node;
   }
   if((node = printCode(tree->right, c)) != NULL) {
      putchar('1');
      return node;
   }
   return NULL;
}

void outputTree(letter_t* tree, letter_t* asciiGram)
{
   letter_t* node = NULL;
   int c;
   for(c = '\0'; c < '~'; c++) {
      if(asciiGram[c].freq > 0) {
         printf("char '%c' = ", c);
         node = printCode(tree, c);
         printf("(%d)\n", node->freq);
      }
   }
}

letter_t* makeHuffTree(char* fileName)
{
   letter_t* asciiGram = NULL, *parentNode = NULL, *left = NULL;
   letter_t* right = NULL;
   list_t sortedList;

   makeFileAsciiGram(fileName, &asciiGram);
   sortedList = insertionSort(asciiGram, ASCIILETTERS);
   deleteZerosFromList(&sortedList);

   while(sortedList.length > 1) {
      removeFromList(&sortedList, left = sortedList.start);
      removeFromList(&sortedList, right = sortedList.start);
      parentNode = createSubTree(left, right);
      if(sortedList.length > 0) {
         insertSorted(&sortedList, parentNode);
      }
   }
   return parentNode;
}

void makeFileAsciiGram(char* file, letter_t** asciiGram)
{
   int c;
   FILE* fh = openFile(file, "r");
   *asciiGram = (letter_t*)callocate(ASCIILETTERS, sizeof(letter_t));
   initAsciigram(*asciiGram);
   do {
      if((c = getc(fh)) != EOF && c < ASCIILETTERS) {
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

void printAsciiGram(letter_t* asciiGram, int length)
{
   int i;
   for(i = 0; i < length; i++) {
      printf("%d, Letter %c, freq %d\n", i, asciiGram[i].letter, asciiGram[i].freq);
   }

}

letter_t* createSubTree(letter_t* left, letter_t* right)
{
   letter_t* parent = (letter_t*)allocate(sizeof(letter_t));
   parent->freq = left->freq + right->freq;
   parent->letter = 0;
   parent->left = allocNode(left->freq, left->left, left->right, left->letter);
   parent->right = allocNode(right->freq, right->left, right->right, right->letter);
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
