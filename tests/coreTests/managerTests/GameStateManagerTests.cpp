#include <gtest/gtest.h>

#include "risk/core/managers/GameStateManager.h"
#include "risk/entities/Card.h"
#include "risk/entities/Player.h"
#include "risk/entities/Territory.h"
#include "risk/world/Continent.h"
#include "risk/world/Map.h"

#include <algorithm>
#include <vector>

using namespace risk;

namespace {

    bool containsTerritory(
        const Player& player,
        TerritoryID territoryID
    )
    {
        const std::vector<TerritoryID>& territories =
            player.getTerritoriesHeld();

        return std::find(
            territories.begin(),
            territories.end(),
            territoryID
        ) != territories.end();
    }

    bool containsContinent(
        const Player& player,
        ContinentID continentID
    )
    {
        const std::vector<ContinentID>& continents =
            player.getContinentsOwned();

        return std::find(
            continents.begin(),
            continents.end(),
            continentID
        ) != continents.end();
    }

} // namespace

// --------------------------------------------------
// Territory Troop Tests
// --------------------------------------------------

TEST(GameStateManagerTests, UpdatesTerritoryTroopCountWhenIncreasing)
{
    Map map;

    Territory alaska(
        TerritoryID::Alaska,
        ContinentID::NorthAmerica,
        {}
    );

    map.addTerritory(alaska);

    std::vector<Player> players;

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updateTerritoryTroopCount(
        TerritoryID::Alaska,
        5
    );

    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::Alaska
        ).getTroopCount(),
        5
    );
}

TEST(GameStateManagerTests, UpdatesTerritoryTroopCountWhenDecreasing)
{
    Map map;

    Territory alaska(
        TerritoryID::Alaska,
        ContinentID::NorthAmerica,
        {}
    );

    alaska.addTroops(5);

    map.addTerritory(alaska);

    std::vector<Player> players;

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updateTerritoryTroopCount(
        TerritoryID::Alaska,
        -3
    );

    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::Alaska
        ).getTroopCount(),
        2
    );
}

// --------------------------------------------------
// Player Territory Tests
// --------------------------------------------------

TEST(GameStateManagerTests, AddsTerritoryToPlayer)
{
    Map map;

    Territory alaska(
        TerritoryID::Alaska,
        ContinentID::NorthAmerica,
        {}
    );

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updatePlayerTerritories(
        0,
        alaska,
        true
    );

    EXPECT_TRUE(
        containsTerritory(
            players[0],
            TerritoryID::Alaska
        )
    );
}

TEST(GameStateManagerTests, RemovesTerritoryFromPlayer)
{
    Map map;

    Territory alaska(
        TerritoryID::Alaska,
        ContinentID::NorthAmerica,
        {}
    );

    std::vector<Player> players;
    players.emplace_back(0);

    players[0].addTerritory(
        TerritoryID::Alaska
    );

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updatePlayerTerritories(
        0,
        alaska,
        false
    );

    EXPECT_FALSE(
        containsTerritory(
            players[0],
            TerritoryID::Alaska
        )
    );
}

// --------------------------------------------------
// Territory Ownership Tests
// --------------------------------------------------

TEST(GameStateManagerTests, TransfersTerritoryBetweenPlayers)
{
    Map map;

    Continent northAmerica(
        ContinentID::NorthAmerica,
        5,
        {
            TerritoryID::Alaska,
            TerritoryID::Alberta,
            TerritoryID::Ontario
        },
        {
            TerritoryID::Alaska
        }
    );

    Territory alaska(
        TerritoryID::Alaska,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Alberta
        }
    );

    Territory alberta(
        TerritoryID::Alberta,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Alaska,
            TerritoryID::Ontario
        }
    );

    Territory ontario(
        TerritoryID::Ontario,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Alberta
        }
    );

    alaska.setOwner(0);
    alberta.setOwner(1);
    ontario.setOwner(0);

    map.addContinent(northAmerica);
    map.addTerritory(alaska);
    map.addTerritory(alberta);
    map.addTerritory(ontario);

    std::vector<Player> players;
    players.emplace_back(0);
    players.emplace_back(1);

    players[0].addTerritory(
        TerritoryID::Alaska
    );

    players[0].addTerritory(
        TerritoryID::Ontario
    );

    players[1].addTerritory(
        TerritoryID::Alberta
    );

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updateTerritoryOwner(
        TerritoryID::Alaska,
        1
    );

    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::Alaska
        ).getOwnerID(),
        1
    );

    EXPECT_FALSE(
        containsTerritory(
            players[0],
            TerritoryID::Alaska
        )
    );

    EXPECT_TRUE(
        containsTerritory(
            players[1],
            TerritoryID::Alaska
        )
    );
}

