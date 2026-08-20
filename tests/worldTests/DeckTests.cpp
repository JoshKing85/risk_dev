#include <gtest/gtest.h>

#include "risk/world/Deck.h"

namespace risk {

    TEST(DeckTests, ThrowsWhenDrawingFromEmptyDeck)
    {
        Deck deck;

        EXPECT_THROW(
            deck.getNextCard(),
            std::runtime_error
        );
    }

    TEST(DeckTests, ReturnsFirstCard)
    {
        Deck deck;

        std::vector<Card> cards{
            Card(CardType::Infantry),
            Card(CardType::Cavalry),
            Card(CardType::Artillery)
        };

        deck.addDeck(cards);

        EXPECT_EQ(
            deck.getNextCard().getCardType(),
            CardType::Infantry
        );
    }

    TEST(DeckTests, ReturnsCardsInOrder)
    {
        Deck deck;

        std::vector<Card> cards{
            Card(CardType::Infantry),
            Card(CardType::Cavalry),
            Card(CardType::Artillery)
        };

        deck.addDeck(cards);

        EXPECT_EQ(deck.getNextCard().getCardType(), CardType::Infantry);
        EXPECT_EQ(deck.getNextCard().getCardType(), CardType::Cavalry);
        EXPECT_EQ(deck.getNextCard().getCardType(), CardType::Artillery);
    }

    TEST(DeckTests, CyclesBackToFirstCard)
    {
        Deck deck;

        std::vector<Card> cards{
            Card(CardType::Infantry),
            Card(CardType::Cavalry)
        };

        deck.addDeck(cards);

        EXPECT_EQ(deck.getNextCard().getCardType(), CardType::Infantry);
        EXPECT_EQ(deck.getNextCard().getCardType(), CardType::Cavalry);
        EXPECT_EQ(deck.getNextCard().getCardType(), CardType::Infantry);
    }

    TEST(DeckTests, AddingNewDeckResetsDrawPosition)
    {
        Deck deck;

        std::vector<Card> firstDeck{
            Card(CardType::Infantry),
            Card(CardType::Cavalry)
        };

        deck.addDeck(firstDeck);

        deck.getNextCard();

        std::vector<Card> secondDeck{
            Card(CardType::Artillery),
            Card(CardType::Wild)
        };

        deck.addDeck(secondDeck);

        EXPECT_EQ(
            deck.getNextCard().getCardType(),
            CardType::Artillery
        );
    }

    TEST(DeckTests, ReturnedCardCanBeModified)
    {
        Deck deck;

        std::vector<Card> cards{
            Card(CardType::Infantry)
        };

        deck.addDeck(cards);

        Card& card = deck.getNextCard();

        EXPECT_EQ(card.getCardType(), CardType::Infantry);
    }

}