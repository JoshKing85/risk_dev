#pragma once

#include <SFML/Graphics.hpp>

#include <optional>

namespace risk {

class SetupControls {
private:
  sf::RectangleShape backButton;
  std::optional<sf::Text> backButtonText;

  sf::RectangleShape confirmButton;
  std::optional<sf::Text> confirmButtonText;

public:
  SetupControls(const sf::Font &font);

  void setBackPosition(sf::Vector2f position);

  void setConfirmPosition(sf::Vector2f position);

  sf::FloatRect getBackBounds() const;

  sf::FloatRect getConfirmBounds() const;

  void draw(sf::RenderWindow &window);
};

} // namespace risk