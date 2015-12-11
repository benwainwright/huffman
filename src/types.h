#ifndef types_H
#define types_H

typedef enum returnCodes {
   SUCCESS,
   USAGE_ERROR
} return_t;

typedef struct letter {
   int letter;
   int freq;
   struct letter* prev;
   struct letter* next;
   struct letter* left;
   struct letter* right;
} letter_t;


typedef struct nodeList {
   letter_t* start;
   letter_t* end;
   int length;
} list_t;

typedef struct code {
   int length;
   int freq;
   char* bits;
} code_t;
#endif