TEST(GameStateManagerTests, TerritoryTransferGrantsContinentOwnership)
{
    Map map;

    Continent northAmerica(
        ContinentID::NorthAmerica,
        5,
        {
            TerritoryID::Alaska,
            TerritoryID::Alberta
        },
        {
            TerritoryID::Alaska
        }
    );

    Territory alaska(
        TerritoryID::Alaska,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Alberta
        }
    );

    Territory alberta(
        TerritoryID::Alberta,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Alaska
        }
    );

    alaska.setOwner(0);
    alberta.setOwner(1);

    map.addContinent(northAmerica);
    map.addTerritory(alaska);
    map.addTerritory(alberta);

    std::vector<Player> players;
    players.emplace_back(0);
    players.emplace_back(1);

    players[0].addTerritory(
        TerritoryID::Alaska
    );

    players[1].addTerritory(
        TerritoryID::Alberta
    );

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updateTerritoryOwner(
        TerritoryID::Alaska,
        1
    );

    EXPECT_EQ(
        map.getContinent(
            ContinentID::NorthAmerica
        ).getOwnerID(),
        1
    );

    EXPECT_TRUE(
        containsContinent(
            players[1],
            ContinentID::NorthAmerica
        )
    );
}

TEST(GameStateManagerTests, TerritoryTransferRemovesContinentOwnership)
{
    Map map;

    Continent northAmerica(
        ContinentID::NorthAmerica,
        5,
        {
            TerritoryID::Alaska,
            TerritoryID::Alberta
        },
        {
            TerritoryID::Alaska
        }
    );

    northAmerica.setOwner(0);

    Territory alaska(
        TerritoryID::Alaska,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Alberta
        }
    );

    Territory alberta(
        TerritoryID::Alberta,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Alaska
        }
    );

    alaska.setOwner(0);
    alberta.setOwner(0);

    map.addContinent(northAmerica);
    map.addTerritory(alaska);
    map.addTerritory(alberta);

    std::vector<Player> players;
    players.emplace_back(0);
    players.emplace_back(1);

    players[0].addTerritory(
        TerritoryID::Alaska
    );

    players[0].addTerritory(
        TerritoryID::Alberta
    );

    players[0].addContinent(
        ContinentID::NorthAmerica
    );

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updateTerritoryOwner(
        TerritoryID::Alaska,
        1
    );

    EXPECT_EQ(
        map.getContinent(
            ContinentID::NorthAmerica
        ).getOwnerID(),
        -1
    );

    EXPECT_FALSE(
        containsContinent(
            players[0],
            ContinentID::NorthAmerica
        )
    );
}

// --------------------------------------------------
// Continent Ownership Check Tests
// --------------------------------------------------

TEST(GameStateManagerTests, ReturnsContinentWhenPlayerOwnsAllTerritories)
{
    Map map;

    Continent northAmerica(
        ContinentID::NorthAmerica,
        5,
        {
            TerritoryID::Alaska,
            TerritoryID::Alberta
        },
        {
            TerritoryID::Alaska
        }
    );

    Territory alaska(
        TerritoryID::Alaska,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Alberta
        }
    );

    Territory alberta(
        TerritoryID::Alberta,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Alaska
        }
    );

    alaska.setOwner(0);
    alberta.setOwner(0);

    map.addContinent(northAmerica);
    map.addTerritory(alaska);
    map.addTerritory(alberta);

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    EXPECT_EQ(
        gameStateManager.checkContinentOwnership(
            0,
            ContinentID::NorthAmerica
        ),
        ContinentID::NorthAmerica
    );
}

