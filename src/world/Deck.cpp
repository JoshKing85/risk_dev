#include "risk/world/Deck.h"

#include <stdexcept>

namespace risk {

    Card& Deck::getNextCard(bool initialBuild)
    {
        if (deck.empty())
        {
            throw std::runtime_error("Cannot draw from an empty deck");
        }

        if (deckCount >= deck.size())
        {
            deckCount = 0;
        }

        while (initialBuild)
        {
            if (deckCount >= deck.size())
            {
                deckCount = 0;
            }

            if (deck[deckCount].hasTerritory())
            {
                return deck[deckCount++];
            }

            deckCount++;
        }

        return deck[deckCount++];
    }

    void Deck::addDeck(const std::vector<Card>& newDeck)
    {
        deck = newDeck;
        deckCount = 0;
    }

}