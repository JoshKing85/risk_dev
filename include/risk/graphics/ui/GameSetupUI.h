#pragma once

#include "risk/core/session/GameSession.h"
#include "risk/core/session/GameSetupState.h"
#include "risk/core/session/GameState.h"
#include "risk/enums.h"
#include "risk/graphics/game_elements/BoardGraphics.h"
#include "risk/graphics/game_elements/PlayerGraphics.h"
#include "risk/graphics/game_elements/TerritoryGraphics.h"
#include "risk/graphics/ui/ProfileUI.h"
#include "risk/world/Map.h"

#include <SFML/Graphics.hpp>

#include <optional>
#include <unordered_map>
#include <vector>

namespace risk {

class GameSetupUI {
private:
  int humanPlayerNumbers = 0;
  int aiPlayerNumbers = 0;
  MapType mapSelection = MapType::None;

  sf::RectangleShape backButton;
  std::optional<sf::Text> backButtonText;

  sf::RectangleShape confirmButton;
  std::optional<sf::Text> confirmButtonText;

  // Current player troop placement indicator
  sf::RectangleShape currentPlayerBox;
  std::optional<sf::Text> currentPlayerText;
  sf::ConvexShape currentPlayerArrow;

  GameSetupState gameSetupState;
  std::optional<ProfileUI> profileUI;

  std::vector<PlayerGraphics> playerGraphics;
  std::optional<BoardGraphics> boardGraphics;

  std::unordered_map<TerritoryID, TerritoryGraphics> territoryGraphicsMap;

  void handleTroops(const sf::Event &event, GameSession &gameSession,
                    GameState &gameState);

  void troopPlacement(const sf::Event &event, GameSession &gameSession);

  void back(const sf::Event &event);

  void confirm(const sf::Event &event, GameSession &gameSession,
               GameState &gameState);

public:
  void draw(sf::RenderWindow &window);

  void handleEvent(const sf::Event &event, sf::RenderWindow &window,
                   GameSession &gameSession, GameState &gameState);

  void initialLoading(GameSession &gameSession, GameState &gameState,
                      int humanPlayers, int aiPlayers, MapType mapSelection);

  void setupState(GameSession &gameSession, const sf::Font &font);

  void createTerritoryGraphicsMap(Map &territoryMap, MapType mapSelection);

  void setBackPosition(sf::Vector2f position);

  void setConfirmPosition(sf::Vector2f position);

  sf::FloatRect getBackBounds() const;

  sf::FloatRect getConfirmBounds() const;

  GameSetupState &getGameSetupState();

  BoardGraphics &getBoardGraphics();

  std::unordered_map<TerritoryID, TerritoryGraphics> &getTerritoryGraphics();

  std::vector<PlayerGraphics> &getPlayerGraphics();
};

} // namespace risk