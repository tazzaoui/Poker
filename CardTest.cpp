#include <iostream>
#include "Card.hpp"
#include "Testing.hpp"
#include <stdlib.h>
#include <time.h>

using namespace std;

#define TEST_SIZE 10

int main(){
  srand(time(0));

  /* TEST GETTERS */
  for(size_t i = 0; i <TEST_SIZE; ++i){
    int randSuit = rand() % 4;
    int randFace = rand() % 13;
    Card c = Card(randSuit, randFace);
    test(c.get_suit() == randSuit &&
	 c.get_face() == randFace, i);
  }

  /* Edge Cases... */
  bool failed = false;
  try {
    Card c = Card(-1,2);
  } catch (const char* x) {
    failed = true;
  }
  test(failed, TEST_SIZE);

 failed = false;
  try {
    Card c = Card(1,-2);
  } catch (const char* x) {
    failed = true;
  }
  test(failed, TEST_SIZE + 1);

  failed = false;
  try {
    Card c = Card(4,2);
  } catch (const char* x) {
    failed = true;
  }
  test(failed, TEST_SIZE + 2);

  failed = false;
  try {
    Card c = Card(3,20);
  } catch (const char* x) {
    failed = true;
  }
  test(failed, TEST_SIZE + 3);

  /*To string tests*/
  Card a = Card(0,3);
  test(a.to_string() == "5 of Clubs", TEST_SIZE + 4);

  Card b = Card(1,6);
  test(b.to_string() == "8 of Diamonds", TEST_SIZE + 5);

  Card c = Card(2,8);
  test(c.to_string() == "10 of Hearts", TEST_SIZE + 6);
  
  Card d = Card(3,11);
  test(d.to_string() == "Ace of Spades", TEST_SIZE + 7);
  
  return 0;
}
