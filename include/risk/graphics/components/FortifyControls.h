#pragma once

#include <SFML/Graphics.hpp>

#include <optional>

namespace risk {

class FortifyControls {
private:
  sf::RectangleShape backButton;
  std::optional<sf::Text> backButtonText;

  sf::RectangleShape confirmButton;
  std::optional<sf::Text> confirmButtonText;

  sf::RectangleShape addTroopsButton;
  std::optional<sf::Text> addTroopsText;

  sf::RectangleShape removeTroopsButton;
  std::optional<sf::Text> removeTroopsText;

  sf::RectangleShape troopCount;
  std::optional<sf::Text> troopCountText;

public:
  FortifyControls(const sf::Font &font);

  void setTroopControlsPosition(sf::Vector2f position);

  void setTroopCount(int troopCount);

  sf::FloatRect getBackBounds() const;
  sf::FloatRect getConfirmBounds() const;
  sf::FloatRect getAddTroopsBounds() const;
  sf::FloatRect getRemoveTroopsBounds() const;

  void draw(sf::RenderWindow &window);
};

} // namespace risk