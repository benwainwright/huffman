#ifndef types_H
#define types_H
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
   int notTagged;
   int length;
} list_t;
#endif
