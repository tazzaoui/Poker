#include <iostream>
#include <stdlib.h>
#include "Deck.hpp"
#include "Card.hpp"
#include "Hand.hpp"
#include "MonteCarlo.hpp"

int main(int argc, char* argv[]){
  /*
    Set Verbosity
     0 = No debug info (default)
     1 = Show only results of Monte Carlo Simulation
     2 = Maximum verbosity (INCLUDING THE DEALER'S HAND)
  */
  const int verbose = (argc > 1 ? atoi(argv[1]) : 0);
  
  Deck d;
  d.shuffle();
  srand(time(0));
  
  /* Set up the dealer's hand */
  cout << "Dealing the dealer's hand..." << endl;
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
  cout << "Dealing your hand..." << endl;
  for(size_t i = 0; i < 5; ++i )
    cards.push_back(d.deal_card());
  Hand h2 = Hand(cards.data());

  cout << "You were dealt: " << endl << h2;
  if(verbose)
    cout << "Value: " << h2.value() << endl;

  
  /*
    Simulate n games in each confguration 
    and act according to the one that yeilded 
    the largest probability of success
  */
  MonteCarlo mc(d, h1, 10000);
  mc.simulate(verbose);
  const int* optimalConfiguation = mc.getOptimalConfiguration();
  for(size_t i = 0; i < 5; ++i){
   if(optimalConfiguation[i]){
     Card temp = d.deal_card();
     h1.replace(temp, h1.get_hand().at(i));
   }
  }
  if(verbose == 2)
    cout << "Dealer's new hand: " << h1 << endl;
  
  cout << (h1 > h2 ? "The Dealer's" : "Your") << " hand is better!" << endl;
  
  return 0;
}
