#include <iostream>
#include "Card.hpp"
#include <string>

using namespace std;

const string Card::suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
const string Card::faces[13] = {"2","3","4","5", "6", "7", "8", "9",
				"10","Jack", "Queen","King","Ace"};

Card::Card(int suit, int face)throw(const char*){
  if(suit > 3 || suit < 0 )
    throw "\033[1;31m SUIT OUT OF RANGE \033[0m\n";
  else
    this->suit = suit;

  if(face > 12 || face < 0 )
    throw "\033[1;31m FACE OUT OF RANGE \033[0m\n";
  else
    this->face = face;

  this->card = 13*suit + face;
}

Card::Card(int card) throw(const char*){
  if(card > 51 || card < 0)
    throw "\033[1;31m CARD OUT OF RANGE \033[0m\n";
  this->card = card;
  this->suit = card/13;
  this->face = card % 13;
}
Card::Card(const Card& card){
  this->suit = card.suit;
  this->face = card.face;
  this->card = card.card;
}

Card& Card::operator=(const Card& rhs){
  if(this != &rhs){
    this->suit = rhs.suit;
    this->face = rhs.face;
    this->card = rhs.card;
  }
  return *this;
}

bool Card::operator==(const Card& rhs){
  return
    this->suit == rhs.suit &&
    this->face == rhs.face
    && this->card == rhs.card;
}
ostream& operator<<(ostream& os, const Card& card){
  os << card.to_string();
  return os;
}

const string Card::to_string(void) const{
  return faces[this->face] + " of " + suits[this->suit];
}

