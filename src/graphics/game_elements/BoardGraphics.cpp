
#include "risk/graphics/game_elements/BoardGraphics.h"

#include <stdexcept>
#include <string>

namespace risk {

BoardGraphics::BoardGraphics(
    const std::string& mapImagePath,
    const sf::Font& font)
    : boardSprite(boardTexture),
      regionBoard(font, {40.f, 0.f})
{
    //-------------------------------------------------
    // Board parchment
    //-------------------------------------------------

    if (!boardTexture.loadFromFile(
        "data/graphics/board/BoardParchment.png"))
    {
        throw std::runtime_error(
            "Could not load board parchment");
    }

    boardSprite.setTexture(boardTexture, true);

    const sf::Vector2u textureSize =
        boardTexture.getSize();

    float scaleX =
        1920.f / static_cast<float>(textureSize.x);

    float scaleY =
        1080.f / static_cast<float>(textureSize.y);

    boardSprite.setScale({scaleX, scaleY});
}

void BoardGraphics::draw(
    sf::RenderWindow& window) const
{
    window.draw(boardSprite);
}

void BoardGraphics::drawRegionUI(
    sf::RenderWindow& window) const
{
    regionBoard.draw(window);
}

bool BoardGraphics::handleRegionClick(
    sf::Vector2f mousePosition)
{
    return regionBoard.handleClick(mousePosition);
}

} // namespace risk
