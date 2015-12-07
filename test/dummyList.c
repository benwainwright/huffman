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

   eight->word = "james";
   eight->next = NULL;
   eight->parent = NULL;

   seven->word = "jimes";
   seven->next = eight;
   seven->parent = NULL;

   six->word = "aames";
   six->next = seven;
   six->parent = NULL;

   five->word = "joen";
   five->next = six;
   five->parent = NULL;

   four->word = "johg";
   four->next = five;
   four->parent = NULL;

   three->word = "james";
   three->next = four;
   three->parent = NULL;

   two->word = "james";
   two->next = three;
   two->parent = NULL;

   one->word = "joon";
   one->prev = NULL;
   one->next = two;
   one->parent = NULL;

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
