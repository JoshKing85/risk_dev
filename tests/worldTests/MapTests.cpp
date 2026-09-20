#include <gtest/gtest.h>

#include "risk/world/Map.h"
#include "risk/world/Continent.h"
#include "risk/entities/Territory.h"
#include "risk/enums.h"

using namespace risk;

// --------------------------------------------------
// Territory Tests
// --------------------------------------------------

TEST(MapTests, TerritoryCanBeAdded)
{
    Map map;

    Territory alaska(
        TerritoryID::Bearus,
        ContinentID::NorthAmerica,
        {}
    );

    map.addTerritory(alaska);

    EXPECT_EQ(
        map.getTerritory(TerritoryID::Bearus).getID(),
        TerritoryID::Bearus
    );
}

TEST(MapTests, TerritoryLookupIndependentOfInsertionOrder)
{
    Map map;

    map.addTerritory(
        Territory(
            TerritoryID::Tairono,
            ContinentID::NorthAmerica,
            {}
        )
    );

    map.addTerritory(
        Territory(
            TerritoryID::Bearus,
            ContinentID::NorthAmerica,
            {}
        )
    );

    EXPECT_EQ(
        map.getTerritory(TerritoryID::Bearus).getID(),
        TerritoryID::Bearus
    );

    EXPECT_EQ(
        map.getTerritory(TerritoryID::Tairono).getID(),
        TerritoryID::Tairono
    );
}

TEST(MapTests, TerritoryReferenceCanBeModified)
{
    Map map;

    map.addTerritory(
        Territory(
            TerritoryID::Bearus,
            ContinentID::NorthAmerica,
            {}
        )
    );

    map.getTerritory(TerritoryID::Bearus)
        .addTroops(5);

    EXPECT_EQ(
        map.getTerritory(TerritoryID::Bearus)
        .getTroopCount(),
        5
    );
}

// --------------------------------------------------
// Continent Tests
// --------------------------------------------------

TEST(MapTests, ContinentCanBeAdded)
{
    Map map;

    Continent continent(
        ContinentID::NorthAmerica,
        5,
        {},
        {}
    );

    map.addContinent(continent);

    EXPECT_EQ(
        map.getContinent(
            ContinentID::NorthAmerica
        ).getContinentID(),
        ContinentID::NorthAmerica
    );
}

TEST(MapTests, ContinentLookupIndependentOfInsertionOrder)
{
    Map map;

    map.addContinent(
        Continent(
            ContinentID::Europe,
            5,
            {},
            {}
        )
    );

    map.addContinent(
        Continent(
            ContinentID::NorthAmerica,
            5,
            {},
            {}
        )
    );

    EXPECT_EQ(
        map.getContinent(
            ContinentID::NorthAmerica
        ).getContinentID(),
        ContinentID::NorthAmerica
    );

    EXPECT_EQ(
        map.getContinent(
            ContinentID::Europe
        ).getContinentID(),
        ContinentID::Europe
    );
}

TEST(MapTests, ContinentReferenceCanBeModified)
{
    Map map;

    map.addContinent(
        Continent(
            ContinentID::NorthAmerica,
            5,
            {},
            {}
        )
    );

    map.getContinent(
        ContinentID::NorthAmerica
    ).setOwner(42);

    EXPECT_EQ(
        map.getContinent(
            ContinentID::NorthAmerica
        ).getOwnerID(),
        42
    );
}