CC=g++
CFLAGS=--std=c++11 -Wall -pedantic
OBJ=card cardtest test_card deck decktest test_deck hand handtest test_hand driver poker

poker: driver deck card hand
	$(CC) $(CFLAGS) driver deck card hand -o poker

test_card: card cardtest
	$(CC) $CFLAGS card cardtest -o test_card

test_deck: card deck decktest
	$(CC) $(CFLAGS) card deck decktest -o test_deck

test_hand: card hand handtest
	$(CC) $(CFLAGS) card hand handtest -o test_hand

cardtest: CardTest.cpp
	$(CC) $(CFLAGS) -c CardTest.cpp -o cardtest

decktest: DeckTest.cpp
	$(CC) $(CFLAGS) -c DeckTest.cpp -o decktest

handtest: HandTest.cpp
	$(CC) $(CFLAGS) -c HandTest.cpp -o handtest

card: Card.cpp Card.hpp
	$(CC) $(CFLAGS) -c Card.cpp -o card 

deck: Deck.cpp Deck.hpp
	$(CC) $(CFLAGS) -c Deck.cpp -o deck

hand: Hand.cpp Hand.hpp
	$(CC) $(CFLAGS) -c Hand.cpp -o hand

driver: Poker.cpp
	$(CC) $(CFLAGS) -c Poker.cpp -o driver

clean:
	rm $(OBJ)
