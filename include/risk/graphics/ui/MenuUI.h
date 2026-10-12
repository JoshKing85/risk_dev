#pragma once

#include <array>
#include <optional>

#include <SFML/Graphics.hpp>

#include "risk/graphics/components/DebugGrid.h"

namespace risk {

class MenuUI {

private:
  int humanPlayerNumbers;
  int aiPlayerNumbers;
  bool GameStarted = false;

  std::optional<DebugGrid> debugGrid;

  //=====================================================
  // Menu graphics
  //=====================================================

  sf::Texture backgroundTexture;
  std::optional<sf::Sprite> backgroundSprite;

  sf::Texture menuFrameTexture;
  std::optional<sf::Sprite> menuFrameSprite;

  sf::Shader desaturationShader;
  sf::Font font;

  // Background dampener
  sf::VertexArray backgroundDampener;

  // Menu title
  sf::Text title;

  // Menu backing
  sf::RectangleShape parchmentBacking;

  //=====================================================
  // Campaign
  //=====================================================

  sf::Text mapSelectionTitle;
  sf::Text campaignTitle;

  // Campaign dividers
  sf::Texture dividerTexture;

  std::optional<sf::Sprite> leftDivider;
  std::optional<sf::Sprite> rightDivider;

  //=====================================================
  // Player selection
  //=====================================================

  sf::Text numberOfPlayersTitle;

  // Number of players dividers
  std::optional<sf::Sprite> playerLeftDivider;
  std::optional<sf::Sprite> playerRightDivider;

  //=====================================================
  // Human players
  //=====================================================

  sf::Text humanPlayersTitle;

  std::array<sf::RectangleShape, 6> humanPlayerBoxes;

  sf::Text humanPlayer1Text;
  sf::Text humanPlayer2Text;
  sf::Text humanPlayer3Text;
  sf::Text humanPlayer4Text;
  sf::Text humanPlayer5Text;
  sf::Text humanPlayer6Text;

  //=====================================================
  // AI players
  //=====================================================

  sf::Text aiPlayersTitle;

  std::array<sf::RectangleShape, 6> aiPlayerBoxes;

  sf::Text aiPlayer0Text;
  sf::Text aiPlayer1Text;
  sf::Text aiPlayer2Text;
  sf::Text aiPlayer3Text;
  sf::Text aiPlayer4Text;
  sf::Text aiPlayer5Text;

  //=====================================================
  // Start button
  //=====================================================

  sf::RectangleShape startButton;
  sf::Text startButtonText;

public:
  MenuUI();

  //=====================================================
  // Menu methods
  //=====================================================

  void draw(sf::RenderWindow &window);

  void handleEvent(const sf::Event &event, sf::RenderWindow &window);

  //=====================================================
  // Setter methods
  //=====================================================

  void setHumanPlayerNumbers(int number);

  void setAiPlayerNumbers(int number);

  void setGameStarted();

  //=====================================================
  // Getter methods
  //=====================================================

  int getHumanPlayerNumbers() const;

  int getAiPlayerNumbers() const;

  bool isGameStarted() const;
};

} // namespace risk