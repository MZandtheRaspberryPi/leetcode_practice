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
Number, Suit, Face Card, Card, CardStack, Deck, Game, Hand, Table, Player

Turn. 
*/


// relationships
/*
A card contains one suit and a number, and is unique in that combination.

A face card is a type of card.

a deck has an array of cards.

A hand is an array of cards.

a table can have multiple hands and or multiple CardStacks.

A game uses one or many decks. A face card may be used differently than normal cards. It may have one or many players.

*/

// investigate actions
/*
A game starts and registers player(s). These Players are given Hands and the table is optionally given CardStacks if called for by the rules of the game.

The next player is selected, and a turn proceeds. This may start with the player getting a card, taking actions, and discarding a card at which point it may go to a table stack.

This proceeds until the game ends at which point all cards are returned to the deck and the table is cleared.

We can use the factory method to make cards, as we will make many cards of different types.

*/
