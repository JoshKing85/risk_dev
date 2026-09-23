#include "risk/graphics/game_elements/BoardGraphics.h"

#include <stdexcept>
#include <string>

namespace risk {

    BoardGraphics::BoardGraphics(
        const std::string& mapImagePath,
        const sf::Font& font)
        : mapSprite(mapTexture)
    {
        if (!mapTexture.loadFromFile(mapImagePath))
        {
            throw std::runtime_error(
                "Could not load map image: " + mapImagePath);
        }

        mapSprite.setTexture(mapTexture, true);

        sf::Vector2u textureSize =
            mapTexture.getSize();

        float scaleX =
            1920.f / static_cast<float>(textureSize.x);

        float scaleY =
            1080.f / static_cast<float>(textureSize.y);

        mapSprite.setScale(
            { scaleX, scaleY });
    }


    void BoardGraphics::addContinentValue(
        std::string continentName,
        int continentValue,
        sf::Vector2f position,
        sf::Vector2f size,
        unsigned int characterSize,
        const sf::Font& font)
    {
        continentValues.emplace_back(
            continentName,
            continentValue,
            position,
            size,
            characterSize,
            font);
    }


    void BoardGraphics::draw(
        sf::RenderWindow& window) const
    {
        // Back layer
        window.draw(mapSprite);

        // Board information layer
        for (const auto& continentValue :
            continentValues)
        {
            continentValue.draw(window);
        }
    }

} // namespace risk