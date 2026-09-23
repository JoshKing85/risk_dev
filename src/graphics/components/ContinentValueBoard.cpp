#include "risk/graphics/components/ContinentValueBoard.h"

namespace risk {

    ContinentValueBoard::ContinentValueBoard(
        const std::string& continentName,
        int continentValue,
        sf::Vector2f position,
        sf::Vector2f size,
        unsigned int characterSize,
        const sf::Font& font)
        : box(size),
        text(font)
    {
        box.setPosition(position);
        box.setFillColor(sf::Color(50, 50, 50));
        box.setOutlineColor(sf::Color::White);
        box.setOutlineThickness(2.f);

        text.setString(
            continentName + "  " + std::to_string(continentValue));

        text.setCharacterSize(characterSize);
        text.setFillColor(sf::Color::White);
        text.setPosition(position);
    }

    void ContinentValueBoard::draw(
        sf::RenderWindow& window) const
    {
        window.draw(box);
        window.draw(text);
    }

} // namespace risk