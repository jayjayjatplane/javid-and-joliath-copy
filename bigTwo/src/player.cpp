#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <functional>

#include "Player.h"
#include "Card.h"

Player::Player()
{
    numPairs = 0;
    numTriples = 0;
    numFlushes = 0;
    numStraights = 0;
}

Player::Player(std::vector<Card> &initialHand)
{
    hand = initialHand;
    numPairs = 0;
    numTriples = 0;
    numFlushes = 0;
    numStraights = 0;
}

// sort hand helper
bool sortHelper(Card &a, Card &b)
{
    return a.isLessThan(b);
}

void Player::sortHand() { sort(hand.begin(), hand.end(), sortHelper); }

void Player::analyseHand() {}

void Player::clearHand() {}

// finders
std::vector<std::vector<Card>> Player::findSingles()
{
    std::vector<std::vector<Card>> singles;
    for (int i = 0; i < hand.size(); i++)
    {
        std::vector<Card> single;
        single.push_back(hand[i]);
        singles.push_back(single);
    }
    return singles;
}

std::vector<std::vector<Card>> Player::findPairs()
{
    std::vector<std::vector<Card>> pairs;
    std::map<int, std::vector<Card>> rankMap;

    for (int i = 0; i < hand.size(); i++)
    {
        rankMap[hand[i].getDigit()].push_back(hand[i]);
    }

    for (std::map<int, std::vector<Card>>::iterator it = rankMap.begin(); it != rankMap.end(); ++it)
    {
        if (it->second.size() >= 2)
        {
            std::vector<Card> pair;
            pair.push_back(it->second[0]);
            pair.push_back(it->second[1]);
            pairs.push_back(pair);
        }
    }

    return pairs;
}

std::vector<std::vector<Card>> Player::findTriples()
{
    std::vector<std::vector<Card>> triples;
    std::map<int, std::vector<Card>> rankMap;

    for (int i = 0; i < hand.size(); i++)
    {
        rankMap[hand[i].getDigit()].push_back(hand[i]);
    }

    for (std::map<int, std::vector<Card>>::iterator it = rankMap.begin(); it != rankMap.end(); ++it)
    {
        if (it->second.size() >= 3)
        {
            std::vector<Card> triple;
            triple.push_back(it->second[0]);
            triple.push_back(it->second[1]);
            triple.push_back(it->second[2]);
            triples.push_back(triple);
        }
    }

    return triples;
}

std::vector<std::vector<Card>> Player::findFourOfAKinds()
{
    std::vector<std::vector<Card>> quads;
    std::map<int, std::vector<Card>> rankMap;

    for (int i = 0; i < hand.size(); i++)
    {
        rankMap[hand[i].getDigit()].push_back(hand[i]);
    }

    for (std::map<int, std::vector<Card>>::iterator it = rankMap.begin(); it != rankMap.end(); ++it)
    {
        if (it->second.size() == 4)
        {
            std::vector<Card> quad = it->second;
            quads.push_back(quad);
        }
    }

    return quads;
}

std::vector<std::vector<Card>> Player::findStraights()
{
    std::vector<std::vector<Card>> straights;
    sortHand(); // make sure sorted

    std::vector<Card> current;

    for (int i = 0; i < hand.size(); i++)
    {
        if (current.empty() || hand[i].getDigit() == current.back().getDigit() + 1)
        {
            current.push_back(hand[i]);
        }
        else if (hand[i].getDigit() == current.back().getDigit())
        {
            // skip duplicate rank (same number, diff suit)
            continue;
        }
        else
        {
            if (current.size() >= 5)
            {
                straights.push_back(current);
            }
            current.clear();
            current.push_back(hand[i]);
        }
    }

    if (current.size() >= 5)
    {
        straights.push_back(current);
    }

    return straights;
}

std::vector<std::vector<Card>> Player::findFlushes()
{
    std::vector<std::vector<Card>> flushes;
    std::map<int, std::vector<Card>> suitMap;

    for (int i = 0; i < hand.size(); i++)
    {
        suitMap[hand[i].getSuit()].push_back(hand[i]);
    }

    for (std::map<int, std::vector<Card>>::iterator it = suitMap.begin(); it != suitMap.end(); ++it)
    {
        if (it->second.size() >= 5)
        {
            flushes.push_back(it->second);
        }
    }

    return flushes;
}

std::vector<std::vector<Card>> Player::findFullHouses()
{
    std::vector<std::vector<Card>> fullHouses;
    std::vector<std::vector<Card>> triples = findTriples();
    std::vector<std::vector<Card>> pairs = findPairs();

    for (int i = 0; i < triples.size(); i++)
    {
        int tripleRank = triples[i][0].getDigit();
        for (int j = 0; j < pairs.size(); j++)
        {
            int pairRank = pairs[j][0].getDigit();
            if (pairRank != tripleRank)
            {
                std::vector<Card> fullHouse;
                fullHouse.insert(fullHouse.end(), triples[i].begin(), triples[i].end());
                fullHouse.insert(fullHouse.end(), pairs[j].begin(), pairs[j].end());
                fullHouses.push_back(fullHouse);
            }
        }
    }

    return fullHouses;
}

