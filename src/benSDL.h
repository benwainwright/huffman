#ifndef benSDL_H
#define benSDL_H

/* Window dimensions and position */
#define WINWIDTH 1024
#define WINHEIGHT 768
#define WINXPOS 100
#define WINYPOS 100


#define TREEBORDER 50
#define NODERADIUS 15
#define FIRSTDRIVER -1
#define NOFLAGS 0

#include <SDL.h>
#include "types.h"
#include "neillsdl2.h"

SDL_Window* loadSDLwindow(char* title);
SDL_Renderer* makeRenderer(SDL_Window* win);
Uint32 getSleepLength(Uint32 frameLength);
SDL_Surface* loadBMP(const char* filename);
SDL_Texture* textureFromSurface(SDL_Renderer* ren, SDL_Surface* surf);
void rendClear(SDL_Renderer* ren);
void rendCopy(SDL_Renderer* ren,
                SDL_Texture* tex,
                const SDL_Rect* src,
                const SDL_Rect* dst);
void loadBackgroundImage(const char* filename, SDL_Window* win);
void drawFilledCircleWithBorder(SDL_Renderer *ren, int x, int y, int r);
void drawNode(SDL_Window* win, dims_t dims, fntrow fontdata[FNTCHARS][FNTHEIGHT], char c);
void drawLine(SDL_Renderer* ren, dims_t from, dims_t to);
void drawChar(SDL_Window* win, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy);
void killWindow(SDL_Window* win);
void sdlDie(const char* context);
void sdlError(const char* context);
void setDrawColor(SDL_Renderer* ren, Uint8 r, Uint8 g, Uint8 b);

#endif
