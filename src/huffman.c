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

void outputTree(letter_t* tree, int* asciiGram)
{
   letter_t* node = NULL;
   int c;
   for(c = '\0'; c < '~'; c++) {
      if(asciiGram[c] > 0) {
         printf("char '%c' = ", c);
         node = printCode(tree, c);
         printf("(%d)\n", node->freq);
      }
   }
}

letter_t* makeHuffTree(char* fileName)
{
   int length = 0;
   int* asciiGram = NULL;
   letter_t* letters = NULL;
   letter_t* parentNode = NULL;
   makeFileAsciiGram(fileName, &asciiGram);
   length = insertSortNoZeros(asciiGram, &letters);
   while(length > 1) {
      parentNode = createSubTree(letters, letters + 1);
      deleteArrayPos(&letters, 0, length--);
      deleteArrayPos(&letters, 0, length--);
      insertSorted(&letters, length++, *parentNode);
   }
   return letters;
}

void makeFileAsciiGram(char* file, int** asciiGram)
{
   int c;
   FILE* fh = openFile(file, "r");
   *asciiGram = (int*)callocate(256, sizeof(int));
   do {
      if((c = getc(fh)) != EOF && c < ASCIILETTERS) {
         (*asciiGram)[c]++;
      }
   } while(!feof(fh) && !ferror(fh));
   fclose(fh);
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

int insertSortNoZeros(int* asciiGram, letter_t** letters)
{
   int i, arrayLength = 0;
   letter_t letter;
   letter.left = NULL;
   letter.right = NULL;
   for(i = 0; i < 256; i++) {
      if(asciiGram[i] > 0) {
         letter.freq = asciiGram[i];
         letter.letter = (char) i;
         insertSorted(letters, arrayLength++, letter);
      }
   }
   return arrayLength;
}


void insertInArray(letter_t** array, letter_t item, int pos, int length)
{
   int i;
   *array = (letter_t*)reAllocate(*array, sizeof(letter_t) * (length + 1));

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
   if(length > 1) {
      *array = (letter_t*)reAllocate(*array, sizeof(letter_t) * (length -1));
   }
}
