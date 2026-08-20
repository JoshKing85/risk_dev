#include <gtest/gtest.h>

#include "risk/core/orders/RollDiceOrder.h"

using namespace risk;

// --------------------------------------------------
// Constructor Tests
// --------------------------------------------------

TEST(RollDiceOrderTests, StoresPlayerID)
{
    RollDiceOrder order(1, 3, 2);

    EXPECT_EQ(order.getPlayerID(), 1);
}

TEST(RollDiceOrderTests, StoresOrderType)
{
    RollDiceOrder order(1, 3, 2);

    EXPECT_EQ(order.getOrderType(), OrderType::RollDice);
}

TEST(RollDiceOrderTests, StartsIncomplete)
{
    RollDiceOrder order(1, 3, 2);

    EXPECT_FALSE(order.isCompleted());
}

// --------------------------------------------------
// Dice Generation Tests
// --------------------------------------------------

TEST(RollDiceOrderTests, GeneratesCorrectNumberOfAttackingDice)
{
    RollDiceOrder order(1, 3, 2);

    EXPECT_EQ(order.getAttackingDice().size(), 3);
}

TEST(RollDiceOrderTests, GeneratesCorrectNumberOfDefendingDice)
{
    RollDiceOrder order(1, 3, 2);

    EXPECT_EQ(order.getDefendingDice().size(), 2);
}

TEST(RollDiceOrderTests, AttackingDiceValuesAreValid)
{
    RollDiceOrder order(1, 3, 2);

    for (int die : order.getAttackingDice())
    {
        EXPECT_GE(die, 1);
        EXPECT_LE(die, 6);
    }
}

TEST(RollDiceOrderTests, DefendingDiceValuesAreValid)
{
    RollDiceOrder order(1, 3, 2);

    for (int die : order.getDefendingDice())
    {
        EXPECT_GE(die, 1);
        EXPECT_LE(die, 6);
    }
}

TEST(RollDiceOrderTests, CanGenerateZeroDice)
{
    RollDiceOrder order(1, 0, 0);

    EXPECT_TRUE(order.getAttackingDice().empty());
    EXPECT_TRUE(order.getDefendingDice().empty());
}