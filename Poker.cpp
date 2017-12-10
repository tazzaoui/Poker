#include <iostream>
#include "Deck.hpp"
#include "Card.hpp"
#include "Hand.hpp"

int main(){
  Deck d;
  d.shuffle();

  vector<Card> cards;

  for(size_t i = 0; i < 5; ++i )
    cards.push_back(d.deal_card());

  Hand h1 = Hand(cards.data());

  cards.clear();

  for(size_t i = 0; i < 5; ++i )
    cards.push_back(d.deal_card());

  Hand h2 = Hand(cards.data());

  cout << "First hand: " << endl << h1 << "Type: " << h1.type() << "Value: "
       << endl << h1.value() << endl << endl
       << "Second hand: " << endl << h2 << "Type: " << h2.type()
       << endl << h2.value() << endl << endl;
  cout << (h1 > h2 ? "First one" : "Second one") << " is better" << endl << endl;

  return 0;
}
