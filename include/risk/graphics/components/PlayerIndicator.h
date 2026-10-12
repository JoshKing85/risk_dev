#pragma once

#include <SFML/Graphics.hpp>

#include <optional>

namespace risk {

class PlayerIndicator {
private:

  std::optional<sf::Text> currentPlayerText;
  sf::Texture pointerTexture;
  sf::Sprite pointerSprite;

  sf::Texture instructionTexture;
  sf::Sprite instructionSprite;

public:
  PlayerIndicator(const sf::Font &font);

  void setPosition(int playerID);

  void draw(sf::RenderWindow &window);
};

} // namespace risk