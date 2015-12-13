#include "main.h"

int main(int argc, char* argv[])
{
   letter_t* tree = NULL;
   letter_t* asciiGram = NULL;

   if(argc != 2) {
      fprintf(stderr, "Incorrect usage, try %s <filename>\n", argv[0]);
      return 1;
   }
   else {
      makeFileAsciiGram(argv[1], &asciiGram);
      tree = makeHuffTree(argv[1]);
      outputTree(tree, asciiGram);
      freeHeapList();
      return 0;
   }
}
