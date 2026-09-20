#include <gtest/gtest.h>

#include "risk/world/Continent.h"
#include "risk/enums.h"

using namespace risk;

// --------------------------------------------------
// Constructor Tests
// --------------------------------------------------

TEST(ContinentTests, StoresCorrectContinentID)
{
    Continent continent(
        ContinentID::NorthAmerica,
        5,
        {},
        {}
    );

    EXPECT_EQ(
        continent.getContinentID(),
        ContinentID::NorthAmerica
    );
}

TEST(ContinentTests, StoresCorrectControlBonus)
{
    Continent continent(
        ContinentID::NorthAmerica,
        5,
        {},
        {}
    );

    EXPECT_EQ(
        continent.getControlBonus(),
        5
    );
}

TEST(ContinentTests, StartsWithoutOwner)
{
    Continent continent(
        ContinentID::NorthAmerica,
        5,
        {},
        {}
    );

    EXPECT_EQ(
        continent.getOwnerID(),
        -1
    );
}

// --------------------------------------------------
// Territory Storage Tests
// --------------------------------------------------

TEST(ContinentTests, StoresTerritories)
{
    std::vector<TerritoryID> territories =
    {
        TerritoryID::Bearus,
        TerritoryID::Rockies,
        TerritoryID::Tairono
    };

    Continent continent(
        ContinentID::NorthAmerica,
        5,
        territories,
        {}
    );

    EXPECT_EQ(
        continent.getTerritories().size(),
        3
    );
}

TEST(ContinentTests, StoresBorderTerritories)
{
    std::vector<TerritoryID> borders =
    {
        TerritoryID::Bearus,
        TerritoryID::Mexico,
        TerritoryID::ArcticIsle
    };

    Continent continent(
        ContinentID::NorthAmerica,
        5,
        {},
        borders
    );

    EXPECT_EQ(
        continent.getBorderTerritories().size(),
        3
    );
}

// --------------------------------------------------
// Owner Tests
// --------------------------------------------------

TEST(ContinentTests, OwnerCanBeAssigned)
{
    Continent continent(
        ContinentID::NorthAmerica,
        5,
        {},
        {}
    );

    continent.setOwner(42);

    EXPECT_EQ(
        continent.getOwnerID(),
        42
    );
}

TEST(ContinentTests, OwnerCanBeChanged)
{
    Continent continent(
        ContinentID::NorthAmerica,
        5,
        {},
        {}
    );

    continent.setOwner(1);
    continent.setOwner(2);

    EXPECT_EQ(
        continent.getOwnerID(),
        2
    );
}