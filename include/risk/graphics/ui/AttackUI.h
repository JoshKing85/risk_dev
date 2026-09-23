#pragma once

#include "risk/core/session/GameSession.h"
#include "risk/core/session/GameState.h"

#include "risk/graphics/components/AttackWindow.h"
#include "risk/graphics/components/CardContainer.h"
#include "risk/graphics/components/PlayerIndicator.h"
#include "risk/graphics/components/PreAttackBox.h"

#include "risk/graphics/game_elements/PlayerGraphics.h"
#include "risk/graphics/game_elements/TerritoryGraphics.h"

#include <SFML/Graphics.hpp>

#include <optional>
#include <unordered_map>
#include <vector>

namespace risk {

class AttackUI {

private:
  //---------------------------------------------------------
  // UI Components
  //---------------------------------------------------------

  sf::Text phaseTitle;

  std::optional<PreAttackBox> preAttackBox;
  std::optional<AttackWindow> attackWindow;
  std::optional<CardContainer> cardContainer;
  std::optional<PlayerIndicator> playerIndicator;

  sf::RectangleShape fortifyButton;
  sf::Text fortifyText;


  //---------------------------------------------------------
  // Event Handling
  //---------------------------------------------------------

  void handleAttackEvent(
      const sf::Event &event, sf::RenderWindow &window,
      GameSession &gameSession, GameState &gameState,
      std::vector<PlayerGraphics> &playerGraphics,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);
  //---------------------------------------------------------
  // Territory Selection
  //---------------------------------------------------------

  void territorySelection(
      const sf::Event &event, sf::RenderWindow &window,
      GameSession &gameSession, GameState &gameState,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

  //---------------------------------------------------------
  // Pre Attack
  //---------------------------------------------------------

  void preAttack(
      const sf::Event &event, sf::RenderWindow &window,
      GameSession &gameSession, GameState &gameState,
      std::vector<PlayerGraphics> &playerGraphics,
      std::unordered_map<TerritoryID, TerritoryGraphics> &territoryGraphicsMap);

  void back(GameSession &gameSession, GameState &gameState);

  void confirm(GameSession &gameSession, GameState &gameState);

  //---------------------------------------------------------
  // Attack Window
  //---------------------------------------------------------
 
  void handleAttackWindow(GameSession &gameSession, GameState &gameState,
                       std::vector<PlayerGraphics> &playerGraphics);

  void selectDice(const sf::Event &event, GameState &gameState,
                  GameSession &gameSession);

  void attack(GameState &gameState, GameSession &gameSession);

  void quitAttack(GameState &gameState, GameSession &gameSession);

  void moveTroops(GameState &gameState, GameSession &gameSession);

public:
  //---------------------------------------------------------
  // Constructor
  //---------------------------------------------------------

  AttackUI(const sf::Font &font,
           const std::unordered_map<TerritoryID, TerritoryGraphics>
               &territoryGraphicsMap,
           GameState &gameState, GameSession &gameSession);

  //---------------------------------------------------------
  // Draw
  //---------------------------------------------------------

  void draw(sf::RenderWindow &window,
            std::vector<PlayerGraphics> &playerGraphics, GameState &gameState);
};

} // namespace risk