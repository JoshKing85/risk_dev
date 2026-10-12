#include "risk/graphics/components/PlayerIndicator.h"

#include <stdexcept>

namespace risk {

    PlayerIndicator::PlayerIndicator(
        const sf::Font& font)
        : pointerSprite(pointerTexture),
        instructionSprite(instructionTexture)
    {
        // -----------------------------
        // Pointer asset
        // -----------------------------

        if (!pointerTexture.loadFromFile(
            "data/graphics/components/Pointer.png"))
        {
            throw std::runtime_error(
                "Could not load active player pointer");
        }

        pointerSprite.setTexture(
            pointerTexture,
            true);
        
        pointerTexture.setSmooth(true);
        // -----------------------------
        // Instruction plate
        // -----------------------------

        if (!instructionTexture.loadFromFile(
            "data/graphics/components/InstructionsPanel.png"))
        {
            throw std::runtime_error(
                "Could not load player instruction panel");
        }

        instructionSprite.setTexture(
            instructionTexture,
            true);


        // -----------------------------
        // Instruction text
        // -----------------------------

        currentPlayerText.emplace(font);

        currentPlayerText->setString(
            "PLACE YOUR TROOP");

        currentPlayerText->setCharacterSize(
            18);

        currentPlayerText->setFillColor(
            sf::Color(235, 215, 170));
    }


    void PlayerIndicator::setPosition(
        int playerID)
    {
        // -----------------------------
        // Player panel layout
        // -----------------------------

        constexpr float startX =
            31.0f;

        constexpr float panelWidth =
            311.0f;

        float playerX =
            startX +
            static_cast<float>(playerID) *
            panelWidth;

        // -----------------------------
        // Instruction plate
        // -----------------------------

        constexpr float instructionX =
            75.0f;

        constexpr float instructionY =
            650.0f;

        instructionSprite.setPosition(
            {
                instructionX,
                instructionY
            });

        // -----------------------------
        // Instruction text
        // -----------------------------

        if (currentPlayerText.has_value())
        {
            sf::FloatRect textBounds =
                currentPlayerText->getLocalBounds();

            sf::FloatRect plateBounds =
                instructionSprite.getGlobalBounds();

            currentPlayerText->setPosition(
                {
                    plateBounds.position.x +
                    (plateBounds.size.x -
                     textBounds.size.x) / 2.0f -
                    textBounds.position.x,

                    plateBounds.position.y +
                    (plateBounds.size.y -
                     textBounds.size.y) / 2.0f -
                    textBounds.position.y
                });
        }

        // -----------------------------
        // Active player pointer
        // -----------------------------

        sf::FloatRect pointerBounds =
            pointerSprite.getLocalBounds();

        float playerCentreX =
            playerX +
            panelWidth / 2.0f;

        pointerSprite.setPosition(
            {
                playerCentreX -
                pointerBounds.size.x / 2.0f,

                720.0f
            });
    }


    void PlayerIndicator::draw(
        sf::RenderWindow& window)
    {
        // Instruction plate
        //window.draw(
        //    instructionSprite);

        //// Instruction text
        //if (currentPlayerText.has_value())
        //{
        //    window.draw(
        //        *currentPlayerText);
        //}

        // Active player pointer
        window.draw(
            pointerSprite);
    }

} // namespace risk