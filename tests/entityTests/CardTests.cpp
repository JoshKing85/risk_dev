#include <gtest/gtest.h>

#include "risk/entities/Card.h"

namespace risk {

    TEST(CardTests, StoresCardType)
    {
        Card card(
            CardType::Infantry,
            TerritoryID::Alaska,
            ContinentID::NorthAmerica
        );

        EXPECT_EQ(card.getCardType(), CardType::Infantry);
    }

    TEST(CardTests, StoresTerritoryID)
    {
        Card card(
            CardType::Cavalry,
            TerritoryID::Alaska,
            ContinentID::NorthAmerica
        );

        ASSERT_TRUE(card.getTerritoryID().has_value());
        EXPECT_EQ(
            card.getTerritoryID().value(),
            TerritoryID::Alaska
        );
    }

    TEST(CardTests, StoresContinentID)
    {
        Card card(
            CardType::Artillery,
            TerritoryID::Alaska,
            ContinentID::NorthAmerica
        );

        ASSERT_TRUE(card.getContinentID().has_value());
        EXPECT_EQ(
            card.getContinentID().value(),
            ContinentID::NorthAmerica
        );
    }

    TEST(CardTests, TerritoryCardHasTerritory)
    {
        Card card(
            CardType::Infantry,
            TerritoryID::Alaska,
            ContinentID::NorthAmerica
        );

        EXPECT_TRUE(card.hasTerritory());
    }

    TEST(CardTests, WildCardHasNoTerritory)
    {
        Card card(CardType::Wild);

        EXPECT_FALSE(card.hasTerritory());
        EXPECT_FALSE(card.getTerritoryID().has_value());
        EXPECT_FALSE(card.getContinentID().has_value());
    }

    TEST(CardTests, WildCardStoresWildType)
    {
        Card card(CardType::Wild);

        EXPECT_EQ(card.getCardType(), CardType::Wild);
    }

}