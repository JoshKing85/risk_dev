#include <gtest/gtest.h>

#include "risk/core/session/GameInitializer.h"

#include "risk/entities/Player.h"
#include "risk/world/Map.h"
#include "risk/world/Deck.h"
#include "risk/entities/Territory.h"

#include <string>
#include <tuple>
#include <vector>

using namespace risk;

//=========================================================
// Helper
//=========================================================

static std::string getClassicMapPath()
{
    return
        "C:\\Users\\joshk\\programming\\risk_V1\\data\\maps\\classic.json";
}

//=========================================================
// Player Setup
//=========================================================

TEST(GameInitializerTests, UpdatePlayerChangesName)
{
    GameInitializer initializer;

    Player player(0);

    std::string name =
        "Josh";

    initializer.updatePlayer(
        player,
        name
    );

    EXPECT_EQ(
        player.getPlayerName(),
        "Josh"
    );
}

//=========================================================
// Initialize Game
//=========================================================

TEST(GameInitializerTests, InitializeGameCreatesCorrectPlayerCount)
{
    GameInitializer initializer;

    std::string filename =
        getClassicMapPath();

    auto [map, players, deck] =
        initializer.initializeGame(
            filename,
            2,
            0
        );

    EXPECT_EQ(
        players.size(),
        2
    );
}

TEST(GameInitializerTests, InitializeGameLoadsAllTerritories)
{
    GameInitializer initializer;

    std::string filename =
        getClassicMapPath();

    auto [map, players, deck] =
        initializer.initializeGame(
            filename,
            2,
            0
        );

    EXPECT_EQ(
        map.getTerritories().size(),
        42
    );
}

TEST(GameInitializerTests, InitializeGameDealsAllTerritories)
{
    GameInitializer initializer;

    std::string filename =
        getClassicMapPath();

    auto [map, players, deck] =
        initializer.initializeGame(
            filename,
            2,
            0
        );

    std::size_t totalTerritoriesHeld = 0;

    for (const Player& player : players)
    {
        totalTerritoriesHeld +=
            player.getTerritoriesHeld().size();
    }

    EXPECT_EQ(
        totalTerritoriesHeld,
        42
    );
}

TEST(GameInitializerTests, InitializeGameDealsTerritoriesEvenlyBetweenTwoPlayers)
{
    GameInitializer initializer;

    std::string filename =
        getClassicMapPath();

    auto [map, players, deck] =
        initializer.initializeGame(
            filename,
            2,
            0
        );

    ASSERT_EQ(
        players.size(),
        2
    );

    EXPECT_EQ(
        players[0].getTerritoriesHeld().size(),
        21
    );

    EXPECT_EQ(
        players[1].getTerritoriesHeld().size(),
        21
    );
}

TEST(GameInitializerTests, InitializeGamePlacesOneTroopOnEachTerritory)
{
    GameInitializer initializer;

    std::string filename =
        getClassicMapPath();

    auto [map, players, deck] =
        initializer.initializeGame(
            filename,
            2,
            0
        );

    for (const auto& territoryPair :
        map.getTerritories())
    {
        const Territory& territory =
            territoryPair.second;

        EXPECT_EQ(
            territory.getTroopCount(),
            1
        );
    }
}

TEST(GameInitializerTests, InitializeGameUpdatesPlayerTroopCounts)
{
    GameInitializer initializer;

    std::string filename =
        getClassicMapPath();

    auto [map, players, deck] =
        initializer.initializeGame(
            filename,
            2,
            0
        );

    ASSERT_EQ(
        players.size(),
        2
    );

    EXPECT_EQ(
        players[0].getTroopCount(),
        21
    );

    EXPECT_EQ(
        players[1].getTroopCount(),
        21
    );
}

TEST(GameInitializerTests, InitializeGameSynchronizesTerritoryOwnership)
{
    GameInitializer initializer;

    std::string filename =
        getClassicMapPath();

    auto [map, players, deck] =
        initializer.initializeGame(
            filename,
            2,
            0
        );

    for (const Player& player : players)
    {
        for (TerritoryID territoryID :
        player.getTerritoriesHeld())
        {
            EXPECT_EQ(
                map.getTerritory(
                    territoryID
                ).getOwnerID(),
                player.getPlayerID()
            );
        }
    }
}

TEST(GameInitializerTests, InitializeGameEveryTerritoryHasValidOwner)
{
    GameInitializer initializer;

    std::string filename =
        getClassicMapPath();

    auto [map, players, deck] =
        initializer.initializeGame(
            filename,
            2,
            0
        );

    for (const auto& territoryPair :
        map.getTerritories())
    {
        const Territory& territory =
            territoryPair.second;

        EXPECT_TRUE(
            territory.getOwnerID() == 0 ||
            territory.getOwnerID() == 1
        );
    }
}

//=========================================================
// Initial Troop Placement
//=========================================================

