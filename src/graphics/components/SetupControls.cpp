#include "risk/graphics/components/SetupControls.h"

namespace risk {

    SetupControls::SetupControls(const sf::Font& font)
    {
        backButton.setSize(
            { 120.0f, 40.0f });

        confirmButton.setSize(
            { 120.0f, 40.0f });

        backButton.setFillColor(
            sf::Color(50, 70, 85));

        confirmButton.setFillColor(
            sf::Color(50, 70, 85));

        backButtonText.emplace(font);
        confirmButtonText.emplace(font);

        backButtonText->setString("Back");
        confirmButtonText->setString("Confirm");

        backButtonText->setCharacterSize(20);
        confirmButtonText->setCharacterSize(20);

        backButtonText->setFillColor(
            sf::Color::White);

        confirmButtonText->setFillColor(
            sf::Color::White);
    }

    void SetupControls::setBackPosition(
        sf::Vector2f position)
    {
        backButton.setPosition(position);

        if (backButtonText.has_value())
        {
            backButtonText->setPosition(
                {
                    position.x + 10.0f,
                    position.y + 8.0f
                });
        }
    }

    void SetupControls::setConfirmPosition(
        sf::Vector2f position)
    {
        confirmButton.setPosition(position);

        if (confirmButtonText.has_value())
        {
            confirmButtonText->setPosition(
                {
                    position.x + 10.0f,
                    position.y + 8.0f
                });
        }
    }

    sf::FloatRect SetupControls::getBackBounds() const
    {
        return backButton.getGlobalBounds();
    }

    sf::FloatRect SetupControls::getConfirmBounds() const
    {
        return confirmButton.getGlobalBounds();
    }

    void SetupControls::draw(
        sf::RenderWindow& window)
    {
        window.draw(backButton);
        window.draw(confirmButton);

        if (backButtonText.has_value())
        {
            window.draw(*backButtonText);
        }

        if (confirmButtonText.has_value())
        {
            window.draw(*confirmButtonText);
        }
    }

} // namespace risk