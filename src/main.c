#include "main.h"

int main(int argc, char* argv[])
{
   letter_t* tree = NULL;
   letter_t* asciiGram = NULL;
   makeFileAsciiGram(argv[1], &asciiGram);
   tree = makeHuffTree(argv[1]);
   outputTree(tree, asciiGram);
   freeHeapList();
}
