#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "Card.h"

Card::Card() : digit(0), suit(0) {}
Card::Card(int d, int s) : digit(d), suit(s) {}

int Card::getDigit() { return digit; }
int Card::getSuit() { return suit; }
void Card::setDigit(int d) { digit = d; }
void Card::setSuit(int s) { suit = s; }

// helper to display digit as text
std::string Card::digitToString(int digit)
{
    if (digit <= 10)
    {
        return std::to_string(digit);
    }
    switch (digit)
    {
    case 11:
        return "J";
    case 12:
        return "Q";
    case 13:
        return "K";
    case 14:
        return "A";
    case 15:
        return "2";
    default:
        return "?";
    }
}

// helper to display suit from number
std::string Card::suitToString(int suit)
{
    switch (suit)
    {
    case 0:
        return "♣";
    case 1:
        return "♦";
    case 2:
        return "♥";
    case 3:
        return "♠";
    default:
        return "?";
    }
}

std::string Card::cardToString()
{
    return digitToString(digit) + suitToString(suit);
}

bool Card::isLessThan(const Card &other)
{
    if (digit == other.digit)
    {
        return suit < other.suit;
    }
    return digit < other.digit;
}