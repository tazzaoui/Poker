#ifndef DECK_HPP
#define DECK_HPP

#include <iostream>
#include "Card.hpp"
#include <vector>

using namespace std;

class Deck{
private:
  vector<Card> cards;
  size_t current_card;
public:
  Deck(void);
  void shuffle(void);
  const Card& deal_card(void);
  bool more_cards(void) const;
  friend ostream& operator<<(ostream&, const Deck&);
  const vector<Card>& get_cards()const;
};

#endif
