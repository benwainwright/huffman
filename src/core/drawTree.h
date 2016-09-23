#ifndef SDL_H
#define SDL_H

#define FONTFILE "resources/m7fixed.fnt"


/* Window Background */
#define BACKGROUNDIMAGE "resources/Oak-tree.bmp"

#define TREEBORDER 50
#define NODERADIUS 15
#define FIRSTDRIVER -1
#define NOFLAGS 0


/**** Spread Algorithm ********************************************/
/* Distance each qualifying node or subtree is moved on each pass */
#define SHUFFLEDISTANCE 10
/* Maximum number of passes before giving up */
#define SPREAD_MAX 30
/******************************************************************/

#include <SDL.h>
#include <math.h>
#include "types.h"
#include "queue.h"
#include "huffman.h"
#include "benSDL.h"


void queueLeaves(letter_t* tree, queue_t* queue);
void createLevelArray(letter_t* tree, list_t*** array);
void setTreeDims(tree_t* tree, int x, int y, int h, int w);
void calcInitCoords(letter_t* tree, int xpos, int ypos, int spacing, double offset);
double getInitialOffset(double width, double depth);
void calcTreeCoords(tree_t* tree);
void addLeavesToList(letter_t* tree, list_t* list);
void drawTreeRecurse(SDL_Window* win, letter_t* node,
                     int level,
                     fntrow fontdata[FNTCHARS][FNTHEIGHT]);
int treeDepth(letter_t* tree);
void drawTree(SDL_Window* win, tree_t* tree);
void drawHuffmanTree(char* filename);
int leftSpace(tree_t* tree, letter_t* node);
int rightSpace(tree_t* tree, letter_t* node);
void moveTreeX(letter_t* tree, int move);
void spreadNodes(tree_t* tree, list_t** levelArray);
int doSpreadPass(tree_t* tree, list_t** levelArray);
int shuffleIfCollisions(tree_t* tree, letter_t* node);
int shuffleIfNotAboveChildren(tree_t* tree, letter_t* node);
int isColliding(letter_t* node);
int isBetweenChildrenIfExist(letter_t* node);
void spreadCollidingNodes(tree_t* tree, list_t** levelArray);

#endif
