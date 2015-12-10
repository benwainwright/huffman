#include "types.h"

letter_t* dummyTree(void)
{
   letter_t* root = (letter_t*)malloc(sizeof(letter_t));
   root->right = (letter_t*)malloc(sizeof(letter_t));

   root->left = (letter_t*)malloc(sizeof(letter_t));
   root->left->left = NULL;
   root->left->right = (letter_t*)malloc(sizeof(letter_t));
   root->left->right->right = NULL;
   root->left->right->left = NULL;

   root->right->left = (letter_t*)malloc(sizeof(letter_t));
   root->right->left->left = (letter_t*)malloc(sizeof(letter_t));
   root->right->left->left->left = (letter_t*)malloc(sizeof(letter_t));
   root->right->left->left->left->left = (letter_t*)malloc(sizeof(letter_t));
   root->right->left->left->left->left->left = NULL;
   root->right->left->left->left->left->right = NULL;
   root->right->left->left->left->right = NULL;
   root->right->left->left->right = NULL;
   root->right->left->right = NULL;
   root->right->right = (letter_t*)malloc(sizeof(letter_t));
   root->right->right->left = NULL;
   root->right->right->right = NULL;
}
