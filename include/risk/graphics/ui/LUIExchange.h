#pragma once

#include "risk/core/session/GameSetupState.h"
#include "risk/core/session/GameState.h"

#include "risk/entities/Player.h"
#include "risk/world/Map.h"

#include "risk/graphics/game_elements/PlayerGraphics.h"
#include "risk/graphics/game_elements/TerritoryGraphics.h"

#include "risk/enums.h"

#include <unordered_map>
#include <vector>

namespace risk {

class LUIExchange {

public:
  LUIExchange();

  void updateGraphics(
      const Map &map, const std::vector<Player> &players,
      const GameState &gameState,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap,
      std::vector<PlayerGraphics> &playerGraphics,
      const GameSetupState *gameSetupState = nullptr);
};

} // namespace risk