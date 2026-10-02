#pragma once

#include "risk/core/session/GameSession.h"
#include "risk/core/session/GameState.h"

#include "risk/graphics/components/FortifyControls.h"
#include "risk/graphics/components/PlayerIndicator.h"

#include "risk/graphics/game_elements/TerritoryGraphics.h"

#include <SFML/Graphics.hpp>

#include <optional>
#include <unordered_map>

namespace risk {

class FortifyUI {

private:
  //---------------------------------------------------------
  // UI Components
  //---------------------------------------------------------

  sf::Text phaseTitle;

  std::optional<FortifyControls> fortifyControls;
  std::optional<PlayerIndicator> playerIndicator;

  //---------------------------------------------------------
  // Territory Selection
  //---------------------------------------------------------

  void territorySelection(
      const sf::Event &event, sf::RenderWindow &window,
      GameSession &gameSession, GameState &gameState,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

  //---------------------------------------------------------
  // Fortify Controls
  //---------------------------------------------------------

  void back(GameSession &gameSession, GameState &gameState);

  void confirm(GameSession &gameSession, GameState &gameState);

  void addTroop(GameSession &gameSession, GameState &gameState);

  void removeTroop(GameSession &gameSession, GameState &gameState);

public:
  FortifyUI(const sf::Font &font, GameState &gameState);

  void draw(sf::RenderWindow &window, GameState &gameState);

  void handleFortifyEvent(
      const sf::Event &event, sf::RenderWindow &window,
      GameSession &gameSession, GameState &gameState,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);
};

} // namespace risk