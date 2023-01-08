#include "hand.h"
/*
* No arguments constructor for the hand class that initializes _size to zero.
*/
hand::hand() {
   _size = 0;
}

/*
* Function that retrieves the size of a hand.
* Returns a size_t variable that is the _size of the hand.
*/
const size_t hand::get_size() {
   return _size;
}
/*
* Void function that adds a card to a hand.
* @param new_card: Card pointer that points to the Card being added to the hand.
*/
void hand::add_card(Card* new_card) {
   cards.push_back(new_card);
   _size++;
}
/*
* Function that takes a user inputted value and suit and finds the index of the corresponding
* card in the player's hand.
* @param value: integer representing the value of the card whose index is being retrieved.
* @param suit: character representing the suit of the card whose index is being retrieved.
* Returns the index of the corresponding card in the hand.
*/
int hand::get_index(const int value, const char suit) {
   for (int i = 0; i < _size; i++) {
      if (cards[i]->value == value && cards[i]->suit == suit) {
         return i;
      }
   }
   return 0;
}
/*
* Function that takes an index and removes the card at that index from a hand of cards.
* @param index: integer representing the index of the card being removed.
* Returns a Card pointer to the Card that has been removed.
*/
Card* hand::remove_card_from_hand(int index) {
   Card* c = cards[index];
   cards.erase(cards.begin() + index);
   _size--;
   return c;
}
/*
* Void function that uses for loops to initialize a hand class to be a 'deck of cards'. The
* function adds the 52 unique cards in a standard deck to an empty hand. 11, 12, and 13 are used
* place of jack, queen and king.
*/
const void hand::initialize_deck() {
   for (int i = 1; i <= 13; i++) {
      Card* baby = new Card{i, 'h', nullptr, nullptr};
      cards.push_back(baby);
      _size++;
   }
   for (int i = 1; i <= 13; i++) {
      Card* baby = new Card{i, 'd', nullptr, nullptr};
      cards.push_back(baby);
      _size++;
   }
   for (int i = 1; i <= 13; i++) {
      Card* baby = new Card{i, 'c', nullptr, nullptr};
      cards.push_back(baby);
      _size++;
   }
   for (int i = 1; i <= 13; i++) {
      Card* baby = new Card{i, 's', nullptr, nullptr};
      cards.push_back(baby);
      _size++;
   }
}
/*
* Function that randomly generates an index within a hand class representing a deck and removes the
* card at this index from the deck, effectively 'drawing' from the deck.
* Returns a Card pointer to the card that has been drawn.
*/
Card* hand::deck_draw() {
   srand(time(0));
   int index = rand() % _size;
   Card* pop = cards[index];
   cards.erase(cards.begin() + index);
   _size--;
   return pop;
}
/*
* Void function that initializes player's hands to begin a game of rummy. 7 cards are drawn
* from the deck being passed as the function's argument and are added to the player's hand of cards.
* @param deck: hand class that was initialized as a deck from which we are drawing a random card.
*/
void hand::initialize_hand(hand &deck) {
   for (int i = 0; i < 7; i++) {
      Card* new_card = deck.deck_draw();
      cards.push_back(new_card);
      _size++;
   }
 }
 /*
 * Bool function that determines whether or not a given card is in a player's hand. This function
 * ensures that a user cannot input a card to put down or discard from their hand that is not
 * actually in their hand.
 * @param value: integer representing the value of the card being searched for in the hand.
 * @param s: character representing the suit of the card being searched for in the hand.
 * Returns true if the corresponding card is found in the hand and false otherwise.
 */
 bool hand::in_hand(const int value, const char s) {
    if (s == 'a') {
      for (size_t i = 0; i < _size; i++) {
         if (cards[i]->value == value) {
            return true;
         }
         return false;
      }
   } else {
      for (size_t i = 0; i < _size; i++) {
         if (cards[i]->value == value && cards[i]->suit == s) {
            return true;
         }
      }
      return false;
   }
   return false;
}

int hand::get_score() {
   int score = 0;
   for (int i = 0; i < cards.size(); i++) {
      if (cards[i]->value > 10) {
         score += 10;
      } else {
         score += 5;
      }
   }
   return score;
}
/*
* Void function that prints the cards in a player's hand.
*/
const void hand::print() {
   cout << "| ";
   for (size_t i = 0; i < _size; i++) {
      cout << cards[i]->value << cards[i]->suit << " | ";
   }
   cout << endl;
}
