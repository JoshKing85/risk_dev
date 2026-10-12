#pragma once

#include "risk/enums.h"
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>

namespace risk {
struct Feature {

  std::string name;
  FeatureType featureType;
  std::vector<sf::Vector2f> vertices;
};
} // namespace risk