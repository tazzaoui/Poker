#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>
using namespace std;

class Card{
private:
  const static string suits[4];
  const static string faces[13];
  
  /*************************SUIT****************************
    RANGE: [0-3]
    {0,1,2,3} --> {Clubs, Diamonds, Hearts, Spades}
    suit = card / 13
  *************************SUIT****************************/
  
  /*************************FACE****************************
    RANGE: [0-12]
    {0,1,...9,10,11,12} --> {2,3,...Jack,Queen,King,Ace}
    face = card % 13
   *************************FACE****************************/

  /*************************CARD****************************
    RANGE: [0-51]
    card = 13(suit) + face
  *************************CARD****************************/
  int card;
public:
  Card(int suit, int face)throw(const char*);
  Card(int card)throw(const char*);
  Card(const Card&);
  friend ostream& operator<<(ostream&, const Card&);
  Card& operator=(const Card&);
  bool operator==(const Card&);
  /*
  bool operator<(const Card&);
  bool operator<=(const Card&);
  bool operator>(const Card&);
  bool operator>=(const Card&);
  */
  const string to_string(void) const;
  int get_suit(void)const{return this->card/13;};
  int get_face(void)const{return this->card%13;};
  int get_card(void)const{return this->card;};
};
#endif
