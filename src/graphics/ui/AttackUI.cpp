#include "risk/graphics/ui/AttackUI.h"
#include "risk/core/validation/ValidateTroopCountInput.h"

#include <iostream>

namespace risk {

    AttackUI::AttackUI(
        const sf::Font& font,
        const std::unordered_map<TerritoryID, TerritoryGraphics>& territoryGraphicsMap,
        GameState& gameState,
        GameSession& gameSession)
        : phaseTitle(font)
    {
        //-----------------------------------------------------
        // Phase title
        //-----------------------------------------------------

        phaseTitle.setString(
            "ATTACK PHASE");

        phaseTitle.setCharacterSize(
            28);

        phaseTitle.setFillColor(
            sf::Color::Black);

        phaseTitle.setStyle(
            sf::Text::Bold);

        sf::FloatRect titleBounds =
            phaseTitle.getLocalBounds();

        phaseTitle.setOrigin({
            titleBounds.position.x +
                titleBounds.size.x / 2.0f,
            titleBounds.position.y
            });

        phaseTitle.setPosition({
            960.0f,
            20.0f
            });

        //-----------------------------------------------------
        // Fortify button
        //-----------------------------------------------------

        fortifyButton.setSize({
            240.0f,
            80.0f
            });

        fortifyButton.setOrigin({
            120.0f,
            40.0f
            });

        fortifyButton.setPosition({
            960.0f,
            700.0f
            });

        fortifyButton.setFillColor(
            sf::Color(70, 70, 70));

        fortifyButton.setOutlineColor(
            sf::Color::Black);

        fortifyButton.setOutlineThickness(
            2.0f);

        //-----------------------------------------------------
        // Fortify Button Text
        //-----------------------------------------------------

        fortifyButtonText.emplace(
            font);

        fortifyButtonText->setString(
            "FORTIFY");

        fortifyButtonText->setCharacterSize(
            28);

        fortifyButtonText->setFillColor(
            sf::Color::White);

        fortifyButtonText->setStyle(
            sf::Text::Bold);

        sf::FloatRect textBounds =
            fortifyButtonText->getLocalBounds();

        fortifyButtonText->setOrigin({
            textBounds.position.x +
                textBounds.size.x / 2.0f,
            textBounds.position.y +
                textBounds.size.y / 2.0f
            });

        fortifyButtonText->setPosition({
            960.0f,
            700.0f
            });

        //-----------------------------------------------------
        // Card container
        //-----------------------------------------------------

        cardContainer.emplace(
            font,
            territoryGraphicsMap,
            gameState.getPlayerCards());

        //-----------------------------------------------------
        // Attack components
        //-----------------------------------------------------

        preAttackBox.emplace(
            font);

        attackWindow.emplace(
            font);

        playerIndicator.emplace(
            font);

        playerIndicator->setPosition(
            gameState.getPlayerTurnID());
    }


    void AttackUI::handleAttackEvent(
        const sf::Event& event,
        sf::RenderWindow& window,
        GameSession& gameSession,
        GameState& gameState,
        std::vector<PlayerGraphics>& playerGraphics,
        std::unordered_map<TerritoryID, TerritoryGraphics>& territoryGraphicsMap)
    {
        if (const auto* mousePressed =
            event.getIf<sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition = {
                static_cast<float>(
                    mousePressed->position.x),
                static_cast<float>(
                    mousePressed->position.y)
            };

            sf::FloatRect bounds =
                fortifyButton.getGlobalBounds();

            if (gameState.getAttackConfirmed() == false &&
                bounds.contains(mousePosition))
            {
                fortify(gameState);
                return;
            }
        }

        if (gameState.getFromTerritorySelection() == TerritoryID::None ||
            gameState.getToTerritorySelection() == TerritoryID::None)
        {
            territorySelection(
                event,
                window,
                gameSession,
                gameState,
                territoryGraphicsMap);
        }
        else if (gameState.getAttackConfirmed() == false &&
            gameState.getToTerritorySelection() != TerritoryID::None)
        {
            handlePreAttack(
                event,
                window,
                gameSession,
                gameState,
                playerGraphics,
                territoryGraphicsMap);
        }
        else if (gameState.getAttackConfirmed() == true)
        {
            handleAttackWindow(
                event,
                window,
                gameSession,
                gameState,
                playerGraphics,
                territoryGraphicsMap);
        }
    }


