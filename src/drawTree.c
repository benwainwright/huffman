#include "drawTree.h"


void drawHuffmanTree(char* filename)
{
   SDL_Renderer* ren = NULL;
   tree_t* tree = makeHuffTree(filename);
   SDL_Window* win = loadSDLwindow(filename);
   setTreeDims(tree, WINWIDTH / 2, TREEBORDER,  WINHEIGHT - (2 * TREEBORDER), WINWIDTH - (2 * TREEBORDER));
   calcTreeCoords(tree);
   drawTree(win, tree);
   runEventLoop(win);
}

void runEventLoop(SDL_Window* win)
{
   SDL_Event event;
   while(1) {
      while(SDL_PollEvent(&event)) {
         switch(event.type) {
            case SDL_QUIT:
            case SDL_MOUSEBUTTONDOWN:
            case SDL_KEYDOWN:
            SDL_Quit();
            exit(0);
         }
      }
      SDL_Delay(getSleepLength(20));
   }
}


SDL_Window* loadSDLwindow(char* title)
{
   SDL_Window* win = NULL;
   SDL_Renderer* ren = NULL;
   if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      sdlDie("SDL Initialisation");
   }

   if((win = SDL_CreateWindow(title, WINXPOS, WINYPOS, WINWIDTH, WINHEIGHT, 0)) == NULL) {
      sdlDie("Window Creation");
   }

   ren = makeRenderer(win);
   SDL_RenderClear(ren);
   SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
   return win;
}

SDL_Renderer* makeRenderer(SDL_Window* win)
{
   SDL_Renderer* ren = NULL;
   if((ren = SDL_CreateRenderer(win, FIRSTDRIVER, NOFLAGS)) == NULL) {
      sdlDie("Renderer Initialisation");
   }

   if(SDL_SetRenderDrawColor(ren, BGCOLOURRED, BGCOLOURGREEN, BGCOLOURBLUE, SDL_ALPHA_OPAQUE) != 0) {
      sdlError("Setting Renderer Draw Color");
   };
   return ren;
}


Uint32 getSleepLength(Uint32 frameLength)
{
   Uint32 ticksUsed = SDL_GetTicks() % frameLength;
   return frameLength - ticksUsed;
}

double getInitialOffset(double width, double depth)
{
   double zeroIndexedDepth = depth - 1.0;
   double potentialNodes = pow(2.0, zeroIndexedDepth);
   double baseWidth = width / (potentialNodes - 1.0);
   double baseOffset = baseWidth / 2;
   double initialOffset = baseOffset * (pow(2.0, depth - 2));
   if(depth > 1) {
         return initialOffset;
   }
}

int getSpacing(int height, int depth)
{
   return height / (depth - 1);
}

void calcTreeCoords(tree_t* tree)
{
   int depth = treeDepth(tree->root);
   int spacing = getSpacing(tree->dims.h, depth);
   int initialOffset = getInitialOffset(tree->dims.w, depth);

   calcCoordsRecurse(tree->root, tree->dims.x, tree->dims.y, spacing, initialOffset, 0);
}

void calcCoordsRecurse(letter_t* tree, int xpos, int ypos, int spacing, double offset, int level)
{

   tree->pos.x = xpos;
   tree->pos.y = ypos;
   if(tree->left != NULL) {
      calcCoordsRecurse(tree->left, xpos - (int)offset, ypos + spacing, spacing, offset / 2.0, level + 1);
   }

   if(tree->right != NULL) {
      calcCoordsRecurse(tree->right, xpos + (int)offset, ypos + spacing, spacing, offset / 2.0, level + 1);
   }
}

void drawNode(SDL_Window* win, dims_t dims)
{
   SDL_Renderer* ren = SDL_GetRenderer(win);
   SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
   SDL_RenderDrawPoint(ren, dims.x, dims.y);
   SDL_RenderDrawPoint(ren, dims.x + 1, dims.y);
   SDL_RenderDrawPoint(ren, dims.x - 1, dims.y );
   SDL_RenderDrawPoint(ren, dims.x, dims.y + 1 );
   SDL_RenderDrawPoint(ren, dims.x, dims.y - 1 );
   SDL_RenderDrawPoint(ren, dims.x - 1, dims.y - 1);
   SDL_RenderDrawPoint(ren, dims.x + 1, dims.y + 1);
   SDL_RenderDrawPoint(ren, dims.x - 1, dims.y + 1);
   SDL_RenderDrawPoint(ren, dims.x + 1, dims.y - 1);
}

void drawLine(SDL_Renderer* ren, dims_t from, dims_t to)
{
   if (SDL_RenderDrawLine(ren, from.x, from.y, to.x, to.y) != 0) {
      sdlError("Line drawing");
   }
}
void setTreeDims(tree_t* tree, int x, int y, int h, int w)
{
   tree->dims.x = x;
   tree->dims.y = y;
   tree->dims.w = w;
   tree->dims.h = h;
}



void drawTree(SDL_Window* win, tree_t* tree)
{
   SDL_Renderer* ren = SDL_GetRenderer(win);
   drawTreeRecurse(win, tree->root, 0);
   SDL_RenderPresent(ren);
}

void drawTreeRecurse(SDL_Window* win, letter_t* node, int level)
{

   SDL_Renderer* ren = SDL_GetRenderer(win);
   drawNode(win, node->pos);

   if(node->left != NULL) {
      drawLine(ren, node->pos, node->left->pos);
      drawTreeRecurse(win, node->left, level + 1);
   }

   if(node->right != NULL) {
      drawLine(ren, node->pos, node->right->pos);
      drawTreeRecurse(win, node->right, level + 1);
   }

}

void killWindow(SDL_Window* win) {
   if(win == NULL) {
      fprintf(stderr, "The window that you tried to kill was a NULL pointer\n");
   }
   else {
      SDL_DestroyWindow(win);
   }
}
void sdlDie(const char* context)
{
   sdlError(context);
   SDL_Quit();
   exit(1);
}

void sdlError(const char* context) {
   fprintf(stderr, "Error: %s", SDL_GetError());
   fprintf(stderr, " (occurred in context: %s)", context);
}

int treeDepth(letter_t* tree)
{
   int fromLeft, fromRight;
   if(tree == NULL) {
      return 0;
   }

   fromLeft = treeDepth(tree->left);
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
   int i, depth = treeDepth(tree);
   letter_t* node = NULL;

   list_t** levelArray = initLevelArray(depth);
   insertAtEnd(tree, levelArray[0]);

   for(i = 0; i < depth; i++) {
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
