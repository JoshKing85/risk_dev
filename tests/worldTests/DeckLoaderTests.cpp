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
            TerritoryID::Bearus,
            TerritoryID::Rockies,
            TerritoryID::Mexico,
            TerritoryID::GreatLakes,
            TerritoryID::ArcticIsle,
            TerritoryID::Yukon,
            TerritoryID::Tairono,
            TerritoryID::StLawrence,
            TerritoryID::California,

            TerritoryID::Patagonia,
            TerritoryID::Amazonia,
            TerritoryID::Andes,
            TerritoryID::Orinoco,

            TerritoryID::GreatBritain,
            TerritoryID::Iceland,
            TerritoryID::Germany,
            TerritoryID::Scandinavia,
            TerritoryID::Iberia,
            TerritoryID::Russia,
            TerritoryID::France,

            TerritoryID::CentralBasin,
            TerritoryID::Riftlands,
            TerritoryID::Nilelands,
            TerritoryID::LemurIsland,
            TerritoryID::WestAfrica,
            TerritoryID::CapeRegion,

            TerritoryID::Highlands,
            TerritoryID::China,
            TerritoryID::Induslands,
            TerritoryID::BaikalRegion,
            TerritoryID::IslandEmpire,
            TerritoryID::EasternPeninsula,
            TerritoryID::ArabianRegion,
            TerritoryID::GreatSteppe,
            TerritoryID::Indochina,
            TerritoryID::NorthernExpanse,
            TerritoryID::UralRange,
            TerritoryID::FarNortheast,

            TerritoryID::NewSouthWales,
            TerritoryID::Komodo,
            TerritoryID::Philippines,
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