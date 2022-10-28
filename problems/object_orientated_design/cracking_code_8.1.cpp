/* design data structures for a generic deck of cards.
explain how subclass datastructures to implement blackjack.
*/

// handle ambiguity
/*
Is this for professional players or hobbysists? Who? Kids or adults? Gamblers or board? Elderly?
What kind of cards? Bavarian or wester? Chinese? Flexible? For poker, texas hold emm or 5 card draw? Or both?
Where will they play? Casino? Online? Security considerations may differ...
When? not important.
How? With cards or online?
Why? For fun or for money?

*/

// core objects
/*

Suit, enum of 4 options spade heart, diamond, clover

Card, takes a value and suit on init.
toggles for available or not, as some cards arent used in some games
get value function

Deck, contains vector of cards

Hand, 

*/


// relationships
/*
deck contains cards

so does hand



*/

// investigate actions
/*
hand can add a card, or get score of all cards in hand, or discard card

dec, can shuffle cards, can getHand of cards, can deal one card, can get number of remaining cards

card, can get value of card, determine if it is avaliable or not

*/
#include <limits.h>
#include <vector>

enum Suit
{
	Club,
	Diamond,
	Heart,
	Spade
};

class Card
{
	public:
	  Card(int c, Suit s) : faceValue(c), suit(s)
		{
		
		}
		
		virtual int value();
		
		Suit getSuit() { return suit; }
		
		bool isAvailable() { return available; }
		void markUnavailable() { available = false; }
    void markAvailable() { available = true; }
		
	private:
	  bool available = true;
	
	protected:
	  int faceValue;
		Suit suit;
};

class Deck
{
	public:
		
		void setDeckOfCards(std::vector<Card> deckOfCards);
		void shuffle();
		int remainingCards()
		{
			return cards.size() - dealtIndex;
		}
	
	  std::vector<Card> dealHand(int number);
		
		Card dealCard();
		
	private:
	  std::vector<Card> cards;
		int dealtIndex;
};

class Hand
{
	protected:
	  std::vector<Card> cards;
	
	public:
	  int score()
		{
			int score = 0;
			for (Card& card : cards)
			{
				score += card.value();
			}
			return score;
		}
		
		void addCard(Card card)
		{
			cards.push_back(card);
		}
	
};

class BlackJackHand : public Hand
{
	public:
	  int score()
		{
			std::vector<int> scores = possibleScores();
			int maxUnder = INT_MIN;
			int minOver = INT_MAX;
			
			for (int score : scores)
			{
			  if (score > 21 && score < minOver)
				{
					minOver = score;
				}
				else if (score <= 21 && score > maxUnder)
				{
				  maxUnder = score;
				}
			}
			
			return maxUnder == INT_MIN ? minOver: maxUnder;
		}
		
		bool busted() {return score() > 21; }
		bool is21() { return score() == 21; }
		bool isBlackJack();
		
	private:
	  // return vector of possible scores evaluating
		// each ace as 1 and 11
	  std::vector<int> possibleScores();
};

class BlackJackCard : public Card
{
	public:
	  BlackJackCard(int c, Suit s) : Card(c, s) {}
		int value()
		{
			if (isAce()) return 1;
			else if (faceValue >= 11 && faceValue <= 13) return 10;
			else return faceValue;
		}
		
		int minValue()
		{
			if (isAce()) return 1;
			else return value();
		}
		
		int maxValue()
		{
		  if (isAce()) return 11;
			else return value();
		}
		
		bool isAce()
		{
			return faceValue == 1;
		}
	
		bool isFaceCard()
		{
			return faceValue >= 11 && faceValue <= 13;
		}
	
};


int main()
{
	Deck my_deck;
}