#include <gtest/gtest.h>

#include "risk/core/managers/GameStateManager.h"
#include "risk/core/managers/TroopManager.h"

#include "risk/core/orders/CashSetOrder.h"
#include "risk/core/orders/FortifyOrder.h"
#include "risk/core/orders/ReinforceOrder.h"

#include "risk/entities/Card.h"
#include "risk/entities/Player.h"
#include "risk/entities/Territory.h"

#include "risk/world/Map.h"

#include <vector>

using namespace risk;

// --------------------------------------------------
// Constructor / Initial State Tests
// --------------------------------------------------

TEST(TroopManagerTests, StartsWithEmptyOrderHistories)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    EXPECT_TRUE(
        troopManager.getReinforceOrders().empty()
    );

    EXPECT_TRUE(
        troopManager.getFortifyOrders().empty()
    );

    EXPECT_TRUE(
        troopManager.getCashSetOrders().empty()
    );
}

// --------------------------------------------------
// Reinforce Order Creation Tests
// --------------------------------------------------

TEST(TroopManagerTests, CreatesReinforceOrder)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createReinforceOrder(
        0,
        TerritoryID::Bearus,
        5
    );

    ASSERT_EQ(
        troopManager.getReinforceOrders().size(),
        1
    );

    const ReinforceOrder& order =
        troopManager.getLastReinforceOrder();

    EXPECT_EQ(order.getPlayerID(), 0);

    EXPECT_EQ(
        order.getTerritoryID(),
        TerritoryID::Bearus
    );

    EXPECT_EQ(
        order.getReinforceTroopCount(),
        5
    );

    EXPECT_FALSE(order.isCompleted());
}

// --------------------------------------------------
// Reinforce Execution Tests
// --------------------------------------------------

TEST(TroopManagerTests, ExecuteReinforceOrderAddsTroopsToTerritory)
{
    Map map;

    Territory alaska(
        TerritoryID::Bearus,
        ContinentID::NorthAmerica,
        {}
    );

    alaska.addTroops(3);

    map.addTerritory(alaska);

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createReinforceOrder(
        0,
        TerritoryID::Bearus,
        5
    );

    troopManager.executeReinforceOrder(gameStateManager);

    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::Bearus
        ).getTroopCount(),
        8
    );
}

TEST(TroopManagerTests, ExecuteReinforceOrderMarksOrderCompleted)
{
    Map map;

    Territory alaska(
        TerritoryID::Bearus,
        ContinentID::NorthAmerica,
        {}
    );

    map.addTerritory(alaska);

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createReinforceOrder(
        0,
        TerritoryID::Bearus,
        5
    );

    troopManager.executeReinforceOrder(gameStateManager);

    EXPECT_TRUE(
        troopManager
        .getLastReinforceOrder()
        .isCompleted()
    );
}

// --------------------------------------------------
// Reinforce Undo Tests
// --------------------------------------------------

TEST(TroopManagerTests, UndoReinforceOrderRemovesLatestPendingOrder)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createReinforceOrder(
        0,
        TerritoryID::Bearus,
        3
    );

    troopManager.undoReinforceOrder();

    EXPECT_TRUE(
        troopManager.getReinforceOrders().empty()
    );
}

TEST(TroopManagerTests, UndoReinforceOrderLeavesEarlierOrdersIntact)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createReinforceOrder(
        0,
        TerritoryID::Bearus,
        3
    );

    troopManager.createReinforceOrder(
        0,
        TerritoryID::Rockies,
        4
    );

    troopManager.undoReinforceOrder();

    ASSERT_EQ(
        troopManager.getReinforceOrders().size(),
        1
    );

    EXPECT_EQ(
        troopManager
        .getLastReinforceOrder()
        .getTerritoryID(),
        TerritoryID::Bearus
    );
}

// --------------------------------------------------
// Fortify Order Creation Tests
// --------------------------------------------------

TEST(TroopManagerTests, CreatesFortifyOrder)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createFortifyOrder(
        0,
        TerritoryID::Bearus,
        TerritoryID::Rockies,
        4
    );

    ASSERT_EQ(
        troopManager.getFortifyOrders().size(),
        1
    );

    const FortifyOrder& order =
        troopManager.getLastFortifyOrder();

    EXPECT_EQ(order.getPlayerID(), 0);

    EXPECT_EQ(
        order.getFromTerritory(),
        TerritoryID::Bearus
    );

    EXPECT_EQ(
        order.getToTerritory(),
        TerritoryID::Rockies
    );

    EXPECT_EQ(
        order.getFortifyTroopCount(),
        4
    );

    EXPECT_FALSE(order.isCompleted());
}

