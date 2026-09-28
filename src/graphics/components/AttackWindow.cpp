#include "risk/graphics/components/AttackWindow.h"

#include <algorithm>
#include <string>

namespace risk {

    //---------------------------------------------------------
    // Constructor
    //---------------------------------------------------------

    AttackWindow::AttackWindow(const sf::Font& font)
        : position({ 350.0f, 180.0f })
    {
        //-----------------------------------------------------
        // Container
        //-----------------------------------------------------

        attackWindow.setSize({
            1200.0f,
            600.0f
            });

        attackWindow.setFillColor(
            sf::Color(30, 35, 45));

        attackWindow.setOutlineColor(
            sf::Color::White);

        attackWindow.setOutlineThickness(
            2.0f);

        //-----------------------------------------------------
        // From Territory
        //-----------------------------------------------------

        fromTerritoryText.emplace(font);
        fromTerritoryText->setCharacterSize(24);
        fromTerritoryText->setFillColor(sf::Color::White);

        fromPlayerText.emplace(font);
        fromPlayerText->setCharacterSize(22);
        fromPlayerText->setFillColor(sf::Color::White);

        fromTroopText.emplace(font);
        fromTroopText->setCharacterSize(20);
        fromTroopText->setFillColor(sf::Color::White);

        fromTerritoryShape.setFillColor(
            sf::Color(180, 60, 60));

        fromTerritoryShape.setOutlineColor(
            sf::Color::White);

        fromTerritoryShape.setOutlineThickness(
            2.0f);

        //-----------------------------------------------------
        // To Territory
        //-----------------------------------------------------

        toTerritoryText.emplace(font);
        toTerritoryText->setCharacterSize(24);
        toTerritoryText->setFillColor(sf::Color::White);

        toPlayerText.emplace(font);
        toPlayerText->setCharacterSize(22);
        toPlayerText->setFillColor(sf::Color::White);

        toTroopText.emplace(font);
        toTroopText->setCharacterSize(20);
        toTroopText->setFillColor(sf::Color::White);

        toTerritoryShape.setFillColor(
            sf::Color(60, 100, 180));

        toTerritoryShape.setOutlineColor(
            sf::Color::White);

        toTerritoryShape.setOutlineThickness(
            2.0f);

        //-----------------------------------------------------
        // Dice
        //-----------------------------------------------------

        attackerDiceText.emplace(font);
        attackerDiceText->setString(
            "Attacker Dice");
        attackerDiceText->setCharacterSize(22);
        attackerDiceText->setFillColor(
            sf::Color::White);

        defenderDiceText.emplace(font);
        defenderDiceText->setString(
            "Defender Dice");
        defenderDiceText->setCharacterSize(22);
        defenderDiceText->setFillColor(
            sf::Color::White);

        //-----------------------------------------------------
        // Attacker Dice
        //-----------------------------------------------------

        for (int i = 0; i < 3; ++i)
        {
            sf::RectangleShape diceButton(
                { 50.0f, 50.0f });

            diceButton.setFillColor(
                sf::Color(70, 70, 70));

            diceButton.setOutlineThickness(
                2.0f);

            diceButton.setOutlineColor(
                sf::Color::White);

            attackerDiceButtons.push_back(
                diceButton);

            sf::Text diceNumber(font);

            diceNumber.setString(
                std::to_string(i + 1));

            diceNumber.setCharacterSize(
                24);

            diceNumber.setFillColor(
                sf::Color::White);

            attackerDiceNumbers.push_back(
                diceNumber);
        }

        //-----------------------------------------------------
        // Defender Dice
        //-----------------------------------------------------

        for (int i = 0; i < 2; ++i)
        {
            sf::RectangleShape diceBox(
                { 50.0f, 50.0f });

            diceBox.setFillColor(
                sf::Color(70, 70, 70));

            diceBox.setOutlineThickness(
                2.0f);

            diceBox.setOutlineColor(
                sf::Color::White);

            defenderDiceBoxes.push_back(
                diceBox);

            sf::Text diceNumber(font);

            diceNumber.setString(
                std::to_string(i + 1));

            diceNumber.setCharacterSize(
                24);

            diceNumber.setFillColor(
                sf::Color::White);

            defenderDiceNumbers.push_back(
                diceNumber);
        }

        //-----------------------------------------------------
        // Result
        //-----------------------------------------------------

        attackResultText.emplace(font);
        attackResultText->setString("");
        attackResultText->setCharacterSize(24);
        attackResultText->setFillColor(
            sf::Color::White);

        //-----------------------------------------------------
        // Quit Attack
        //-----------------------------------------------------

        quitAttackButton.setSize({
            180.0f,
            55.0f
            });

        quitAttackButton.setFillColor(
            sf::Color(150, 50, 50));

        quitAttackText.emplace(font);
        quitAttackText->setString(
            "Quit Attack");
        quitAttackText->setCharacterSize(20);
        quitAttackText->setFillColor(
            sf::Color::White);

        //-----------------------------------------------------
        // Attack
        //-----------------------------------------------------

        attackButton.setSize({
            180.0f,
            55.0f
            });

        attackButton.setFillColor(
            sf::Color(180, 140, 50));

        attackButtonText.emplace(font);
        attackButtonText->setString(
            "Attack");
        attackButtonText->setCharacterSize(20);
        attackButtonText->setFillColor(
            sf::Color::Black);

        //-----------------------------------------------------
        // Add Troop
        //-----------------------------------------------------

        addTroopButton.setSize({
            55.0f,
            55.0f
            });

        addTroopButton.setFillColor(
            sf::Color(70, 80, 95));

        addTroopText.emplace(font);
        addTroopText->setString("+");
        addTroopText->setCharacterSize(28);
        addTroopText->setFillColor(
            sf::Color::White);

        //-----------------------------------------------------
        // Remove Troop
        //-----------------------------------------------------

        removeTroopButton.setSize({
            55.0f,
            55.0f
            });

        removeTroopButton.setFillColor(
            sf::Color(70, 80, 95));

        removeTroopText.emplace(font);
        removeTroopText->setString("-");
        removeTroopText->setCharacterSize(28);
        removeTroopText->setFillColor(
            sf::Color::White);

        //-----------------------------------------------------
        // Move Troop Count
        //-----------------------------------------------------

        moveTroopCountText.emplace(font);
        moveTroopCountText->setString("0");
        moveTroopCountText->setCharacterSize(24);
        moveTroopCountText->setFillColor(
            sf::Color::White);

        //-----------------------------------------------------
        // Confirm Move
        //-----------------------------------------------------

        confirmMoveButton.setSize({
            180.0f,
            55.0f
            });

        confirmMoveButton.setFillColor(
            sf::Color(50, 140, 70));

        confirmMoveText.emplace(font);
        confirmMoveText->setString(
            "Confirm Move");
        confirmMoveText->setCharacterSize(20);
        confirmMoveText->setFillColor(
            sf::Color::White);

        //-----------------------------------------------------
        // Default Position
        //-----------------------------------------------------

        setPosition(position);
    }


