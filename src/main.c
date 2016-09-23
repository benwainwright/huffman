#include "main.h"
#include "printTree.h"

options_t getOptions(int argc, char** argv);

int main(int argc, char* argv[])
{
      tree_t*   tree      = NULL;
      letter_t* asciiGram = NULL;
      options_t options   = getOptions(argc, argv);

   if(argc < 3 || argc > 5 || options.fileName == NULL) {
      fprintf(stderr, "Incorrect usage: try -f %s <filename>\n", argv[0]);
      return 1;
   }

   switch(options.op) {
      case PRINT_TREE_TO_TERMINAL:
         tree = makeHuffTree(options.fileName);
         printTree(tree);
         freeHeapList();
         break;

      case DISPLAY_GRAPHICAL_TREE:
         drawHuffmanTree(options.fileName);
   }

   return 0;
}

options_t getOptions(int argc, char** argv)
{
   int i;
   options_t options;
   options.fileName = NULL;
   options.op = DISPLAY_GRAPHICAL_TREE;
   for(i = 1; i < argc; i++) {
      if(argv[i][0] == '-') {
         switch(argv[i][1]) {
            case 't': options.op = PRINT_TREE_TO_TERMINAL; break;
            case 'f':
               if(i < argc - 1 && argv[i + 1][0] != '-') {
                  options.fileName = argv[i + 1];
               }
         }
      }
   }
   return options;
}


