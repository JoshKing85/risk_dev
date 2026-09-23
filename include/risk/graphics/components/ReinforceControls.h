#pragma once

#include <SFML/Graphics.hpp>

#include <optional>

namespace risk {

class ReinforceControls {
private:
  sf::RectangleShape backButton;
  std::optional<sf::Text> backButtonText;

  sf::RectangleShape confirmButton;
  std::optional<sf::Text> confirmButtonText;

  sf::RectangleShape addTroopsButton;
  std::optional<sf::Text> addTroopsText;

  sf::RectangleShape removeTroopsButton;
  std::optional<sf::Text> removeTroopsText;

  sf::RectangleShape remainingTroops;
  std::optional<sf::Text> remainingTroopsText;

public:
  ReinforceControls(const sf::Font &font);

  void setBackPosition(sf::Vector2f position);
  void setConfirmPosition(sf::Vector2f position);
  void setTroopControlsPosition(sf::Vector2f position);

  void setRemainingTroops(int troopCount);

  sf::FloatRect getBackBounds() const;
  sf::FloatRect getConfirmBounds() const;
  sf::FloatRect getAddTroopsBounds() const;
  sf::FloatRect getRemoveTroopsBounds() const;

  void draw(sf::RenderWindow &window);
};

} // namespace risk