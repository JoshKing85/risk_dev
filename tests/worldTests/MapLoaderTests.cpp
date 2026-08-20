#include <gtest/gtest.h>

#include "risk/world/MapLoader.h"

using namespace risk;

// --------------------------------------------------
// Continent Conversion Tests
// --------------------------------------------------

TEST(MapLoaderTests, ConvertsNorthAmerica)
{
    EXPECT_EQ(
        stringToContinentID("NorthAmerica"),
        ContinentID::NorthAmerica
    );
}

TEST(MapLoaderTests, ConvertsEurope)
{
    EXPECT_EQ(
        stringToContinentID("Europe"),
        ContinentID::Europe
    );
}

TEST(MapLoaderTests, UnknownContinentThrows)
{
    EXPECT_THROW(
        stringToContinentID("Atlantis"),
        std::invalid_argument
    );
}

// --------------------------------------------------
// Territory Conversion Tests
// --------------------------------------------------

TEST(MapLoaderTests, ConvertsAlaska)
{
    EXPECT_EQ(
        stringToTerritoryID("Alaska"),
        TerritoryID::Alaska
    );
}

TEST(MapLoaderTests, ConvertsBrazil)
{
    EXPECT_EQ(
        stringToTerritoryID("Brazil"),
        TerritoryID::Brazil
    );
}

TEST(MapLoaderTests, UnknownTerritoryThrows)
{
    EXPECT_THROW(
        stringToTerritoryID("MiddleEarth"),
        std::invalid_argument
    );
}

// --------------------------------------------------
// File Tests
// --------------------------------------------------

TEST(MapLoaderTests, MissingFileThrows)
{
    EXPECT_THROW(
        loadMap("does_not_exist.json"),
        std::runtime_error
    );
}