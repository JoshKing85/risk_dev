
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
  std::string title;

  std::vector<std::vector<sf::Vector2f>> vertices;

  std::vector<sf::VertexArray> fills;
  std::vector<sf::VertexArray> outlines;

  sf::Text titleText;
  sf::Text troopCountText;

  float outlineThickness;
  bool selected = false;

  void updateOutlines();

public:
  TerritoryGraphics(TerritoryID territoryID, ContinentID continentID,
                    int playerID, const std::string &title,
                    const std::vector<std::vector<sf::Vector2f>> &vertices,
                    unsigned int titleCharacterSize,
                    unsigned int troopCharacterSize, float outlineThickness,
                    const sf::Font &font);

  void setPlayerID(int playerID);

  void setTroopCount(int troopCount);

  void setSelected(bool selected);

  void setFactionColour(int avatarID);

  void draw(sf::RenderWindow &window) const;

  sf::FloatRect getBounds() const;

  bool contains(sf::Vector2f point) const;

  sf::Vector2f getLabelOffset() const;

  TerritoryID getTerritoryID() const;

  int getPlayerID() const;

  const std::vector<std::vector<sf::Vector2f>> &getVertices() const;

  std::string getTitle() const;
};

} // namespace risk
