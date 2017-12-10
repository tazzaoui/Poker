#include <algorithm>
#include <vector>
#include <math.h>
#include "Hand.hpp"
#define HAND 5

using namespace std;

void Hand::sortByFace(){
  sort(this->hand.begin(), this->hand.end(),
       [](const Card&a,const Card&b) -> bool{
	 return a.get_face() > b.get_face();});
}

void Hand::replace(Card& new_card, Card& old_card){
  for(size_t i = 0; i < HAND; ++i)
    if(this->hand[i] == old_card){
      this->hand[i] = new_card;
      return;
    }
}

Hand::Hand(Card* cards){
  for(size_t i = 0; i < HAND; ++i)
    this->hand.push_back(cards[i]);
  this->sortByFace();
  this->hand_type = this->calculateType();
  this->val = this->calculateValue();
}

Hand::Hand(Card& a, Card& b, Card& c, Card& d){
  this->hand = {a,b,c,d};
  this->sortByFace();
}

bool Hand::contains(const Card& c){
  for(size_t i = 0; i < HAND; ++i)
    if(this->hand[i] == c)
      return true;
  return false;
}

vector<Card> Hand::get_hand(void)const{
  return this->hand;
}

/*
{none,pair,2pairs,3ofakind,4ofakind,flush,straight} ->{0,1,2,3,4,5,6}
*/

int Hand::type()const{
  return this->hand_type;
}

int Hand::value()const{
  return this->val;
}

bool Hand::hasPair()const{
  for(size_t i = 0; i < HAND - 1; ++i)
    if(this->hand[i].get_face() == this->hand[i + 1].get_face())
      return true;
  return false;
}

int Hand::getFirstPair()const{
  for(size_t i = 0; i < HAND - 1; ++i)
    if(this->hand[i].get_face() == this->hand[i + 1].get_face())
      return this->hand[i].get_face();
  return false;
}

bool Hand::hasTwoPairs()const{
  bool found = false;
  for(size_t i = 0; i < HAND - 1; ++i){
    if(this->hand[i].get_face() == this->hand[i + 1].get_face()){
      if(found)
	return true;
      else{
	found = true;
	i++;
      }
    }
  }
  return 0;
}

int Hand::getSecondPair(void)const{
  bool found = false;
  for(size_t i = 0; i < HAND - 1; ++i){
    if(this->hand[i].get_face() == this->hand[i + 1].get_face()){
      if(found)
	this->hand[i].get_face();
      else{
	found = true;
	i++;
      }
    }
  }
  return 0;
}

bool Hand::hasThreeOfAKind()const{
  for(size_t i = 0; i < HAND - 2; ++i){
    if(this->hand[i].get_face() == this->hand[i + 1].get_face()){
      if(this->hand[i + 1].get_face() == this->hand[i + 2].get_face())
	return true;
    }
  }
  return false;
}

int Hand::getThreeOfAKind(void)const{
  for(size_t i = 0; i < HAND - 2; ++i){
    if(this->hand[i].get_face() == this->hand[i + 1].get_face()){
      if(this->hand[i + 1].get_face() == this->hand[i + 2].get_face())
	return this->hand[i].get_face();
    }
  }
  return 0;
}

bool Hand::hasFourOfAKind()const{
for(size_t i = 0; i < HAND - 3; ++i){
    if(this->hand[i].get_face() == this->hand[i + 1].get_face()){
      if(this->hand[i + 1].get_face() == this->hand[i + 2].get_face())
	if(this->hand[i + 2].get_face() == this->hand[i + 3].get_face())
	  return true;
    }
  }
  return false;
}

int Hand::getFourOfAKind()const{
  for(size_t i = 0; i < HAND - 3; ++i){
    if(this->hand[i].get_face() == this->hand[i + 1].get_face()){
      if(this->hand[i + 1].get_face() == this->hand[i + 2].get_face())
	if(this->hand[i + 2].get_face() == this->hand[i + 3].get_face())
	  return this->hand[i].get_face();
    }
  }
  return 0;
}

