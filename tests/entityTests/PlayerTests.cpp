#include <gtest/gtest.h>

#include "risk/entities/Player.h"
#include "risk/enums.h"

#include <string>

using namespace risk;

// --------------------------------------------------
// Constructor Tests
// --------------------------------------------------

TEST(PlayerTests, StartsWithZeroTroops)
{
    Player player(1);

    EXPECT_EQ(
        player.getTroopCount(),
        0
    );
}

TEST(PlayerTests, StartsWithNoTerritories)
{
    Player player(1);

    EXPECT_TRUE(
        player.getTerritoriesHeld().empty()
    );
}

TEST(PlayerTests, StartsWithNoAllies)
{
    Player player(1);

    EXPECT_TRUE(
        player.getAllies().empty()
    );
}

// --------------------------------------------------
// Player Name Tests
// --------------------------------------------------

TEST(PlayerTests, CanSetPlayerName)
{
    Player player(1);

    std::string name =
        "Josh";

    player.setPlayerName(name);

    EXPECT_EQ(
        player.getPlayerName(),
        "Josh"
    );
}

// --------------------------------------------------
// Troop Tests
// --------------------------------------------------

TEST(PlayerTests, CanAddTroops)
{
    Player player(1);

    player.addTroops(10);

    EXPECT_EQ(
        player.getTroopCount(),
        10
    );
}

TEST(PlayerTests, CanRemoveTroops)
{
    Player player(1);

    player.addTroops(10);
    player.removeTroops(3);

    EXPECT_EQ(
        player.getTroopCount(),
        7
    );
}

TEST(PlayerTests, TroopsCannotGoNegative)
{
    Player player(1);

    player.addTroops(5);
    player.removeTroops(100);

    EXPECT_EQ(
        player.getTroopCount(),
        0
    );
}

// --------------------------------------------------
// Territory Tests
// --------------------------------------------------

TEST(PlayerTests, CanAddTerritory)
{
    Player player(1);

    player.addTerritory(
        TerritoryID::Bearus
    );

    EXPECT_EQ(
        player.getTerritoriesHeld().size(),
        1
    );
}

TEST(PlayerTests, DuplicateTerritoryNotAdded)
{
    Player player(1);

    player.addTerritory(
        TerritoryID::Bearus
    );

    player.addTerritory(
        TerritoryID::Bearus
    );

    EXPECT_EQ(
        player.getTerritoriesHeld().size(),
        1
    );
}

TEST(PlayerTests, CanRemoveTerritory)
{
    Player player(1);

    player.addTerritory(
        TerritoryID::Bearus
    );

    player.removeTerritory(
        TerritoryID::Bearus
    );

    EXPECT_TRUE(
        player.getTerritoriesHeld().empty()
    );
}

// --------------------------------------------------
// Alliance Tests
// --------------------------------------------------

TEST(PlayerTests, CannotAllySelf)
{
    Player player(1);

    player.addAlly(
        player.getPlayerID()
    );

    EXPECT_TRUE(
        player.getAllies().empty()
    );
}

TEST(PlayerTests, CanAddAlly)
{
    Player player(1);

    player.addAlly(999);

    EXPECT_EQ(
        player.getAllies().size(),
        1
    );
}

TEST(PlayerTests, DuplicateAllyNotAdded)
{
    Player player(1);

    player.addAlly(999);
    player.addAlly(999);

    EXPECT_EQ(
        player.getAllies().size(),
        1
    );
}

TEST(PlayerTests, CanRemoveAlly)
{
    Player player(1);

    player.addAlly(999);
    player.removeAlly(999);

    EXPECT_TRUE(
        player.getAllies().empty()
    );
}