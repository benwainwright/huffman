#include "printTree.h"



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

void create2Darray(char*** array, int h, int w)
{
   int x, y;
   char** local = (char**)allocate(sizeof(char*) * h);
   for(y = 0; y < h; y++) {
      local[y] = (char*)allocate(sizeof(char) * w);
      for(x = 0; x < w; x++) {
         local[y][x] = ' ';
      }
   }
   *array = local;
}

void print2DArray(char** array, int h, int w)
{
   int y, x;
   for(y = 0; y < h; y++) {
      for(x = 0; x < w; x++) {
         putchar(array[y][x]);
      }
      putchar('\n');
   }
}