// --------------------------------------------------
// Fortify Execution Tests
// --------------------------------------------------

TEST(TroopManagerTests, ExecuteFortifyOrderMovesTroopsBetweenTerritories)
{
    Map map;

    Territory alaska(
        TerritoryID::Bearus,
        ContinentID::NorthAmerica,
        {}
    );

    Territory alberta(
        TerritoryID::Rockies,
        ContinentID::NorthAmerica,
        {}
    );

    alaska.addTroops(10);
    alberta.addTroops(2);

    map.addTerritory(alaska);
    map.addTerritory(alberta);

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createFortifyOrder(
        0,
        TerritoryID::Bearus,
        TerritoryID::Rockies,
        4
    );

    troopManager.executeFortifyOrder(gameStateManager);

    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::Bearus
        ).getTroopCount(),
        6
    );

    EXPECT_EQ(
        map.getTerritory(
            TerritoryID::Rockies
        ).getTroopCount(),
        6
    );
}

TEST(TroopManagerTests, ExecuteFortifyOrderDoesNotChangeCombinedTroopCount)
{
    Map map;

    Territory alaska(
        TerritoryID::Bearus,
        ContinentID::NorthAmerica,
        {}
    );

    Territory alberta(
        TerritoryID::Rockies,
        ContinentID::NorthAmerica,
        {}
    );

    alaska.addTroops(10);
    alberta.addTroops(2);

    map.addTerritory(alaska);
    map.addTerritory(alberta);

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    const int troopsBefore =
        map.getTerritory(
            TerritoryID::Bearus
        ).getTroopCount()
        +
        map.getTerritory(
            TerritoryID::Rockies
        ).getTroopCount();

    troopManager.createFortifyOrder(
        0,
        TerritoryID::Bearus,
        TerritoryID::Rockies,
        4
    );

    troopManager.executeFortifyOrder(gameStateManager);

    const int troopsAfter =
        map.getTerritory(
            TerritoryID::Bearus
        ).getTroopCount()
        +
        map.getTerritory(
            TerritoryID::Rockies
        ).getTroopCount();

    EXPECT_EQ(
        troopsAfter,
        troopsBefore
    );
}

TEST(TroopManagerTests, ExecuteFortifyOrderMarksOrderCompleted)
{
    Map map;

    Territory alaska(
        TerritoryID::Bearus,
        ContinentID::NorthAmerica,
        {}
    );

    Territory alberta(
        TerritoryID::Rockies,
        ContinentID::NorthAmerica,
        {}
    );

    alaska.addTroops(5);

    map.addTerritory(alaska);
    map.addTerritory(alberta);

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createFortifyOrder(
        0,
        TerritoryID::Bearus,
        TerritoryID::Rockies,
        2
    );

    troopManager.executeFortifyOrder(gameStateManager);

    EXPECT_TRUE(
        troopManager
        .getLastFortifyOrder()
        .isCompleted()
    );
}

// --------------------------------------------------
// Fortify Undo Tests
// --------------------------------------------------

TEST(TroopManagerTests, UndoFortifyOrderRemovesLatestPendingOrder)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createFortifyOrder(
        0,
        TerritoryID::Bearus,
        TerritoryID::Rockies,
        3
    );

    troopManager.undoFortifyOrder();

    EXPECT_TRUE(
        troopManager.getFortifyOrders().empty()
    );
}

// --------------------------------------------------
// Cash Set Creation Tests
// --------------------------------------------------

TEST(TroopManagerTests, CreatesCashSetOrder)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    std::vector<Card> cards
    {
        Card(
            CardType::Infantry,
            TerritoryID::Bearus,
            ContinentID::NorthAmerica
        ),
        Card(
            CardType::Infantry,
            TerritoryID::Amazonia,
            ContinentID::SouthAmerica
        ),
        Card(
            CardType::Infantry,
            TerritoryID::Nilelands,
            ContinentID::Africa
        )
    };

    troopManager.createCashSetOrder(
        0,
        SetType::InfantrySet,
        cards
    );

    ASSERT_EQ(
        troopManager.getCashSetOrders().size(),
        1
    );

    const CashSetOrder& order =
        troopManager.getLastCashSetOrder();

    EXPECT_EQ(order.getPlayerID(), 0);

    EXPECT_EQ(
        order.getCards().size(),
        3
    );

    EXPECT_FALSE(order.isCompleted());
}

// --------------------------------------------------
// Cash Set Execution Tests
// --------------------------------------------------

