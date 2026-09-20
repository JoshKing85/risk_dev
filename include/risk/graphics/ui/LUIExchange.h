#pragma once

#include "risk/core/session/GameSession.h"
#include "risk/core/session/GameSetupState.h"
#include "risk/core/session/GameState.h"

#include "risk/graphics/ui/GameSetupUI.h"
#include "risk/graphics/ui/LoadingUI.h"

#include "risk/entities/Player.h"
#include "risk/world/Map.h"

#include "risk/graphics/game_elements/PlayerGraphics.h"
#include "risk/graphics/game_elements/TerritoryGraphics.h"

#include "risk/enums.h"

#include <unordered_map>
#include <vector>

#include <SFML/Graphics.hpp>

namespace risk {

class LUIExchange {
private:
public:
  LUIExchange();

  void loading(sf::RenderWindow &window, LoadingUI &loadingUI);

  void initialLoading(GameSession &gameSession, GameSetupUI &gameSetupUI,
                      GameState &gameState, int humanPlayers, int aiPlayers,
                      MapType mapSelection);

  void updateGraphics(
      const Map &map, const std::vector<Player> &players,
      const GameState &gameState,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap,
      std::vector<PlayerGraphics> &playerGraphics,
      const GameSetupState *gameSetupState = nullptr);

  void gameSetupDraw(sf::RenderWindow &window, GameSetupUI &gameSetupUI);

  void handleGameSetupEvent(const sf::Event &event, sf::RenderWindow &window,
                            GameSetupUI &gameSetupUI, GameSession &gameSession,
                            GameState &gameState);
    };
} // namespace risk