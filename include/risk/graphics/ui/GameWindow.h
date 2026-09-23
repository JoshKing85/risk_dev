#pragma once

#include <SFML/Graphics.hpp>

#include "risk/core/session/GameSession.h"
#include "risk/core/session/GameState.h"
#include "risk/graphics/ui/LUIExchange.h"
#include "risk/graphics/ui/LoadingUI.h"
#include "risk/graphics/ui/MenuUI.h"
#include "risk/graphics/ui/GameSessionUI.h"


namespace risk {

class GameWindow {
private:
  sf::RenderWindow window;
  MenuUI menuUI;
  GameState gameState;
  GameSession gameSession;
  LUIExchange exchangeLUI;

  LoadingUI loadingUI;
  GameSessionUI gameSessionUI;

  sf::Clock loadingClock;
  bool loadingStarted = false;

public:
  GameWindow(sf::VideoMode videoMode, std::string title);

  void run();
};

} // namespace risk