#include "risk/graphics/game_elements/BoardGraphics.h"

#include <stdexcept>
#include <string>

namespace risk {

    BoardGraphics::BoardGraphics(
        const std::string& mapImagePath,
        const sf::Font& font)
        : boardSprite(boardTexture)
    {
        if (!boardTexture.loadFromFile("data/graphics/board/BoardParchment.png"))
        {
            throw std::runtime_error(
                "Could not load map image: " );
        }

        boardSprite.setTexture(boardTexture, true);

        sf::Vector2u textureSize =
            boardTexture.getSize();

        float scaleX =
            1920.f / static_cast<float>(textureSize.x);

        float scaleY =
            1080.f / static_cast<float>(textureSize.y);

        boardSprite.setScale(
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
        window.draw(boardSprite);

        // Board information layer
        for (const auto& continentValue :
            continentValues)
        {
            continentValue.draw(window);
        }
    }

} // namespace risk