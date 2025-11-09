#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include "../include/Card.h"
#include "../include/Player.h"

using namespace std;
/*
int main()
{
    vector<Card> hand;
    cout << "Enter your 13-card hand.\n";
    cout << "Format: digit suit  (e.g., '13 0' for King of Clubs)\n";
    cout << "Suits: 0=♣, 1=♦, 2=♥, 3=♠\n";

    for (int i = 0; i < 13; ++i)
    {
        int digit, suit;
        while (true)
        {
            std::cout << "Card " << (i + 1) << ": ";
            std::cin >> digit >> suit;
            if (digit >= 1 && digit <= 13 && suit >= 0 && suit <= 3)
            {
                hand.push_back(Card(digit, suit));
                break;
            }
            else
            {
                std::cout << "Invalid input. Try again.\n";
            }
        }
    }

    Player player(hand);
    player.printHand();

    return 0;
}
*/