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

            if (bounds.contains(mousePosition))
            {
                std::cout << "[ATTACK UI] Fortify button clicked" << std::endl;
                fortify(gameState);
                return;
            }
        }

        if (gameState.getFromTerritorySelection() == TerritoryID::None ||
            gameState.getToTerritorySelection() == TerritoryID::None)
        {
            std::cout << "[ROUTE] Territory Selection | FROM="
                << static_cast<int>(gameState.getFromTerritorySelection())
                << " TO=" << static_cast<int>(gameState.getToTerritorySelection())
                << " Confirmed=" << gameState.getAttackConfirmed() << std::endl;

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
            std::cout << "[ROUTE] Pre Attack | FROM="
                << static_cast<int>(gameState.getFromTerritorySelection())
                << " TO=" << static_cast<int>(gameState.getToTerritorySelection())
                << " Confirmed=" << gameState.getAttackConfirmed() << std::endl;

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
            std::cout << "[ROUTE] Attack Window | FROM="
                << static_cast<int>(gameState.getFromTerritorySelection())
                << " TO=" << static_cast<int>(gameState.getToTerritorySelection())
                << " Confirmed=" << gameState.getAttackConfirmed() << std::endl;

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
                    std::cout << "[CLICK] Territory ID="
                        << static_cast<int>(territoryID)
                        << " Title=" << territoryGraphics.getTitle() << std::endl;
                    //-------------------------------------------------
                    // FROM selection
                    //-------------------------------------------------

                    if (fromTerritory == TerritoryID::None)
                    {
                        TerritoryID selectedTerritoryID =
                            territoryID;

                        bool validFrom = gameSession.validateAttackSelection(
                            gameState.getPlayerTurnID(),
                            selectedTerritoryID);

                        std::cout << "[FROM] Validation=" << validFrom << std::endl;

                        if (validFrom)
                        {
                            gameState.setFromSelection(
                                selectedTerritoryID);

                            std::cout << "[FROM] Selected ID="
                                << static_cast<int>(selectedTerritoryID)
                                << " Title=" << territoryGraphics.getTitle() << std::endl;
                        }

                        return;
                    }

                    //-------------------------------------------------
                    // TO selection
                    //-------------------------------------------------

                    bool validTo = gameSession.validateAttackInput(
                        fromTerritory,
                        territoryID);

                    std::cout << "[TO] Validation=" << validTo << std::endl;

                    if (validTo)
                    {
                        gameState.setToSelection(
                            territoryID);

                        std::cout << "[TO] Selected ID="
                            << static_cast<int>(territoryID)
                            << " Title=" << territoryGraphics.getTitle() << std::endl;

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
                std::cout << "[PRE ATTACK] Back clicked" << std::endl;
                back(
                    gameSession,
                    gameState);

                return;
            }

            if (preAttackBox->getConfirmBounds().contains(
                mousePosition))
            {
                std::cout << "[PRE ATTACK] Confirm clicked" << std::endl;
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
        std::cout << "[PRE ATTACK] Clearing attack selection" << std::endl;
        gameState.clearAttack();
    }


    void AttackUI::confirm(
        GameSession& gameSession,
        GameState& gameState,
        std::vector<PlayerGraphics>& playerGraphics,
        std::unordered_map<TerritoryID, TerritoryGraphics>& territoryGraphicsMap)
    {
        std::cout << "[CONFIRM] FROM="
            << static_cast<int>(gameState.getFromTerritorySelection())
            << " TO=" << static_cast<int>(gameState.getToTerritorySelection()) << std::endl;

        gameState.setAttackConfirmed(
            true);

        gameSession.createAttackOrder(
            gameState);

        std::cout << "[ORDER] AttackOrder created | attacking troops="
            << gameState.getLastAttackOrder().getAttackingTroopCount()
            << " defending troops="
            << gameState.getLastAttackOrder().getDefendingTroopCount() << std::endl;

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

            //---------------------------------------------------------
            // Move Troops
            //---------------------------------------------------------

            if (gameState.hasMoveTroopsOrder())
            {
                std::cout << "[ATTACK WINDOW] Move Troops mode" << std::endl;
                if (attackWindow->getAddTroopBounds().contains(
                    mousePosition))
                {
                    std::cout << "[MOVE] Add clicked" << std::endl;
                    addTroops(
                        gameSession,
                        gameState);

                    return;
                }

                if (attackWindow->getRemoveTroopBounds().contains(
                    mousePosition))
                {
                    std::cout << "[MOVE] Remove clicked" << std::endl;
                    removeTroops(
                        gameSession,
                        gameState);

                    return;
                }

                if (attackWindow->getConfirmMoveBounds().contains(
                    mousePosition))
                {
                    std::cout << "[MOVE] Confirm clicked" << std::endl;
                    confirmMove(
                        gameState,
                        gameSession);

                    return;
                }

                return;
            }

            //---------------------------------------------------------
            // Attack
            //---------------------------------------------------------

            int diceCount =
                attackWindow->getAttackerDiceSelection(
                    mousePosition);

            if (diceCount > 0)
            {
                std::cout << "[DICE] Dice button clicked=" << diceCount << std::endl;
                selectDice(
                    diceCount,
                    gameState,
                    gameSession);

                return;
            }

            if (attackWindow->getAttackBounds().contains(
                mousePosition))
            {
                std::cout << "[ATTACK WINDOW] Attack clicked" << std::endl;
                attack(
                    gameState,
                    gameSession);

                return;
            }

            if (attackWindow->getQuitAttackBounds().contains(
                mousePosition))
            {
                std::cout << "[ATTACK WINDOW] Quit clicked" << std::endl;
                quitAttack(
                    gameState,
                    gameSession);

                return;
            }
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




        std::cout << "[WINDOW] Configuring AttackWindow | attacker=" << attPlayerID
            << " defender=" << defPlayerID
            << " FROM=" << fromTitle
            << " TO=" << toTitle
            << " attacker troops=" << attTroopCount
            << " defender troops=" << defTroopCount << std::endl;

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
        bool validDice = gameSession.validateDiceInput(
            diceCount,
            gameState);

        std::cout << "[DICE] Selection=" << diceCount
            << " Valid=" << validDice << std::endl;

        if (!validDice)
        {
            return;
        }

        if (gameState.getAttackerDice() > 0)
        {
            gameSession.updateRollDiceOrder(
                diceCount);
            std::cout << "[ORDER] RollDiceOrder updated" << std::endl;
        }
        else
        {
            gameSession.createRollDiceOrder(
                diceCount,
                gameState);
            std::cout << "[ORDER] RollDiceOrder created" << std::endl;
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
        std::cout << "[ATTACK] Executing AttackOrder" << std::endl;

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

        std::cout << "[ATTACK] Outcome=" << static_cast<int>(outcome)
            << " attacker losses=" << gameState.getLastAttackOrder().getResult().attackerLosses
            << " defender losses=" << gameState.getLastAttackOrder().getResult().defenderLosses
            << " attacker remaining=" << gameState.getLastAttackOrder().getResult().attackingTroopCount
            << " defender remaining=" << gameState.getLastAttackOrder().getResult().defendingTroopCount
            << " movable troops=" << troopsAvailable << std::endl;

        if (outcome == AttackOutcome::Captured)
        {
            std::cout << "[ATTACK] Territory captured" << std::endl;
            if (troopsAvailable >= diceCount)
            {
                gameSession.createMoveTroopsOrder(
                    fromTerritory,
                    toTerritory,
                    diceCount,
                    gameState);

                std::cout << "[ORDER] MoveTroopsOrder created | troops="
                    << gameState.getLastMoveTroopsOrder().getTroopsMoved() << std::endl;

                if (troopsAvailable == diceCount)
                {
                    std::cout << "[MOVE] Forced move - executing automatically" << std::endl;
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

            std::cout << "[ORDER] MoveTroopsOrder created | troops="
                << gameState.getLastMoveTroopsOrder().getTroopsMoved() << std::endl;

            return;
        }

        if (troopsAvailable > 0)
        {
            std::cout << "[ATTACK] Continuing attack" << std::endl;
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

        std::cout << "[ATTACK] No movable attacking troops - clearing attack" << std::endl;
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
        std::cout << "[QUIT] Quit attack requested" << std::endl;

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
        std::cout << "[QUIT] Attack cleared" << std::endl;
    }


    //---------------------------------------------------------
    // Move Troops
    //---------------------------------------------------------

    void AttackUI::addTroops(
        GameSession& gameSession,
        GameState& gameState)
    {
        int troopCount = gameState.getLastMoveTroopsOrder().getTroopsMoved() + 1;
        int troopPool = gameState.getLastAttackOrder().getResult().attackingTroopCount - 1;

        std::cout << "[MOVE] Add proposed=" << troopCount
            << " max=" << troopPool << std::endl;

        if (isTroopCountValid(troopCount, troopPool))

        {
            gameSession.updateMoveTroopsOrder(true);
            std::cout << "[MOVE] Updated troops="
                << gameState.getLastMoveTroopsOrder().getTroopsMoved() << std::endl;
        }

    }


    void AttackUI::removeTroops(
        GameSession& gameSession,
        GameState& gameState)
    {
        int minTroopCount = gameState.getLastRollDiceOrder().getAttackingDice().size();
        int currentTroopsMoved = gameState.getLastMoveTroopsOrder().getTroopsMoved();

        std::cout << "[MOVE] Remove proposed=" << currentTroopsMoved - 1
            << " minimum=" << minTroopCount << std::endl;

        if (minTroopCount <= currentTroopsMoved - 1)
        {
            gameSession.updateMoveTroopsOrder(false);
            std::cout << "[MOVE] Updated troops="
                << gameState.getLastMoveTroopsOrder().getTroopsMoved() << std::endl;
        }

    }


    void AttackUI::confirmMove(
        GameState& gameState,
        GameSession& gameSession)
    {
        std::cout << "[MOVE] Executing MoveTroopsOrder | troops="
            << gameState.getLastMoveTroopsOrder().getTroopsMoved() << std::endl;

        gameSession.executeMoveTroopsOrder(
            gameState);

        attackWindow->clearDice();

        gameState.clearAttack();
        std::cout << "[MOVE] Complete - attack state cleared" << std::endl;
    }


    //---------------------------------------------------------
    // Fortify Button 
    //---------------------------------------------------------

    void AttackUI::fortify(GameState& gameState)
    {
        if (!gameState.getAttackConfirmed())
        {
            std::cout << "[FORTIFY] Transitioning to Fortify phase" << std::endl;
            attackWindow->clearDice();
            gameState.clearAttack();
            gameState.setPhase(PhaseType::Fortify);
        }
    }

    //---------------------------------------------------------
    // Draw
    //---------------------------------------------------------

    void AttackUI::draw(
        sf::RenderWindow& window,
        std::vector<PlayerGraphics>& playerGraphics,
        GameState& gameState)
    {
        //-----------------------------------------------------
        // Phase
        //-----------------------------------------------------

        window.draw(phaseTitle);

        //-----------------------------------------------------
        // Player Graphics
        //-----------------------------------------------------

        for (auto& player : playerGraphics)
        {
            player.draw(window);
        }
        //-----------------------------------------------------
        // Player Indicator
        //-----------------------------------------------------

        if (playerIndicator)
        {
            playerIndicator->draw(window);
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
                preAttackBox->draw(window);
            }
        }

        //-----------------------------------------------------
        // Attack Window
        //-----------------------------------------------------

        if (gameState.getAttackConfirmed() == true)
        {
            if (attackWindow)
            {
                attackWindow->draw(window);
            }
        }

        //-----------------------------------------------------
        // Fortify
        //-----------------------------------------------------

        //-----------------------------------------------------
        // Fortify
        //-----------------------------------------------------

        if (gameState.getAttackConfirmed() == false)
        {
            window.draw(fortifyButton);

            if (fortifyButtonText)
            {
                window.draw(*fortifyButtonText);
            }
        }
    }

} // namespace risk