    //---------------------------------------------------------
    // Territory Selection
    //---------------------------------------------------------

    void AttackUI::territorySelection(
        const sf::Event& event,
        sf::RenderWindow& window,
        GameSession& gameSession,
        GameState& gameState,
        std::unordered_map<TerritoryID, TerritoryGraphics>& territoryGraphicsMap)
    {
        TerritoryID fromTerritory =
            gameState.getFromTerritorySelection();

        TerritoryID toTerritory =
            gameState.getToTerritorySelection();

        if (const auto* mousePressed =
            event.getIf<sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition = {
                static_cast<float>(
                    mousePressed->position.x),
                static_cast<float>(
                    mousePressed->position.y)
            };

            for (auto& [territoryID, territoryGraphics] :
                territoryGraphicsMap)
            {
                if (territoryGraphics.contains(
                    mousePosition))
                {
                    //-------------------------------------------------
                    // FROM selection
                    //-------------------------------------------------

                    if (fromTerritory == TerritoryID::None)
                    {
                        TerritoryID selectedTerritoryID =
                            territoryID;

                        bool validFrom =
                            gameSession.validateAttackSelection(
                                gameState.getPlayerTurnID(),
                                selectedTerritoryID);

                        if (validFrom)
                        {
                            gameState.setFromSelection(
                                selectedTerritoryID);
                        }

                        return;
                    }

                    TerritoryID selectedTerritoryID =
                        territoryID;

                    //-------------------------------------------------
                    // TO selection
                    //-------------------------------------------------

                    bool validTo =
                        gameSession.validateAttackInput(
                            territoryID,
                            fromTerritory);

                    if (validTo)
                    {
                        gameState.setToSelection(
                            territoryID);

                        sf::FloatRect bounds =
                            territoryGraphics.getBounds();

                        float boxX =
                            bounds.position.x +
                            bounds.size.x +
                            10.0f;

                        float boxY =
                            bounds.position.y;

                        if (boxX + 400.0f >
                            static_cast<float>(
                                window.getSize().x))
                        {
                            boxX =
                                bounds.position.x -
                                400.0f -
                                10.0f;
                        }

                        preAttackBox->setPosition({
                            boxX,
                            boxY
                            });
                    }

                    //-------------------------------------------------
                    // CHANGE FROM selection
                    //-------------------------------------------------

                    else if (gameSession.validateAttackSelection(
                        gameState.getPlayerTurnID(),
                        selectedTerritoryID))
                    {
                        gameState.setFromSelection(
                            selectedTerritoryID);
                    }

                    return;
                }
            }
        }
    }


    //---------------------------------------------------------
    // Pre Attack
    //---------------------------------------------------------

    void AttackUI::handlePreAttack(
        const sf::Event& event,
        sf::RenderWindow& window,
        GameSession& gameSession,
        GameState& gameState,
        std::vector<PlayerGraphics>& playerGraphics,
        std::unordered_map<TerritoryID, TerritoryGraphics>& territoryGraphicsMap)
    {
        if (const auto* mousePressed =
            event.getIf<sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition = {
                static_cast<float>(
                    mousePressed->position.x),
                static_cast<float>(
                    mousePressed->position.y)
            };

            if (preAttackBox->getBackBounds().contains(
                mousePosition))
            {
                back(
                    gameSession,
                    gameState);

                return;
            }

            if (preAttackBox->getConfirmBounds().contains(
                mousePosition))
            {
                confirm(
                    gameSession,
                    gameState,
                    playerGraphics,
                    territoryGraphicsMap);

                return;
            }
        }
    }


