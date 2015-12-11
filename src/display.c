#include "display.h"


SDL_Window* initSDLWindow(char* title, position_t pos, dimension_t dim)
{
   SDL_Window* win = NULL;
   if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
      sdlDie("SDL Initialisation");
   }

   if((win = SDL_CreateWindow(title, pos.x, pos.y, dim.w, dim.h, 0)) == NULL) {
      sdlDie("Window Creation");
   }
   return win;
}

SDL_Renderer* makeRenderer(SDL_Window* win, Uint32 flags, rgb_t background)
{
   SDL_Renderer* ren = NULL;
   if((ren = SDL_CreateRenderer(win, FIRSTDRIVER, flags)) == NULL) {
      sdlDie("Renderer Initialisation");
   }

   if(SDL_SetRenderDrawColor(ren, background.r, background.g, background.b, SDL_ALPHA_OPAQUE) != 0) {
      sdlError("Setting Renderer Draw Color");
   };
   return ren;
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
   exit(1);
}

void sdlError(const char* context) {
   fprintf(stderr, "Error: %s", SDL_GetError());
   fprintf(stderr, " (occurred in context: %s)", context);
}
