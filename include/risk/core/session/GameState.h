#pragma once

#include "risk/core/orders/AttackOrder.h"
#include "risk/core/orders/FortifyOrder.h"
#include "risk/core/orders/MoveTroopsOrder.h"
#include "risk/core/orders/ReinforceOrder.h"
#include "risk/core/orders/RollDiceOrder.h"

#include "risk/entities/Card.h"
#include "risk/enums.h"

#include <vector>

namespace risk {

class GameState {
private:
  PhaseType phase = PhaseType::Loading;

  int playerTurnID = 0;

  int reinforcePool = 0;
  bool initReinforceComplete = false;

  TerritoryID ToSelection = TerritoryID::None;
  TerritoryID FromSelection = TerritoryID::None;

  int attackerDice = 0;
  bool attackConfirmed = false;

  int setCount = 0;
  std::vector<Card> playerCards;

  //=========================================================
  // ORDERS
  //=========================================================

  std::vector<const ReinforceOrder *> reinforceOrders;
  std::vector<const AttackOrder *> attackOrders;
  std::vector<const RollDiceOrder *> rollDiceOrders;
  std::vector<const MoveTroopsOrder *> moveTroopsOrders;
  std::vector<const FortifyOrder *> fortifyOrders;

public:
  GameState();

  //=========================================================
  // SETTERS
  //=========================================================

  void setPhase(PhaseType newPhase);

  void setPlayerTurnID(int playerID);

  void setToSelection(TerritoryID territoryID);
  void setFromSelection(TerritoryID territoryID);

  void setAttackerDice(int diceCount);
  void setAttackConfirmed(bool confirmed);

  void setInitialReinforceCount(int troopCount);
  void updateReinforcePool(int troopCount);
  void setReinforceComplete(bool complete);

  void setPlayerCards(std::vector<Card> &playerSet);

  //=========================================================
  // ADD ORDERS
  //=========================================================

  void addReinforceOrder(const ReinforceOrder &order);
  void addAttackOrder(const AttackOrder &order);
  void addRollDiceOrder(const RollDiceOrder &order);
  void addMoveTroopsOrder(const MoveTroopsOrder &order);
  void addFortifyOrder(const FortifyOrder &order);

  //=========================================================
  // REMOVE LAST ORDERS
  //=========================================================

  void removeLastReinforceOrder();
  void removeLastAttackOrder();
  void removeLastRollDiceOrder();
  void removeLastMoveTroopsOrder();
  void removeLastFortifyOrder();

  //=========================================================
  // CLEARERS
  //=========================================================

  void clearOrders();

  void clearAttack();
  //=========================================================
  // GETTERS
  //=========================================================

  PhaseType getPhase() const;

  int getPlayerTurnID();

  int getReinforcePool();

  bool getReinforceComplete();

  int calcSetCount();

  TerritoryID getToTerritorySelection() const;
  TerritoryID getFromTerritorySelection() const;

  int getAttackerDice() const;
  bool getAttackConfirmed() const;

  std::vector<Card> getPlayerCards();

  //=========================================================
  // ORDER GETTERS
  //=========================================================

  const ReinforceOrder &getLastReinforceOrder() const;
  const AttackOrder &getLastAttackOrder() const;
  const RollDiceOrder &getLastRollDiceOrder() const;
  const MoveTroopsOrder &getLastMoveTroopsOrder() const;
  const FortifyOrder &getLastFortifyOrder() const;
};

} // namespace risk