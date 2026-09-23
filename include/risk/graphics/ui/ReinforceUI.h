#pragma once

#include "risk/core/session/GameSession.h"
#include "risk/core/session/GameState.h"

#include "risk/graphics/components/CardContainer.h"
#include "risk/graphics/components/PlayerIndicator.h"
#include "risk/graphics/components/ReinforceControls.h"

#include "risk/graphics/game_elements/PlayerGraphics.h"
#include "risk/graphics/game_elements/TerritoryGraphics.h"

#include <SFML/Graphics.hpp>

#include <optional>
#include <unordered_map>
#include <vector>

namespace risk {

class ReinforceUI {

private:
  //---------------------------------------------------------
  // UI Components
  //---------------------------------------------------------

  sf::Text phaseTitle;

  std::optional<ReinforceControls> reinforceControls;
  std::optional<CardContainer> cardContainer;
  std::optional<PlayerIndicator> playerIndicator;

  //---------------------------------------------------------
  // Player State
  //---------------------------------------------------------

  void setPlayerState(GameState &gameState, GameSession &gameSession);

  //---------------------------------------------------------
  // Troop Placement
  //---------------------------------------------------------

  void handleTroops(
      const sf::Event &event, sf::RenderWindow &window,
      GameSession &gameSession, GameState &gameState,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

  void troopPlacement(
      const sf::Event &event, sf::RenderWindow &window,
      GameSession &gameSession, GameState &gameState,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

  //---------------------------------------------------------
  // Reinforce Controls
  //---------------------------------------------------------

  void back(GameSession &gameSession, GameState &gameState);

  void confirm(GameSession &gameSession, GameState &gameState);

  void addTroop(GameSession &gameSession, GameState &gameState);

  void removeTroop(GameSession &gameSession, GameState &gameState);

public:
  ReinforceUI(const sf::Font &font,
              const std::unordered_map<TerritoryID, TerritoryGraphics>
                  &territoryGraphicsMap,
              GameState &gameState, GameSession &gameSession);

  void draw(sf::RenderWindow &window,
            std::vector<PlayerGraphics> &playerGraphics, GameState &gameState);

  void handleReinforceEvent(
      const sf::Event &event, sf::RenderWindow &window,
      GameSession &gameSession, GameState &gameState,
      std::vector<PlayerGraphics> &playerGraphics,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);
};

} // namespace risk