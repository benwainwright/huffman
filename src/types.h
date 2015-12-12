#ifndef types_H
#define types_H


typedef struct dimensions {
   int y;
   int x;
   int h;
   int w;
} dims_t;

typedef struct colourRGB {
   int r;
   int g;
   int b;
} rgb_t;

typedef struct letter {
   int letter;
   int freq;
   struct letter* prev;
   struct letter* next;
   struct letter* left;
   struct letter* right;
   dims_t pos;
} letter_t;

typedef struct tree {
   dims_t dims;
   letter_t* root;
} tree_t;

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
   int length;
   letter_t* front;
   letter_t* back;
} queue_t;

#endif
