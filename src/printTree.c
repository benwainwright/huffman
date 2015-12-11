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
