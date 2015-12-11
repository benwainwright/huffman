#include "unity.h"
#include "display.h"
#include "types.h"


void testDisplayWindow(void)
{
   position_t position = { .x = 100, .y = 100 };
   dimension_t dimension = { .w = 1024, .h = 768 };
   rgb_t background = { .r = 100, .g = 100, .b = 100 };
   SDL_Window* win = initSDLWindow("Test window", position, dimension);
   SDL_Renderer* ren = makeRenderer(win, NOFLAGS, background);
   sleep(4);
}
