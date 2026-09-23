#include "risk/graphics/components/ReinforceControls.h"

#include <string>

namespace risk {

    ReinforceControls::ReinforceControls(const sf::Font& font)
    {
        //---------------------------------------------------------
        // Button Sizes
        //---------------------------------------------------------

        backButton.setSize(
            { 120.0f, 40.0f });

        confirmButton.setSize(
            { 120.0f, 40.0f });

        addTroopsButton.setSize(
            { 40.0f, 40.0f });

        removeTroopsButton.setSize(
            { 40.0f, 40.0f });

        remainingTroops.setSize(
            { 120.0f, 40.0f });

        //---------------------------------------------------------
        // Button Colours
        //---------------------------------------------------------

        backButton.setFillColor(
            sf::Color(50, 70, 85));

        confirmButton.setFillColor(
            sf::Color(50, 70, 85));

        addTroopsButton.setFillColor(
            sf::Color(50, 70, 85));

        removeTroopsButton.setFillColor(
            sf::Color(50, 70, 85));

        remainingTroops.setFillColor(
            sf::Color(50, 70, 85));

        //---------------------------------------------------------
        // Text
        //---------------------------------------------------------

        backButtonText.emplace(font);
        confirmButtonText.emplace(font);
        addTroopsText.emplace(font);
        removeTroopsText.emplace(font);
        remainingTroopsText.emplace(font);

        backButtonText->setString("Back");
        confirmButtonText->setString("Confirm");
        addTroopsText->setString("+");
        removeTroopsText->setString("-");
        remainingTroopsText->setString("Remaining: 0");

        backButtonText->setCharacterSize(20);
        confirmButtonText->setCharacterSize(20);
        addTroopsText->setCharacterSize(20);
        removeTroopsText->setCharacterSize(20);
        remainingTroopsText->setCharacterSize(16);

        backButtonText->setFillColor(
            sf::Color::White);

        confirmButtonText->setFillColor(
            sf::Color::White);

        addTroopsText->setFillColor(
            sf::Color::White);

        removeTroopsText->setFillColor(
            sf::Color::White);

        remainingTroopsText->setFillColor(
            sf::Color::White);
    }


    //---------------------------------------------------------
    // Positioning
    //---------------------------------------------------------

    void ReinforceControls::setBackPosition(
        sf::Vector2f position)
    {
        backButton.setPosition(position);

        backButtonText->setPosition(
            {
                position.x + 10.0f,
                position.y + 8.0f
            });
    }


    void ReinforceControls::setConfirmPosition(
        sf::Vector2f position)
    {
        confirmButton.setPosition(position);

        confirmButtonText->setPosition(
            {
                position.x + 10.0f,
                position.y + 8.0f
            });
    }


    void ReinforceControls::setTroopControlsPosition(
        sf::Vector2f position)
    {
        //---------------------------------------------------------
        // Remove
        //---------------------------------------------------------

        removeTroopsButton.setPosition(
            position);

        removeTroopsText->setPosition(
            {
                position.x + 14.0f,
                position.y + 8.0f
            });

        //---------------------------------------------------------
        // Remaining Troops
        //---------------------------------------------------------

        remainingTroops.setPosition(
            {
                position.x + 50.0f,
                position.y
            });

        remainingTroopsText->setPosition(
            {
                position.x + 58.0f,
                position.y + 10.0f
            });

        //---------------------------------------------------------
        // Add
        //---------------------------------------------------------

        addTroopsButton.setPosition(
            {
                position.x + 180.0f,
                position.y
            });

        addTroopsText->setPosition(
            {
                position.x + 194.0f,
                position.y + 8.0f
            });

        //---------------------------------------------------------
        // Back
        //---------------------------------------------------------

        backButton.setPosition(
            {
                position.x,
                position.y + 50.0f
            });

        backButtonText->setPosition(
            {
                position.x + 10.0f,
                position.y + 58.0f
            });

        //---------------------------------------------------------
        // Confirm
        //---------------------------------------------------------

        confirmButton.setPosition(
            {
                position.x + 130.0f,
                position.y + 50.0f
            });

        confirmButtonText->setPosition(
            {
                position.x + 140.0f,
                position.y + 58.0f
            });
    }


    //---------------------------------------------------------
    // Remaining Troops
    //---------------------------------------------------------

    void ReinforceControls::setRemainingTroops(
        int troopCount)
    {
        remainingTroopsText->setString(
            "Remaining: " +
            std::to_string(troopCount));
    }


    //---------------------------------------------------------
    // Bounds
    //---------------------------------------------------------

    sf::FloatRect ReinforceControls::getBackBounds() const
    {
        return backButton.getGlobalBounds();
    }


    sf::FloatRect ReinforceControls::getConfirmBounds() const
    {
        return confirmButton.getGlobalBounds();
    }


    sf::FloatRect ReinforceControls::getAddTroopsBounds() const
    {
        return addTroopsButton.getGlobalBounds();
    }


    sf::FloatRect ReinforceControls::getRemoveTroopsBounds() const
    {
        return removeTroopsButton.getGlobalBounds();
    }


    //---------------------------------------------------------
    // Draw
    //---------------------------------------------------------

    void ReinforceControls::draw(
        sf::RenderWindow& window)
    {
        window.draw(backButton);
        window.draw(confirmButton);

        window.draw(removeTroopsButton);
        window.draw(remainingTroops);
        window.draw(addTroopsButton);

        window.draw(*backButtonText);
        window.draw(*confirmButtonText);

        window.draw(*removeTroopsText);
        window.draw(*remainingTroopsText);
        window.draw(*addTroopsText);
    }

} // namespace risk