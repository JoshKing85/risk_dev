#include "risk/core/orders/Order.h"

namespace risk {

    Order::Order(int playerID, OrderType orderType)
        : playerID(playerID),
        orderType(orderType)
    {
    }

    int Order::getPlayerID() const
    {
        return playerID;
    }

    OrderType Order::getOrderType() const
    {
        return orderType;
    }

    bool Order::isCompleted() const
    {
        return completed;
    }
    void Order::complete()
    {
        markCompleted();
    }
    void Order::markCompleted()
    {
        completed = true;
    }

}