    //---------------------------------------------------------
    // Position
    //---------------------------------------------------------

    void AttackWindow::setPosition(
        sf::Vector2f newPosition)
    {
        position = newPosition;

        attackWindow.setPosition(
            position);

        //-----------------------------------------------------
        // From Side
        //-----------------------------------------------------

        fromTerritoryShape.setPosition({
            position.x + 230.0f,
            position.y + 90.0f
            });

        fromTerritoryText->setPosition({
            position.x + 230.0f,
            position.y + 250.0f
            });

        fromPlayerText->setPosition({
            position.x + 50.0f,
            position.y + 250.0f
            });

        fromTroopText->setPosition({
            position.x + 230.0f,
            position.y + 290.0f
            });

        //-----------------------------------------------------
        // To Side
        //-----------------------------------------------------

        toTerritoryShape.setPosition({
            position.x + 820.0f,
            position.y + 90.0f
            });

        toTerritoryText->setPosition({
            position.x + 820.0f,
            position.y + 250.0f
            });

        toPlayerText->setPosition({
            position.x + 1010.0f,
            position.y + 250.0f
            });

        toTroopText->setPosition({
            position.x + 820.0f,
            position.y + 290.0f
            });

        //-----------------------------------------------------
        // Existing Avatars
        //-----------------------------------------------------

        if (fromAvatar)
        {
            fromAvatar->setPosition({
                position.x + 50.0f,
                position.y + 80.0f
                });
        }

        if (toAvatar)
        {
            toAvatar->setPosition({
                position.x + 1010.0f,
                position.y + 80.0f
                });
        }

        //-----------------------------------------------------
        // Dice
        //-----------------------------------------------------

        attackerDiceText->setPosition({
            position.x + 455.0f,
            position.y + 110.0f
            });

        defenderDiceText->setPosition({
            position.x + 650.0f,
            position.y + 110.0f
            });

        //-----------------------------------------------------
        // Attacker Dice
        //-----------------------------------------------------

        for (std::size_t i = 0;
            i < attackerDiceButtons.size();
            ++i)
        {
            float x =
                position.x + 455.0f +
                static_cast<float>(i) * 65.0f;

            float y =
                position.y + 155.0f;

            attackerDiceButtons[i].setPosition(
                { x, y });

            attackerDiceNumbers[i].setPosition(
                { x + 18.0f, y + 9.0f });
        }

        //-----------------------------------------------------
        // Defender Dice
        //-----------------------------------------------------

        for (std::size_t i = 0;
            i < defenderDiceBoxes.size();
            ++i)
        {
            float x =
                position.x + 650.0f +
                static_cast<float>(i) * 65.0f;

            float y =
                position.y + 155.0f;

            defenderDiceBoxes[i].setPosition(
                { x, y });

            defenderDiceNumbers[i].setPosition(
                { x + 18.0f, y + 9.0f });
        }

        //-----------------------------------------------------
        // Result
        //-----------------------------------------------------

        attackResultText->setPosition({
            position.x + 470.0f,
            position.y + 230.0f
            });

        //-----------------------------------------------------
        // Bottom Controls
        //-----------------------------------------------------

        quitAttackButton.setPosition({
            position.x + 40.0f,
            position.y + 500.0f
            });

        quitAttackText->setPosition({
            position.x + 70.0f,
            position.y + 515.0f
            });

        removeTroopButton.setPosition({
            position.x + 430.0f,
            position.y + 500.0f
            });

        removeTroopText->setPosition({
            position.x + 450.0f,
            position.y + 510.0f
            });

        moveTroopCountText->setPosition({
            position.x + 510.0f,
            position.y + 512.0f
            });

        addTroopButton.setPosition({
            position.x + 550.0f,
            position.y + 500.0f
            });

        addTroopText->setPosition({
            position.x + 568.0f,
            position.y + 508.0f
            });

        confirmMoveButton.setPosition({
            position.x + 630.0f,
            position.y + 500.0f
            });

        confirmMoveText->setPosition({
            position.x + 650.0f,
            position.y + 515.0f
            });

        attackButton.setPosition({
            position.x + 980.0f,
            position.y + 500.0f
            });

        attackButtonText->setPosition({
            position.x + 1035.0f,
            position.y + 515.0f
            });
    }


