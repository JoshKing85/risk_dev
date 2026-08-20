#include "risk/core/orders/CashSetOrder.h"

namespace risk {

    CashSetOrder::CashSetOrder(
        int playerID,
        SetType setType,
        std::vector<Card> cards
    )
        : Order(playerID, OrderType::CashSet),
        setType(setType),
        cards(std::move(cards)),
        setValue(calculateSetValue(setType))
    {
    }

    const std::vector<Card>& CashSetOrder::getCards() const
    {
        return cards;
    }

    int CashSetOrder::getSetValue() const
    {
        return setValue;
    }

    int CashSetOrder::calculateSetValue(SetType setType)
    {
        switch (setType)
        {
        case SetType::InfantrySet:
            return 8;

        case SetType::CavalrySet:
            return 10;

        case SetType::ArtillerySet:
            return 12;

        case SetType::MixedSet:
            return 14;

        default:
            return 0;
        }
    }

}