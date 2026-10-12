#pragma once

#include <SFML/Graphics.hpp>

namespace risk {

class FineMesh {

private:
  static constexpr float canvasWidth = 1920.f;
  static constexpr float canvasHeight = 1080.f;

  static constexpr float minorSpacing = 10.f;
  static constexpr float majorSpacing = 50.f;

  sf::VertexArray minorLines;
  sf::VertexArray majorLines;

public:
  FineMesh();

  void draw(sf::RenderWindow &window) const;
};

} // namespace risk