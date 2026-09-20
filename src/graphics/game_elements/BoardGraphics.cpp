#include "risk/graphics/game_elements/BoardGraphics.h"

#include <stdexcept>
#include <string>

#include <iostream>
namespace risk
{
    BoardGraphics::BoardGraphics(
        const std::string& mapImagePath,
        const sf::Font& font
    )
        : mapSprite(mapTexture)
    {
        if (!mapTexture.loadFromFile(mapImagePath))
        {
            throw std::runtime_error(
                "Could not load map image: " + mapImagePath
            );
        }

        mapSprite.setTexture(mapTexture, true);

        sf::Vector2u textureSize = mapTexture.getSize();

        float scaleX =
            1920.f / static_cast<float>(textureSize.x);

        float scaleY =
            1080.f / static_cast<float>(textureSize.y);

        mapSprite.setScale({ scaleX, scaleY });
    }


    void BoardGraphics::addContinentValue(
        std::string continentName,
        int continentValue,
        sf::Vector2f position,
        sf::Vector2f size,
        unsigned int characterSize,
        const sf::Font& font
    )
    {
        sf::RectangleShape box(size);

        box.setPosition(position);
        box.setFillColor(sf::Color(50, 50, 50));
        box.setOutlineColor(sf::Color::White);
        box.setOutlineThickness(2.f);

        continentValueBoxes.push_back(box);


        sf::Text text(font);

        text.setString(
            continentName + "  " + std::to_string(continentValue)
        );
        text.setCharacterSize(characterSize);
        text.setFillColor(sf::Color::White);
        text.setPosition(position);

        continentValueTexts.push_back(text);
    }


    void BoardGraphics::draw(sf::RenderWindow& window) const
    {
        // Back layer
        window.draw(mapSprite);

        // Board information layer
        for (const auto& box : continentValueBoxes)
        {
            window.draw(box);
        }

        for (const auto& text : continentValueTexts)
        {
            window.draw(text);
        }
    }
}