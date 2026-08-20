#include <gtest/gtest.h>

#include "risk/entities/Territory.h"
#include "risk/enums.h"

using namespace risk;

// --------------------------------------------------
// Constructor Tests
// --------------------------------------------------

TEST(TerritoryTests, StartsWithZeroTroops)
{
    Territory territory(
        TerritoryID::Alaska,
        ContinentID::NorthAmerica,
        {}
    );

    EXPECT_EQ(territory.getTroopCount(), 0);
}

TEST(TerritoryTests, StoresCorrectTerritoryID)
{
    Territory territory(
        TerritoryID::Alaska,
        ContinentID::NorthAmerica,
        {}
    );

    EXPECT_EQ(
        territory.getID(),
        TerritoryID::Alaska
    );
}

TEST(TerritoryTests, StoresCorrectContinentID)
{
    Territory territory(
        TerritoryID::Alaska,
        ContinentID::NorthAmerica,
        {}
    );

    EXPECT_EQ(
        territory.getContinentID(),
        ContinentID::NorthAmerica
    );
}

// --------------------------------------------------
// Adjacency Tests
// --------------------------------------------------

TEST(TerritoryTests, StoresAdjacentTerritories)
{
    std::vector<TerritoryID> neighbours =
    {
        TerritoryID::Alberta,
        TerritoryID::NorthwestTerritory
    };

    Territory territory(
        TerritoryID::Alaska,
        ContinentID::NorthAmerica,
        neighbours
    );

    EXPECT_EQ(
        territory.getAdjacentTerritories().size(),
        2
    );
}

// --------------------------------------------------
// Troop Tests
// --------------------------------------------------

TEST(TerritoryTests, CanAddTroops)
{
    Territory territory(
        TerritoryID::Alaska,
        ContinentID::NorthAmerica,
        {}
    );

    territory.addTroops(10);

    EXPECT_EQ(
        territory.getTroopCount(),
        10
    );
}

TEST(TerritoryTests, CanRemoveTroops)
{
    Territory territory(
        TerritoryID::Alaska,
        ContinentID::NorthAmerica,
        {}
    );

    territory.addTroops(10);
    territory.removeTroops(3);

    EXPECT_EQ(
        territory.getTroopCount(),
        7
    );
}

TEST(TerritoryTests, TroopsCannotGoBelowZero)
{
    Territory territory(
        TerritoryID::Alaska,
        ContinentID::NorthAmerica,
        {}
    );

    territory.addTroops(3);
    territory.removeTroops(100);

    EXPECT_EQ(
        territory.getTroopCount(),
        0
    );
}

TEST(TerritoryTests, TerritoryCanLoseFinalTroop)
{
    Territory territory(
        TerritoryID::Alaska,
        ContinentID::NorthAmerica,
        {}
    );

    territory.addTroops(1);
    territory.removeTroops(1);

    EXPECT_EQ(
        territory.getTroopCount(),
        0
    );
}