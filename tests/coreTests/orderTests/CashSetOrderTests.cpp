#include <gtest/gtest.h>

#include "risk/core/orders/CashSetOrder.h"

using namespace risk;

// --------------------------------------------------
// Constructor Tests
// --------------------------------------------------

TEST(CashSetOrderTests, StoresPlayerID)
{
    std::vector<Card> cards{
        Card(CardType::Infantry),
        Card(CardType::Infantry),
        Card(CardType::Infantry)
    };

    CashSetOrder order(
        1,
        SetType::InfantrySet,
        cards
    );

    EXPECT_EQ(order.getPlayerID(), 1);
}

TEST(CashSetOrderTests, StoresOrderType)
{
    std::vector<Card> cards{
        Card(CardType::Infantry),
        Card(CardType::Infantry),
        Card(CardType::Infantry)
    };

    CashSetOrder order(
        1,
        SetType::InfantrySet,
        cards
    );

    EXPECT_EQ(order.getOrderType(), OrderType::CashSet);
}

TEST(CashSetOrderTests, StartsIncomplete)
{
    std::vector<Card> cards{
        Card(CardType::Infantry),
        Card(CardType::Infantry),
        Card(CardType::Infantry)
    };

    CashSetOrder order(
        1,
        SetType::InfantrySet,
        cards
    );

    EXPECT_FALSE(order.isCompleted());
}

// --------------------------------------------------
// Card Storage Tests
// --------------------------------------------------

TEST(CashSetOrderTests, StoresCards)
{
    std::vector<Card> cards{
        Card(CardType::Infantry),
        Card(CardType::Cavalry),
        Card(CardType::Artillery)
    };

    CashSetOrder order(
        1,
        SetType::MixedSet,
        cards
    );

    const std::vector<Card>& storedCards = order.getCards();

    ASSERT_EQ(storedCards.size(), 3);

    EXPECT_EQ(
        storedCards[0].getCardType(),
        CardType::Infantry
    );

    EXPECT_EQ(
        storedCards[1].getCardType(),
        CardType::Cavalry
    );

    EXPECT_EQ(
        storedCards[2].getCardType(),
        CardType::Artillery
    );
}

// --------------------------------------------------
// Set Value Tests
// --------------------------------------------------

TEST(CashSetOrderTests, InfantrySetHasValueEight)
{
    std::vector<Card> cards{
        Card(CardType::Infantry),
        Card(CardType::Infantry),
        Card(CardType::Infantry)
    };

    CashSetOrder order(
        1,
        SetType::InfantrySet,
        cards
    );

    EXPECT_EQ(order.getSetValue(), 8);
}

TEST(CashSetOrderTests, CavalrySetHasValueTen)
{
    std::vector<Card> cards{
        Card(CardType::Cavalry),
        Card(CardType::Cavalry),
        Card(CardType::Cavalry)
    };

    CashSetOrder order(
        1,
        SetType::CavalrySet,
        cards
    );

    EXPECT_EQ(order.getSetValue(), 10);
}

TEST(CashSetOrderTests, ArtillerySetHasValueTwelve)
{
    std::vector<Card> cards{
        Card(CardType::Artillery),
        Card(CardType::Artillery),
        Card(CardType::Artillery)
    };

    CashSetOrder order(
        1,
        SetType::ArtillerySet,
        cards
    );

    EXPECT_EQ(order.getSetValue(), 12);
}

TEST(CashSetOrderTests, MixedSetHasValueFourteen)
{
    std::vector<Card> cards{
        Card(CardType::Infantry),
        Card(CardType::Cavalry),
        Card(CardType::Artillery)
    };

    CashSetOrder order(
        1,
        SetType::MixedSet,
        cards
    );

    EXPECT_EQ(order.getSetValue(), 14);
}