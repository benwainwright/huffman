#ifndef types_H
#define types_H

typedef struct position {
   int y;
   int x;
} position_t;

typedef struct dimensions {
   int h;
   int w;
} dimension_t;

typedef struct colourRGB {
   int r;
   int g;
   int b;
} rgb_t;

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

typedef struct queue {
   letter_t* front;
   letter_t* back;
} queue_t;

#endif
