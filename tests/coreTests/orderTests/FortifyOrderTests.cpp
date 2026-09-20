#include <gtest/gtest.h>

#include "risk/core/orders/FortifyOrder.h"

using namespace risk;

// --------------------------------------------------
// Constructor Tests
// --------------------------------------------------

TEST(FortifyOrderTests, StoresPlayerID)
{
    FortifyOrder order(
        1,
        TerritoryID::Bearus,
        TerritoryID::Rockies,
        5
    );

    EXPECT_EQ(order.getPlayerID(), 1);
}

TEST(FortifyOrderTests, StoresOrderType)
{
    FortifyOrder order(
        1,
        TerritoryID::Bearus,
        TerritoryID::Rockies,
        5
    );

    EXPECT_EQ(order.getOrderType(), OrderType::Fortify);
}

TEST(FortifyOrderTests, StartsIncomplete)
{
    FortifyOrder order(
        1,
        TerritoryID::Bearus,
        TerritoryID::Rockies,
        5
    );

    EXPECT_FALSE(order.isCompleted());
}

// --------------------------------------------------
// Territory Tests
// --------------------------------------------------

TEST(FortifyOrderTests, StoresFromTerritory)
{
    FortifyOrder order(
        1,
        TerritoryID::Bearus,
        TerritoryID::Rockies,
        5
    );

    EXPECT_EQ(
        order.getFromTerritory(),
        TerritoryID::Bearus
    );
}

TEST(FortifyOrderTests, StoresToTerritory)
{
    FortifyOrder order(
        1,
        TerritoryID::Bearus,
        TerritoryID::Rockies,
        5
    );

    EXPECT_EQ(
        order.getToTerritory(),
        TerritoryID::Rockies
    );
}

TEST(FortifyOrderTests, StoresFortifyTroopCount)
{
    FortifyOrder order(
        1,
        TerritoryID::Bearus,
        TerritoryID::Rockies,
        5
    );

    EXPECT_EQ(order.getFortifyTroopCount(), 5);
}