    //---------------------------------------------------------
    // From Territory
    //---------------------------------------------------------

    void AttackWindow::setFromTerritoryName(
        const std::string& name)
    {
        fromTerritoryText->setString(
            name);
    }


    void AttackWindow::setFromPlayerName(
        const std::string& name)
    {
        fromPlayerText->setString(
            name);
    }


    void AttackWindow::setFromTroopCount(
        int troopCount)
    {
        fromTroopText->setString(
            std::to_string(troopCount) +
            " troops");
    }


    void AttackWindow::setFromAvatar(
        int avatarID)
    {
        std::string avatarPath;

        switch (avatarID)
        {
        case 0:
            avatarPath =
                "C:/Users/joshk/programming/risk_V1/data/graphics/avatars/nelson.png";
            break;

        case 1:
            avatarPath =
                "C:/Users/joshk/programming/risk_V1/data/graphics/avatars/samurai.png";
            break;

        case 2:
            avatarPath =
                "C:/Users/joshk/programming/risk_V1/data/graphics/avatars/viking.png";
            break;

        default:
            avatarPath =
                "C:/Users/joshk/programming/risk_V1/data/graphics/avatars/blank.png";
            break;
        }

        if (fromAvatarTexture.loadFromFile(
            avatarPath))
        {
            fromAvatar.emplace(
                fromAvatarTexture);

            sf::Vector2u size =
                fromAvatarTexture.getSize();

            fromAvatar->setScale({
                120.0f / size.x,
                120.0f / size.y
                });

            fromAvatar->setPosition({
                position.x + 50.0f,
                position.y + 80.0f
                });
        }
    }


