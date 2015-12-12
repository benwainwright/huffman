#ifndef SDL_H
#define SDL_H

/* Window dimensions and position */
#define WINWIDTH 1024
#define WINHEIGHT 768
#define WINXPOS 100
#define WINYPOS 100

/* Window Background colour */
#define BGCOLOURRED 0
#define BGCOLOURGREEN 255
#define BGCOLOURBLUE 0

#define TREEBORDER 50

#define FIRSTDRIVER -1
#define NOFLAGS 0

#include <SDL.h>
#include <math.h>
#include "types.h"
#include "queue.h"
#include "huffman.h"

SDL_Window* loadSDLwindow(char* title);
SDL_Renderer* makeRenderer(SDL_Window* win);

void sdlDie(const char* context);
void sdlError(const char* context);
void killWindow(SDL_Window* win);
void queueLeaves(letter_t* tree, queue_t* queue);
void createLevelArray(letter_t* tree, list_t*** array);
void setTreeDims(tree_t* tree, int x, int y, int h, int w);
void calcCoordsRecurse(letter_t* tree, int xpos, int ypos, int spacing, double offset, int level);
double getInitialOffset(double width, double depth);
void calcTreeCoords(tree_t* tree);
void addLeavesToList(letter_t* tree, list_t* list);
void drawTreeRecurse(SDL_Window* win, letter_t* node, int level);
int treeDepth(letter_t* tree);
void drawTree(SDL_Window* win, tree_t* tree);
void drawHuffmanTree(char* filename);
void runEventLoop(SDL_Window* win);
Uint32 getSleepLength(Uint32 frameLength);

#endif
