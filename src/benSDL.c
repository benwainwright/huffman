#include "benSDL.h"

void runEventLoop(SDL_Window *win)
{
   SDL_Renderer* ren = NULL;
   SDL_Event event;
   while(1) {
      while(SDL_PollEvent(&event)) {
         switch(event.type) {
            case SDL_KEYDOWN:
            case SDL_MOUSEBUTTONDOWN:
               ren = SDL_GetRenderer(win);
               SDL_Quit();
               SDL_DestroyWindow(win);
               SDL_DestroyRenderer(ren);
               freeHeapList();
               exit(0);
            break;
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

   if((win = SDL_CreateWindow(title, WINXPOS, WINYPOS,
                              WINWIDTH, WINHEIGHT, 0)) == NULL) {

      sdlDie("Window Creation");
   }

   ren = makeRenderer(win);
   SDL_RenderClear(ren);
   return win;
}

SDL_Renderer* makeRenderer(SDL_Window* win)
{
   SDL_Renderer* ren = NULL;
   if((ren = SDL_CreateRenderer(win, FIRSTDRIVER, NOFLAGS)) == NULL) {
      sdlDie("Renderer Initialisation");
   }
   return ren;
}


void setDrawColor(SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b) {
   if(SDL_SetRenderDrawColor(ren, r, g, b, SDL_ALPHA_OPAQUE) != 0) {
      sdlError("Setting Renderer Draw Color");
   };
}
Uint32 getSleepLength(Uint32 frameLength)
{
   Uint32 ticksUsed = SDL_GetTicks() % frameLength;
   return frameLength - ticksUsed;
}

SDL_Surface* loadBMP(const char* filename)
{
   SDL_Surface* background = SDL_LoadBMP(filename);

   if(background == NULL) {
      sdlError("Background load");
   }
   return background;
}

SDL_Texture* textureFromSurface(SDL_Renderer* ren, SDL_Surface* surf)
{
   SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surf);

   if(texture == NULL) {
      sdlError("Converting background to texture");
   }
   return texture;
}

void rendClear(SDL_Renderer* ren)
{
   if(SDL_RenderClear(ren) != 0) {
      sdlError("Clearing renderer");
   };
}

void rendCopy(SDL_Renderer* ren, SDL_Texture* tex,
                const SDL_Rect* src, const SDL_Rect* dst) {

   if(SDL_RenderCopy(ren, tex, src, dst) != 0) {
      sdlError("Copying texture to renderer");
   }
}

void loadBackgroundImage(const char* filename, SDL_Window* win)
{
   SDL_Surface* background = loadBMP(filename);
   SDL_Renderer* ren = SDL_GetRenderer(win);
   SDL_Texture* bgTexture = textureFromSurface(ren, background);
   SDL_FreeSurface(background);
   rendClear(ren);
   rendCopy(ren, bgTexture, NULL, NULL);
   SDL_DestroyTexture(bgTexture);
}

void drawFilledCircleWithBorder(SDL_Renderer *ren, int x, int y, int r) {

      SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
      Neill_SDL_RenderFillCircle(ren, x, y, r);
      SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
      Neill_SDL_RenderDrawCircle(ren, x, y, r);
}

void drawNode(SDL_Window* win, dims_t dims,
              fntrow fontdata[FNTCHARS][FNTHEIGHT], char c)
{
   SDL_Renderer* ren = SDL_GetRenderer(win);

   if(isgraph(c)) {
      drawFilledCircleWithBorder(ren, dims.x, dims.y, NODERADIUS);

      drawChar(win, fontdata, c,
               dims.x - (NODERADIUS / 2),
               dims.y - (NODERADIUS / 2));
   }
   else {
      drawFilledCircleWithBorder(ren, dims.x, dims.y, NODERADIUS / 2);
   }
}

void drawLine(SDL_Renderer* ren, dims_t from, dims_t to)
{
   if (SDL_RenderDrawLine(ren, from.x, from.y, to.x, to.y) != 0) {
      sdlError("Line drawing");
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

/* This is an adapted version of Neill_SDL_DrawChar since I don't use
   the 'simplewin' structure */
void drawChar(SDL_Window* win, fntrow fontdata[FNTCHARS][FNTHEIGHT],
              unsigned char chr, int ox, int oy)
{
   SDL_Renderer* ren= SDL_GetRenderer(win);
   unsigned x, y;
   for(y = 0; y < FNTHEIGHT; y++){
      for(x = 0; x < FNTWIDTH; x++){
         if(fontdata[chr-FNT1STCHAR][y] >> (FNTWIDTH - 1 - x) & 1){
            SDL_SetRenderDrawColor(ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(ren, x + ox, y+oy);
         }
         else{
            SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(ren, x + ox, y+oy);
         }
      }
   }
}
