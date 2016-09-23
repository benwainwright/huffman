#ifndef main_H
#define main_H

#include "types.h"
#include "huffman.h"
#include "drawTree.h"

#include <SDL.h>
#include <unistd.h>

typedef enum OPERATION {
   PRINT_TREE_TO_TERMINAL,
   DISPLAY_GRAPHICAL_TREE
} operation_t;

typedef struct options {
   operation_t op;
   char*       fileName;
} options_t;

#endif
