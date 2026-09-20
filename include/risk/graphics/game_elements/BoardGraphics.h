#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

namespace risk {
class BoardGraphics {
private:
  sf::Texture mapTexture;
  sf::Sprite mapSprite;

  std::vector<sf::RectangleShape> continentValueBoxes;
  std::vector<sf::Text> continentValueTexts;

public:
  BoardGraphics(const std::string &mapImagePath, const sf::Font &font);

  void addContinentValue(std::string continentName, int continentValue, sf::Vector2f position,
                         sf::Vector2f size, unsigned int characterSize,
                         const sf::Font &font);

  void draw(sf::RenderWindow &window) const;
};
} // namespace risk