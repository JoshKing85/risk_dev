#include "risk/graphics/components/PlayerIndicator.h"

namespace risk {

    PlayerIndicator::PlayerIndicator(const sf::Font& font)
    {
        currentPlayerBox.setSize(
            { 220.0f, 45.0f });

        currentPlayerBox.setFillColor(
            sf::Color(30, 40, 50, 230));

        currentPlayerBox.setOutlineColor(
            sf::Color::White);

        currentPlayerBox.setOutlineThickness(
            2.0f);

        currentPlayerText.emplace(font);

        currentPlayerText->setString(
            "PLACE YOUR TROOP");

        currentPlayerText->setCharacterSize(
            18);

        currentPlayerText->setFillColor(
            sf::Color::White);

        currentPlayerArrow.setPointCount(3);

        currentPlayerArrow.setPoint(
            0,
            { 0.0f, 0.0f });

        currentPlayerArrow.setPoint(
            1,
            { 30.0f, 0.0f });

        currentPlayerArrow.setPoint(
            2,
            { 15.0f, 20.0f });

        currentPlayerArrow.setFillColor(
            sf::Color::White);
    }

    void PlayerIndicator::setPosition(int playerID)
    {
        float playerX =
            static_cast<float>(
                playerID * 320);

        float boxX =
            playerX + 50.0f;

        float boxY =
            755.0f;

        currentPlayerBox.setPosition(
            { boxX, boxY });

        if (currentPlayerText.has_value())
        {
            currentPlayerText->setPosition(
                {
                    boxX + 20.0f,
                    boxY + 11.0f
                });
        }

        currentPlayerArrow.setPosition(
            {
                playerX + 145.0f,
                boxY + 48.0f
            });
    }

    void PlayerIndicator::draw(
        sf::RenderWindow& window)
    {
        window.draw(
            currentPlayerBox);

        if (currentPlayerText.has_value())
        {
            window.draw(
                *currentPlayerText);
        }

        window.draw(
            currentPlayerArrow);
    }

} // namespace risk