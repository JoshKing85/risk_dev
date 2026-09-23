#pragma once

#include "risk/enums.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

namespace risk {

class TerritoryGraphics {
private:
  TerritoryID territoryID;
  ContinentID continentID;
  int playerID;

  std::vector<sf::Vector2f> vertices;

  sf::ConvexShape shape;
  sf::Text titleText;
  sf::Text troopCountText;

  float outlineThickness;

public:
  TerritoryGraphics(TerritoryID territoryID, ContinentID continentID,
                    int playerID, const std::string &title,
                    const std::vector<sf::Vector2f> &vertices,
                    sf::Vector2f titlePosition, sf::Vector2f troopCountPosition,
                    unsigned int titleCharacterSize,
                    unsigned int troopCharacterSize, float outlineThickness,
                    const sf::Font &font);

  void setPlayerID(int playerID);
  void setTroopCount(int troopCount);
  void setSelected(bool selected);

  void draw(sf::RenderWindow &window) const;

  sf::FloatRect getBounds() const;
  bool contains(sf::Vector2f point) const;
  TerritoryID getTerritoryID() const;
  int getPlayerID() const;
  const std::vector<sf::Vector2f> &getVertices() const;
};

} // namespace risk