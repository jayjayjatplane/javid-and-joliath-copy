#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <set>
#include "../include/Card.h"
#include "../include/Player.h"

using namespace std;

// create a deck
vector<Card> createDeck()
{
    vector<Card> deck;
    for (int digit = 3; digit <= 15; digit++)
    {
        for (int suit = 0; suit < 4; suit++)
        {
            deck.push_back({digit, suit});
        }
    }
    return deck;
}

// deal the deck (13 to 4 players)
vector<vector<Card>> deal(vector<Card> &deck)
{
    vector<vector<Card>> hands(4);
    for (int i = 0; i < 52; i++)
    {
        hands[i % 4].push_back(deck[i]);
    }
    return hands;
}

// shuffle deck, uses Mersenne Twister (mt19937) and time to create random
void shuffleDeck(vector<Card> &deck)
{
    unsigned seed = static_cast<unsigned>(time(0));
    mt19937 g(seed);
    shuffle(deck.begin(), deck.end(), g);
}

int main()
{
    // set up
    vector<Card> deck = createDeck();
    shuffleDeck(deck);
    vector<vector<Card>> hands = deal(deck);
    Player player1(hands[0]);
    player1.sortHand();
    player1.printHand();

    ComboSummary allCombos = player1.summary();
    player1.printSummary(allCombos);

    // greedy order
    vector<Card> greedyOrder = player1.greedyPlay();
    player1.printGreedyPlay(greedyOrder);

    return 0;
}