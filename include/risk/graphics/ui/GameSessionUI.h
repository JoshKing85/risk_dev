#pragma once

#include "risk/core/session/GameSession.h"
#include "risk/core/session/GameState.h"
#include "risk/enums.h"

#include "risk/graphics/components/PlayerProfile.h"
#include "risk/graphics/game_elements/BoardGraphics.h"
#include "risk/graphics/game_elements/PlayerGraphics.h"
#include "risk/graphics/game_elements/TerritoryGraphics.h"
#include "risk/graphics/game_elements/FeatureGraphics.h"
#include "risk/graphics/components/DebugGrid.h"
#include "risk/graphics/ui/AttackUI.h"
#include "risk/graphics/ui/FortifyUI.h"
#include "risk/graphics/ui/GameSetupUI.h"
#include "risk/graphics/ui/ReinforceUI.h"
#include "risk/graphics/components/FineMesh.h"
#include "risk/world/Map.h"

#include <SFML/Graphics.hpp>
#include <optional>
#include <unordered_map>
#include <vector>

namespace risk {

class GameSessionUI {
private:
  // Development overlays
  sf::Texture devMapTexture;
  sf::Sprite devMapSprite;
  std::optional<FineMesh> fineMesh;

  // Session state
  int humanPlayerNumbers = 0;
  int aiPlayerNumbers = 0;

  // Game graphics
  std::vector<PlayerGraphics> playerGraphics;
  std::optional<BoardGraphics> boardGraphics;
  std::optional<FeatureGraphics> featureGraphics;
  std::unordered_map<TerritoryID, TerritoryGraphics> territoryGraphicsMap;

  // Shared board components
  sf::Texture frameTexture;
  sf::Sprite frameSprite;
  sf::Texture playerSlotsTexture;
  sf::Sprite playerSlotsSprite{playerSlotsTexture};

  // Shared phase title: the text follows GameState::getPhase().
  sf::Texture phaseBannerTexture;
  sf::Sprite phaseBannerSprite{phaseBannerTexture};
  sf::Font phaseTitleFont;
  sf::Text phaseTitleText{phaseTitleFont};

  std::vector<sf::Texture> factionTroopCounters;
  std::optional<DebugGrid> debugGrid;

  // Paper grain shader
  sf::Shader paperGrainShader;
  sf::Texture screenTexture;
  std::optional<sf::Sprite> screenSprite;

  // Phase-specific UI
  std::optional<GameSetupUI> gameSetupUI;
  std::optional<ReinforceUI> reinforceUI;
  std::optional<AttackUI> attackUI;
  std::optional<FortifyUI> fortifyUI;
  int activePlayerID = -1;

public:
  GameSessionUI();

  void draw(sf::RenderWindow &window, GameState &gameState,
            GameSession &gameSession);

  void handleEvent(const sf::Event &event, sf::RenderWindow &window,
                   GameSession &gameSession, GameState &gameState);

  void initialLoading(GameSession &gameSession, GameState &gameState,
                      int humanPlayers, int aiPlayers,
                      const std::vector<PlayerProfile> &playerProfiles);

  void createTerritoryGraphicsMap(Map &territoryMap);

  GameSetupState &getGameSetupState();
  BoardGraphics &getBoardGraphics();
  std::unordered_map<TerritoryID, TerritoryGraphics> &getTerritoryGraphics();
  std::vector<PlayerGraphics> &getPlayerGraphics();
};

} // namespace risk