    void AttackWindow::setFromVertices(
        const std::vector<sf::Vector2f>& vertices)
    {
        if (vertices.empty())
        {
            return;
        }

        float minX = vertices[0].x;
        float maxX = vertices[0].x;
        float minY = vertices[0].y;
        float maxY = vertices[0].y;

        for (const auto& vertex : vertices)
        {
            minX =
                std::min(minX, vertex.x);

            maxX =
                std::max(maxX, vertex.x);

            minY =
                std::min(minY, vertex.y);

            maxY =
                std::max(maxY, vertex.y);
        }

        float width =
            maxX - minX;

        float height =
            maxY - minY;

        float scaleX =
            150.0f / width;

        float scaleY =
            130.0f / height;

        float scale =
            std::min(scaleX, scaleY);

        fromTerritoryShape.setPointCount(
            vertices.size());

        for (std::size_t i = 0;
            i < vertices.size();
            i++)
        {
            fromTerritoryShape.setPoint(
                i,
                {
                    (vertices[i].x - minX) * scale,
                    (vertices[i].y - minY) * scale
                });
        }
    }


    //---------------------------------------------------------
    // To Territory
    //---------------------------------------------------------

    void AttackWindow::setToTerritoryName(
        const std::string& name)
    {
        toTerritoryText->setString(
            name);
    }


    void AttackWindow::setToPlayerName(
        const std::string& name)
    {
        toPlayerText->setString(
            name);
    }


    void AttackWindow::setToTroopCount(
        int troopCount)
    {
        toTroopText->setString(
            std::to_string(troopCount) +
            " troops");
    }


    void AttackWindow::setToAvatar(
        int avatarID)
    {
        std::string avatarPath;

        switch (avatarID)
        {
        case 0:
            avatarPath =
                "C:/Users/joshk/programming/risk_V1/data/graphics/avatars/nelson.png";
            break;

        case 1:
            avatarPath =
                "C:/Users/joshk/programming/risk_V1/data/graphics/avatars/samurai.png";
            break;

        case 2:
            avatarPath =
                "C:/Users/joshk/programming/risk_V1/data/graphics/avatars/viking.png";
            break;

        default:
            avatarPath =
                "C:/Users/joshk/programming/risk_V1/data/graphics/avatars/blank.png";
            break;
        }

        if (toAvatarTexture.loadFromFile(
            avatarPath))
        {
            toAvatar.emplace(
                toAvatarTexture);

            sf::Vector2u size =
                toAvatarTexture.getSize();

            toAvatar->setScale({
                120.0f / size.x,
                120.0f / size.y
                });

            toAvatar->setPosition({
                position.x + 1010.0f,
                position.y + 80.0f
                });
        }
    }


