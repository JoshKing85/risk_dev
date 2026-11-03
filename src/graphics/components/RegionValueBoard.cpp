
#include "risk/graphics/components/RegionValueBoard.h"

#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace risk {

//---------------------------------------------------------
// Initialization
//---------------------------------------------------------

RegionValueBoard::RegionValueBoard(
    const sf::Font& font,
    sf::Vector2f position)
    : buttonSprite(buttonTexture),
      arrowSprite(arrowTexture),
      panelSprite(panelTexture)
{
    //-----------------------------------------------------
    // Load textures
    //-----------------------------------------------------

    if (!buttonTexture.loadFromFile(
        "data/graphics/board/RegionDropdownButton.png"))
    {
        throw std::runtime_error(
            "Could not load region dropdown button");
    }

    if (!arrowTexture.loadFromFile(
        "data/graphics/board/BrassArrow.png"))
    {
        throw std::runtime_error(
            "Could not load region dropdown arrow");
    }

    if (!panelTexture.loadFromFile(
        "data/graphics/board/RegionDropdownPanel.png"))
    {
        throw std::runtime_error(
            "Could not load region dropdown panel");
    }

    //-----------------------------------------------------
    // Button
    //-----------------------------------------------------

    buttonSprite.setTexture(buttonTexture, true);

    // Position supplied by BoardGraphics.
    buttonSprite.setPosition({
        position.x + 125.f,
        position.y
    });

    //-----------------------------------------------------
    // Arrow
    //-----------------------------------------------------

    arrowSprite.setTexture(arrowTexture, true);

    // Centre the arrow around its rotation point.
    const sf::FloatRect arrowBounds =
        arrowSprite.getLocalBounds();

    arrowSprite.setOrigin({
        arrowBounds.position.x +
            arrowBounds.size.x / 2.f,
        arrowBounds.position.y +
            arrowBounds.size.y / 2.f
    });

    // Position relative to the actual button dimensions.
    const sf::FloatRect buttonBounds =
        buttonSprite.getGlobalBounds();

    arrowSprite.setPosition({
        buttonBounds.position.x +
            buttonBounds.size.x - 25.f,
        buttonBounds.position.y +
            buttonBounds.size.y / 2.f
    });

    //-----------------------------------------------------
    // Dropdown panel
    //-----------------------------------------------------

    panelSprite.setTexture(panelTexture, true);

    // Align the panel directly beneath the button.

    panelSprite.setPosition({
        position.x,
        position.y + -20.f
    });

    //-----------------------------------------------------
    // Region values
    //-----------------------------------------------------

    const std::vector<std::pair<std::string, int>> values = {
        {"British Isles", 3},
        {"Western Europe", 5},
        {"German States", 5},
        {"Austrian Empire", 6},
        {"Italian States", 4},
        {"Scandinavia", 3},
        {"Russian Empire", 7}
    };

    // Text positions are relative to the panel.
    const sf::FloatRect panelBounds =
        panelSprite.getGlobalBounds();

    const float textCentreX =
        panelBounds.position.x +
        panelBounds.size.x / 2.f;

    float textY =
        panelBounds.position.y + 100.f;

    for (const auto& [name, bonus] : values)
    {
        sf::Text text(
            font,
            name + "  +" + std::to_string(bonus),
            23
        );

        text.setFillColor(
            sf::Color(232, 207, 151));

        const sf::FloatRect bounds =
            text.getLocalBounds();

        text.setOrigin({
            bounds.position.x +
                bounds.size.x / 2.f,
            bounds.position.y +
                bounds.size.y / 2.f
        });

        text.setPosition({
            textCentreX,
            textY
        });

        regionTexts.push_back(std::move(text));

        textY += 53.f;
    }
}

//---------------------------------------------------------
// Interaction
//---------------------------------------------------------

bool RegionValueBoard::handleClick(
    sf::Vector2f mousePosition)
{
    if (!buttonSprite.getGlobalBounds().contains(
        mousePosition))
    {
        return false;
    }

    expanded = !expanded;

    arrowSprite.setRotation(
        sf::degrees(expanded ? 180.f : 0.f));

    return true;
}

//---------------------------------------------------------
// Draw
//---------------------------------------------------------

void RegionValueBoard::draw(
    sf::RenderWindow& window) const
{
    if (expanded)
    {
        window.draw(panelSprite);

        for (const auto& text : regionTexts)
        {
            window.draw(text);
        }
    }

    // Keep the button and arrow above the panel.
    window.draw(buttonSprite);
    window.draw(arrowSprite);
}

} // namespace risk
