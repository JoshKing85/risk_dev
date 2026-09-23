#pragma once

#include "risk/core/session/GameSession.h"
#include "risk/core/session/GameState.h"
#include "risk/enums.h"
#include "risk/graphics/game_elements/BoardGraphics.h"
#include "risk/graphics/game_elements/PlayerGraphics.h"
#include "risk/graphics/game_elements/TerritoryGraphics.h"
#include "risk/graphics/ui/GameSetupUI.h"
#include "risk/graphics/ui/ReinforceUI.h"
#include "risk/world/Map.h"

#include <SFML/Graphics.hpp>

#include <optional>
#include <unordered_map>
#include <vector>

namespace risk {

class GameSessionUI {
private:
  //---------------------------------------------------------
  // Session State
  //---------------------------------------------------------

  int humanPlayerNumbers = 0;
  int aiPlayerNumbers = 0;
  MapType mapSelection = MapType::None;

  //---------------------------------------------------------
  // Game Graphics
  //---------------------------------------------------------

  std::vector<PlayerGraphics> playerGraphics;
  std::optional<BoardGraphics> boardGraphics;

  std::unordered_map<TerritoryID, TerritoryGraphics> territoryGraphicsMap;

  //---------------------------------------------------------
  // Phase UI
  //---------------------------------------------------------

  std::optional<GameSetupUI> gameSetupUI;
  std::optional<ReinforceUI> reinforceUI;

public:
  //---------------------------------------------------------
  // UI Routing
  //---------------------------------------------------------

  void draw(sf::RenderWindow &window, GameState &gameState,
            GameSession &gameSession);

  void handleEvent(const sf::Event &event, sf::RenderWindow &window,
                   GameSession &gameSession, GameState &gameState);

  //---------------------------------------------------------
  // Initial Loading
  //---------------------------------------------------------

  void initialLoading(GameSession &gameSession, GameState &gameState,
                      int humanPlayers, int aiPlayers, MapType mapSelection);

  void createTerritoryGraphicsMap(Map &territoryMap, MapType mapSelection);

  //---------------------------------------------------------
  // UI State Access
  //---------------------------------------------------------

  GameSetupState &getGameSetupState();

  BoardGraphics &getBoardGraphics();

  std::unordered_map<TerritoryID, TerritoryGraphics> &getTerritoryGraphics();

  std::vector<PlayerGraphics> &getPlayerGraphics();
};

} // namespace risk