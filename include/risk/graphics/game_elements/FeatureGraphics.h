#pragma once

#include "risk/graphics/components/Feature.h"

#include <SFML/Graphics.hpp>
#include <vector>

namespace risk {

class FeatureGraphics {
public:
  FeatureGraphics(const std::vector<Feature> &features);

  void draw(sf::RenderWindow &window) const;

private:
  std::vector<sf::VertexArray> featureShapes;

  void createRiver(const Feature &feature);
};

} // namespace risk