TEST(TroopManagerTests, ExecuteCashSetOrderRemovesCashedCardsFromPlayer)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    std::vector<Card> playerCards
    {
        Card(
            CardType::Infantry,
            TerritoryID::Bearus,
            ContinentID::NorthAmerica
        ),
        Card(
            CardType::Infantry,
            TerritoryID::Amazonia,
            ContinentID::SouthAmerica
        ),
        Card(
            CardType::Infantry,
            TerritoryID::Nilelands,
            ContinentID::Africa
        ),
        Card(
            CardType::Cavalry,
            TerritoryID::Induslands,
            ContinentID::Asia
        )
    };

    players[0].setPlayerSet(playerCards);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    std::vector<Card> cardsToCash
    {
        playerCards[0],
        playerCards[1],
        playerCards[2]
    };

    troopManager.createCashSetOrder(
        0,
        SetType::InfantrySet,
        cardsToCash
    );

    troopManager.executeCashSetOrder(
        players[0],
        gameStateManager);

    const std::vector<Card>& remainingCards =
        players[0].getPlayerSet();

    ASSERT_EQ(
        remainingCards.size(),
        1
    );

    EXPECT_EQ(
        remainingCards[0].getCardType(),
        CardType::Cavalry
    );

    EXPECT_EQ(
        remainingCards[0].getTerritoryID(),
        TerritoryID::Induslands
    );
}


TEST(TroopManagerTests, ExecuteCashSetOrderReturnsSetValue)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    std::vector<Card> cards
    {
        Card(
            CardType::Cavalry,
            TerritoryID::Bearus,
            ContinentID::NorthAmerica
        ),
        Card(
            CardType::Cavalry,
            TerritoryID::Amazonia,
            ContinentID::SouthAmerica
        ),
        Card(
            CardType::Cavalry,
            TerritoryID::Nilelands,
            ContinentID::Africa
        )
    };

    players[0].setPlayerSet(cards);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createCashSetOrder(
        0,
        SetType::CavalrySet,
        cards
    );

    const int expectedValue =
        troopManager
        .getLastCashSetOrder()
        .getSetValue();

    const int returnedValue =
        troopManager.executeCashSetOrder(
            players[0],
            gameStateManager);

    EXPECT_EQ(
        returnedValue,
        expectedValue
    );
}

TEST(TroopManagerTests, ExecuteCashSetOrderMarksOrderCompleted)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    std::vector<Card> cards
    {
        Card(
            CardType::Artillery,
            TerritoryID::Bearus,
            ContinentID::NorthAmerica
        ),
        Card(
            CardType::Artillery,
            TerritoryID::Amazonia,
            ContinentID::SouthAmerica
        ),
        Card(
            CardType::Artillery,
            TerritoryID::Nilelands,
            ContinentID::Africa
        )
    };

    players[0].setPlayerSet(cards);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createCashSetOrder(
        0,
        SetType::ArtillerySet,
        cards
    );

    troopManager.executeCashSetOrder(
        players[0],
        gameStateManager);

    EXPECT_TRUE(
        troopManager
        .getLastCashSetOrder()
        .isCompleted()
    );
}

// --------------------------------------------------
// Cash Set Undo Tests
// --------------------------------------------------

TEST(TroopManagerTests, UndoCashSetOrderRemovesLatestPendingOrder)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    std::vector<Card> cards
    {
        Card(CardType::Wild),
        Card(CardType::Wild),
        Card(CardType::Wild)
    };

    troopManager.createCashSetOrder(
        0,
        SetType::MixedSet,
        cards
    );

    troopManager.undoCashSetOrder();

    EXPECT_TRUE(
        troopManager.getCashSetOrders().empty()
    );
}

// --------------------------------------------------
// History Tests
// --------------------------------------------------

TEST(TroopManagerTests, OrderGettersReturnCompleteHistories)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createReinforceOrder(
        0,
        TerritoryID::Bearus,
        3
    );

    troopManager.createReinforceOrder(
        0,
        TerritoryID::Rockies,
        4
    );

    troopManager.createFortifyOrder(
        0,
        TerritoryID::Bearus,
        TerritoryID::Rockies,
        2
    );

    std::vector<Card> cards
    {
        Card(CardType::Wild),
        Card(CardType::Wild),
        Card(CardType::Wild)
    };

    troopManager.createCashSetOrder(
        0,
        SetType::MixedSet,
        cards
    );

    EXPECT_EQ(
        troopManager.getReinforceOrders().size(),
        2
    );

    EXPECT_EQ(
        troopManager.getFortifyOrders().size(),
        1
    );

    EXPECT_EQ(
        troopManager.getCashSetOrders().size(),
        1
    );
}

// --------------------------------------------------
// Getter Tests
// --------------------------------------------------

