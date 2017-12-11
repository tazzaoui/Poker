# Poker
Using Monte Carlo methods to approximate the likelihood of success

# 5 Card Draw

## How it works

### Card Representation:

There are 52 unique cards in your average deck, so we’ll assign each card a unique number from 0 to 51. We can save ourselves some space and computation down the line by assigning card values as functions of their suit and face. To do so, note that there are four suits {Clubs = 0, Diamonds = 1, Hearts = 2, Spades = 3} and thirteen faces: {2 = 0, 3 = 1, … , Jack = 9, Queen = 10, King = 11, Ace = 12}. We can encode this information into the value of our card using the following equation: card = 13(suit) + face. It’s trivial to see that we end up with 52 unique cards with the set of cards sorted in order from least valuable ( 0 = 2 of Clubs) to most valuable (51 = Ace of Spades). Finally, note that we can go backwards and extract a card’s face and suit using the following equations: suit=card/13 and face=card%13.

### Underlying Data Structures and Properties:

We define a card as a single integer (described above) wrapped by a class which specifies certain functions that operate on cards. A Deck is simply a vector of cards. Two decks are equal if and only if they contain the same cards in the same order. A hand is implemented as a vector of five cards, such that it has strictly no intersections with the deck nor with any other hands in play.

### Value of a hand:

To determine the value of hand, we must first differentiate between the different types of hands that we’re interested in. We limit our set of hand types to the following: {pair = 0, 2 pairs = 1, 3 of a kind = 2, 4 of a kind = 3, flush = 4, straight = 5}. Since the largest face value is 12 (Ace), we can represent the value of a hand as a tridecimal number (base-13) where the most significant digit represents the type of the hand and the remaining digits represent the faces of each card in the hand. For example, if we have the hand: {(suit, face) : (2,2), (1,7), (0,2), (1,5), (3,10)} We know we have a pair of diamonds (type 1) , so the most significant digit of the card value is 1. Followed by the value of the pair then by suits in the decreasing order, which yields the tridecimal number 113200.  The only exception to this rule is in the case of a flush, where we encode only the hand type and the suit. This convention may seem cumbersome, but note that it allows us to assert that hand1 > hand2 iff hand1.value > hand2.value. This step is important as we can now reduce an entire hand to one single value and therefore comparisons are trivial.

### Drawing cards:

Now that we have all the tools we need to manipulate our cards, we must choose  (based on the quality of the hand) whether we wish to draw zero, one, two or three more cards to replace the corresponding number of unneeded cards in the original hand. This can be done in various ways, for example we can consider what cards have been dealt and determine the probability of getting a better hand. However, recall that the hands we’re dealing with are only of size 5. Since we’ve limited our choices to  zero, one, two or three additional cards, there are only 26 different possible configurations we could make. i.e. 26 = (5 choose 0) + (5 choose 1) + (5 choose 2) + (5 choose 3). We can take advantage of this relatively small number of combinations by running a Monte Carlo simulation to approximate the probability of winning after switching to a given configuration of cards. The algorithm is roughly as follows: 
```
                              for i = 1 → 26:
                                  for j = 1 → n:
                                  Deck.shuffle()
                                  Deck.deal(player1)
                                  Deck.deal(player2)
                                  player1.switchToConfiguration(i)
                                  if(player1 > player2)
                                    wins[i]++
                                wins[i] /= n
                              return wins.configuration_of_max_value()
```
As n gets larger, the simulation returns a better approximation of the probability of  the success of a certain configuration. The default value of n is 1000 runs per configuration which takes about 1 second to complete my machine. For greater accuracy, one may choose to increase the number of runs to 10000 (takes about 3 seconds on my machine). 

Testing:

I tested my implementation both by playing myself and by having the bots play each other and record their results. To do so, I wrote a simpler bot that chooses the number and type of cards to draw at random (probably not the best approximation of a human player). I had the “smart” bot play 10000 games against the simpler bot. See results.png for a graph of the results. 

