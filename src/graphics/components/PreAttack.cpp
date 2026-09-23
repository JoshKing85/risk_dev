#include "risk/graphics/components/PreAttackBox.h"

namespace risk {

    PreAttackBox::PreAttackBox(
        const sf::Font& font)
    {
        //---------------------------------------------------------
        // Container
        //---------------------------------------------------------

        preAttackBox.setSize({
            400.0f,
            220.0f
            });

        preAttackBox.setFillColor(
            sf::Color(220, 220, 220));

        preAttackBox.setOutlineColor(
            sf::Color::Black);

        preAttackBox.setOutlineThickness(
            2.0f);

        //---------------------------------------------------------
        // From Territory
        //---------------------------------------------------------

        fromTerritoryText.emplace(font);
        fromTerritoryText->setCharacterSize(20);
        fromTerritoryText->setFillColor(sf::Color::Black);
        fromTerritoryText->setStyle(sf::Text::Bold);

        fromPlayerText.emplace(font);
        fromPlayerText->setCharacterSize(18);
        fromPlayerText->setFillColor(sf::Color::Black);

        fromTroopText.emplace(font);
        fromTroopText->setCharacterSize(18);
        fromTroopText->setFillColor(sf::Color::Black);

        //---------------------------------------------------------
        // To Territory
        //---------------------------------------------------------

        toTerritoryText.emplace(font);
        toTerritoryText->setCharacterSize(20);
        toTerritoryText->setFillColor(sf::Color::Black);
        toTerritoryText->setStyle(sf::Text::Bold);

        toPlayerText.emplace(font);
        toPlayerText->setCharacterSize(18);
        toPlayerText->setFillColor(sf::Color::Black);

        toTroopText.emplace(font);
        toTroopText->setCharacterSize(18);
        toTroopText->setFillColor(sf::Color::Black);

        //---------------------------------------------------------
        // Back Button
        //---------------------------------------------------------

        backButton.setSize({
            140.0f,
            50.0f
            });

        backButton.setFillColor(
            sf::Color(70, 70, 70));

        backButton.setOutlineColor(
            sf::Color::Black);

        backButton.setOutlineThickness(
            2.0f);

        backButtonText.emplace(font);
        backButtonText->setString("BACK");
        backButtonText->setCharacterSize(20);
        backButtonText->setFillColor(sf::Color::White);
        backButtonText->setStyle(sf::Text::Bold);

        //---------------------------------------------------------
        // Confirm Button
        //---------------------------------------------------------

        confirmButton.setSize({
            140.0f,
            50.0f
            });

        confirmButton.setFillColor(
            sf::Color(70, 70, 70));

        confirmButton.setOutlineColor(
            sf::Color::Black);

        confirmButton.setOutlineThickness(
            2.0f);

        confirmButtonText.emplace(font);
        confirmButtonText->setString("CONFIRM");
        confirmButtonText->setCharacterSize(20);
        confirmButtonText->setFillColor(sf::Color::White);
        confirmButtonText->setStyle(sf::Text::Bold);
    }


    //=========================================================
    // POSITION
    //=========================================================

    void PreAttackBox::setPosition(
        sf::Vector2f position)
    {
        preAttackBox.setPosition(
            position);

        //---------------------------------------------------------
        // From Territory
        //---------------------------------------------------------

        fromTerritoryText->setPosition({
            position.x + 20.0f,
            position.y + 20.0f
            });

        fromPlayerText->setPosition({
            position.x + 20.0f,
            position.y + 55.0f
            });

        fromTroopText->setPosition({
            position.x + 20.0f,
            position.y + 85.0f
            });

        //---------------------------------------------------------
        // To Territory
        //---------------------------------------------------------

        toTerritoryText->setPosition({
            position.x + 220.0f,
            position.y + 20.0f
            });

        toPlayerText->setPosition({
            position.x + 220.0f,
            position.y + 55.0f
            });

        toTroopText->setPosition({
            position.x + 220.0f,
            position.y + 85.0f
            });

        //---------------------------------------------------------
        // Back Button
        //---------------------------------------------------------

        backButton.setPosition({
            position.x + 30.0f,
            position.y + 150.0f
            });

        sf::FloatRect backTextBounds =
            backButtonText->getLocalBounds();

        backButtonText->setOrigin({
            backTextBounds.position.x +
                backTextBounds.size.x / 2.0f,
            backTextBounds.position.y +
                backTextBounds.size.y / 2.0f
            });

        backButtonText->setPosition({
            position.x + 100.0f,
            position.y + 175.0f
            });

        //---------------------------------------------------------
        // Confirm Button
        //---------------------------------------------------------

        confirmButton.setPosition({
            position.x + 230.0f,
            position.y + 150.0f
            });

        sf::FloatRect confirmTextBounds =
            confirmButtonText->getLocalBounds();

        confirmButtonText->setOrigin({
            confirmTextBounds.position.x +
                confirmTextBounds.size.x / 2.0f,
            confirmTextBounds.position.y +
                confirmTextBounds.size.y / 2.0f
            });

        confirmButtonText->setPosition({
            position.x + 300.0f,
            position.y + 175.0f
            });
    }


    //=========================================================
    // FROM TERRITORY
    //=========================================================

    void PreAttackBox::setFromTerritoryName(
        const std::string& name)
    {
        fromTerritoryText->setString(
            name);
    }


    void PreAttackBox::setFromPlayerName(
        const std::string& name)
    {
        fromPlayerText->setString(
            name);
    }


    void PreAttackBox::setFromTroopCount(
        int troopCount)
    {
        fromTroopText->setString(
            "Troops: " +
            std::to_string(troopCount));
    }


    //=========================================================
    // TO TERRITORY
    //=========================================================

    void PreAttackBox::setToTerritoryName(
        const std::string& name)
    {
        toTerritoryText->setString(
            name);
    }


    void PreAttackBox::setToPlayerName(
        const std::string& name)
    {
        toPlayerText->setString(
            name);
    }


    void PreAttackBox::setToTroopCount(
        int troopCount)
    {
        toTroopText->setString(
            "Troops: " +
            std::to_string(troopCount));
    }


    //=========================================================
    // BOUNDS
    //=========================================================

    sf::FloatRect PreAttackBox::getBackBounds() const
    {
        return backButton.getGlobalBounds();
    }


    sf::FloatRect PreAttackBox::getConfirmBounds() const
    {
        return confirmButton.getGlobalBounds();
    }


    //=========================================================
    // DRAW
    //=========================================================

    void PreAttackBox::draw(
        sf::RenderWindow& window)
    {
        window.draw(
            preAttackBox);

        window.draw(
            *fromTerritoryText);

        window.draw(
            *fromPlayerText);

        window.draw(
            *fromTroopText);

        window.draw(
            *toTerritoryText);

        window.draw(
            *toPlayerText);

        window.draw(
            *toTroopText);

        window.draw(
            backButton);

        window.draw(
            *backButtonText);

        window.draw(
            confirmButton);

        window.draw(
            *confirmButtonText);
    }

} // namespace risk