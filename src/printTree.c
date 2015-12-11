#include "printTree.h"



void printTree(letter_t* tree)
{
   int height = leftDepth(tree) * 2;
   int width = ((numOfRights(tree) + 1) * 2);
   char** output = NULL;
   create2Darray(&output, height, width);
   printTreeRecurse(tree, output, 0, 0);
   print2DArray(output, height, width);
}

void printRightBranchLine(char** output, int y, int x, int length)
{
   int i;
   for(i = 1; i < length; i++){
      output[y][x + i] = '-';
   }
}
void printLeftBranchLine(char** output, int y, int x)
{
   output[y + 1][x] = '|';
}
void printTreeRecurse(letter_t* tree, char** output, int y, int x)
{
   int rightDistance = numOfRights(tree->left);

   output[y][x] = 'x';
   if(tree->right != NULL) {
      printTreeRecurse(tree->right, output, y, x + (rightDistance * 2) + 2);
      printRightBranchLine(output, y, x, (rightDistance * 2) + 2);
   }
   if(tree->left != NULL) {
      printTreeRecurse(tree->left, output, y + 2, x);
      printLeftBranchLine(output, y, x);
   }
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
