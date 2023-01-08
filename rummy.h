#ifndef RUMMY_H
#define RUMMY_H
#include <iostream>
#include <vector>
#include "hand.h"
#include "table.h"
#include "board.h"
using namespace std;
/*
* Class representing the game of rummy. This class uses hand, table and board classes
* in order to execute the game.
* private player1score, player2score: integers representing the number of points for each
* player in the game.
*/
class Rummy{
public:
   Rummy();
   const char draw_or_pick();
   const char put_down_prompt();
   const char single_or_set_prompt();
   const int card_prompt();
   int calculate_points(vector <Card*> vec);
   int put_down(hand &h, Table &t, board &b);
   void discard(hand &hand_of_cards,Table &t);
   void pick_up_from_table(hand &hand_of_cards, Table &t, board b);
   void entireplayer1print(hand hand_of_cards, Table t, board b);
   void entireplayer2print(hand hand_of_cards, Table t, board b);
   void shortplayerprint(hand hand_of_cards, Table t, board b);
   void player1play(hand &hand_of_cards, hand &deck, Table &t, board &b);
   void player2play(hand &hand_of_cards, hand &deck, Table &t, board &b);
   void end_game();
   const void play();


private:
   int player1score;
   int player2score;

};

#endif
