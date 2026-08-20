#pragma once

#include "risk/enums.h"

namespace risk {

class Map;
class Player;
class GameStateManager;
class TroopManager;
class AttackManager;
class LogManager;

class TurnManager {

private:
  Player &currentPlayer;
  int playerID;
  std::vector<Player> &players;
  Map &map;
  GameStateManager gameStateManager;
  AttackManager attackManager;
  TroopManager troopManager;
  LogManager logManager;
  


public:
  TurnManager(Player &currentPlayer, std::vector<Player> &players, Map &map, Deck &deck);

  void runTurn();
  void reinforcePhase(bool calculateBaseReinforcements = true);
  void attackPhase();
  void fortifyPhase();
  void logPhase();
};

} // namespace risk