#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "hand.h"
using namespace std;

/*
* Class representing the 'board' in a game of rummy. This class ensures that players
* are putting down valid cards and are receiving correct scoring for their sets and runs.
* private: vector <vector <Card*>>: vector of vectors of Card pointers. This vector represents
* all of the sets and runs that have been played in a given game.
*/
class board{
public:
   board();
   bool valid_set_run(vector <Card*> setrun);
   Card* card_prompt(hand h);
   vector <Card*> add_set_or_run(hand &h, int num_cards);
   bool add_to_existing(hand &h, const int value, const char s);
   const void print();

private:
   vector <vector <Card*>> setsruns;
};

#endif
