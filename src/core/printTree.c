#include "printTree.h"

void printTree(tree_t* tree)
{
   int height = leftDepth(tree->root) * 2;
   int width = ((numOfRights(tree->root) + 1) * 2);
   char** output = NULL;
   create2Darray(&output, height, width);
   printTreeRecurse(tree->root, output, 0, 0);
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

char getNodeChar(letter_t* node)
{
   if(node->letter == '\0') {
      return '#';
   }
   return node->letter;
}

void printTreeRecurse(letter_t* node, char** output, int y, int x)
{
   int rDistance = numOfRights(node->left) * R_BRANCH_INIT_LEN
                 + R_BRANCH_INIT_LEN;

   output[y][x] = getNodeChar(node);

   if(node->right != NULL) {
      printTreeRecurse(node->right, output, y, x + rDistance);
      printRightBranchLine(output, y, x, rDistance);
   }

   if(node->left != NULL) {
      printTreeRecurse(node->left, output, y + 2, x);
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
