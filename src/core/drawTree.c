/*
 * Huffman Code Assignment
 *
 * Functions in this file calculate the initial coordinates of
 * the tree nodes, spread them out based on collision
 * and distribution, then draw them.
 */

#include "drawTree.h"


void drawHuffmanTree(char* filename)
{

   tree_t*     tree = makeHuffTree(filename);
   SDL_Window* win  = loadSDLwindow(filename);

   loadBackgroundImage(BACKGROUNDIMAGE, win);

   tree->dims.x = WINWIDTH / 2;
   tree->dims.y = TREEBORDER;
   tree->dims.w = WINWIDTH - (2 * TREEBORDER);
   tree->dims.h = WINHEIGHT - (2 * TREEBORDER);

   calcTreeCoords(tree);
   drawTree(win, tree);
   runEventLoop(win);
}


void spreadNodes(tree_t* tree, list_t** levelArray) {
   int moved, i = 0;
   do {
      moved = doSpreadPass(tree, levelArray);
   } while(moved == 1 && i++ < SPREAD_MAX);
}

int doSpreadPass(tree_t* tree, list_t** levelArray)
{
   letter_t* node  = NULL;
   int       depth = treeDepth(tree->root);
   int       moved = 0;
   int       level; 

   for(level = depth - 1; level > 0; level--) {
      node = levelArray[level]->start;

      while(node != NULL) {
         if(shuffleIfCollisions(tree, node)) {
            moved = 1;
         }
         if(shuffleIfNotAboveChildren(tree, node)) {
            moved = 1;
         }
         node = node->next;
      }
   }
   return moved;
}

int isAboveChildren(letter_t* node)
{
   if((node->pos.x > node->left->pos.x) &&
      (node->pos.x < node->right->pos.x)) {
      return 1;
   }
   return 0;
}

int shuffleIfNotAboveChildren(tree_t* tree, letter_t* node)
{
   int lspace = leftSpace(tree, node);
   int rspace = rightSpace(tree, node);

   if (node->left != NULL && node->right != NULL) {
      if (!isAboveChildren(node) && lspace > rspace) {
         node->pos.x -= SHUFFLEDISTANCE;
         return 1;
      }
      else if (!isAboveChildren(node) && rspace > lspace) {
         node->pos.x += SHUFFLEDISTANCE;
         return 1;
      }
   }
   return 0;
}

int shuffleIfCollisions(tree_t* tree, letter_t* node)
{
   int lspace = leftSpace(tree, node);
   int rspace = rightSpace(tree, node);

   if (isColliding(node)) {
      if(lspace > rspace) {
         moveTreeX(node, -SHUFFLEDISTANCE);
         return 1;
      }
      else if (rspace > lspace) {
         moveTreeX(node, +SHUFFLEDISTANCE);
         return 1;
      }
   }
   return 0;
}

int isColliding(letter_t* node) {

   if(node->prev != NULL &&
     ((node->pos.x - node->prev->pos.x) < NODERADIUS * 2)) {
      return 1;
   }

   if(node->next != NULL &&
     ((node->next->pos.x - node->pos.x) < NODERADIUS * 2)) {
      return 1;
   }
   return 0;
}

int leftSpace(tree_t* tree, letter_t* node)
{
   int treeXorigin = tree->dims.x - (tree->dims.w / 2);
   if(node->prev != NULL) {
      return node->pos.x - node->prev->pos.x;
   }
   else {
      return node->pos.x - treeXorigin;
   }
}

int rightSpace(tree_t* tree, letter_t* node)
{
   int treeXedge = tree->dims.x + (tree->dims.w / 2);
   if(node->next != NULL) {
      return node->next->pos.x - node->pos.x;
   }
   else {
      return  treeXedge - node->pos.x;
   }
}

void moveTreeX(letter_t* tree, int move)
{
   tree->pos.x += move;
   if(tree->left != NULL) {
      moveTreeX(tree->left, move);
   }
   if(tree->right != NULL) {
      moveTreeX(tree->right, move);
   }
}


