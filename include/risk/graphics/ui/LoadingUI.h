#pragma once

#include <SFML/Graphics.hpp>

#include <optional>

namespace risk {

class LoadingUI {

private:
  //---------------------------------------------------------
  // Background
  //---------------------------------------------------------

  sf::Texture backgroundTexture;
  std::optional<sf::Sprite> backgroundSprite;

  sf::VertexArray backgroundDampener;

  //---------------------------------------------------------
  // Loading banner
  //---------------------------------------------------------

  sf::Font font;

  sf::RectangleShape loadingBanner;
  sf::Text loadingText;

  sf::RectangleShape topLine;
  sf::RectangleShape bottomLine;

  //---------------------------------------------------------
  // Loading text
  //---------------------------------------------------------

  void updateLoadingText(float elapsedSeconds);

public:
  LoadingUI();

  void draw(sf::RenderWindow &window, float elapsedSeconds);
};

} // namespace risk