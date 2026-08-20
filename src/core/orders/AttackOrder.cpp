#include "risk/core/orders/AttackOrder.h"

namespace risk {

AttackOrder::AttackOrder(
    int playerID,
    TerritoryID attackingFrom,
    TerritoryID attackingTo,
    int attackingTroopCount,
    int defendingTroopCount
)
    : Order(playerID, OrderType::Attack),
      attackingFrom(attackingFrom),
      attackingTo(attackingTo),
      attackingTroopCount(attackingTroopCount),
      defendingTroopCount(defendingTroopCount)
{
}

TerritoryID AttackOrder::getAttackingFrom() const
{
    return attackingFrom;
}

TerritoryID AttackOrder::getAttackingTo() const
{
    return attackingTo;
}

int AttackOrder::getAttackingTroopCount() const
{
    return attackingTroopCount;
}

int AttackOrder::getDefendingTroopCount() const
{
    return defendingTroopCount;
}

const AttackResult& AttackOrder::getResult() const
{
    return result;
}

void AttackOrder::setResult(const AttackResult& result)
{
    this->result = result;
    markCompleted();
}

}