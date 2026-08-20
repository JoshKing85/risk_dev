#include "risk/world/DeckLoader.h"

#include <algorithm>
#include <random>
#include <vector>

namespace risk {

    Deck createDeck(const Map& map)
    {
        Deck deck;

        std::vector<Card> tempDeck;

        int infantryCount = 0;
        int cavalryCount = 0;
        int artilleryCount = 0;

        //-----------------------------------------------------
        // Create territory cards
        //-----------------------------------------------------

        for (const auto& territoryPair :
            map.getTerritories())
        {
            const Territory& territory =
                territoryPair.second;

            CardType cardType;

            if (infantryCount < 14)
            {
                cardType =
                    CardType::Infantry;

                ++infantryCount;
            }
            else if (cavalryCount < 14)
            {
                cardType =
                    CardType::Cavalry;

                ++cavalryCount;
            }
            else
            {
                cardType =
                    CardType::Artillery;

                ++artilleryCount;
            }

            tempDeck.emplace_back(
                cardType,
                territory.getID(),
                territory.getContinentID()
            );
        }

        //-----------------------------------------------------
        // Add Wild cards
        //-----------------------------------------------------

        for (int i = 0; i < 4; ++i)
        {
            tempDeck.emplace_back(
                CardType::Wild
            );
        }

        //-----------------------------------------------------
        // Shuffle deck
        //-----------------------------------------------------

        std::random_device rd;
        std::mt19937 generator(rd());

        std::shuffle(
            tempDeck.begin(),
            tempDeck.end(),
            generator
        );

        //-----------------------------------------------------
        // Store cards in Deck
        //-----------------------------------------------------

        deck.addDeck(tempDeck);

        return deck;
    }

} // namespace risk