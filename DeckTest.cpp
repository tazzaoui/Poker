#include <iostream>
#include <vector>
#include <algorithm>
#include "Deck.hpp"
#include "Testing.hpp"

using namespace std;

int main(){

  /*Verify ordering of cards post-shuffle*/
  Deck a;
  Deck b; b.suffle();

  vector<Card> pure = a.get_cards();
  vector<Card> shuffled = b.get_cards();

  /*Verify deck contains 52 elements both before and after*/
  test(pure.size() == 52, 0);
  test(shuffled.size() == 52, 1);

 
  /* Verify that all cards are in the deck by default*/
  bool missing_cards = false;
  for(size_t i = 0; i < pure.size(); ++i)
    if(pure.at(i).get_card() != i){
      missing_cards = true; break;
    }
  test(!missing_cards, 2);
  
 /* Verify that no cards are lost after shuffling */
  missing_cards = false;
  for(size_t i = 0; i < pure.size(); ++i){
    if(std::find(pure.begin(), pure.end(), shuffled.at(i))
       == pure.end()){
      cout << shuffled.at(i);
      missing_cards = true; break;
    }
  }
  test(!missing_cards, 3);

  /* Verify finite dealing of cards*/
  size_t num_iterations = 0;
  while(a.more_cards()){
    ++num_iterations;
    auto dealt = a.deal_card();
  }
  test(num_iterations == 52, 4);
  return 0;
}