// counters

int Player::countPairs()
{
    sortHand();
    int pairs = 0;
    int count = 1;

    for (size_t i = 1; i <= hand.size(); ++i)
    {
        if (i < hand.size() && hand[i].getDigit() == hand[i - 1].getDigit())
        {
            count++;
        }
        else
        {
            pairs += (count * (count - 1)) / 2;
            count = 1;
        }
    }

    return pairs;
}

int Player::countTriples()
{
    sortHand();
    int triples = 0;
    int count = 1;

    for (size_t i = 1; i <= hand.size(); ++i)
    {
        if (i < hand.size() && hand[i].getDigit() == hand[i - 1].getDigit())
        {
            count++;
        }
        else
        {
            triples += (count * (count - 1) * (count - 2)) / 6;
            count = 1;
        }
    }

    return triples;
}

int Player::countFlushes()
{
    int suitCount[4] = {0, 0, 0, 0};

    for (size_t i = 0; i < hand.size(); ++i)
    {
        int s = hand[i].getSuit();
        suitCount[s]++;
    }

    int flushes = 0;

    for (int i = 0; i < 4; ++i)
    {
        int c = suitCount[i];
        if (c >= 5)
            flushes += (c * (c - 1) * (c - 2) * (c - 3) * (c - 4)) / 120; // C(c,5)
    }

    return flushes;
}

int Player::countStraights()
{
    sortHand();
    if (hand.size() < 5)
    {
        return 0;
    }

    bool hasRank[13] = {false};
    for (auto &card : hand)
    {
        int rank = card.getDigit();
        if (rank == 2)
        {
            continue;
        }
        hasRank[rank - 3] = true;
    }

    int straights = 0;
    int consecutive = 0;

    for (int i = 0; i < 13; ++i)
    {
        if (i >= 12)
        {
            break;
        }

        if (hasRank[i])
        {
            consecutive++;
            if (consecutive >= 5)
                straights++;
        }
        else
        {
            consecutive = 0;
        }
    }

    return straights;
}

// output/display

void Player::printHand()
{
    for (Card &card : hand)
    {
        std::cout << card.cardToString() << " ";
    }
    std::cout << std::endl;
}

ComboSummary Player::summary()
{
    ComboSummary summaryData;

    summaryData.singles = findSingles();
    summaryData.pairs = findPairs();
    summaryData.triples = findTriples();
    summaryData.straights = findStraights();
    summaryData.flushes = findFlushes();
    summaryData.fullHouses = findFullHouses();
    summaryData.fourOfAKinds = findFourOfAKinds();

    return summaryData;
}

