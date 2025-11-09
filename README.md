# javid-and-joliath
PSSD Group Assignment:
Big 2 is a C++ tool that allow players to determine the best play from their hand in the card game Big 2 (also called Chor Dai Dee or Deuces) 

This project focusses on decision support rather than simulating a full game. So you will specify the kind of move you want to make for example, single, pair, straight, full house, etc. and the program uses a greedy algorithm to select the best possible card combination for that play. 

The goal is to stimulate how a "greedy" player might select cards, always selecting the strongest possible option for the current choice, and to investigate the effectiveness of this approach. 

Project Overview 
This project investigates greedy algorithms in the context of the Big 2 strategy. 
It assists in analysing your and to determine the best card choices given your current decision, rather than playing the game turn by turn.

It's useful for: 
Hand evaluation logic testing
Analysing the performance of greedy strategies
Recognising the different power of card combinations
Helping players make strong and fast plays

Core Concept: 
Players in Big 2 must choose from a wide variety of plays including singles, pairs, three-of-a-kind and five-card poker like hands. 
This tool aims to answer the question: "If I want to play a pair (or straight, etc.), which cards from my hand should I use to make the strongest possible play?" 

It uses greedy evaluation: 
Identify every possible play of the selected kind.
Rank them according to their strengths using the Big 2 hand rankings.
Return the best one back immediately.

This reflects a greedy decision-making process of always picking the strongest possible move without considering future rounds or card conservation.

How it works: 
You have the option of manually inputing your hand or have the program randomly select 13 cards for you to hold. The program looks through your hand for all possible combinations of the play type you have selected (such as single, pair, triple, straight, flush, full house, etc.)
Based on suit priority and card values, each combination is ranked by Big 2 strength.
The remaining hand is returned in the proper order for you to play, along with the strongest valid combination.

How to run:
g++ bigTwo/src/*.cpp -IbigTwo/include -o run

Default behaviour
The sample main program:
1) Creates and shuffles a 52-card deck
2) Deals 13 cards to one player
3) Prints the hand
4) Prints a combination summary (singles, pairs, triples, straights, flushes, full houses, four of a kinds)
5) Prints the greedy play order

Manual input (optional)
An interactive input path is included in src/main.cpp (commented). Uncomment it to enter a hand manually. Enter 13 cards as pairs of integers:
• Digit 3..15, where 11=J, 12=Q, 13=K, 14=A, 15=2
• Suit 0..3, where 0=clubs, 1=diamonds, 2=hearts, 3=spades
Example line for King of clubs: 13 0

Rules and ranking
• Rank order: 3 < 4 < 5 < 6 < 7 < 8 < 9 < 10 < J < Q < K < A < 2
• Suit order (for tie-breaks): clubs < diamonds < hearts < spades
• Straights: strictly increasing ranks of length at least 5, the rank 2 is not part of straights, duplicate ranks are skipped so runs remain strictly increasing

Key features
1) Combination finding
Find all singles, pairs, triples, four of a kinds, straights, flushes, and full houses from the current hand.

2) Greedy selector
   Player::greedyPlay() consumes non-overlapping combinations in this fixed priority:
   four of a kinds, full houses, flushes, straights, triples, pairs, singles.
   Cards already used in a chosen combo will not be reused. Use Player::printGreedyPlay(...) to print the suggested order.

3) DP strategies (packing variants) 
All DP functions the hand reordered so that chosen combinations appear first, followed by leftover cards.
- dpCoverFive(): chooses separated five-card sets (straights, flushes, full houses) to cover as many cards as possible
- dpReduceSingle(): packs triples and pairs first to reduce singletons
- dpMaxPairs(): maximises the number of separated pairs
- dpKeepQuads(): preserves separated four of a kinds
- dpStraightsOnly(): packs separated straights where possible
Internals: strategies share a simple memory bank search over a boolean used mask with deterministic reconstruction.

Program outputs
- Hand printout: Player::printHand() prints cards using rank and suit symbols, ordered for readability.
- Summary: Player::summary() returns, and Player::printSummary(...) prints, all detected combination categories and their members.
- Greedy order: Player::printGreedyPlay(...) prints the greedy consumption order, useful as a quick play guide.

Typical workflow:
A) Quick greedy suggestion
   1) Start the program for a random hand
   2) Examine the summary of the combination.
   3) Use the greedy order as the suggested sequence of plays

Compare greedy and DP 
   1) On the same hand, call one or more of the DP functions
   2) Compare the front segments of each output to see differences in coverage, singles remaining, and pair counts
   3) Use this to discuss when greedy is sufficient and when packing is better

File map
• include/Card.h, src/Card.cpp: card model, rank and suit mapping, display helpers, comparisons
• include/Player.h, src/Player.cpp: hand storage, sorting, combination finders and counters, summary printing, greedy selector, DP strategies and helpers
• src/main.cpp: example runner (random deal by default; manual input path available)

Limitations and improvements 
- By default, straight listing is maximal. In long runs, listing fixed-length windows would enable more precise selection. 
- For clarity, the DP memo makes use of string keys. For large searches, bitsets or integer masks would be quicker. 
- For quick testing, a small parser like "3C 3D 3H 5S..." can be added to improve input layout. 

Testing guide
- To exercise all finders, use hands with lots of duplicates, all one suit, no five-card sets and near-runs. 
- Verify that leftovers are included in a stable order and that there is no duplicate usage across the chosen combos 
- Compare greedy and DP outputs to confirm exact differences in coverage
