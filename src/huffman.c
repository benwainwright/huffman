#include "huffman.h"

tree_t* initTree(letter_t* root, int h, int w, int x, int y)
{
   tree_t* tree = (tree_t*)allocate(sizeof(tree_t));
   tree->dims.x = x;
   tree->dims.y = y;
   tree->dims.w = w;
   tree->dims.h = h;
   tree->root = root;
   return tree;
}

tree_t* makeHuffTree(char* fileName)
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

   return initTree(parent, 0, 0, 0, 0);
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
