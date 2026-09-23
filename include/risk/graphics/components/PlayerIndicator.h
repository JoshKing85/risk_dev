#pragma once

#include <SFML/Graphics.hpp>

#include <optional>

namespace risk {

class PlayerIndicator {
private:
  sf::RectangleShape currentPlayerBox;
  std::optional<sf::Text> currentPlayerText;
  sf::ConvexShape currentPlayerArrow;

public:
  PlayerIndicator(const sf::Font &font);

  void setPosition(int playerID);

  void draw(sf::RenderWindow &window);
};

} // namespace risk