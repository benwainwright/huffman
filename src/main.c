#include "main.h"

int main(int argc, char* argv[])
{


   if(argc == 2) {
      drawHuffmanTree(argv[1]);
      return 0;
   }
   else {
      fprintf(stderr, "Incorrect usage: try %s <filename>\n", argv[0]);
      return 1;
   }
}
