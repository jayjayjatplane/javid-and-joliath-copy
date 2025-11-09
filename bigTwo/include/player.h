#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>

#include "Card.h"

struct ComboSummary
{
    std::vector<std::vector<Card>> singles;
    std::vector<std::vector<Card>> pairs;
    std::vector<std::vector<Card>> triples;
    std::vector<std::vector<Card>> straights;
    std::vector<std::vector<Card>> flushes;
    std::vector<std::vector<Card>> fullHouses;
    std::vector<std::vector<Card>> fourOfAKinds;
};

class Player
{
private:
    std::vector<Card> hand;

    int numPairs;
    int numTriples;
    int numFlushes;
    int numStraights;

public:
    Player();
    Player(std::vector<Card> &initialHand);

    // --- Core functionality ---
    void sortHand();
    void analyseHand(); // fill in rank/suit counts and find combos
    void clearHand();

    // finds
    std::vector<std::vector<Card>> findSingles();
    std::vector<std::vector<Card>> findPairs();
    std::vector<std::vector<Card>> findTriples();
    std::vector<std::vector<Card>> findFourOfAKinds();
    std::vector<std::vector<Card>> findStraights();
    std::vector<std::vector<Card>> findFlushes();
    std::vector<std::vector<Card>> findFullHouses();

    // counts
    int countPairs();
    int countTriples();
    int countFlushes();
    int countStraights();

    // output/display
    void printHand();
    ComboSummary summary();
    void printSummary(ComboSummary &summaryData);

    // greedy
    std::vector<Card> greedyPlay();
    void printGreedyPlay(std::vector<Card> &greedyOrder);

    // dynamic programming
    std::vector<Card> dpCoverFive();     // chooses five card sets to cover the most cards then appends leftovers
    std::vector<Card> dpReduceSingle();  // chooses pairs and trips to cover the most cards then appends leftovers
    std::vector<Card> dpMaxPairs();      // chooses the maximum number of pairs then appends leftovers
    std::vector<Card> dpKeepQuads();     // chooses disjoint quads to cover the most cards then appends leftovers
    std::vector<Card> dpStraightsOnly(); // chooses disjoint five card straights to cover the most cards then appends leftovers

    // access
    const std::vector<Card> &getHand();
    int getNumPairs();
    int getNumTriples();
    int getNumFlushes();
    int getNumStraights();
};

#endif
