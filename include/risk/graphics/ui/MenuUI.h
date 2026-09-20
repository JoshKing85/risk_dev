#pragma once

#include <array>

#include <SFML/Graphics.hpp>

#include "risk/enums.h"

namespace risk {

class MenuUI {

private:
  MapType mapSelection;
  int humanPlayerNumbers;
  int aiPlayerNumbers;
  bool GameStarted = false;

  sf::RectangleShape menuBox;

  sf::Font font;


  // Menu title
  sf::Text title;

 
  // Map selection
  sf::Text mapSelectionTitle;

  sf::RectangleShape classicMapBox;
  sf::Text classicMapText;

  // Player selection
  sf::Text numberOfPlayersTitle;

  // Human players
  sf::Text humanPlayersTitle;

  std::array<sf::RectangleShape, 6> humanPlayerBoxes;

  sf::Text humanPlayer1Text;
  sf::Text humanPlayer2Text;
  sf::Text humanPlayer3Text;
  sf::Text humanPlayer4Text;
  sf::Text humanPlayer5Text;
  sf::Text humanPlayer6Text;

  // AI players
  sf::Text aiPlayersTitle;

  std::array<sf::RectangleShape, 6> aiPlayerBoxes;

  sf::Text aiPlayer0Text;
  sf::Text aiPlayer1Text;
  sf::Text aiPlayer2Text;
  sf::Text aiPlayer3Text;
  sf::Text aiPlayer4Text;
  sf::Text aiPlayer5Text;

// Start button
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

  void setMapSelection(MapType mapSelection);
  void setHumanPlayerNumbers(int number);
  void setAiPlayerNumbers(int number);
  void setGameStarted();

  //=====================================================
  // Getter methods
  //=====================================================

  MapType getMapSelection() const;
  int getHumanPlayerNumbers() const;
  int getAiPlayerNumbers() const;
  bool isGameStarted() const;
};

} // namespace risk