
#pragma once

#include "risk/graphics/components/RegionValueBoard.h"

#include <SFML/Graphics.hpp>
#include <string>

namespace risk {

class BoardGraphics {
private:
    sf::Texture boardTexture;
    sf::Sprite boardSprite;

   RegionValueBoard regionBoard;

public:
    BoardGraphics(
        const std::string& mapImagePath,
        const sf::Font& font);

    void draw(sf::RenderWindow& window) const;

    void drawRegionUI(sf::RenderWindow& window) const;

    bool handleRegionClick(sf::Vector2f mousePosition);
};

} // namespace risk