bool Hand::hasFlush()const{
  for(size_t i = HAND-1; i > 0; --i){
  if(this->hand[i].get_suit() != this->hand[i - 1].get_suit())
    return false;
  }
  return true;
}

int Hand::getFlush(void)const{
  for(size_t i = HAND-1; i > 0; --i){
  if(this->hand[i].get_suit() != this->hand[i - 1].get_suit())
    return 0;
  }
  return this->hand[0].get_suit();
}

bool Hand::hasStraight()const{
  for(size_t i = HAND-1; i > 0; --i)
    if(this->hand[i].get_face() != this->hand[i - 1].get_face() - 1)
      return false;
  return true;    
}

int Hand::getStraight(void)const{
for(size_t i = HAND-1; i > 0; --i)
  if(this->hand[i].get_face() != this->hand[i - 1].get_face() - 1)
    return 0;
  return this->hand[0].get_face();    
}

ostream& operator<<(ostream& os, const Hand& h){
  for(size_t i = 0; i < h.hand.size(); ++i)
    os << h.hand.at(i) << endl;
  return os;
}

bool Hand::operator>(const Hand& rhs){
  return this->val > rhs.val;
}

bool Hand::operator<(const Hand& rhs){
  return this->val < rhs.val;
}

int Hand::calculateValue()const{
  int value = 0;
  value += this->hand_type * pow(16,HAND);

  if(this->hand_type == 6){
    int straight = this->getStraight();
    value += straight * pow(16, HAND - 1);
  }else if(this->hand_type == 5){
    int flush = this->getFlush();
    value += flush * pow(16, HAND - 1);
  }else if(this->hand_type == 4){
    int fourKind = this->getFourOfAKind();
    value += fourKind * pow(16, HAND - 1);
    for(size_t i = 0; i < HAND; ++i)
      if(this->hand[i].get_face() != fourKind){
	value += this->hand[i].get_face() * pow(16, HAND - 2);
	break;
      }
  }else if(this->hand_type == 3){
    int threeKind = this->getThreeOfAKind();
    value += threeKind * pow(16, HAND - 1);
    int firstKind = -1;
    for(size_t i = 0; i < HAND; ++i)
      if(this->hand[i].get_face() != threeKind &&
	 this->hand[i].get_face() != firstKind){
	if(firstKind == -1){
	  firstKind = this->hand[i].get_face();
	  value += this->hand[i].get_face() * pow(16, HAND - 2);
	}else{
	  value += this->hand[i].get_face() * pow(16, HAND - 3);
	  break;
	}
      }
  }else if(this->hand_type == 2){
    int pairOne = this->getFirstPair();
    int pairTwo = this->getSecondPair();
    value += (pairOne > pairTwo ? pairOne : pairTwo) * pow(16, HAND - 1);
    value += (pairOne < pairTwo ? pairOne : pairTwo) * pow(16, HAND - 2);
    for(size_t i = 0; i < HAND; ++i)
      if(this->hand[i].get_face() != pairOne &&
	 this->hand[i].get_face() != pairTwo){
	value +=  this->hand[i].get_face() * pow(16, HAND - 3);
	break;
      }
  }else if(this->hand_type == 1){
    int pairOne = this->getFirstPair();
    value += pairOne  * pow(16, HAND - 1);
    size_t j = 0;
    for(size_t i = 0; i < HAND; ++i)
      if(this->hand[i].get_face() != pairOne)
      value += this->hand[i].get_face() * pow(16, HAND - j++ - 2);
  }else{
    for(size_t i = 0; i < HAND; ++i) 
      value += this->hand[i].get_face() * pow(16, HAND - i - 1);
  }
  return value;
}

int Hand::calculateType() const{
  if(this->hasStraight()) return 6;
  if(this->hasFlush()) return 5;
  if(this->hasFourOfAKind()) return 4;
  if(this->hasThreeOfAKind()) return 3;
  if(this->hasTwoPairs()) return 2;
  if(this->hasPair()) return 1;
  return 0;
}
