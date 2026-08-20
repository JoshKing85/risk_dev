#pragma once

#include "risk/core/orders/Order.h"
#include "risk/enums.h"

#include <vector>

namespace risk {

class RollDiceOrder : public Order {
private:
  int numberAttackerDice;
  int numberDefenderDice;

  std::vector<int> attackingDice;
  std::vector<int> defendingDice;

  std::vector<int> generateDice(int numberOfDice);

public:
  RollDiceOrder(int playerID, int numberAttackerDice, int numberDefenderDice);

  RollDiceOrder(int playerID, const std::vector<int> &attackingDice,
                const std::vector<int> &defendingDice);

  const std::vector<int> &getAttackingDice() const;
  const std::vector<int> &getDefendingDice() const;
};

} // namespace risk