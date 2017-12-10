#include <time.h>
#include <stdlib.h>
#include "MonteCarlo.hpp"
const int MonteCarlo::cases[26][5] = {
  /*Hold*/
  {0,0,0,0,0},
  /*Draw one card*/
  {1,0,0,0,0}, {0,1,0,0,0},{0,0,1,0,0},{0,0,0,1,0},{0,0,0,0,1},
  /*Draw Two cards*/
  {1,1,0,0,0},{1,0,1,0,0},{1,0,0,1,0},{1,0,0,0,1},{0,1,1,0,0},
  {0,1,0,1,0},{0,1,0,0,1},{0,0,1,1,0},{0,0,1,0,1},{0,0,0,1,1},
  /*Draw three cards*/
  {1,1,1,0,0},{1,1,0,1,0},{1,1,0,0,1},{1,0,0,1,1},{1,0,1,0,1},
  {1,0,1,1,0},{0,1,1,1,0},{0,1,0,1,1},{0,1,1,0,1},{0,0,1,1,1}
};


void MonteCarlo::simulate(int verbose){
  srand(time(0));
  if(verbose){
    cout << "==================================================================="
	 << endl;
    cout << "Running Monte Carlo simulation to approximate optimal decision..."
	 << endl;
  }
  
  if(verbose == 2){
    cout << "=========================================" << endl;
    cout << "Previous Hand: " << this->original_hand << endl;
    cout << "=========================================" << endl;
  }
  
  /* For each of the 26 combinations... */
  const vector<Card> original_cards = this->original_hand.get_hand();
  for(size_t i = 0; i < 26; ++i){
    for(size_t k = 0; k < this->iterations; ++k){
      Deck new_deck;
      new_deck.shuffle();
      vector<Card> new_cards;
      /* Set up version of hand with corresponding exchange*/
      for(size_t j = 0; j < 5; ++j){
	if(this->cases[i][j]){
	  Card c = new_deck.deal_card();
	  while(this->original_hand.contains(c))
	    c = new_deck.deal_card();
	  new_cards.push_back(c);
	}else{
	  new_cards.push_back(original_cards.at(j));
	}
      }
      Hand eHand = Hand(new_cards.data());
      new_cards.clear();
      
      /* Deal out hand to the simulated player..*/
      for(size_t j = 0; j < 5; ++j){
	Card c = new_deck.deal_card();
	while(this->original_hand.contains(c))
	  c = new_deck.deal_card();
	new_cards.push_back(c);
      }  
      
      Hand playerHand = Hand(new_cards.data());
      new_cards.clear();
      
      if(verbose == 2){
	cout << "=========================================" << endl;
	cout << "New Hand: " << endl << eHand << endl << "Value: "
	     << eHand.value()<< endl;
	cout << "=========================================" << endl;
      
	cout << "=========================================" << endl;
	cout << "Player Hand: " << endl << playerHand << endl << "Value: "
	     << playerHand.value()<< endl;
	cout << "=========================================" << endl;
      }

      expectedValue[i] += (eHand > playerHand);	
    }
    
    expectedValue[i] /= this->iterations;

    if(verbose){
      cout << "Probability of success after switching to configuration "
	   << i << " :" << expectedValue[i] << endl;
    }
  }
  if(verbose)
    cout << "==================================================================="
	 << endl << endl;
  this->calculateOptimalConfiguration();
}

void MonteCarlo::calculateOptimalConfiguration(){
  double currentMax = 0;
  size_t maxIndex = 0;
  for(size_t i = 0; i < 26; ++i)
    if(this->expectedValue[i] > currentMax){
      currentMax = this->expectedValue[i];
      maxIndex = i;
    }
  for(size_t i = 0; i < 5; ++i)
    this->optimalConfiguation[i] = this->cases[maxIndex][i];
}

const int* MonteCarlo::getOptimalConfiguration()const{
  return this->optimalConfiguation;
}
