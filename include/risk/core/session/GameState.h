#pragma once

#include "risk/core/orders/order.h"
#include "risk/entities/Card.h"
#include "risk/enums.h"

#include <vector>
namespace risk {

class GameState {
private:
  PhaseType phase = PhaseType::Loading;
  AuxiliaryPhase auxPhase = AuxiliaryPhase::None;

  int playerTurn = 0;
  int setCount = 0;

  int reinforcePool = 0;

  TerritoryID tempToSelection = TerritoryID::None;
  TerritoryID tempFromSelection = TerritoryID::None;

  int tempReinforceCount = 0;

  std::vector<Card> playerCards;
  std::vector<Card> SelectedCards;
  
  //Order lastOrder;

public:
  GameState();

  // Setters
  void setPhase(PhaseType newPhase);
  void calcSetCount(int setCount);
  void setPlayerCards(std::vector<Card> &playerSet);
  void addSelectedCard(Card &card);
  void setPlayerTurn(int playerID);
  void setAuxPhase(AuxiliaryPhase auxPhase);
  void setReinforcePool(int reinforcePool);
  void setTempToSelection(TerritoryID &territoryID);
  void setTempFromSelection(TerritoryID &territoryID);
  void setTempReinforceCount(int count);




  // Getters
  PhaseType getPhase() const;
  int getPlayerTurn();
  int getSetCount();
  int getReinforcePool();
  int getTempReinforceCount();
  TerritoryID getTempToTerritorySelection();
  TerritoryID getTempFromTerritorySelection();
  


};

} // namespace risk