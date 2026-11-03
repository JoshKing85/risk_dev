#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>
#include <utility>

namespace risk {

class RegionValueBoard {
private:
    sf::Texture buttonTexture;
    sf::Texture arrowTexture;
    sf::Texture panelTexture;

    sf::Sprite buttonSprite;
    sf::Sprite arrowSprite;
    sf::Sprite panelSprite;

    std::vector<sf::Text> regionTexts;

    bool expanded = false;

public:
    RegionValueBoard(
        const sf::Font& font,
        sf::Vector2f position);

    bool handleClick(sf::Vector2f mousePosition);

    void draw(sf::RenderWindow& window) const;
};

} // namespace risk