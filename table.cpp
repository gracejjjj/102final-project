#include "table.h"
/*
* No arguments constructor for the Table class. Initializes _size to zero and _first and
* _last to be nullptrs.
*/
Table::Table() {
   _size = 0;
   Card* _first = nullptr;
   Card* _last = nullptr;
}

/*
* Void function that draws a card from the deck and initializes a Table with the drawn card
* to start the game.
* @param deck: hand class representing the deck of cards that is being drawn from.
*/
void Table::initialize_table(hand &deck) {
   Card* new_card = deck.deck_draw();
   _first = new_card;
   _last = new_card;
   _size++;
}
/*
* Function that pops the last card from the pick_up pile (the furthest left card in the pile)
* and returns a pointer to that card.
* Returns a pointer to the last Card in the pick-up pile.
*/
Card* Table::pop_last() {
   if (_size == 1) {
      Card* c = _last;
      _first = nullptr;
      _last = nullptr;
      _size--;
      return c;
   } else {
      Card* pop = _last;
      _last->previous->next = nullptr;
      _last = _last->previous;
      _last->next = nullptr;
      _size--;
      return pop;
   }
}
/*
* Void function that adds a card to the pick-up pile. This function is used to discard from
* player's hands at the end of their turn.
*/
void Table::add(Card* card) {
   if (_size == 0) {
      _first = card;
      _last = card;
      _size++;
   } else {
      _last->next = card;
      card->previous = _last;
      _last = card;
      _size++;
   }
}
/*
* Void function that takes a user inputted value and suit to be picked up and finds the corresponding
* Card in the pick up pile. The function then adds the selected card and all the cards to the left of
* it to the user's hand using the pop_last() function.
* @param h: hand class representing the player's hand to which the cards from the pick-up pile
* are being added.
* @param value: user selected integer representing the value of the card they want to pick up.
* @param suit: user selected character representing the suit of the card they want to pick up.
*/
void Table::pick_up(hand &h, int value, char suit) {
   while (_last->value != value || _last->suit != suit) {
      Card* add_to_hand = pop_last();
      h.add_card(add_to_hand);
   }
   Card* final_card = pop_last();
   h.add_card(final_card);
}
/*
* Bool function that takes a user inputted value and suit to be picked up and determines whether
* the corresponding card is actually in the pick-up pile.
* @param value: user selected integer representing the value of the card they want to pick up.
* @param s: user selected character representing the suit of the card they want to pick up.
* Returns true if the corresponding card is identified in the table and false otherwise.
*/
bool Table::in_table(int value, char s) {
   if (s == 'a') {
     Card* current = _first;
     for (size_t i = 0; i < _size; i++) {
        if (current->value == value) {
           return true;
        } else {
           current = current->next;
        }
        return false;
     }
  } else {
     Card* current = _first;
     for (size_t i = 0; i < _size; i++) {
        if (current->value == value && current->suit == s) {
           return true;
        } else {
           current = current->next;
        }
     }
     return false;
  }
  return false;
}
/*
* Void function that prints the pick-up pile, beginning with the most recently discarded card,
* '_last', and ending with the _first card in the class.
*/
const void Table::print() {
   Card* current = _last;
   cout << "| ";
   for (int i = 0; i < _size; i++) {
      cout << current->value << current->suit << " | ";
      current = current->previous;
   }
   cout << endl;
}
