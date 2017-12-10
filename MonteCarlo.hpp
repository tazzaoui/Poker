#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include "Deck.hpp"
#include "Hand.hpp"
#include "Card.hpp"

class MonteCarlo{
private:
  size_t iterations;
  Deck original_deck;
  Hand original_hand;
  /*We can choose to draw 0,1,2,3 cards out of the 5 in our hand.
    The total numer of way of doing so is...
    5 choose 3 + 5 choose 2 + 5 choose 1 + 5 choose 0 = 26*/
  double expectedValue[26];
  int optimalConfiguation[5];
  const static int cases[26][5];
  void calculateOptimalConfiguration(void);
public:
  MonteCarlo(const Deck& d, const Hand& h, size_t itr=1000) :
    iterations(itr), original_deck(d), original_hand(h){
    for(size_t i = 0; i < 26; ++i) expectedValue[i] = 0.0;
  };
  void simulate(int verbose=false);
  const int* getOptimalConfiguration(void)const;
};

#endif