TEST(TroopManagerTests, GetReinforceOrdersReturnsCompleteHistory)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createReinforceOrder(
        0,
        TerritoryID::Bearus,
        3
    );

    troopManager.createReinforceOrder(
        0,
        TerritoryID::Rockies,
        5
    );

    const std::vector<ReinforceOrder>& orders =
        troopManager.getReinforceOrders();

    ASSERT_EQ(
        orders.size(),
        2
    );

    EXPECT_EQ(
        orders[0].getTerritoryID(),
        TerritoryID::Bearus
    );

    EXPECT_EQ(
        orders[1].getTerritoryID(),
        TerritoryID::Rockies
    );
}

TEST(TroopManagerTests, GetFortifyOrdersReturnsCompleteHistory)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createFortifyOrder(
        0,
        TerritoryID::Bearus,
        TerritoryID::Rockies,
        2
    );

    troopManager.createFortifyOrder(
        0,
        TerritoryID::Rockies,
        TerritoryID::Tairono,
        3
    );

    const std::vector<FortifyOrder>& orders =
        troopManager.getFortifyOrders();

    ASSERT_EQ(
        orders.size(),
        2
    );

    EXPECT_EQ(
        orders[0].getFromTerritory(),
        TerritoryID::Bearus
    );

    EXPECT_EQ(
        orders[1].getFromTerritory(),
        TerritoryID::Rockies
    );
}

TEST(TroopManagerTests, GetCashSetOrdersReturnsCompleteHistory)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    std::vector<Card> firstSet
    {
        Card(CardType::Infantry),
        Card(CardType::Infantry),
        Card(CardType::Infantry)
    };

    std::vector<Card> secondSet
    {
        Card(CardType::Cavalry),
        Card(CardType::Cavalry),
        Card(CardType::Cavalry)
    };

    troopManager.createCashSetOrder(
        0,
        SetType::InfantrySet,
        firstSet
    );

    troopManager.createCashSetOrder(
        0,
        SetType::CavalrySet,
        secondSet
    );

    const std::vector<CashSetOrder>& orders =
        troopManager.getCashSetOrders();

    ASSERT_EQ(
        orders.size(),
        2
    );

    EXPECT_EQ(
        orders[0].getCards().size(),
        3
    );

    EXPECT_EQ(
        orders[1].getCards().size(),
        3
    );
}

TEST(TroopManagerTests, GetLastReinforceOrderReturnsNewestOrder)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createReinforceOrder(
        0,
        TerritoryID::Bearus,
        3
    );

    troopManager.createReinforceOrder(
        0,
        TerritoryID::Tairono,
        6
    );

    const ReinforceOrder& order =
        troopManager.getLastReinforceOrder();

    EXPECT_EQ(
        order.getTerritoryID(),
        TerritoryID::Tairono
    );

    EXPECT_EQ(
        order.getReinforceTroopCount(),
        6
    );
}

TEST(TroopManagerTests, GetLastFortifyOrderReturnsNewestOrder)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    troopManager.createFortifyOrder(
        0,
        TerritoryID::Bearus,
        TerritoryID::Rockies,
        2
    );

    troopManager.createFortifyOrder(
        0,
        TerritoryID::Tairono,
        TerritoryID::StLawrence,
        4
    );

    const FortifyOrder& order =
        troopManager.getLastFortifyOrder();

    EXPECT_EQ(
        order.getFromTerritory(),
        TerritoryID::Tairono
    );

    EXPECT_EQ(
        order.getToTerritory(),
        TerritoryID::StLawrence
    );

    EXPECT_EQ(
        order.getFortifyTroopCount(),
        4
    );
}

TEST(TroopManagerTests, GetLastCashSetOrderReturnsNewestOrder)
{
    Map map;

    std::vector<Player> players;
    players.emplace_back(0);

    GameStateManager gameStateManager(
        map,
        players
    );

    TroopManager troopManager;

    std::vector<Card> firstSet
    {
        Card(CardType::Infantry),
        Card(CardType::Infantry),
        Card(CardType::Infantry)
    };

    std::vector<Card> secondSet
    {
        Card(CardType::Artillery),
        Card(CardType::Artillery),
        Card(CardType::Artillery)
    };

    troopManager.createCashSetOrder(
        0,
        SetType::InfantrySet,
        firstSet
    );

    troopManager.createCashSetOrder(
        0,
        SetType::ArtillerySet,
        secondSet
    );

    const CashSetOrder& order =
        troopManager.getLastCashSetOrder();

    ASSERT_EQ(
        order.getCards().size(),
        3
    );

    EXPECT_EQ(
        order.getCards()[0].getCardType(),
        CardType::Artillery
    );
}