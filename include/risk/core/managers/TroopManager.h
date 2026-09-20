#pragma once

#include "risk/core/orders/CashSetOrder.h"
#include "risk/core/orders/FortifyOrder.h"
#include "risk/core/orders/ReinforceOrder.h"

#include <vector>

namespace risk {

class GameStateManager;
class Player;

class TroopManager {

private:
  GameStateManager &gameStateManager;

  std::vector<ReinforceOrder> reinforceOrders;
  std::vector<FortifyOrder> fortifyOrders;
  std::vector<CashSetOrder> cashSetOrders;

public:
  TroopManager(GameStateManager &gameStateManager);

  //=========================================================
  // Reinforcement calculation
  //=========================================================

  int calculateReinforcements(const Player &player);

  //=========================================================
  // Create orders
  //=========================================================

  void createReinforceOrder(int playerID, TerritoryID territoryID,
                            int reinforceTroopCount);

  void createFortifyOrder(int playerID, TerritoryID fromTerritory,
                          TerritoryID toTerritory, int fortifyTroopCount);

  void createCashSetOrder(int playerID, SetType setType,
                          std::vector<Card> cards);

  //=========================================================
  // Execute orders
  //=========================================================

  void executeReinforceOrder();
  void executeFortifyOrder();
  int executeCashSetOrder(const Player &player);

  //=========================================================
  // Undo orders
  //=========================================================

  void undoReinforceOrder();
  void undoFortifyOrder();
  void undoCashSetOrder();


  void clearOrders();
  //=========================================================
  // Getters
  //=========================================================

  const std::vector<ReinforceOrder> &getReinforceOrders() const;
  const std::vector<FortifyOrder> &getFortifyOrders() const;
  const std::vector<CashSetOrder> &getCashSetOrders() const;

  const ReinforceOrder &getLastReinforceOrder() const;
  const FortifyOrder &getLastFortifyOrder() const;
  const CashSetOrder &getLastCashSetOrder() const;
};

} // namespace risk