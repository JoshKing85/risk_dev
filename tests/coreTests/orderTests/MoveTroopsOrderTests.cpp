#include <gtest/gtest.h>

#include "risk/core/orders/MoveTroopsOrder.h"

using namespace risk;

// --------------------------------------------------
// Constructor Tests
// --------------------------------------------------

TEST(MoveTroopsOrderTests, StoresPlayerID)
{
    MoveTroopsOrder order(
        1,
        TerritoryID::Alaska,
        TerritoryID::Alberta,
        5
    );

    EXPECT_EQ(order.getPlayerID(), 1);
}

TEST(MoveTroopsOrderTests, StoresOrderType)
{
    MoveTroopsOrder order(
        1,
        TerritoryID::Alaska,
        TerritoryID::Alberta,
        5
    );

    EXPECT_EQ(order.getOrderType(), OrderType::MoveTroops);
}

TEST(MoveTroopsOrderTests, StartsIncomplete)
{
    MoveTroopsOrder order(
        1,
        TerritoryID::Alaska,
        TerritoryID::Alberta,
        5
    );

    EXPECT_FALSE(order.isCompleted());
}

// --------------------------------------------------
// Territory Tests
// --------------------------------------------------

TEST(MoveTroopsOrderTests, StoresFromTerritory)
{
    MoveTroopsOrder order(
        1,
        TerritoryID::Alaska,
        TerritoryID::Alberta,
        5
    );

    EXPECT_EQ(
        order.getFromTerritory(),
        TerritoryID::Alaska
    );
}

TEST(MoveTroopsOrderTests, StoresToTerritory)
{
    MoveTroopsOrder order(
        1,
        TerritoryID::Alaska,
        TerritoryID::Alberta,
        5
    );

    EXPECT_EQ(
        order.getToTerritory(),
        TerritoryID::Alberta
    );
}

TEST(MoveTroopsOrderTests, StoresTroopsMoved)
{
    MoveTroopsOrder order(
        1,
        TerritoryID::Alaska,
        TerritoryID::Alberta,
        5
    );

    EXPECT_EQ(
        order.getTroopsMoved(),
        5
    );
}