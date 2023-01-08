#ifndef HAND_H
#define HAND_H
#include <iostream>
#include <vector>
using namespace std;

/*
* Struct representing a card in the deck.
* value: integer representing the value of the Card.
* suit: character, 'd','c','s','h', representing the suit, diamonds, clubs, spades, or hearts,
* of the Card.
* next: Card pointer that points to the next card in a class. This pointer is exclusively used
* in the table class.
* previous: Card pointer that points to the previous card in a class. This pointer is exclusively used
* in the table class.
*/
struct Card {
   int value;
   char suit;
   Card* next;
   Card* previous;
};
/*
* Class representing a collection of cards, in this game being either a hand of cards or a deck of cards.
* private cards: vector of Card pointers representing a hand of cards or a deck of cards.
* private _size: size_t variable representing the number of cards in a hand.
*/
class hand{
public:
   hand();
   void add_card(Card* new_card);
   const size_t get_size();
   Card* remove_card_from_hand(const int index);
   int get_index(const int value, const char suit);
   const void initialize_deck();
   Card* deck_draw();
   void initialize_hand(hand &deck);
   bool in_hand(const int value, const char s);
   int get_score();
   const void print();

private:
   vector <Card*> cards;
   size_t _size;
};

#endif