TEST(GameStateManagerTests, ReturnsNoneWhenPlayerDoesNotOwnAllTerritories)
{
    Map map;

    Continent northAmerica(
        ContinentID::NorthAmerica,
        5,
        {
            TerritoryID::Alaska,
            TerritoryID::Alberta
        },
        {
            TerritoryID::Alaska
        }
    );

    Territory alaska(
        TerritoryID::Alaska,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Alberta
        }
    );

    Territory alberta(
        TerritoryID::Alberta,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Alaska
        }
    );

    alaska.setOwner(0);
    alberta.setOwner(1);

    map.addContinent(northAmerica);
    map.addTerritory(alaska);
    map.addTerritory(alberta);

    std::vector<Player> players;
    players.emplace_back(0);
    players.emplace_back(1);

    GameStateManager gameStateManager(
        map,
        players
    );

    EXPECT_EQ(
        gameStateManager.checkContinentOwnership(
            0,
            ContinentID::NorthAmerica
        ),
        ContinentID::None
    );
}

// --------------------------------------------------
// Continent Update Tests
// --------------------------------------------------

TEST(GameStateManagerTests, TransfersContinentBetweenPlayers)
{
    Map map;

    Continent northAmerica(
        ContinentID::NorthAmerica,
        5,
        {},
        {}
    );

    northAmerica.setOwner(0);

    map.addContinent(northAmerica);

    std::vector<Player> players;
    players.emplace_back(0);
    players.emplace_back(1);

    players[0].addContinent(
        ContinentID::NorthAmerica
    );

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updateContinentOwner(
        ContinentID::NorthAmerica,
        1
    );

    EXPECT_EQ(
        map.getContinent(
            ContinentID::NorthAmerica
        ).getOwnerID(),
        1
    );

    EXPECT_FALSE(
        containsContinent(
            players[0],
            ContinentID::NorthAmerica
        )
    );

    EXPECT_TRUE(
        containsContinent(
            players[1],
            ContinentID::NorthAmerica
        )
    );
}

// --------------------------------------------------
// Player Continent Tests
// --------------------------------------------------

TEST(GameStateManagerTests, AddsContinentToPlayer)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updatePlayerContinentOwnership(
        0,
        ContinentID::NorthAmerica,
        true
    );

    EXPECT_TRUE(
        containsContinent(
            players[0],
            ContinentID::NorthAmerica
        )
    );
}

TEST(GameStateManagerTests, RemovesContinentFromPlayer)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    players[0].addContinent(
        ContinentID::NorthAmerica
    );

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updatePlayerContinentOwnership(
        0,
        ContinentID::NorthAmerica,
        false
    );

    EXPECT_FALSE(
        containsContinent(
            players[0],
            ContinentID::NorthAmerica
        )
    );
}

// --------------------------------------------------
// Player Troop Tests
// --------------------------------------------------

TEST(GameStateManagerTests, UpdatesPlayerTroopCountWhenIncreasing)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updatePlayerTroopCount(
        0,
        10
    );

    EXPECT_EQ(
        players[0].getTroopCount(),
        10
    );
}

TEST(GameStateManagerTests, UpdatesPlayerTroopCountWhenDecreasing)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    players[0].addTroops(10);

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updatePlayerTroopCount(
        0,
        -6
    );

    EXPECT_EQ(
        players[0].getTroopCount(),
        4
    );
}

// --------------------------------------------------
// Player Set Tests
// --------------------------------------------------

TEST(GameStateManagerTests, UpdatesPlayerSet)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    std::vector<Card> newSet{
        Card(
            CardType::Infantry,
            TerritoryID::Alaska,
            ContinentID::NorthAmerica
        ),
        Card(
            CardType::Cavalry,
            TerritoryID::Brazil,
            ContinentID::SouthAmerica
        ),
        Card(
            CardType::Artillery,
            TerritoryID::Egypt,
            ContinentID::Africa
        )
    };

    GameStateManager gameStateManager(
        map,
        players
    );

    gameStateManager.updatePlayerSet(
        0,
        newSet
    );

    const std::vector<Card>& playerSet =
        players[0].getPlayerSet();

    ASSERT_EQ(
        playerSet.size(),
        3
    );

    EXPECT_EQ(
        playerSet[0].getCardType(),
        CardType::Infantry
    );

    EXPECT_EQ(
        playerSet[0].getTerritoryID(),
        TerritoryID::Alaska
    );

    EXPECT_EQ(
        playerSet[1].getCardType(),
        CardType::Cavalry
    );

    EXPECT_EQ(
        playerSet[1].getTerritoryID(),
        TerritoryID::Brazil
    );

    EXPECT_EQ(
        playerSet[2].getCardType(),
        CardType::Artillery
    );

    EXPECT_EQ(
        playerSet[2].getTerritoryID(),
        TerritoryID::Egypt
    );
}