    void AttackWindow::setToVertices(
        const std::vector<sf::Vector2f>& vertices)
    {
        if (vertices.empty())
        {
            return;
        }

        float minX = vertices[0].x;
        float maxX = vertices[0].x;
        float minY = vertices[0].y;
        float maxY = vertices[0].y;

        for (const auto& vertex : vertices)
        {
            minX =
                std::min(minX, vertex.x);

            maxX =
                std::max(maxX, vertex.x);

            minY =
                std::min(minY, vertex.y);

            maxY =
                std::max(maxY, vertex.y);
        }

        float width =
            maxX - minX;

        float height =
            maxY - minY;

        float scaleX =
            150.0f / width;

        float scaleY =
            130.0f / height;

        float scale =
            std::min(scaleX, scaleY);

        toTerritoryShape.setPointCount(
            vertices.size());

        for (std::size_t i = 0;
            i < vertices.size();
            i++)
        {
            toTerritoryShape.setPoint(
                i,
                {
                    (vertices[i].x - minX) * scale,
                    (vertices[i].y - minY) * scale
                });
        }
    }


    //---------------------------------------------------------
    // Move Troop Count
    //---------------------------------------------------------

    void AttackWindow::setMoveTroopCount(
        int troopCount)
    {
        moveTroopCountText->setString(
            std::to_string(troopCount));
    }


    //---------------------------------------------------------
    // Dice
    //---------------------------------------------------------

    void AttackWindow::setAttackerDice(
        int diceCount)
    {
        selectedAttackerDice =
            diceCount;

        for (std::size_t i = 0;
            i < attackerDiceButtons.size();
            ++i)
        {
            if (static_cast<int>(i) <
                selectedAttackerDice)
            {
                attackerDiceButtons[i].setOutlineColor(
                    sf::Color::Yellow);

                attackerDiceButtons[i].setOutlineThickness(
                    4.0f);
            }
            else
            {
                attackerDiceButtons[i].setOutlineColor(
                    sf::Color::White);

                attackerDiceButtons[i].setOutlineThickness(
                    2.0f);
            }
        }
    }


    void AttackWindow::setDefenderDice(
        int diceCount)
    {
        selectedDefenderDice =
            diceCount;

        for (std::size_t i = 0;
            i < defenderDiceBoxes.size();
            ++i)
        {
            if (static_cast<int>(i) <
                selectedDefenderDice)
            {
                defenderDiceBoxes[i].setOutlineColor(
                    sf::Color::Yellow);

                defenderDiceBoxes[i].setOutlineThickness(
                    4.0f);
            }
            else
            {
                defenderDiceBoxes[i].setOutlineColor(
                    sf::Color::White);

                defenderDiceBoxes[i].setOutlineThickness(
                    2.0f);
            }
        }
    }


    int AttackWindow::getAttackerDiceSelection(
        sf::Vector2f mousePosition) const
    {
        for (std::size_t i = 0;
            i < attackerDiceButtons.size();
            ++i)
        {
            if (attackerDiceButtons[i]
                .getGlobalBounds()
                .contains(mousePosition))
            {
                return static_cast<int>(i) + 1;
            }
        }

        return 0;
    }


    void AttackWindow::clearDice()
    {
        selectedAttackerDice = 0;
        selectedDefenderDice = 0;

        for (auto& diceButton :
            attackerDiceButtons)
        {
            diceButton.setOutlineColor(
                sf::Color::White);

            diceButton.setOutlineThickness(
                2.0f);
        }

        for (auto& diceBox :
            defenderDiceBoxes)
        {
            diceBox.setOutlineColor(
                sf::Color::White);

            diceBox.setOutlineThickness(
                2.0f);
        }
    }


    //---------------------------------------------------------
    // Result
    //---------------------------------------------------------

    void AttackWindow::setAttackResult(
        const AttackResult& result,
        const std::vector<int>& attackingDice,
        const std::vector<int>& defendingDice)
    {
        attackResultText->setString(
            "Attacker Losses: " +
            std::to_string(result.attackerLosses) +
            "    Defender Losses: " +
            std::to_string(result.defenderLosses));

        for (std::size_t i = 0;
            i < attackerResultDiceNumbers.size();
            ++i)
        {
            if (i < attackingDice.size() && i < 2)
            {
                attackerResultDiceNumbers[i].setString(
                    std::to_string(attackingDice[i]));
            }
            else
            {
                attackerResultDiceNumbers[i].setString("");
            }
        }

        for (std::size_t i = 0;
            i < defenderResultDiceNumbers.size();
            ++i)
        {
            if (i < defendingDice.size() && i < 2)
            {
                defenderResultDiceNumbers[i].setString(
                    std::to_string(defendingDice[i]));
            }
            else
            {
                defenderResultDiceNumbers[i].setString("");
            }
        }
    }


