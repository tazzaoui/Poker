#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "Deck.hpp"

using namespace std;

Deck::Deck(){
  this->cards = vector<Card>();
  this->current_card = 0;

  for(size_t i = 0; i < 52; ++i)
    this->cards.push_back(Card(i));
}

Deck::Deck(const Deck&d){
  this->current_card = d.current_card;
  this->cards = d.cards;
}

void Deck::shuffle(){
  for(int i = 0; i < 52; ++i){
    size_t index = i + (rand() % (52 - i));
    Card temp = this->cards[i];
    this->cards[i] = this->cards[index];
    this->cards[index] = temp;
  }
}

const Card& Deck::deal_card(){
  if(this->more_cards())
    return this->cards[this->current_card++];
  else{
    cout << "ALL CARDS DEALT" << endl;
    return this->cards[0];
  }
}

bool Deck::more_cards(void) const{
  return this->current_card < 52;
}

const vector<Card>& Deck::get_cards()const{
  return this->cards;
}

ostream& operator<<(ostream& os, const Deck& d){
  for(size_t i = 0; i < d.cards.size(); ++i)
    os << d.cards.at(i).get_card() << " " << d.cards.at(i) << endl;
  return os;
}

Deck& Deck::operator=(const Deck& d){
  if(this != &d){
    this->current_card = d.current_card;
    this->cards = d.cards;
  }
  return *this;
}

