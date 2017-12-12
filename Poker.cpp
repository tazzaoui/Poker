#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string>
#include "Deck.hpp"
#include "Card.hpp"
#include "Hand.hpp"
#include "MonteCarlo.hpp"


using namespace std;

int verbose = 0;
int numRuns = 1000;

int main(int argc, char* argv[]){
  printf(R"EOF(
          _____
         |A .  | _____
         | /.\ ||A ^  | _____
         |(_._)|| / \ ||A _  | _____
         |  |  || \ / || ( ) ||A_ _ |
         |____V||  .  ||(_'_)||( v )|
                |____V||  |  || \ / |
                       |____V||  .  |
                              |____V|)EOF");

  cout << endl << endl;
  
  vector<string> cmdArgs = vector<string>(argv, argv + argc);

  for(size_t i = 0; i < cmdArgs.size(); ++i){
    if(cmdArgs[i] == "-h" || cmdArgs[i] == "--help"){
      cout << "Usage: poker [-h] [-v VERBOSITY] [-n NUMRUNS]" << endl;
      cout << "-h, --help:     show this help message and exit." << endl;
      cout << "-v, --verbose:  set verbosity. Default = 0." 
	   << "(0 = output essentials only, 1 = output Monte Carlo stats, "
	   << "2 = Maximum verbosity)" << endl;
      cout << "-n, --numruns:  Number of simulations per card configuration. Default = 1000" << endl;
      exit(0);
    }if(cmdArgs[i] == "-v"|| cmdArgs[i] == "--verbose"){
      if(i + 1 < cmdArgs.size()) verbose = atoi(cmdArgs[i + 1].c_str());
    }if(cmdArgs[i] == "-n" || cmdArgs[i] == "--numruns"){
      if(i + 1 < cmdArgs.size()) numRuns= atoi(cmdArgs[i + 1].c_str());
    }
  }
  
  Deck d;
  d.shuffle();
  srand(time(0));
  
  /* Set up the dealer's hand */
  cout << endl << endl << "Dealing the dealer's hand..." << endl << endl;
  vector<Card> cards;
  for(size_t i = 0; i < 5; ++i )
   cards.push_back(d.deal_card());
  Hand h1 = Hand(cards.data());

  cards.clear();

  if(verbose == 2){
    cout << "The dealer was dealt: " << endl << h1;
    cout << "Value: " << h1.value() << endl << endl;;
  }

  /* Set up the player's hand... */
  cout << "Dealing your hand..." << endl << endl;
  for(size_t i = 0; i < 5; ++i )
    cards.push_back(d.deal_card());
  Hand h2 = Hand(cards.data());

  cout << "You were dealt: " << endl << h2;
  if(verbose)
    cout << "Value: " << h2.value() << endl;

  cout << endl << "You can now choose to draw one, two or three " <<
    "more cards to replace\nthe corresponding number of unneeded"<<
    "cards in the original hand..." << endl << endl;

  size_t numToDraw = 0;
  
  for (;;) {
    cout << "Please enter a number in the range of [0,3]" 
       << " representing the number\nof cards you would like to replace: ";
    if (cin >> numToDraw && numToDraw >= 0 && numToDraw <=3)
      break; // valid input
    else {
      // Invalid input detected
      cout << "Invalid input!" << endl;
      cin.clear(); // Flush buffer
      cin.ignore(INT_MAX, '\n');
    }
  }
  cout << endl;
  
  const size_t index = numToDraw;
  int card_choices[index];
  
  
  for(size_t i = 0; i < index; ++i){
    for (;;) {
      cout <<"Please enter a number in the range of [0,4]" 
       << " representing the index \nof the card you would like to replace: ";
      if (cin >> card_choices[i] && card_choices[i] >= 0 && card_choices[i] <=4)
      break; // valid input
    else {
      // Invalid input detected
      cout << "Invalid input!" << endl;
      cin.clear(); // Flush buffer
      cin.ignore(INT_MAX, '\n');
    }
    }
    Card temp = d.deal_card(); 
    h2.replace(temp, h2.get_hand().at(card_choices[i]));
    cout << endl;
  }
  if(numToDraw)
    cout << "Your new hand is: " << endl << h2 << endl;
  
  /*
    Simulate n games in each confguration 
    and act according to the one that yeilded 
    the largest probability of success
  */
  MonteCarlo mc(d, h1, numRuns);
  mc.simulate(verbose);
  const int* optimalConfiguation = mc.getOptimalConfiguration();
  for(size_t i = 0; i < 5; ++i){
   if(optimalConfiguation[i]){
     Card temp = d.deal_card();
     h1.replace(temp, h1.get_hand().at(i));
   }
  }
  if(verbose == 2)
    cout << endl << "Dealer's new hand: " << endl << h1 << endl;
  
  cout << (h1 > h2 ? "The Dealer's" : "Your") << " hand is better!" << endl;
  
  return 0;
}
