#ifndef SDL_H
#define SDL_H

#define FIRSTDRIVER -1
#define NOFLAGS 0
#include <sdl.h>
#include "types.h"

SDL_Window* initSDLWindow(char* title, position_t pos, dimension_t dim);
void sdlDie(const char* context);
void sdlError(const char* context);
SDL_Renderer* makeRenderer(SDL_Window* win, Uint32 flags, rgb_t background);
void killWindow(SDL_Window* win);

#endif