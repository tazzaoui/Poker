#ifndef HAND_H
#define HAND_H

#include <vector>
#include "Card.hpp"

using namespace std;

class Hand{
private:
  vector<Card> hand;
  int hand_type;
  int val;
  void sortByFace(void);
  int calculateValue(void) const;
  int calculateType(void) const;
public:
  Hand(Card*);
  Hand(Card&, Card&, Card&, Card&);
  void Replace(Card& new_card, Card& old_card);
  int type(void)const;
  int value(void)const;
  bool hasPair(void)const;
  int getFirstPair(void)const;
  bool hasTwoPairs(void)const;
  int getSecondPair(void)const;
  bool hasThreeOfAKind(void)const;
  int getThreeOfAKind(void)const;
  bool hasFourOfAKind(void)const;
  int getFourOfAKind(void)const;
  bool hasFlush(void)const;
  int getFlush(void)const;
  bool hasStraight(void)const;
  int getStraight(void)const;
  friend ostream& operator<<(ostream&, const Hand&);
  bool operator<(const Hand&);
  bool operator>(const Hand&);
};








#endif
