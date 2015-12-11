#include "main.h"

int main(int argc, char* argv[])
{
   position_t position = { .x = 100, .y = 100 };
   dimension_t dimension = { .w = 1024, .h = 768 };
   rgb_t background = { .r = 230, .g = 12, .b = 12 };
   SDL_Window* win = NULL;
   SDL_Renderer* ren = NULL;
   letter_t* tree = NULL;
   letter_t* asciiGram = NULL;

   if(argc == 2) {

      makeFileAsciiGram(argv[1], &asciiGram);
      tree = makeHuffTree(argv[1]);
      win = initSDLWindow("Test window", position, dimension);
      ren = makeRenderer(win, NOFLAGS, background);

      sleep(4);
      killWindow(win);

      freeHeapList();
      return 0;
   }
   else {
      fprintf(stderr, "Incorrect usage: try %s <filename>\n", argv[0]);
      return 1;
   }
}
