#pragma once

#include "risk/core/orders/Order.h"
#include "risk/enums.h"

namespace risk {

struct AttackResult {
  int attackerLosses = 0;
  int defenderLosses = 0;

  int attackingTroopCount = 0;
  int defendingTroopCount = 0;

  AttackOutcome attackOutcome = AttackOutcome::None;
};

class AttackOrder : public Order {
private:
  TerritoryID attackingFrom;
  TerritoryID attackingTo;

  int attackingTroopCount;
  int defendingTroopCount;

  AttackResult result;

public:
  AttackOrder(int playerID, TerritoryID attackingFrom, TerritoryID attackingTo,
              int attackingTroopCount, int defendingTroopCount);

  TerritoryID getAttackingFrom() const;
  TerritoryID getAttackingTo() const;

  int getAttackingTroopCount() const;
  int getDefendingTroopCount() const;

  const AttackResult &getResult() const;

  void setResult(const AttackResult &result);
};

} // namespace risk