    void AttackUI::back(
        GameSession& gameSession,
        GameState& gameState)
    {
        gameState.clearAttack();
    }


    void AttackUI::confirm(
        GameSession& gameSession,
        GameState& gameState,
        std::vector<PlayerGraphics>& playerGraphics,
        std::unordered_map<TerritoryID, TerritoryGraphics>& territoryGraphicsMap)
    {
        gameState.setAttackConfirmed(
            true);

        gameSession.createAttackOrder(
            gameState);

        setAttackWindow(
            gameState,
            gameSession,
            playerGraphics,
            territoryGraphicsMap);
    }


    void AttackUI::handleAttackWindow(
        const sf::Event& event,
        sf::RenderWindow& window,
        GameSession& gameSession,
        GameState& gameState,
        std::vector<PlayerGraphics>& playerGraphics,
        std::unordered_map<TerritoryID, TerritoryGraphics>& territoryGraphicsMap)
    {
        if (const auto* mousePressed =
            event.getIf<sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition = {
                static_cast<float>(
                    mousePressed->position.x),
                static_cast<float>(
                    mousePressed->position.y)
            };

            std::cout << "\n========== ATTACK WINDOW ==========\n";

            std::cout << "FROM: "
                << static_cast<int>(
                    gameState.getFromTerritorySelection())
                << "\n";

            std::cout << "TO: "
                << static_cast<int>(
                    gameState.getToTerritorySelection())
                << "\n";

            std::cout << "Attack confirmed: "
                << gameState.getAttackConfirmed()
                << "\n";

            std::cout << "Attacker dice: "
                << gameState.getAttackerDice()
                << "\n";

            std::cout << "Has move order: "
                << gameState.hasMoveTroopsOrder()
                << "\n";

            if (gameState.hasMoveTroopsOrder())
            {
                std::cout << "Move completed: "
                    << gameState.getLastMoveTroopsOrder()
                    .isCompleted()
                    << "\n";

                std::cout << "Troops moving: "
                    << gameState.getLastMoveTroopsOrder()
                    .getTroopsMoved()
                    << "\n";
            }

            //---------------------------------------------------------
            // Move Troops
            //---------------------------------------------------------

            if (gameState.hasMoveTroopsOrder() &&
                !gameState.getLastMoveTroopsOrder().isCompleted())
            {
                std::cout << "[ROUTE] MOVE TROOPS\n";

                if (attackWindow->getAddTroopBounds().contains(
                    mousePosition))
                {
                    std::cout << "[CLICK] ADD TROOP\n";

                    addTroops(
                        gameSession,
                        gameState);

                    std::cout << "Troops moving after add: "
                        << gameState.getLastMoveTroopsOrder()
                        .getTroopsMoved()
                        << "\n";

                    return;
                }

                if (attackWindow->getRemoveTroopBounds().contains(
                    mousePosition))
                {
                    std::cout << "[CLICK] REMOVE TROOP\n";

                    removeTroops(
                        gameSession,
                        gameState);

                    std::cout << "Troops moving after remove: "
                        << gameState.getLastMoveTroopsOrder()
                        .getTroopsMoved()
                        << "\n";

                    return;
                }

                if (attackWindow->getConfirmMoveBounds().contains(
                    mousePosition))
                {
                    std::cout << "[CLICK] CONFIRM MOVE\n";

                    confirmMove(
                        gameState,
                        gameSession);

                    std::cout << "[AFTER CONFIRM] Move completed: "
                        << gameState.getLastMoveTroopsOrder()
                        .isCompleted()
                        << "\n";

                    return;
                }

                std::cout << "[MOVE] Click matched no move control\n";
                return;
            }

            //---------------------------------------------------------
            // Attack
            //---------------------------------------------------------

            std::cout << "[ROUTE] NORMAL ATTACK\n";

            int diceCount =
                attackWindow->getAttackerDiceSelection(
                    mousePosition);

            if (diceCount > 0)
            {
                std::cout << "[CLICK] DICE: "
                    << diceCount
                    << "\n";

                selectDice(
                    diceCount,
                    gameState,
                    gameSession);

                return;
            }

            if (attackWindow->getAttackBounds().contains(
                mousePosition))
            {
                std::cout << "[CLICK] ATTACK\n";

                attack(
                    gameState,
                    gameSession);

                return;
            }

            if (attackWindow->getQuitAttackBounds().contains(
                mousePosition))
            {
                std::cout << "[CLICK] QUIT ATTACK\n";

                quitAttack(
                    gameState,
                    gameSession);

                return;
            }

            std::cout << "[ATTACK] Click matched no attack control\n";
        }
    }


