#pragma once

#include <SFML/Graphics.hpp>

namespace risk {

class LoadingUI {
private:
  sf::Font font;
  sf::Text loadingText;
  sf::RectangleShape loadingBox;

public:
  LoadingUI();
  void draw(sf::RenderWindow &window);
};

} // namespace risk