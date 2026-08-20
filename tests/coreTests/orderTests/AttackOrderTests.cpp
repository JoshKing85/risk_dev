#include <gtest/gtest.h>

#include "risk/core/orders/AttackOrder.h"

using namespace risk;

// --------------------------------------------------
// Constructor Tests
// --------------------------------------------------

TEST(AttackOrderTests, StoresPlayerID)
{
    AttackOrder order(
        1,
        TerritoryID::Alaska,
        TerritoryID::Alberta,
        5,
        3
    );

    EXPECT_EQ(order.getPlayerID(), 1);
}

TEST(AttackOrderTests, StoresOrderType)
{
    AttackOrder order(
        1,
        TerritoryID::Alaska,
        TerritoryID::Alberta,
        5,
        3
    );

    EXPECT_EQ(order.getOrderType(), OrderType::Attack);
}

TEST(AttackOrderTests, StoresAttackingTerritory)
{
    AttackOrder order(
        1,
        TerritoryID::Alaska,
        TerritoryID::Alberta,
        5,
        3
    );

    EXPECT_EQ(
        order.getAttackingFrom(),
        TerritoryID::Alaska
    );
}

TEST(AttackOrderTests, StoresDefendingTerritory)
{
    AttackOrder order(
        1,
        TerritoryID::Alaska,
        TerritoryID::Alberta,
        5,
        3
    );

    EXPECT_EQ(
        order.getAttackingTo(),
        TerritoryID::Alberta
    );
}

TEST(AttackOrderTests, StoresAttackingTroopCount)
{
    AttackOrder order(
        1,
        TerritoryID::Alaska,
        TerritoryID::Alberta,
        5,
        3
    );

    EXPECT_EQ(order.getAttackingTroopCount(), 5);
}

TEST(AttackOrderTests, StoresDefendingTroopCount)
{
    AttackOrder order(
        1,
        TerritoryID::Alaska,
        TerritoryID::Alberta,
        5,
        3
    );

    EXPECT_EQ(order.getDefendingTroopCount(), 3);
}

// --------------------------------------------------
// Initial State Tests
// --------------------------------------------------

TEST(AttackOrderTests, StartsIncomplete)
{
    AttackOrder order(
        1,
        TerritoryID::Alaska,
        TerritoryID::Alberta,
        5,
        3
    );

    EXPECT_FALSE(order.isCompleted());
}

TEST(AttackOrderTests, ResultStartsWithDefaultValues)
{
    AttackOrder order(
        1,
        TerritoryID::Alaska,
        TerritoryID::Alberta,
        5,
        3
    );

    const AttackResult& result = order.getResult();

    EXPECT_EQ(result.attackerLosses, 0);
    EXPECT_EQ(result.defenderLosses, 0);
    EXPECT_EQ(result.attackingTroopCount, 0);
    EXPECT_EQ(result.defendingTroopCount, 0);
    EXPECT_EQ(
        result.attackOutcome,
        AttackOutcome::None
    );
}

// --------------------------------------------------
// Result Tests
// --------------------------------------------------

TEST(AttackOrderTests, SetResultStoresAttackResult)
{
    AttackOrder order(
        1,
        TerritoryID::Alaska,
        TerritoryID::Alberta,
        5,
        3
    );

    AttackResult result;
    result.attackerLosses = 2;
    result.defenderLosses = 3;
    result.attackingTroopCount = 3;
    result.defendingTroopCount = 0;
    result.attackOutcome = AttackOutcome::Captured;

    order.setResult(result);

    const AttackResult& storedResult = order.getResult();

    EXPECT_EQ(storedResult.attackerLosses, 2);
    EXPECT_EQ(storedResult.defenderLosses, 3);
    EXPECT_EQ(storedResult.attackingTroopCount, 3);
    EXPECT_EQ(storedResult.defendingTroopCount, 0);
    EXPECT_EQ(
        storedResult.attackOutcome,
        AttackOutcome::Captured
    );
}

TEST(AttackOrderTests, SetResultMarksOrderCompleted)
{
    AttackOrder order(
        1,
        TerritoryID::Alaska,
        TerritoryID::Alberta,
        5,
        3
    );

    AttackResult result;
    result.attackOutcome = AttackOutcome::DefenderGain;

    order.setResult(result);

    EXPECT_TRUE(order.isCompleted());
}