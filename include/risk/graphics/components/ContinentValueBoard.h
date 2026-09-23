#pragma once

#include <SFML/Graphics.hpp>

#include <string>

namespace risk {

class ContinentValueBoard {
private:
  sf::RectangleShape box;
  sf::Text text;

public:
  ContinentValueBoard(const std::string &continentName, int continentValue,
                      sf::Vector2f position, sf::Vector2f size,
                      unsigned int characterSize, const sf::Font &font);

  void draw(sf::RenderWindow &window) const;
};

} // namespace risk