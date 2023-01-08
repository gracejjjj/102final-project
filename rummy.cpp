#include "rummy.h"

/*
* No arguments constructor for the Rummy class. This function initializes player1score and
* player2score to be zero.
*/
Rummy::Rummy() {
   player1score = 0;
   player2score = 0;
}

/*
* This helper function prompts the user to choose to draw a card or pick up from the pick-up
* pile. It ensures that the user input is valid and that an incorrect entry will not crash the
* program.
* Returns character 'd' if user chooses to draw from the deck and 'p' if they choose to pick up.
*/
const char Rummy::draw_or_pick() {
   char choice = '\0';
   cout << "Enter 'd' to draw from the deck or 'p' to pick up from the table: ";
   cin >> choice;
   while (choice != 'p' && choice != 'd') {
      cout << endl;
      cout << "Invalid entry. Please enter 'd' if you want to draw from the deck or 'p' if you want to pick up from the table: ";
      cin >> choice;
      cout << endl;
   }
   return choice;
}

/*
* This helper function prompts the user to indicate whether they have any cards they would
* like to put down on the board. It ensures that the user input is valid and that an incorrect entry
* will not crash the program.
* Returns character 'y' if user wants to put down a card or cards and 'n' if they are ready to discard.
*/
const char Rummy::put_down_prompt() {
   char choice = '\0';
   cout << endl;
   cout << "Do you have any cards in your hand you want to put down for points? Enter 'y' if you do and 'n' if you are ready to discard: ";
   cin >> choice;
   while (choice != 'y' && choice != 'n') {
      cout << endl;
      cout << "Invalid entry. Please enter 'y' if you want to put down cards for points or 'n' if you are ready to dicard: ";
      cin >> choice;
      cout << endl;
   }
   return choice;
}
/*
* This helper function prompts the user to indicate whether they want to put down a single card or a set or run. It
* protects against invalid entries.
* Returns character 's' if user wants to put down a single card and 'n' if they want to create a new set
* and 'd' if they are ready to discard.
*/
const char Rummy::single_or_set_prompt() {
   char choice = '\0';
   cout << endl;
   cout << "Please enter 's' to add a single card to an existing set or run or 'n' to create a new set or run. To skip straight to discard, enter 'd': ";
   cin >> choice;
   while (choice != 's' && choice != 'n' && choice != 'd') {
      cout << endl << endl;
      cout << "Please enter 's' to add a single card to an existing set or run or 'n' to create a new set or run. To skip straight to discard, enter 'd': ";
      cin >> choice;
      cout << endl << endl;
   }
   return choice;
}
/*
* This helper function prompts the user to enter how many cards are in their set or run. It protects
* against invalid entries.
* Returns integer representing the number of cards in their set/run.
*/
const int Rummy::card_prompt() {
   int num = 0;
   cout << "How many cards would you like to put down? ";
   cin >> num;
   while (num != 3 && num != 4 && num != 5 && num != 6 && num != 7 && num != 8) {
      cout << endl << endl << "Set or run must be at least 3 cards long. Enter a valid size for your set/run: " << endl;
      cin >> num;
   }
   return num;
}
/*
* Function that takes a vector of Card* returned from the add_set_or_run function and calculates the number
* of points in the set or run.
* Returns integer representing the number of points gained from the set/run.
*/
int Rummy::calculate_points(vector <Card*> vec) {
   int points = 0;
   if (vec.size() == 1) {
      points += vec[0]->value;
   } else {
      for (int i = 0; i < vec.size(); i++) {
         if (vec[i]->value > 10) {
            points += 10;
         } else {
            points += 5;
         }
      }
   }
   return points;
}

/*
* This function executes the entire put-down process for a single card or a set or run. It
* prompts the user for information about the cards they want to put down and then calls either
* add_to_existing or add_set_or_run to execute the play.
* @param h: hand class representing the player's hand of cards that is being drawn from.
* @param t: table class representing the pick-up pile. This is a necessary argument for the
* shortplayerprint function to show the user the updated state of the game.
* @param b: board class representing the board of the game that to which the function will
* append a single card or a new set or run.
* Returns an integer value representing the points that a user has earned from their play to
* be added to that player's score.
*/
int Rummy::put_down(hand &h, Table &t, board &b) {
   int points = 0;
   int value = 0;
   char suit = '\0';
   char choice = single_or_set_prompt();
   if (choice == 'd') {
      shortplayerprint(h, t, b);
      return 0;
   } else if (choice == 's') {
      cout << "Enter the value of the card you would like to put down followed by the suit (d,h,c,s): ";
      cin >> value;
      cin >> suit;
      if (b.add_to_existing(h, value, suit)) {
         if (value > 10) {
            points += 10;
         } else {
            points += 5;
         }
      } else {
         cout << "There is no existing set or run that you can add this card to." << endl;
      }
      shortplayerprint(h, t, b);
      return points;
   } else {
      int num_cards = card_prompt();
      vector <Card*> new_vec = b.add_set_or_run(h, num_cards);
      points += calculate_points(new_vec);
      shortplayerprint(h, t, b);
      return points;
   }
}