    void AttackUI::setAttackWindow(
        GameState& gameState,
        GameSession& gameSession,
        std::vector<PlayerGraphics>& playerGraphics,
        std::unordered_map<TerritoryID, TerritoryGraphics>& territoryGraphicsMap)
    {
        int attPlayerID =
            gameState.getPlayerTurnID();

        int attTroopCount =
            gameState.getLastAttackOrder()
            .getAttackingTroopCount();

        int defTroopCount =
            gameState.getLastAttackOrder()
            .getDefendingTroopCount();

        TerritoryGraphics& fromTerritory =
            territoryGraphicsMap.at(
                gameState.getFromTerritorySelection());

        std::string fromTitle =
            fromTerritory.getTitle();

        const std::vector<sf::Vector2f>& fromVertices =
            fromTerritory.getVertices();

        int defPlayerID =
            gameSession.getMap()
            .getTerritory(
                gameState.getToTerritorySelection())
            .getOwnerID();

        TerritoryGraphics& toTerritory =
            territoryGraphicsMap.at(
                gameState.getToTerritorySelection());

        std::string toTitle =
            toTerritory.getTitle();

        const std::vector<sf::Vector2f>& toVertices =
            toTerritory.getVertices();

        for (auto& player : playerGraphics)
        {
            if (player.getPlayerID() ==
                attPlayerID)
            {
                attackWindow->setFromPlayerName(
                    player.getName());

                attackWindow->setFromAvatar(
                    player.getAvatarID());

                attackWindow->setFromTroopCount(
                    attTroopCount);

                attackWindow->setFromTerritoryName(
                    fromTitle);

                attackWindow->setFromVertices(
                    fromVertices);
            }

            if (player.getPlayerID() ==
                defPlayerID)
            {
                attackWindow->setToPlayerName(
                    player.getName());

                attackWindow->setToAvatar(
                    player.getAvatarID());

                attackWindow->setToTroopCount(
                    defTroopCount);

                attackWindow->setToTerritoryName(
                    toTitle);

                attackWindow->setToVertices(
                    toVertices);

                attackWindow->setToTroopCount(
                    defTroopCount);

                attackWindow->setDefenderDice(
                    defTroopCount >= 2 ? 2 : 1);
            }
        }
    }


    //---------------------------------------------------------
    // Dice
    //---------------------------------------------------------

    void AttackUI::selectDice(
        int diceCount,
        GameState& gameState,
        GameSession& gameSession)
    {
        bool validDice =
            gameSession.validateDiceInput(
                diceCount,
                gameState);

        if (!validDice)
        {
            return;
        }

        if (gameState.getAttackerDice() > 0)
        {
            gameSession.updateRollDiceOrder(
                diceCount);
        }
        else
        {
            gameSession.createRollDiceOrder(
                diceCount,
                gameState);
        }

        gameState.setAttackerDice(
            diceCount);

        attackWindow->setAttackerDice(
            diceCount);
    }


