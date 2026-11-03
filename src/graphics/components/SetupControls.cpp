
#include "risk/graphics/components/SetupControls.h"

#include <algorithm>
#include <stdexcept>

namespace risk {

//-------------------------------------------------
// Constructor
//-------------------------------------------------

SetupControls::SetupControls(const sf::Font& font)
    : backButton(buttonTexture),
      confirmButton(buttonTexture)
{
    if (!buttonTexture.loadFromFile(
        "data/graphics/components/SelectionButton.png"))
    {
        throw std::runtime_error(
            "Could not load selection button texture");
    }

    backButton.setTexture(buttonTexture, true);
    confirmButton.setTexture(buttonTexture, true);

    //-------------------------------------------------
    // Crop transparent texture padding
    //-------------------------------------------------

    const sf::IntRect buttonRect(
        {20, 23},
        {160, 57}
    );

    backButton.setTextureRect(buttonRect);
    confirmButton.setTextureRect(buttonRect);

    //-------------------------------------------------
    // Button text
    //-------------------------------------------------

    backButtonText.emplace(font);
    confirmButtonText.emplace(font);

    backButtonText->setString("Back");
    confirmButtonText->setString("Confirm");

    backButtonText->setCharacterSize(20);
    confirmButtonText->setCharacterSize(20);

    backButtonText->setFillColor(sf::Color::White);
    confirmButtonText->setFillColor(sf::Color::White);
}

//-------------------------------------------------
// Calculate complete stack position
//-------------------------------------------------

sf::Vector2f SetupControls::calculateStackPosition(
    sf::Vector2f counterCentre) const
{
    constexpr float screenWidth = 1920.f;
    constexpr float screenHeight = 1080.f;

    constexpr float margin = 50.f;
    constexpr float gap = 15.f;
    constexpr float buttonSpacing = 5.f;
    constexpr float counterRadius = 21.f;

    //-------------------------------------------------
    // Actual cropped sprite dimensions
    //-------------------------------------------------

    const sf::FloatRect buttonBounds =
        confirmButton.getLocalBounds();

    const float buttonWidth =
        buttonBounds.size.x;

    const float buttonHeight =
        buttonBounds.size.y;

    const float stackHeight =
        buttonHeight * 2.f + buttonSpacing;

    //-------------------------------------------------
    // Horizontal positioning
    //-------------------------------------------------

    // Prefer left of troop counter.
    const float leftX =
        counterCentre.x
        - counterRadius
        - gap
        - buttonWidth;

    // Alternative: right of troop counter.
    const float rightX =
        counterCentre.x
        + counterRadius
        + gap;

    float x;

    if (leftX >= margin)
    {
        x = leftX;
    }
    else
    {
        x = rightX;
    }

    // If right side exceeds screen boundary,
    // switch back to the left.
    if (x + buttonWidth > screenWidth - margin)
    {
        x = leftX;
    }

    //-------------------------------------------------
    // Vertical positioning
    //-------------------------------------------------

    // Centre complete stack on troop counter.
    float y =
        counterCentre.y - stackHeight / 2.f;

    // Keep entire stack within screen margins.
    y = std::clamp(
        y,
        margin,
        screenHeight - margin - stackHeight
    );

    return {x, y};
}

//-------------------------------------------------
// Centre text on button
//-------------------------------------------------

void SetupControls::centreText(
    sf::Text& text,
    const sf::Sprite& button)
{
    const sf::FloatRect textBounds =
        text.getLocalBounds();

    text.setOrigin({
        textBounds.position.x
            + textBounds.size.x / 2.f,
        textBounds.position.y
            + textBounds.size.y / 2.f
    });

    const sf::FloatRect buttonBounds =
        button.getGlobalBounds();

    text.setPosition({
        buttonBounds.position.x
            + buttonBounds.size.x / 2.f,
        buttonBounds.position.y
            + buttonBounds.size.y / 2.f
    });
}

//-------------------------------------------------
// Position both buttons
//-------------------------------------------------

void SetupControls::setPosition(
    sf::Vector2f counterCentre)
{
    constexpr float buttonSpacing = 5.f;

    const sf::Vector2f stackPosition =
        calculateStackPosition(counterCentre);

    const float buttonHeight =
        confirmButton.getLocalBounds().size.y;

    //-------------------------------------------------
    // Confirm above Back
    //-------------------------------------------------

    confirmButton.setPosition(stackPosition);

    backButton.setPosition({
        stackPosition.x,
        stackPosition.y + buttonHeight + buttonSpacing
    });

    //-------------------------------------------------
    // Update text positions
    //-------------------------------------------------

    if (confirmButtonText.has_value())
    {
        centreText(
            *confirmButtonText,
            confirmButton);
    }

    if (backButtonText.has_value())
    {
        centreText(
            *backButtonText,
            backButton);
    }
}

//-------------------------------------------------
// Button bounds for mouse detection
//-------------------------------------------------

sf::FloatRect SetupControls::getBackBounds() const
{
    return backButton.getGlobalBounds();
}

sf::FloatRect SetupControls::getConfirmBounds() const
{
    return confirmButton.getGlobalBounds();
}

//-------------------------------------------------
// Draw
//-------------------------------------------------

void SetupControls::draw(sf::RenderWindow& window)
{
    window.draw(confirmButton);
    window.draw(backButton);

    if (confirmButtonText.has_value())
    {
        window.draw(*confirmButtonText);
    }

    if (backButtonText.has_value())
    {
        window.draw(*backButtonText);
    }
}

} // namespace risk
