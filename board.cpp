#include "board.h"
/*
* No Arguments constructor for board class. Initializes the vector of vectors of Card pointers
* that will be the 'board'.
*/
board::board() {
   vector <vector <Card*>> setsruns;
}

/*
* Bool function that determines whether the user inputted set or run is valid.
* @param setrun: vector of Card pointers to the 3 or more cards in the user's proposed set or run.
* Returns true if the user enters 3 or more cards of the same value or a run of 3 ascending
* cards of the same suit, and false otherwise.
*/
bool board::valid_set_run(vector<Card*> setrun) {
   bool result = false;
   for (int i = 0; i < setrun.size() - 1; i++) {
      if (setrun[i]->value == setrun[i + 1]->value) {
         result = true;
      } else {
         result = false;
      }
   }
   if (result == true) {
      return result;
   }
   for (int i = 0; i < setrun.size() - 1; i++) {
      if ((setrun[i]->value == setrun[i + 1]->value - 1) && (setrun[i]->suit == setrun[i + 1]->suit)) {
         result = true;
      } else {
         result = false;
      }
   }
   return result;
}
/*
* Helper function that prompts the user for the value and suit of the card they want to put down.
* Returns a card pointer to a card with the user inputted value and suit.
*/
Card* board::card_prompt(hand h) {
   int value = 0;
   char suit = '\0';
   cout << "Enter the value of one of the cards you would like to put down followed by the suit (d,h,c,s): ";
   cin >> value;
   cin >> suit;
   while (!h.in_hand(value, suit)) {
      cout << endl;
      cout << "Oops! That card isn't in your hand. Please re-enter the value of the card you want to put down: ";
      cin >> value;
      cout << "Now please re-enter the suit of the card you want to put down (h,d,s,c): ";
      cin >> suit;
      cout << endl;
   }
   Card* to_add = new Card{value, suit, nullptr, nullptr};
   return to_add;
}
/*
* Function that takes the vector containing the user's invalid set or run and calculates the points that
* should be deducted from their score.
* Returns a vector of card pointers containing one card whose value is the number of points to be deducted.
*/
vector <Card*> calc_invalid_run(vector <Card*> new_vec) {
   cout << endl << "Invalid set or run. These points will be deducted from your score." << endl << endl;
   vector <Card*> subtractpoints;
   int subtract = 0;
   for (int i = 0; i < new_vec.size(); i++) {
      if (new_vec[i]->value > 10) {
         subtract -= 10;
      } else {
         subtract -= 5;
      }
   }
   Card* point_value = new Card{subtract, '\0', nullptr, nullptr};
   subtractpoints.push_back(point_value);
   return subtractpoints;
}

/*
* Function that adds valid user inputted sets or runs to the board.
* @param h: a hand class representing the player's hand of cards that is being drawn from.
* @param num_cards: integer representing the number of cards in the user's set or run(>= 3).
* Returns a vector of cards to be converted to points and added to that player's score. If the
* user inputs an invalid set or run, a vector containing a card with the value of the points
* for each invalid card is returned and then subtracted from that player's score.
*/
vector <Card*> board::add_set_or_run(hand &h, int num_cards) {
   vector <Card*> new_vec;
   vector <Card*> temp_vec;
   for (int i = 0; i < num_cards; i++) {
      Card* to_add = card_prompt(h);
      temp_vec.push_back(to_add);
   }
   for (int i = 0; i < num_cards; i++) {
      Card* add = temp_vec[0];
      int index = 0;
      for (int j = 0; j < temp_vec.size(); j++) {
         if (temp_vec[j]->value < add->value) {
            add = temp_vec[j];
            index = j;
         }
      }
      new_vec.push_back(add);
      h.remove_card_from_hand(h.get_index(add->value, add->suit));
      temp_vec.erase(temp_vec.begin() + index);
   }
   if (valid_set_run(new_vec)) {
      setsruns.push_back(new_vec);
      return new_vec;
   }
   vector <Card*> subtractpoints = calc_invalid_run(new_vec);
   return subtractpoints;
}

/*
* Function that adds a single user inputted card to an existing set or run on the board.
* @param h: a hand class representing the player's hand of cards that is being drawn from.
* @param value: integer representing the value of the card that the player is putting on the board.
* @param suit: character representing the suit of the card that the player is putting on the board.
* Returns true if a valid set or run is found that the card can be added to and false otherwise.
*/
bool board::add_to_existing(hand &h, const int value, const char s) {
   Card* single = new Card{value, s, nullptr, nullptr};
   for (int i = 0; i < setsruns.size(); i++) {
      if (single->value == setsruns[i][0]->value) {
         if(single->value == setsruns[i][1]->value){
            if(single->value == setsruns[i][2]->value) {
               setsruns[i].push_back(single);
               h.remove_card_from_hand(h.get_index(value, s));
               return true;
            }
         }
      } else if (single->value == setsruns[i][0]->value - 1 && single->suit == setsruns[i][0]->suit && single->value == setsruns[i][1]->value - 2 && single->suit == setsruns[i][1]->suit) {
         setsruns[i].insert(setsruns[i].begin(), single);
         h.remove_card_from_hand(h.get_index(value, s));
         return true;
      } else if (single->value == setsruns[i][setsruns[i].size() - 1]->value + 1 && single->suit == setsruns[i][setsruns[i].size() - 1]->suit && single->value == setsruns[i][setsruns[i].size() - 2]->value + 2 && single->suit == setsruns[i][setsruns[i].size() - 2]->suit) {
         setsruns[i].push_back(single);
         h.remove_card_from_hand(h.get_index(value, s));
         return true;
      }
   }
   cout << "You cannot place this card on the board." << endl;
   return false;
}
/*
* Void function that prints the 'board' to display the cards that have been put down and that
* a user can add cards to. This function uses a for loop to print out each set and run
* individually in an organized format.
*/
const void board::print() {
   for (int i = 0; i < setsruns.size(); i++) {
      cout << "| ";
      for (int j = 0; j < setsruns[i].size(); j++) {
         cout << setsruns[i][j]->value << setsruns[i][j]->suit << " | ";
      }
      cout << endl;
   }
}