    //---------------------------------------------------------
    // Attack
    //---------------------------------------------------------

    void AttackUI::attack(
        GameState& gameState,
        GameSession& gameSession)
    {
        gameSession.executeAttackOrder(
            gameState);

        AttackOutcome outcome =
            gameState.getLastAttackOrder()
            .getResult()
            .attackOutcome;

        TerritoryID fromTerritory =
            gameState.getFromTerritorySelection();

        TerritoryID toTerritory =
            gameState.getToTerritorySelection();

        int diceCount =
            gameState.getAttackerDice();

        int troopsAvailable =
            gameState.getLastAttackOrder()
            .getResult()
            .attackingTroopCount - 1;

        //-----------------------------------------------------
        // Attack Result Debug
        //-----------------------------------------------------

        const auto& attackingDice =
            gameState.getLastRollDiceOrder()
            .getAttackingDice();

        const auto& defendingDice =
            gameState.getLastRollDiceOrder()
            .getDefendingDice();

        const auto& result =
            gameState.getLastAttackOrder()
            .getResult();

        std::cout << "\n========== ATTACK RESULT ==========\n";

        std::cout << "Attacker dice: ";

        for (int dice : attackingDice)
        {
            std::cout << dice << " ";
        }

        std::cout << "\nDefender dice: ";

        for (int dice : defendingDice)
        {
            std::cout << dice << " ";
        }

        std::cout << "\n\nAttacker losses: "
            << result.attackerLosses;

        std::cout << "\nDefender losses: "
            << result.defenderLosses;

        std::cout << "\n\nAttacker troops remaining: "
            << result.attackingTroopCount;

        std::cout << "\nDefender troops remaining: "
            << result.defendingTroopCount;

        std::cout << "\nOutcome: ";

        switch (outcome)
        {
        case AttackOutcome::Captured:
            std::cout << "Captured";
            break;

        case AttackOutcome::DefenderGain:
            std::cout << "DefenderGain";
            break;

        case AttackOutcome::AttackerGain:
            std::cout << "AttackerGain";
            break;

        case AttackOutcome::Draw:
            std::cout << "Draw";
            break;
        }

        std::cout << "\n===================================\n"
            << std::endl;

        //-----------------------------------------------------
        // Capture
        //-----------------------------------------------------

        if (outcome == AttackOutcome::Captured)
        {
            if (troopsAvailable >= diceCount)
            {
                gameSession.createMoveTroopsOrder(
                    fromTerritory,
                    toTerritory,
                    diceCount,
                    gameState);
                attackWindow->setMoveTroopCount(
                    gameState.getLastMoveTroopsOrder().getTroopsMoved());
                
                if (troopsAvailable == diceCount)
                {
                    gameSession.executeMoveTroopsOrder(
                        gameState);

                    attackWindow->clearDice();
                    gameState.clearAttack();

                    return;
                }

                return;
            }
            
            gameSession.createMoveTroopsOrder(
                fromTerritory,
                toTerritory,
                troopsAvailable,
                gameState);

            return;
        }

        //-----------------------------------------------------
        // Continue Attack
        //-----------------------------------------------------

        if (troopsAvailable > 0)
        {
            gameSession.createAttackOrder(
                gameState);

            gameState.setAttackerDice(0);

            attackWindow->clearDice();

            attackWindow->setDefenderDice(
                gameState.getLastAttackOrder()
                .getDefendingTroopCount() >= 2
                ? 2
                : 1);

            attackWindow->setFromTroopCount(
                gameState.getLastAttackOrder()
                .getAttackingTroopCount());

            attackWindow->setToTroopCount(
                gameState.getLastAttackOrder()
                .getDefendingTroopCount());

            return;
        }

        gameState.clearAttack();
        attackWindow->clearDice();
    }


    //---------------------------------------------------------
    // Quit Attack
    //---------------------------------------------------------

