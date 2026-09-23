#pragma once

#include <SFML/Graphics.hpp>

#include <optional>
#include <string>

namespace risk {

class PreAttackBox {

private:
  //---------------------------------------------------------
  // Container
  //---------------------------------------------------------

  sf::RectangleShape preAttackBox;

  //---------------------------------------------------------
  // From Territory
  //---------------------------------------------------------

  std::optional<sf::Text> fromTerritoryText;
  std::optional<sf::Text> fromPlayerText;
  std::optional<sf::Text> fromTroopText;

  //---------------------------------------------------------
  // To Territory
  //---------------------------------------------------------

  std::optional<sf::Text> toTerritoryText;
  std::optional<sf::Text> toPlayerText;
  std::optional<sf::Text> toTroopText;

  //---------------------------------------------------------
  // Controls
  //---------------------------------------------------------

  sf::RectangleShape backButton;
  std::optional<sf::Text> backButtonText;

  sf::RectangleShape confirmButton;
  std::optional<sf::Text> confirmButtonText;

public:
  PreAttackBox(const sf::Font &font);

  //---------------------------------------------------------
  // Position
  //---------------------------------------------------------

  void setPosition(sf::Vector2f position);

  //---------------------------------------------------------
  // From Territory
  //---------------------------------------------------------

  void setFromTerritoryName(const std::string &name);

  void setFromPlayerName(const std::string &name);

  void setFromTroopCount(int troopCount);

  //---------------------------------------------------------
  // To Territory
  //---------------------------------------------------------

  void setToTerritoryName(const std::string &name);

  void setToPlayerName(const std::string &name);

  void setToTroopCount(int troopCount);

  //---------------------------------------------------------
  // Bounds
  //---------------------------------------------------------

  sf::FloatRect getBackBounds() const;

  sf::FloatRect getConfirmBounds() const;

  //---------------------------------------------------------
  // Draw
  //---------------------------------------------------------

  void draw(sf::RenderWindow &window);
};

} // namespace risk