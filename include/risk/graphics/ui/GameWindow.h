#pragma once

#include <SFML/Graphics.hpp>

#include "risk/core/session/GameSession.h"
#include "risk/core/session/GameState.h"

#include "risk/graphics/components/PlayerProfile.h"

#include "risk/graphics/ui/GameSessionUI.h"
#include "risk/graphics/ui/LUIExchange.h"
#include "risk/graphics/ui/LoadingUI.h"
#include "risk/graphics/ui/MenuUI.h"
#include "risk/graphics/ui/ProfileUI.h"

#include <optional>
#include <string>
#include <vector>

namespace risk {

class GameWindow {

private:
  //---------------------------------------------------------
  // Window
  //---------------------------------------------------------

  sf::RenderWindow window;

  //---------------------------------------------------------
  // Core
  //---------------------------------------------------------

  GameState gameState;
  GameSession gameSession;
  LUIExchange exchangeLUI;

  //---------------------------------------------------------
  // Pre-game UI
  //---------------------------------------------------------

  MenuUI menuUI;

  sf::Font profileFont;
  std::optional<ProfileUI> profileUI;

  std::vector<PlayerProfile> playerProfiles;
  int currentProfile = 0;

  //---------------------------------------------------------
  // Game UI
  //---------------------------------------------------------

  LoadingUI loadingUI;
  GameSessionUI gameSessionUI;

  //---------------------------------------------------------
  // Loading
  //---------------------------------------------------------

  sf::Clock loadingClock;
  bool loadingStarted = false;

public:
  //---------------------------------------------------------
  // Construction
  //---------------------------------------------------------

  GameWindow(sf::VideoMode videoMode, std::string title);

  //---------------------------------------------------------
  // Main loop
  //---------------------------------------------------------

  void run();
};

} // namespace risk