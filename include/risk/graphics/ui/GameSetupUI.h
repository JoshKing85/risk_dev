#pragma once

#include "risk/core/session/GameSession.h"
#include "risk/core/session/GameSetupState.h"
#include "risk/core/session/GameState.h"
#include "risk/graphics/components/PlayerIndicator.h"
#include "risk/graphics/components/SetupControls.h"
#include "risk/graphics/game_elements/PlayerGraphics.h"
#include "risk/graphics/game_elements/TerritoryGraphics.h"
#include "risk/graphics/ui/ProfileUI.h"

#include <SFML/Graphics.hpp>

#include <optional>
#include <unordered_map>
#include <vector>

namespace risk {

class GameSetupUI {
private:
  GameSetupState gameSetupState;

  std::optional<ProfileUI> profileUI;
  std::optional<PlayerIndicator> playerIndicator;
  std::optional<SetupControls> setupControls;
  std::optional<sf::Text> phaseTitle;

  void handleTroops(
      const sf::Event &event, GameSession &gameSession, GameState &gameState,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

  void troopPlacement(
      const sf::Event &event, GameSession &gameSession,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

  void back(const sf::Event &event);

  void confirm(const sf::Event &event, GameSession &gameSession,
               GameState &gameState);

public:
  void initialize(GameSession &gameSession, sf::Font &font,
                  std::vector<PlayerGraphics> &playerGraphics);

  void draw(sf::RenderWindow &window,
            std::vector<PlayerGraphics> &playerGraphics);

  void handleEvent(
      const sf::Event &event, sf::RenderWindow &window,
      GameSession &gameSession, GameState &gameState,
      std::vector<PlayerGraphics> &playerGraphics,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

  GameSetupState &getGameSetupState();
};

} // namespace risk