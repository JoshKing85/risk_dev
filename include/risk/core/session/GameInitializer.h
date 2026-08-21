#pragma once

#include "risk/enums.h"

#include "risk/entities/Player.h"

#include "risk/world/Deck.h"
#include "risk/world/Map.h"

#include "risk/core/managers/GameStateManager.h"

#include <string>
#include <tuple>
#include <vector>

namespace risk {

class GameInitializer {

public:
  GameInitializer();

  std::tuple<Map, std::vector<Player>, Deck>
  initializeGame(std::string &filename, int playerNumbers, int aiNumbers);

  void updatePlayer(Player &player, const std::string &name);

  void dealDeck(Deck &deck, std::vector<Player> &players, Map &map,
                GameStateManager &gameStateManager);
};

} // namespace risk