#pragma once

#include "risk/graphics/components/ContinentValueBoard.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

namespace risk {

class BoardGraphics {
private:
  sf::Texture mapTexture;
  sf::Sprite mapSprite;

  std::vector<ContinentValueBoard> continentValues;

public:
  BoardGraphics(const std::string &mapImagePath, const sf::Font &font);

  void addContinentValue(std::string continentName, int continentValue,
                         sf::Vector2f position, sf::Vector2f size,
                         unsigned int characterSize, const sf::Font &font);

  void draw(sf::RenderWindow &window) const;
};

} // namespace risk