/*
* Void function that prompts the user to indicate which card from their hand they want to discard
* to the pick-up pile once their turn has finished.
* @param hand_of_cards: hand class representing the player's hand of cards that is being modified.
* @param t: table class representing the pick-up pile that the discarded card is being pushed onto.
*/
void Rummy::discard(hand &hand_of_cards,Table &t) {
   int value = 0;
   char suit = '\0';
   cout << endl;
   cout << "Please enter first the value of the card you want to discard followed by its suit (d,h,s,c): ";
   cin >> value;
   cin >> suit;
   while (!hand_of_cards.in_hand(value, suit)) {
      cout << endl;
      cout << "Oops! That card isn't in your hand. Please re-enter the value of the card you want to discard: ";
      cin >> value;
      cout << "Now please re-enter the suit of the card your need to discard (h,d,s,c): ";
      cin >> suit;
      cout << endl;
   }
   int index = hand_of_cards.get_index(value, suit);
   Card* add_to_table = hand_of_cards.remove_card_from_hand(index);
   t.add(add_to_table);
   cout << endl;
}

/*
* Void function that prompts the user which card they want to pick up from the pick-up pile once
* they have indicated that they want to pick up instead of draw.
* @param hand_of_cards: hand class representing the player's hand of cards that will be added to.
* @param t: table class representing the pick-up pile that the user is picking up from.
* @param b: board class representing the board containing all cards that have been put down
* for points. This is a necessary argument for the shortplayerprint function to show the user
* the updated state of the game.
*/
void Rummy::pick_up_from_table(hand &hand_of_cards, Table &t, board b) {
   int value = 0;
   char suit = '\0';
   cout << endl;
   cout << "Please enter first the value of the card you want to pick up followed by its suit (d,h,s,c): ";
   cin >> value;
   cin >> suit;
   while (!t.in_table(value, suit)) {
      cout << endl;
      cout << "Oops! That card isn't in the discard pile. Please re-enter the value of the card you want to pick up: ";
      cin >> value;
      cout << "Now please re-enter the suit of the card you want to pick up (h,d,s,c): ";
      cin >> suit;
      cout << endl;
   }
   t.pick_up(hand_of_cards, value, suit);
   shortplayerprint(hand_of_cards, t, b);
}