/* Calculates the offset needed for a full bottom layer, then
   multiplies to get the corrasponding initial offset */
double getInitialOffset(double width, double depth)
{
   double zeroIndexedDepth = depth - 1.0;
   double potentialNodes   = pow(2.0, zeroIndexedDepth);
   double baseWidth        = width / (potentialNodes - 1.0);
   double baseOffset       = baseWidth / 2;
   double initialOffset    = baseOffset * (pow(2.0, depth - 2));

   if(depth > 1) {
         return initialOffset;
   }
   return 0;
}

int getSpacing(int height, int depth)
{
   return height / (depth - 1);
}

void calcTreeCoords(tree_t* tree)
{
   list_t** levelArray    = NULL;
   int      depth         = treeDepth(tree->root);
   int      spacing       = getSpacing(tree->dims.h, depth);
   int      initialOffset = getInitialOffset(tree->dims.w, depth);

   calcInitCoords(tree->root, tree->dims.x, tree->dims.y,
                     spacing, initialOffset);
   createLevelArray(tree->root, &levelArray);
   spreadNodes(tree, levelArray);
}

void calcInitCoords(letter_t* tree, int x,
                    int y, int yspace, double offset)
{
   int newY    = y + yspace;
   int newOffs = offset / 2;

   tree->pos.x = x;
   tree->pos.y = y;

   if(tree->left != NULL) {
      calcInitCoords(tree->left, x - (int)offset, newY,
                     yspace, newOffs);
   }

   if(tree->right != NULL) {
      calcInitCoords(tree->right, x + (int)offset, newY,
                     yspace, newOffs);
   }
}

void drawTree(SDL_Window* win, tree_t* tree)
{
   fntrow fontdata[FNTCHARS][FNTHEIGHT];
   SDL_Renderer* ren = SDL_GetRenderer(win);

   Neill_SDL_ReadFont(fontdata, FONTFILE);
   drawTreeRecurse(win, tree->root, 0, fontdata);
   SDL_RenderPresent(ren);
}

void drawTreeRecurse(SDL_Window* win, letter_t* node,
                     int level,
                     fntrow fontdata[FNTCHARS][FNTHEIGHT])
{

   SDL_Renderer* ren = SDL_GetRenderer(win);
   drawNode(win, node->pos, fontdata, node->letter);

   setDrawColor(ren, 0, 0, 0);
   if(node->left != NULL) {
      drawLine(ren, node->pos, node->left->pos);
      drawTreeRecurse(win, node->left, level + 1, fontdata);
   }

   if(node->right != NULL) {
      drawLine(ren, node->pos, node->right->pos);
      drawTreeRecurse(win, node->right, level + 1, fontdata);
   }
}

int treeDepth(letter_t* tree)
{
   int fromLeft, fromRight;
   if(tree == NULL) {
      return 0;
   }

   fromLeft  = treeDepth(tree->left);
   fromRight = treeDepth(tree->right);

   if(fromLeft > fromRight) {
      return fromLeft + 1;
   }
   else {
      return fromRight + 1;
   }
}

list_t** initLevelArray(int depth) {
   int i;
   list_t** levelArray = (list_t**)allocate(sizeof(list_t*) * depth);
   for(i = 0; i < depth; i++) {
      levelArray[i] = (list_t*)allocate(sizeof(list_t));
      initList(levelArray[i]);
   }
   return levelArray;
}

void createLevelArray(letter_t* tree, list_t*** array)
{
   int i, depth   = treeDepth(tree);
   letter_t* node = NULL;

   list_t** levelArray = initLevelArray(depth);
   insertAtEnd(tree, levelArray[0]);

   for(i = 0; i < depth - 1; i++) {
      node = levelArray[i]->start;

      while(node != NULL) {
         addLeavesToList(node, levelArray[i + 1]);
         node = node->next;
      }
   }
   *array = levelArray;
}

void addLeavesToList(letter_t* tree, list_t* list)
{
   insertAtEnd(tree->left, list);
   insertAtEnd(tree->right, list);
}
