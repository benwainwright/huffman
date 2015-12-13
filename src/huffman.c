#include "huffman.h"

code_t* getCode(letter_t* tree, char c, int i)
{
   code_t* code = NULL;
   if(tree == NULL) {
      return NULL;
   }
   if(tree->letter == c) {
      return initCode(i, tree->freq);
   }
   if((code = getCode(tree->left, c, i + 1)) != NULL) {
      code->bits[i] = '0';
      return code;
   }
   if((code = getCode(tree->right, c, i + 1)) != NULL) {
      code->bits[i] = '1';
      return code;
   }
   return NULL;
}

code_t* initCode(int length, int freq)
{
   code_t* code = (code_t*)allocate(sizeof(code_t));
   code->bits = (char*)allocate(sizeof(char) * (length + NULLCHARLEN));
   code->bits[length] = '\0';
   code->freq = freq;
   return code;
}

void outputTree(letter_t* tree, letter_t* asciiGram)
{
   code_t* code;
   int c, freq, len, bitCount = 0;
   for(c = '\0'; c < '~'; c++) {
      if(asciiGram[c].freq > 0) {
         code = getCode(tree, c, 0);
         freq = code->freq;
         len = strlen(code->bits);
         if(isprint(c)) {
            printf("'%c'", c);
         }
         else {
            printf("%03d", (int) c);
         }
         printf(" : %24s ( %4d * %6d )\n", code->bits, len, freq);
         bitCount += freq * len;
      }
   }
   printf("%d bytes\n", getBytes(bitCount));
}

int getBytes(int bitCount) {
   return (int)ceil((double)bitCount / 8.0);
}

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

int numOfRights(letter_t* tree)
{
   int fromLeft = 0, fromRight = 0;
   if (tree == NULL) {
      return 0;
   }

   if (tree->left != NULL) {
      fromLeft = numOfRights(tree->left);
   }

   if (tree->right != NULL) {
      fromRight = numOfRights(tree->right) + 1;
   }

   return fromLeft + fromRight;
}

int leftDepth(letter_t* tree)
{
   int fromLeft, fromRight;
   if (tree == NULL) {
      return 0;
   }

   fromLeft = leftDepth(tree->left) + 1;
   fromRight = leftDepth(tree->right);

   if (fromLeft > fromRight) {
      return fromLeft;
   }
   else {
      return fromRight;
   }
}
