#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <vector>
#include "hand.h"
using namespace std;
/*
* Class representing the stack of discarded cards that are able to be picked up.
* private _size: size_t variable representing the number of cards in the pick-up pile.
* private _first: Card pointer to the first card in the pick-up pile.
* private _last: Card pointer to the last card in the pick-up pile.
*/
class Table{
public:
   Table();
   void initialize_table(hand &deck);
   Card* pop_last();
   void add(Card* card);
   void pick_up(hand &h, int value, char suit);
   bool in_table(int value, char s);
   const void print();

private:
   size_t _size;
   Card* _first;
   Card* _last;

};

#endif
