#include "dummyList.h"

list_t dummyList(void)
{
   letter_t* one = (letter_t*)malloc(sizeof(letter_t));
   letter_t* two = (letter_t*)malloc(sizeof(letter_t));
   letter_t* three = (letter_t*)malloc(sizeof(letter_t));
   letter_t* four = (letter_t*)malloc(sizeof(letter_t));
   letter_t* five = (letter_t*)malloc(sizeof(letter_t));
   letter_t* six = (letter_t*)malloc(sizeof(letter_t));
   letter_t* seven = (letter_t*)malloc(sizeof(letter_t));
   letter_t* eight = (letter_t*)malloc(sizeof(letter_t));
   list_t list;

   eight->letter = 'j';
   eight->next = NULL;

   seven->letter = 'i';
   seven->next = eight;

   six->letter = 'a';
   six->next = seven;

   five->letter = 'o';
   five->next = six;

   four->letter = 'g';
   four->next = five;

   three->letter = 'l';
   three->next = four;

   two->letter = 's';
   two->next = three;

   one->letter = 'f';
   one->prev = NULL;
   one->next = two;

   eight->prev = seven;
   seven->prev = six;
   six->prev = five;
   five->prev = four;
   four->prev = three;
   three->prev = two;
   two->prev = one;

   list.start = one;
   list.end = eight;

   return list;
}