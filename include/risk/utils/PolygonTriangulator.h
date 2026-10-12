#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
namespace risk {

	std::vector<sf::Vertex> polyTri(const std::vector<sf::Vector2f> &vertices);

}