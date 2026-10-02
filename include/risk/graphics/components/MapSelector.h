#pragma once

#include <SFML/Graphics.hpp>

#include <optional>

namespace risk {

class MapSelector {

private:
  //=========================================================
  // Map preview
  //=========================================================

  sf::RectangleShape mapImageBox;

  sf::Texture mapTexture;
  std::optional<sf::Sprite> mapSprite;

  //=========================================================
  // Map titles
  //=========================================================

  sf::RectangleShape mapTitleBox;
  sf::Text mapTitleClassicText;

  //=========================================================
  // Selection arrows
  //=========================================================

  sf::RectangleShape leftArrowBox;
  sf::RectangleShape rightArrowBox;

  sf::ConvexShape leftArrow;
  sf::ConvexShape rightArrow;

public:
  //=========================================================
  // Constructor
  //=========================================================

  explicit MapSelector(const sf::Font &font);

  //=========================================================
  // Draw
  //=========================================================

  void draw(sf::RenderWindow &window);

  //=========================================================
  // Getters
  //=========================================================

  const sf::RectangleShape &getLeftArrowBox() const;
  const sf::RectangleShape &getRightArrowBox() const;
};

} // namespace risk