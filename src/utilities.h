#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "memory.h"
#define NULLCHARSIZE 1

void skipLine(FILE* fh);
void die(const char* message);
void closeAndDie(FILE* file, const char* message);
FILE* openFile(char* file, const char* mode);
void dieOnReadError(FILE* fh);
int getWord(char** word);
