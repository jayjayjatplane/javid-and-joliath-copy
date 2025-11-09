#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Card
{
private:
    int digit; // 3–15 (3..10, 11=J, 12=Q, 13=K, 14=A, 15=2)
    int suit;  // 0=♣, 1=♦, 2=♥, 3=♠
public:
    Card();
    Card(int d, int s);
    int getDigit();
    int getSuit();
    void setDigit(int d);
    void setSuit(int s);

    // display card info
    std::string digitToString(int digit);
    std::string suitToString(int suit);
    std::string cardToString();

    // Simple comparison helper
    bool isLessThan(const Card &other);

    // stuff
    bool operator==(const Card &other) const
    {
        return digit == other.digit && suit == other.suit;
    }
};

#endif