/*
* Void function that prints at the beginning of player 1's turn. It prints player 1's hand,
* their points thus far, the pick-up pile, and the cards that have already been put down on
* the board for points.
* @param hand_of_cards: hand class representing player 1's current hand of cards.
* @param t: table class representing the pick-up pile.
* @param b: board class representing the board containing all cards that have been put down
* for points.
*/
void Rummy::entireplayer1print(hand hand_of_cards, Table t, board b) {
   cout << endl;
   cout << "Player 1 points: " << player1score << endl;
   cout << "Player 1 hand: ";
   hand_of_cards.print();
   cout << "Cards in the pick-up pile: ";
   t.print();
   cout << endl;
   cout << "Cards on the table: " << endl;
   b.print();
   cout << endl;
}
/*
* Void function that prints at the beginning of player 2's turn. It prints player 2's hand,
* their points thus far, the pick-up pile, and the cards that have already been put down on
* the board for points.
* @param hand_of_cards: hand class representing player 2's current hand of cards.
* @param t: table class representing the pick-up pile.
* @param b: board class representing the board containing all cards that have been put down
* for points.
*/
void Rummy::entireplayer2print(hand hand_of_cards, Table t, board b) {
   cout << endl;
   cout << "Player 2 points: " << player2score << endl;
   cout << "Player 2 hand: ";
   hand_of_cards.print();
   cout << "Cards in the pick-up pile: ";
   t.print();
   cout << endl;
   cout << "Cards on the table: " << endl;
   b.print();
   cout << endl;
}
/*
* Void function that serves as an abbreviated print statement after each modification to
* a hand, the table, or the board during a player's turn.
* @param hand_of_cards: hand class representing the player's current hand of cards.
* @param t: table class representing the pick-up pile.
* @param b: board class representing the board containing all cards that have been put down
* for points.
*/
void Rummy::shortplayerprint(hand hand_of_cards, Table t, board b) {
   cout << endl;
   cout << "Your current hand is: ";
   hand_of_cards.print();
   cout << "Cards in the pick-up pile: ";
   t.print();
   cout << endl;
   cout << "Cards on the table: " << endl;
   b.print();
}
/*
* Void function that executes a full turn for player 1.
* @param hand_of_cards: hand class representing player 1's current hand of cards.
* @param deck: hand class representing the deck of cards remaining that have not been drawn
* into player's hands, put down on the table, or discarded into the pick-up pile.
* @param t: table class representing the pick-up pile.
* @param b: board class representing the board containing all cards that have been put down
* for points.
*/
void Rummy::player1play(hand &hand_of_cards, hand &deck, Table &t, board &b) {
   entireplayer1print(hand_of_cards, t, b);
   if (draw_or_pick() == 'd') {
      hand_of_cards.add_card(deck.deck_draw());
      shortplayerprint(hand_of_cards, t, b);
      while (put_down_prompt() == 'y') {
         player1score += put_down(hand_of_cards, t, b);
      }
      discard(hand_of_cards, t);
   } else {
      pick_up_from_table(hand_of_cards, t, b);
      player1score += put_down(hand_of_cards, t, b);
      while (put_down_prompt() == 'y') {
         player1score += put_down(hand_of_cards, t, b);
      }
      discard(hand_of_cards, t);
   }
   cout << "End of player 1's turn. You have " << player1score << " points." << endl;
}
/*
* Void function that executes a full turn for player 2.
* @param hand_of_cards: hand class representing player 2's current hand of cards.
* @param deck: hand class representing the deck of cards remaining that have not been drawn
* into player's hands, put down on the table, or discarded into the pick-up pile.
* @param t: table class representing the pick-up pile.
* @param b: board class representing the board containing all cards that have been put down
* for points.
*/
void Rummy::player2play(hand &hand_of_cards, hand &deck, Table &t, board &b) {
   entireplayer2print(hand_of_cards, t, b);
   if (draw_or_pick() == 'd') {
      hand_of_cards.add_card(deck.deck_draw());
      shortplayerprint(hand_of_cards, t, b);
      while (put_down_prompt() == 'y') {
         player2score += put_down(hand_of_cards, t, b);
      }
      discard(hand_of_cards, t);
   } else {
      pick_up_from_table(hand_of_cards, t, b);
      player2score += put_down(hand_of_cards, t, b);
      while (put_down_prompt() == 'y') {
         player2score += put_down(hand_of_cards, t, b);
      }
      discard(hand_of_cards, t);
   }
   cout << "End of player 2's turn. You have " << player2score << " points." << endl;
}
/*
* Void function that is called once the game has ended to determine which player has
* more points. It then prints a statement 'Game Over. Player __ wins!'.
*/
void Rummy::end_game() {
   cout << endl;
   if (player1score > player2score) {
      cout << "Game over." << endl;
      cout << "Player 1: " << player1score << " points" << endl;
      cout << "Player 2: " << player2score << " points" << endl << endl;
      cout << "Player 1 wins!" << endl;
   } else if (player1score < player2score) {
      cout << "Game over." << endl;
      cout << "Player 1: " << player1score << " points" << endl;
      cout << "Player 2: " << player2score << " points" << endl << endl;
      cout << "Player 2 wins!" << endl;
   } else {
      cout << "Game over." << endl;
      cout << "Player 1: " << player1score << " points" << endl;
      cout << "Player 2: " << player2score << " points" << endl << endl;
      cout << "It's a tie!" << endl;
   }
   cout << endl;
}
/*
* Void function that executes the entire rummy game. It creates a deck of cards and initializes
* hands for both players, the table class for the pick-up pile, the board class for the played
* sets and runs, and the rummy class to play the game. The function alternates turns between
* player 1 and player 2 until a player runs out of cards in their deck or until the deck of cards
* is empty.
*/
const void Rummy::play() {
   hand one;
   hand two;
   hand deck;
   Table t;
   board b;
   Rummy rummy;
   deck.initialize_deck();
   one.initialize_hand(deck);
   two.initialize_hand(deck);
   t.initialize_table(deck);
   while (deck.get_size() != 0 && one.get_size() != 0 && two.get_size() != 0) {
      rummy.player1play(one, deck, t, b);
      if (deck.get_size() != 0 && one.get_size() != 0 && two.get_size() != 0) {
         rummy.player2play(two,deck,t, b);
      }
   }
   player1score -= one.get_score();
   player2score -= two.get_score();
   rummy.end_game();
}
