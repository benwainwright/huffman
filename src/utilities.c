/*
 * Utility functions. Originally written as part of Game
 * of life assignment
 *
 * Updated in this version
 *   - skipLine has been shortened
 *   - New: getWord()
 *
 * Author: Ben Wainwright
 * Date: October 2015
 */
#include "utilities.h"

void skipLine(FILE* fh)
{
   int c;
   do {
      c = fgetc(fh);
   } while(c != '\n' && c != EOF);
}

void die(const char* message)
{
   fprintf(stderr, "%s", message);
   exit(1);
}
void closeAndDie(FILE* file, const char* message)
{
   fclose(file);
   die(message);
}

FILE* openFile(char* file, const char* mode)
{
   const char* message = "Could not open file '%s'...\n";
   char* fmessage = NULL;

   /* -2 for the format specifier, + 1 for the null char */
   int fMessageLen = strlen(file) + strlen(message) - 1;

   FILE* fh = fopen(file, mode);
   if(fh == NULL) {
      fmessage = (char*)allocate(sizeof(char) * fMessageLen);
      sprintf(fmessage, message, file);
      die(fmessage);
   }
   return fh;
}


void dieOnReadError(FILE* fh)
{
   if (ferror(fh)) {
      closeAndDie(fh, "File read error...\n");
   }
}

int getWord(char** word)
{
   char* tempWord = NULL;
   int c, i = 0;
   size_t size;
   c = getchar();
   for(i = 0; c != EOF && isalpha(c); i++) {
      size = sizeof(char) * i + NULLCHARSIZE + 1;
      if((tempWord = (char*)realloc((void*)tempWord, size)) == NULL) {
         die("Failed to allocate memory. Goodbye...\n");
      };
      tempWord[i] = c;
      c = getchar();
   }
   tempWord[i] = '\0';
   *word = tempWord;
   return i;
}