void Player::printSummary(ComboSummary &summaryData)
{
    std::cout << "\nSingles (" << summaryData.singles.size() << "):" << std::endl;
    for (int i = 0; i < summaryData.singles.size(); i++)
    {
        for (int j = 0; j < summaryData.singles[i].size(); j++)
        {
            std::cout << summaryData.singles[i][j].cardToString() << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nPairs (" << summaryData.pairs.size() << "):" << std::endl;
    for (int i = 0; i < summaryData.pairs.size(); i++)
    {
        for (int j = 0; j < summaryData.pairs[i].size(); j++)
        {
            std::cout << summaryData.pairs[i][j].cardToString() << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nTriples (" << summaryData.triples.size() << "):" << std::endl;
    for (int i = 0; i < summaryData.triples.size(); i++)
    {
        for (int j = 0; j < summaryData.triples[i].size(); j++)
        {
            std::cout << summaryData.triples[i][j].cardToString() << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nStraights (" << summaryData.straights.size() << "):" << std::endl;
    for (int i = 0; i < summaryData.straights.size(); i++)
    {
        for (int j = 0; j < summaryData.straights[i].size(); j++)
        {
            std::cout << summaryData.straights[i][j].cardToString() << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nFlushes (" << summaryData.flushes.size() << "):" << std::endl;
    for (int i = 0; i < summaryData.flushes.size(); i++)
    {
        for (int j = 0; j < summaryData.flushes[i].size(); j++)
        {
            std::cout << summaryData.flushes[i][j].cardToString() << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nFull Houses (" << summaryData.fullHouses.size() << "):" << std::endl;
    for (int i = 0; i < summaryData.fullHouses.size(); i++)
    {
        for (int j = 0; j < summaryData.fullHouses[i].size(); j++)
        {
            std::cout << summaryData.fullHouses[i][j].cardToString() << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nFour of a Kinds (" << summaryData.fourOfAKinds.size() << "):" << std::endl;
    for (int i = 0; i < summaryData.fourOfAKinds.size(); i++)
    {
        for (int j = 0; j < summaryData.fourOfAKinds[i].size(); j++)
        {
            std::cout << summaryData.fourOfAKinds[i][j].cardToString() << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<Card> Player::greedyPlay()
{
    ComboSummary summaryData = summary();
    std::vector<Card> playOrder;
    std::vector<Card> usedCards; // use vector instead of set

    // Helper lambda to append a combo if cards are not already used
    auto appendCombos = [&playOrder, &usedCards](const std::vector<std::vector<Card>> &combos)
    {
        for (const auto &combo : combos)
        {
            bool comboUsed = false;
            for (const auto &card : combo)
            {
                // linear search to see if card was already used
                if (std::find(usedCards.begin(), usedCards.end(), card) != usedCards.end())
                {
                    comboUsed = true;
                    break;
                }
            }

            if (!comboUsed)
            {
                for (const auto &card : combo)
                {
                    playOrder.push_back(card);
                    usedCards.push_back(card);
                }
            }
        }
    };

    // Start from biggest combos
    appendCombos(summaryData.fourOfAKinds);
    appendCombos(summaryData.fullHouses);
    appendCombos(summaryData.flushes);
    appendCombos(summaryData.straights);
    appendCombos(summaryData.triples);
    appendCombos(summaryData.pairs);
    appendCombos(summaryData.singles);

    return playOrder;
}

void Player::printGreedyPlay(std::vector<Card> &greedyOrder)
{
    std::cout << "Greedy play order: ";
    for (Card &c : greedyOrder)
    {
        std::cout << c.cardToString() << " ";
    }
    std::cout << std::endl;
}

// simple helper dp without bit operations that chooses disjoint combos to cover the most cards
// all comments are lower case letters only
static int dfsCoverSimple(
    const std::vector<std::vector<int>> &combo_idx,
    int hand_size,
    std::vector<bool> &used_flag,
    std::map<std::string, int> &memo_val,
    std::map<std::string, int> &memo_pick)
{
    // build key string from used flags
    std::string key_string = "";
    {
        key_string.reserve(hand_size);
        for (int pos = 0; pos < hand_size; pos++)
        {
            if (used_flag[pos])
            {
                key_string.push_back('1');
            }
            else
            {
                key_string.push_back('0');
            }
        }
    }

    if (memo_val.count(key_string) > 0)
    {
        int cached_val = memo_val[key_string];
        return cached_val;
    }

    int best_val = 0;
    int best_pick = -1;

    for (int combo_index = 0; combo_index < (int)combo_idx.size(); combo_index++)
    {
        bool fits_now = true;
        for (int idx : combo_idx[combo_index])
        {
            if (used_flag[idx])
            {
                fits_now = false;
                break;
            }
        }
        if (!fits_now)
        {
            continue;
        }

        for (int idx : combo_idx[combo_index])
        {
            used_flag[idx] = true;
        }

        int combo_gain = (int)combo_idx[combo_index].size();
        int next_val = dfsCoverSimple(combo_idx, hand_size, used_flag, memo_val, memo_pick);
        int total_val = combo_gain + next_val;

        if (total_val > best_val)
        {
            best_val = total_val;
            best_pick = combo_index;
        }

        for (int idx : combo_idx[combo_index])
        {
            used_flag[idx] = false;
        }
    }

    memo_val[key_string] = best_val;
    memo_pick[key_string] = best_pick;
    return best_val;
}

// simple helper dp without bit operations that chooses disjoint combos to cover the most cards
// all comments are lower case letters only
static std::vector<std::vector<Card>> pickMaxCoverSimple(
    const std::vector<Card> &hand_list,
    const std::vector<std::vector<Card>> &combo_list)
{
    int hand_size = (int)hand_list.size();

    // map each combo to indices in the hand
    std::vector<std::vector<int>> combo_idx;
    {
        std::vector<std::vector<int>> temp_idx;
        for (const auto &one_combo : combo_list)
        {
            std::vector<int> idx_list;
            for (const Card &one_card : one_combo)
            {
                int found_idx = -1;
                for (int pos = 0; pos < hand_size; pos++)
                {
                    if (hand_list[pos] == one_card)
                    {
                        found_idx = pos;
                        break;
                    }
                }
                if (found_idx >= 0)
                {
                    idx_list.push_back(found_idx);
                }
            }
            temp_idx.push_back(idx_list);
        }
        combo_idx = temp_idx;
    }

    // run dfs with memo
    std::map<std::string, int> memo_val;
    std::map<std::string, int> memo_pick;
    std::vector<bool> used_flag(hand_size, false);
    int start_val = dfsCoverSimple(combo_idx, hand_size, used_flag, memo_val, memo_pick);
    (void)start_val; // quiet unused warning if any

    // reconstruct picks
    std::vector<std::vector<Card>> pick_list;
    while (true)
    {
        std::string key_string = "";
        {
            key_string.reserve(hand_size);
            for (int pos = 0; pos < hand_size; pos++)
            {
                if (used_flag[pos])
                {
                    key_string.push_back('1');
                }
                else
                {
                    key_string.push_back('0');
                }
            }
        }

        if (memo_pick.count(key_string) == 0)
        {
            break;
        }
        int take_index = memo_pick[key_string];
        if (take_index < 0)
        {
            break;
        }

        std::vector<Card> chosen_combo;
        for (int idx : combo_idx[take_index])
        {
            chosen_combo.push_back(hand_list[idx]);
        }
        pick_list.push_back(chosen_combo);

        for (int idx : combo_idx[take_index])
        {
            used_flag[idx] = true;
        }
    }

    return pick_list;
}

static std::vector<Card> flattenWithLeftover(
    const std::vector<Card> &hand_list,
    const std::vector<std::vector<Card>> &pick_list)
{
    std::vector<Card> out_list;
    std::vector<Card> used_list;

    for (const auto &one_combo : pick_list)
    {
        for (const Card &one_card : one_combo)
        {
            out_list.push_back(one_card);
            used_list.push_back(one_card);
        }
    }

    for (const Card &one_card : hand_list)
    {
        bool already_used = false;
        for (const Card &seen_card : used_list)
        {
            if (seen_card == one_card)
            {
                already_used = true;
                break;
            }
        }
        if (!already_used)
        {
            out_list.push_back(one_card);
        }
    }

    return out_list;
}

std::vector<Card> Player::dpCoverFive()
{
    ComboSummary combo_sum = summary();

    std::vector<std::vector<Card>> five_list;
    {
        std::vector<std::vector<Card>> copy_list = combo_sum.straights;
        for (const auto &group_item : copy_list)
        {
            five_list.push_back(group_item);
        }
    }
    {
        std::vector<std::vector<Card>> copy_list = combo_sum.flushes;
        for (const auto &group_item : copy_list)
        {
            five_list.push_back(group_item);
        }
    }
    {
        std::vector<std::vector<Card>> copy_list = combo_sum.fullHouses;
        for (const auto &group_item : copy_list)
        {
            five_list.push_back(group_item);
        }
    }

    std::vector<std::vector<Card>> chosen_list = pickMaxCoverSimple(hand, five_list);
    std::vector<Card> flat_list = flattenWithLeftover(hand, chosen_list);
    return flat_list;
}

std::vector<Card> Player::dpReduceSingle()
{
    ComboSummary combo_sum = summary();

    std::vector<std::vector<Card>> set_list;
    {
        std::vector<std::vector<Card>> copy_list = combo_sum.triples;
        for (const auto &group_item : copy_list)
        {
            set_list.push_back(group_item);
        }
    }
    {
        std::vector<std::vector<Card>> copy_list = combo_sum.pairs;
        for (const auto &group_item : copy_list)
        {
            set_list.push_back(group_item);
        }
    }

    std::vector<std::vector<Card>> chosen_list = pickMaxCoverSimple(hand, set_list);
    std::vector<Card> flat_list = flattenWithLeftover(hand, chosen_list);
    return flat_list;
}

std::vector<Card> Player::dpMaxPairs()
{
    ComboSummary combo_sum = summary();

    std::vector<std::vector<Card>> pair_list = combo_sum.pairs;
    std::vector<std::vector<Card>> chosen_list = pickMaxCoverSimple(hand, pair_list);
    std::vector<Card> flat_list = flattenWithLeftover(hand, chosen_list);
    return flat_list;
}

std::vector<Card> Player::dpKeepQuads()
{
    ComboSummary combo_sum = summary();

    std::vector<std::vector<Card>> quad_list = combo_sum.fourOfAKinds;
    std::vector<std::vector<Card>> chosen_list = pickMaxCoverSimple(hand, quad_list);
    std::vector<Card> flat_list = flattenWithLeftover(hand, chosen_list);
    return flat_list;
}

std::vector<Card> Player::dpStraightsOnly()
{
    ComboSummary combo_sum = summary();

    std::vector<std::vector<Card>> straight_list = combo_sum.straights;
    std::vector<std::vector<Card>> chosen_list = pickMaxCoverSimple(hand, straight_list);
    std::vector<Card> flat_list = flattenWithLeftover(hand, chosen_list);
    return flat_list;
}

// accsess

const std::vector<Card> &Player::getHand()
{
    return hand;
}

int Player::getNumPairs() { return numPairs; }

int Player::getNumTriples() { return numTriples; }

int Player::getNumFlushes() { return numFlushes; }

int Player::getNumStraights() { return numStraights; }