    void AttackUI::quitAttack(
        GameState& gameState,
        GameSession& gameSession)
    {
        if (!gameState.getLastRollDiceOrder().isCompleted())
        {
            gameSession.undoRollDiceOrder(
                gameState);
        }

        if (!gameState.getLastAttackOrder().isCompleted())
        {
            gameSession.undoAttackOrder(
                gameState);
        }

        gameState.clearAttack();
        attackWindow->clearDice();
    }


    //---------------------------------------------------------
    // Move Troops
    //---------------------------------------------------------

    void AttackUI::addTroops(
        GameSession& gameSession,
        GameState& gameState)
    {
        int troopCount =
            gameState.getLastMoveTroopsOrder().getTroopsMoved() + 1;

        int troopPool =
            gameState.getLastAttackOrder().getResult().attackingTroopCount - 1;

        if (isTroopCountValid(
            troopCount,
            troopPool))
        {
            gameSession.updateMoveTroopsOrder(
                true);

            attackWindow->setMoveTroopCount(
                gameState.getLastMoveTroopsOrder().getTroopsMoved());
        }
    }


    void AttackUI::removeTroops(
        GameSession& gameSession,
        GameState& gameState)
    {
        int minTroopCount =
            gameState.getLastRollDiceOrder()
            .getAttackingDice()
            .size();

        int currentTroopsMoved =
            gameState.getLastMoveTroopsOrder()
            .getTroopsMoved();

        if (minTroopCount <=
            currentTroopsMoved - 1)
        {
            gameSession.updateMoveTroopsOrder(
                false);

            attackWindow->setMoveTroopCount(
                gameState.getLastMoveTroopsOrder().getTroopsMoved());
        }
    }


    void AttackUI::confirmMove(
        GameState& gameState,
        GameSession& gameSession)
    {
        gameSession.executeMoveTroopsOrder(
            gameState);

        attackWindow->clearDice();

        gameState.clearAttack();
        gameState.setPlayerCards(gameSession.getPlayerCards(gameState.getPlayerTurnID()));
        if (gameState.calcSetCount() >= 5)
        {
            gameState.setPhase(PhaseType::Reinforce);
        }
    }


    //---------------------------------------------------------
    // Fortify Button
    //---------------------------------------------------------

    void AttackUI::fortify(
        GameState& gameState)
    {
        if (!gameState.getAttackConfirmed())
        {
            attackWindow->clearDice();
            gameState.clearAttack();
            gameState.setPhase(
                PhaseType::Fortify);
        }
    }


    //---------------------------------------------------------
    // Draw
    //---------------------------------------------------------

    void AttackUI::draw(
        sf::RenderWindow& window,
        GameState& gameState)
    {
        //-----------------------------------------------------
        // Phase
        //-----------------------------------------------------

        window.draw(
            phaseTitle);

        //-----------------------------------------------------
        // Player Indicator
        //-----------------------------------------------------

        if (playerIndicator)
        {
            playerIndicator->draw(
                window);
        }

        //-----------------------------------------------------
        // Pre Attack
        //-----------------------------------------------------

        if (gameState.getFromTerritorySelection() != TerritoryID::None &&
            gameState.getToTerritorySelection() != TerritoryID::None &&
            gameState.getAttackConfirmed() == false)
        {
            if (preAttackBox)
            {
                preAttackBox->draw(
                    window);
            }
        }

        //-----------------------------------------------------
        // Attack Window
        //-----------------------------------------------------

        if (gameState.getAttackConfirmed() == true)
        {
            if (attackWindow)
            {
                attackWindow->draw(
                    window);
            }
        }

        //-----------------------------------------------------
        // Fortify
        //-----------------------------------------------------

        if (gameState.getAttackConfirmed() == false)
        {
            window.draw(
                fortifyButton);

            if (fortifyButtonText)
            {
                window.draw(
                    *fortifyButtonText);
            }
        }
    }

} // namespace risk