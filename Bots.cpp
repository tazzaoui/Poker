#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Deck.hpp"
#include "Card.hpp"
#include "Hand.hpp"
#include "MonteCarlo.hpp"
#include <string>

using namespace std;

bool contains_val(int* arr, int val, size_t size);

int main(int argc, char* argv[]){
  /********************************************************
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

  *********************************************************/
  /*
    Set Verbosity
     0 = No debug info (default)
     1 = Show only results of Monte Carlo Simulation
     2 = Maximum verbosity (INCLUDING THE DEALER'S HAND)
  */

  const int verbose = (argc > 1 ? atoi(argv[1]) : 0);
  srand(time(0));
  for(size_t z = 0; z < 1000; ++z){
    Deck d;
    d.shuffle();
    
    /* Set up the dealer's hand */
    if(verbose == 2)
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
    if(verbose == 2)
      cout << "Dealing the player's hand..." << endl << endl;
    for(size_t i = 0; i < 5; ++i )
      cards.push_back(d.deal_card());
    Hand h2 = Hand(cards.data());

    if(verbose == 2){
      cout << "The player was dealt: " << endl << h2;
      cout << "Value: " << h2.value() << endl << endl;
    }
  
    size_t numToDraw = 0;

    // Choose to draw a random number of cards...
    numToDraw = rand() % 3;

    const size_t index = numToDraw;
    int card_choices[index];
  
    for(size_t i = 0; i < numToDraw; ++i){
      int rand_card_index = rand() % 5;
      while(contains_val(card_choices, rand_card_index, 5))
	rand_card_index = rand() % 5;
      card_choices[i] = rand_card_index;
      Card temp = d.deal_card(); 
      h2.replace(temp, h2.get_hand().at(rand_card_index));
      if(verbose == 2)
	cout << endl;
    }
  
    if(numToDraw && verbose == 2)
      cout << "Your new hand is: " << endl << h2 << endl;

    if(verbose == 2)
      cout << "The dealer is making the same choice..." << endl << endl;

    /*
      Simulate n games in each confguration 
      and act according to the one that yeilded 
      the largest probability of success
    */
    size_t swap_count = 0;
    MonteCarlo mc(d, h1, 1000);
    mc.simulate(verbose);
    const int* optimalConfiguation = mc.getOptimalConfiguration();
    for(size_t i = 0; i < 5; ++i){
      if(optimalConfiguation[i]){
	++swap_count;
	Card temp = d.deal_card();
	h1.replace(temp, h1.get_hand().at(i));
      }
    }

  
    if(verbose == 2){
      cout << endl << "Dealer's new hand: " << endl << h1 << endl << endl;
      cout << "The dealer decided to swap "<< swap_count << " cards." << endl << endl;
    }

    if(verbose == 2)
      cout << (h1 > h2 ? "The Dealer's" : "Your") << " hand is better!" << endl;
    else
      cout << (h1 > h2 ? 1 : 0) << endl;
  }      
  return 0;
}

bool contains_val(int* arr, int val, size_t size){
  for(size_t i = 0; i < size; ++i)
    if(arr[i] == val)
      return true;
  return false;
}
