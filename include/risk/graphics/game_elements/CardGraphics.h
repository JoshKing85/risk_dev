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
  sf::ConvexShape territoryShape;
  sf::Text cardTypeText;

  //---------------------------------------------------------
  // State
  //---------------------------------------------------------

  bool selected = false;

public:
  CardGraphics(CardType cardType,
               const std::vector<sf::Vector2f> &territoryVertices,
               const sf::Font &font);

  //---------------------------------------------------------
  // Position
  //---------------------------------------------------------

  void setPosition(sf::Vector2f position);
  void setRotation(sf::Angle rotation);

  //---------------------------------------------------------
  // Selection
  //---------------------------------------------------------

  void setSelected(bool selected);
  bool isSelected() const;

  //---------------------------------------------------------
  // Access
  //---------------------------------------------------------

  CardType getCardType() const;

  sf::FloatRect getBounds() const;
  bool contains(sf::Vector2f point) const;

  //---------------------------------------------------------
  // Draw
  //---------------------------------------------------------

  void draw(sf::RenderWindow &window) const;
};

} // namespace risk