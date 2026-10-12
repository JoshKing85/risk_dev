
#pragma once

#include "risk/enums.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

namespace risk {

class CardGraphics {
private:
  //---------------------------------------------------------
  // Card Data
  //---------------------------------------------------------

  CardType cardType;

  //---------------------------------------------------------
  // Graphics
  //---------------------------------------------------------

  sf::RectangleShape cardShape;
  std::vector<sf::VertexArray> territoryShapes;
  sf::Text cardTypeText;

  //---------------------------------------------------------
  // Territory Transform
  //---------------------------------------------------------

  sf::Vector2f territoryPosition = {0.0f, 0.0f};
  float territoryScale = 1.0f;
  sf::Angle territoryRotation = sf::degrees(0.0f);

  //---------------------------------------------------------
  // State
  //---------------------------------------------------------

  bool selected = false;

public:
  CardGraphics(CardType cardType,
               const std::vector<std::vector<sf::Vector2f>> &territoryVertices,
               const sf::Font &font);

  void setPosition(sf::Vector2f position);
  void setRotation(sf::Angle rotation);

  void setSelected(bool selected);
  bool isSelected() const;

  CardType getCardType() const;

  sf::FloatRect getBounds() const;
  bool contains(sf::Vector2f point) const;

  void draw(sf::RenderWindow &window) const;
};

} // namespace risk