    //---------------------------------------------------------
    // Bounds
    //---------------------------------------------------------

    sf::FloatRect AttackWindow::getQuitAttackBounds() const
    {
        return quitAttackButton.getGlobalBounds();
    }


    sf::FloatRect AttackWindow::getAttackBounds() const
    {
        return attackButton.getGlobalBounds();
    }


    sf::FloatRect AttackWindow::getAddTroopBounds() const
    {
        return addTroopButton.getGlobalBounds();
    }


    sf::FloatRect AttackWindow::getRemoveTroopBounds() const
    {
        return removeTroopButton.getGlobalBounds();
    }


    sf::FloatRect AttackWindow::getConfirmMoveBounds() const
    {
        return confirmMoveButton.getGlobalBounds();
    }


    //---------------------------------------------------------
    // Draw
    //---------------------------------------------------------

    void AttackWindow::draw(
        sf::RenderWindow& window)
    {
        window.draw(
            attackWindow);

        //-----------------------------------------------------
        // From
        //-----------------------------------------------------

        window.draw(
            fromTerritoryShape);

        if (fromAvatar)
        {
            window.draw(
                *fromAvatar);
        }

        if (fromTerritoryText)
        {
            window.draw(
                *fromTerritoryText);
        }

        if (fromPlayerText)
        {
            window.draw(
                *fromPlayerText);
        }

        if (fromTroopText)
        {
            window.draw(
                *fromTroopText);
        }

        //-----------------------------------------------------
        // To
        //-----------------------------------------------------

        window.draw(
            toTerritoryShape);

        if (toAvatar)
        {
            window.draw(
                *toAvatar);
        }

        if (toTerritoryText)
        {
            window.draw(
                *toTerritoryText);
        }

        if (toPlayerText)
        {
            window.draw(
                *toPlayerText);
        }

        if (toTroopText)
        {
            window.draw(
                *toTroopText);
        }

        //-----------------------------------------------------
        // Dice
        //-----------------------------------------------------

        if (attackerDiceText)
        {
            window.draw(
                *attackerDiceText);
        }

        for (const auto& diceButton :
            attackerDiceButtons)
        {
            window.draw(
                diceButton);
        }

        for (const auto& diceNumber :
            attackerDiceNumbers)
        {
            window.draw(
                diceNumber);
        }

        if (defenderDiceText)
        {
            window.draw(
                *defenderDiceText);
        }

        for (const auto& diceBox :
            defenderDiceBoxes)
        {
            window.draw(
                diceBox);
        }

        for (const auto& diceNumber :
            defenderDiceNumbers)
        {
            window.draw(
                diceNumber);
        }

        //-----------------------------------------------------
        // Result
        //-----------------------------------------------------

        if (attackResultText)
        {
            window.draw(
                *attackResultText);
        }

        //-----------------------------------------------------
        // Quit Attack
        //-----------------------------------------------------

        window.draw(
            quitAttackButton);

        if (quitAttackText)
        {
            window.draw(
                *quitAttackText);
        }

        //-----------------------------------------------------
        // Move Troops
        //-----------------------------------------------------

        window.draw(
            removeTroopButton);

        if (removeTroopText)
        {
            window.draw(
                *removeTroopText);
        }

        if (moveTroopCountText)
        {
            window.draw(
                *moveTroopCountText);
        }

        window.draw(
            addTroopButton);

        if (addTroopText)
        {
            window.draw(
                *addTroopText);
        }

        window.draw(
            confirmMoveButton);

        if (confirmMoveText)
        {
            window.draw(
                *confirmMoveText);
        }

        //-----------------------------------------------------
        // Attack
        //-----------------------------------------------------

        window.draw(
            attackButton);

        if (attackButtonText)
        {
            window.draw(
                *attackButtonText);
        }
    }

} // namespace risk