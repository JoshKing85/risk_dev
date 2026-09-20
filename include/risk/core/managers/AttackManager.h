#pragma once

#include "risk/core/orders/AttackOrder.h"
#include "risk/core/orders/MoveTroopsOrder.h"
#include "risk/core/orders/RollDiceOrder.h"
#include "risk/enums.h"

#include <vector>

namespace risk {

class GameStateManager;

class AttackManager {
private:
  GameStateManager &gameStateManager;

  std::vector<AttackOrder> attackOrders;
  std::vector<RollDiceOrder> rollDiceOrders;
  std::vector<MoveTroopsOrder> moveTroopsOrders;

  void resolveAttack(AttackOrder &currentAttack,
                     const RollDiceOrder &currentRoll);

public:
  AttackManager(GameStateManager &gameStateManager);

  //=========================================================
  // Attack order
  //=========================================================

  void createAttack(int playerID, TerritoryID fromTerritory,
                    TerritoryID toTerritory, int attackingTroopCount,
                    int defendingTroopCount);

  void undoAttack();

  //=========================================================
  // Dice-roll order
  //=========================================================

  // Gameplay dice creation
  void createRollDiceOrder(int attackDiceCount);

  // Deterministic dice creation for tests
  void createRollDiceOrder(const std::vector<int> &attackingDice,
                           const std::vector<int> &defendingDice);

  void undoRollDiceOrder();

  // Resolves latest AttackOrder using latest RollDiceOrder
  void executeAttackOrder();

  //=========================================================
  // Post-capture troop movement
  //=========================================================

  void createMoveTroopsOrder(int playerID, TerritoryID fromTerritory,
                             TerritoryID toTerritory, int moveTroopCount);
  void undoMoveTroopsOrder();
  void executeMoveTroopsOrder();

  void clearOrders();



  //=========================================================
  // Getters
  //=========================================================

  const AttackOrder &getLastAttackOrder() const;
  const RollDiceOrder &getLastRollDiceOrder() const;
  const MoveTroopsOrder &getLastMoveTroopsOrder() const;

  const std::vector<AttackOrder> &getAttackOrders() const;
  const std::vector<RollDiceOrder> &getRollDiceOrders() const;
  const std::vector<MoveTroopsOrder> &getMoveTroopsOrders() const;
};

} // namespace risk