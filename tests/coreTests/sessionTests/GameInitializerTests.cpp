#include <gtest/gtest.h>

#include "risk/core/managers/GameStateManager.h"
#include "risk/core/session/GameInitializer.h"

#include "risk/entities/Player.h"
#include "risk/entities/Territory.h"

#include "risk/world/Deck.h"
#include "risk/world/Map.h"

#include "risk/utils/FilePathConverter.h"

#include <string>
#include <tuple>
#include <vector>

using namespace risk;

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
        mapTypeToFilename(MapType::Classic);

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
        mapTypeToFilename(MapType::Classic);

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

//=========================================================
// Deal Deck
//=========================================================

TEST(GameInitializerTests, DealDeckDealsAllTerritories)
{
    GameInitializer initializer;

    std::string filename =
        mapTypeToFilename(MapType::Classic);

    auto [map, players, deck] =
        initializer.initializeGame(
            filename,
            2,
            0
        );

    GameStateManager gameStateManager(
        map,
        players
    );

    initializer.dealDeck(
        deck,
        players,
        map,
        gameStateManager
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

TEST(GameInitializerTests, DealDeckDealsTerritoriesEvenlyBetweenTwoPlayers)
{
    GameInitializer initializer;

    std::string filename =
        mapTypeToFilename(MapType::Classic);

    auto [map, players, deck] =
        initializer.initializeGame(
            filename,
            2,
            0
        );

    GameStateManager gameStateManager(
        map,
        players
    );

    initializer.dealDeck(
        deck,
        players,
        map,
        gameStateManager
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

TEST(GameInitializerTests, DealDeckPlacesOneTroopOnEachTerritory)
{
    GameInitializer initializer;

    std::string filename =
        mapTypeToFilename(MapType::Classic);

    auto [map, players, deck] =
        initializer.initializeGame(
            filename,
            2,
            0
        );

    GameStateManager gameStateManager(
        map,
        players
    );

    initializer.dealDeck(
        deck,
        players,
        map,
        gameStateManager
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

TEST(GameInitializerTests, DealDeckUpdatesPlayerTroopCounts)
{
    GameInitializer initializer;

    std::string filename =
        mapTypeToFilename(MapType::Classic);

    auto [map, players, deck] =
        initializer.initializeGame(
            filename,
            2,
            0
        );

    GameStateManager gameStateManager(
        map,
        players
    );

    initializer.dealDeck(
        deck,
        players,
        map,
        gameStateManager
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

TEST(GameInitializerTests, DealDeckSynchronizesTerritoryOwnership)
{
    GameInitializer initializer;

    std::string filename =
        mapTypeToFilename(MapType::Classic);

    auto [map, players, deck] =
        initializer.initializeGame(
            filename,
            2,
            0
        );

    GameStateManager gameStateManager(
        map,
        players
    );

    initializer.dealDeck(
        deck,
        players,
        map,
        gameStateManager
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

TEST(GameInitializerTests, DealDeckEveryTerritoryHasValidOwner)
{
    GameInitializer initializer;

    std::string filename =
        mapTypeToFilename(MapType::Classic);

    auto [map, players, deck] =
        initializer.initializeGame(
            filename,
            2,
            0
        );

    GameStateManager gameStateManager(
        map,
        players
    );

    initializer.dealDeck(
        deck,
        players,
        map,
        gameStateManager
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