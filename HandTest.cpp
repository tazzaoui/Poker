#include <iostream>
#include "Testing.hpp"
#include "Hand.hpp"
#include "Card.hpp"
#include <vector>

using namespace std;

int main(){

  /* Testing for no type*/
  vector<Card> cards = {Card(1,1), Card(3,5), Card(2,3), Card(1,2), Card(2,8)};
  Hand h = Hand(cards.data());
  test(h.type() == 0, 0);

  /* Testing for a pair*/
  vector<Card> cards2 = {Card(1,1), Card(3,1), Card(2,3), Card(1,4), Card(2,5)};
  Hand h2 = Hand(cards2.data());
  test(h2.type() == 1, 1);

  /* Testing for a 2pair*/
  vector<Card> cards3 = {Card(1,1), Card(3,1), Card(2,2), Card(1,2), Card(2,5)};
  Hand h3 = Hand(cards3.data());
  test(h3.type() == 2, 2);
  
  /*Testing for 3 of a kind*/
  vector<Card> cards4 = {Card(1,1), Card(3,1), Card(2,1), Card(1,4), Card(2,5)};
  Hand h4 = Hand(cards4.data());
  test(h4.type() == 3, 3);

  /*Testing for 4 of a kind*/
  vector<Card> cards5 = {Card(1,1), Card(3,1), Card(2,1), Card(1,1), Card(2,2)};
  Hand h5 = Hand(cards5.data());
  test(h5.type() == 4, 4);

  /*Testing for a flush*/
  vector<Card> cards6 = {Card(1,1), Card(1,4), Card(1,8), Card(1,3), Card(1,10)};
  Hand h6 = Hand(cards6.data());
  test(h6.type() == 5, 5);

  /*Testing for a flush*/
  vector<Card> cards7 = {Card(1,1), Card(3,2), Card(2,3), Card(1,4), Card(2,5)};
  Hand h7 = Hand(cards7.data());
  test(h7.type() == 6, 6);

  vector<Card> cards8 = {Card(2, 12), Card(1,10), Card(3,2), Card(2,11), Card(0,6)};
  Hand h8 = Hand(cards8.data());
  test(h8.value() == 834146, 7);

  vector<Card> cards9 = {Card(0, 5), Card(0,4), Card(0,3), Card(0,2), Card(1,1)};
  Hand h9 = Hand(cards9.data());
  cout << h9.type() << endl << h9.value() << endl;
  test(h9.value() == 6619136, 8);

  vector<Card> cards10 = {Card(1, 2), Card(1,9), Card(0,2), Card(1,12), Card(1,1)};
  Hand h10 = Hand(cards10.data());
  cout << h10.type() <<endl << h10.value() << endl;
  test(h10.value() == 1231120, 9);
  
  
  return 0;
}
