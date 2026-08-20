#include <gtest/gtest.h>

#include "risk/world/DeckLoader.h"

#include <unordered_set>
#include <vector>

using namespace risk;

namespace {

    Map buildTestMap()
    {
        Map map;

        const std::vector<TerritoryID> territoryIDs{
            TerritoryID::Alaska,
            TerritoryID::Alberta,
            TerritoryID::CentralAmerica,
            TerritoryID::EasternUnitedStates,
            TerritoryID::Greenland,
            TerritoryID::NorthwestTerritory,
            TerritoryID::Ontario,
            TerritoryID::Quebec,
            TerritoryID::WesternUnitedStates,

            TerritoryID::Argentina,
            TerritoryID::Brazil,
            TerritoryID::Peru,
            TerritoryID::Venezuela,

            TerritoryID::GreatBritain,
            TerritoryID::Iceland,
            TerritoryID::NorthernEurope,
            TerritoryID::Scandinavia,
            TerritoryID::SouthernEurope,
            TerritoryID::Ukraine,
            TerritoryID::WesternEurope,

            TerritoryID::Congo,
            TerritoryID::EastAfrica,
            TerritoryID::Egypt,
            TerritoryID::Madagascar,
            TerritoryID::NorthAfrica,
            TerritoryID::SouthAfrica,

            TerritoryID::Afghanistan,
            TerritoryID::China,
            TerritoryID::India,
            TerritoryID::Irkutsk,
            TerritoryID::Japan,
            TerritoryID::Kamchatka,
            TerritoryID::MiddleEast,
            TerritoryID::Mongolia,
            TerritoryID::Siam,
            TerritoryID::Siberia,
            TerritoryID::Ural,
            TerritoryID::Yakutsk,

            TerritoryID::EasternAustralia,
            TerritoryID::Indonesia,
            TerritoryID::NewGuinea,
            TerritoryID::WesternAustralia
        };

        for (TerritoryID territoryID : territoryIDs)
        {
            map.addTerritory(
                Territory(
                    territoryID,
                    ContinentID::NorthAmerica,
                    {}
                )
            );
        }

        return map;
    }

}

// --------------------------------------------------
// Deck Creation Tests
// --------------------------------------------------

TEST(DeckLoaderTests, CreatesDeckWithFortySixCards)
{
    Map map = buildTestMap();
    Deck deck = createDeck(map);

    for (int i = 0; i < 46; i++)
    {
        EXPECT_NO_THROW(deck.getNextCard());
    }
}

TEST(DeckLoaderTests, CreatesFourteenOfEachTerritoryCardType)
{
    Map map = buildTestMap();
    Deck deck = createDeck(map);

    int infantryCount = 0;
    int cavalryCount = 0;
    int artilleryCount = 0;
    int wildCount = 0;

    for (int i = 0; i < 46; i++)
    {
        const Card& card = deck.getNextCard();

        switch (card.getCardType())
        {
        case CardType::Infantry:
            infantryCount++;
            break;

        case CardType::Cavalry:
            cavalryCount++;
            break;

        case CardType::Artillery:
            artilleryCount++;
            break;

        case CardType::Wild:
            wildCount++;
            break;
        }
    }

    EXPECT_EQ(infantryCount, 14);
    EXPECT_EQ(cavalryCount, 14);
    EXPECT_EQ(artilleryCount, 14);
    EXPECT_EQ(wildCount, 4);
}

TEST(DeckLoaderTests, TerritoryCardsContainTerritoryAndContinentIDs)
{
    Map map = buildTestMap();
    Deck deck = createDeck(map);

    int territoryCardCount = 0;

    for (int i = 0; i < 46; i++)
    {
        const Card& card = deck.getNextCard();

        if (card.getCardType() != CardType::Wild)
        {
            EXPECT_TRUE(card.hasTerritory());
            EXPECT_TRUE(card.getTerritoryID().has_value());
            EXPECT_TRUE(card.getContinentID().has_value());

            territoryCardCount++;
        }
    }

    EXPECT_EQ(territoryCardCount, 42);
}

TEST(DeckLoaderTests, WildCardsContainNoTerritoryOrContinent)
{
    Map map = buildTestMap();
    Deck deck = createDeck(map);

    int wildCount = 0;

    for (int i = 0; i < 46; i++)
    {
        const Card& card = deck.getNextCard();

        if (card.getCardType() == CardType::Wild)
        {
            EXPECT_FALSE(card.hasTerritory());
            EXPECT_FALSE(card.getTerritoryID().has_value());
            EXPECT_FALSE(card.getContinentID().has_value());

            wildCount++;
        }
    }

    EXPECT_EQ(wildCount, 4);
}

TEST(DeckLoaderTests, EveryTerritoryAppearsOnce)
{
    Map map = buildTestMap();
    Deck deck = createDeck(map);

    std::unordered_set<TerritoryID> foundTerritories;

    for (int i = 0; i < 46; i++)
    {
        const Card& card = deck.getNextCard();

        if (card.hasTerritory())
        {
            foundTerritories.insert(
                card.getTerritoryID().value()
            );
        }
    }

    EXPECT_EQ(foundTerritories.size(), 42);
}

TEST(DeckLoaderTests, DrawingPastEndCyclesDeck)
{
    Map map = buildTestMap();
    Deck deck = createDeck(map);

    const Card* firstCard = &deck.getNextCard();

    for (int i = 1; i < 46; i++)
    {
        deck.getNextCard();
    }

    const Card* cycledCard = &deck.getNextCard();

    EXPECT_EQ(firstCard, cycledCard);
}