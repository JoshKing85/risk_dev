#include "risk/graphics/ui/ReinforceUI.h"
#include <iostream>

namespace risk {

    ReinforceUI::ReinforceUI(
        const sf::Font& font,
        const std::unordered_map<TerritoryID, TerritoryGraphics>&
        territoryGraphicsMap,
        GameState& gameState,
        GameSession& gameSession)
        : phaseTitle(font)
    {
        //-----------------------------------------------------
        // Phase title
        //-----------------------------------------------------

        phaseTitle.setString(
            "REINFORCEMENT PHASE");

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
        // Player state
        //-----------------------------------------------------

        setPlayerState(
            gameState,
            gameSession);

        cardContainer.emplace(
            font,
            territoryGraphicsMap,
            gameState.getPlayerCards());

        if (gameState.getPlayerCards().size() >= 5)
        {
            cardContainer->openContainer();
        }

        reinforceControls.emplace(
            font);

        reinforceControls->setRemainingTroops(
            gameState.getReinforcePool());

        playerIndicator.emplace(
            font);

        playerIndicator->setPosition(
            gameState.getPlayerTurnID());
    }


    void ReinforceUI::setPlayerState(
        GameState& gameState,
        GameSession& gameSession)
    {
        gameSession.setReinforcePool(
            gameState);

        Player& player =
            gameSession.getPlayer(
                gameState.getPlayerTurnID());

        std::vector<Card> playerSet =
            player.getPlayerSet();

        gameState.setPlayerCards(
            playerSet);
    }


    void ReinforceUI::handleTroops(
        const sf::Event& event,
        sf::RenderWindow& window,
        GameSession& gameSession,
        GameState& gameState,
        std::unordered_map<TerritoryID, TerritoryGraphics>& territoryGraphicsMap)
    {
        TerritoryID territorySelection =
            gameState.getToTerritorySelection();

        if (territorySelection == TerritoryID::None)
        {
            troopPlacement(
                event,
                window,
                gameSession,
                gameState,
                territoryGraphicsMap);

            return;
        }

        if (const auto* mousePressed =
            event.getIf<sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition = {
                static_cast<float>(
                    mousePressed->position.x),
                static_cast<float>(
                    mousePressed->position.y)
            };

            if (reinforceControls
                ->getAddTroopsBounds()
                .contains(mousePosition))
            {
                addTroop(
                    gameSession,
                    gameState);
            }
            else if (reinforceControls
                ->getRemoveTroopsBounds()
                .contains(mousePosition))
            {
                removeTroop(
                    gameSession,
                    gameState);
            }
            else if (reinforceControls
                ->getBackBounds()
                .contains(mousePosition))
            {
                back(
                    gameSession,
                    gameState);
            }
            else if (reinforceControls
                ->getConfirmBounds()
                .contains(mousePosition))
            {
                confirm(
                    gameSession,
                    gameState);
            }
        }
    }


    void ReinforceUI::troopPlacement(
        const sf::Event& event,
        sf::RenderWindow& window,
        GameSession& gameSession,
        GameState& gameState,
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

            for (auto& [territoryID, territoryGraphics] :
                territoryGraphicsMap)
            {
                if (territoryGraphics.contains(
                    mousePosition))
                {
                    const std::vector<TerritoryID>& territories =
                        gameSession
                        .getPlayer(
                            gameState.getPlayerTurnID())
                        .getTerritoriesHeld();

                    if (gameSession.validateSelection(
                        territoryID,
                        territories))
                    {
                        gameState.setToSelection(
                            territoryID);

                        gameSession.createReinforceOrder(
                            territoryID,
                            1,
                            gameState);

                        gameState.updateReinforcePool(
                            1);

                        reinforceControls->setRemainingTroops(
                            gameState.getReinforcePool());

                        //-------------------------------------------------
                        // Position controls beside selected territory
                        //-------------------------------------------------

                        sf::FloatRect bounds =
                            territoryGraphics.getBounds();

                        float controlX =
                            bounds.position.x +
                            bounds.size.x +
                            10.0f;

                        //-------------------------------------------------
                        // Move controls to left if they exceed screen
                        //-------------------------------------------------

                        if (controlX + 220.0f >
                            static_cast<float>(
                                window.getSize().x))
                        {
                            controlX =
                                bounds.position.x -
                                220.0f -
                                10.0f;
                        }

                        reinforceControls
                            ->setTroopControlsPosition({
                                controlX,
                                bounds.position.y
                                });
                    }

                    break;
                }
            }
        }
    }


    void ReinforceUI::addTroop(
        GameSession& gameSession,
        GameState& gameState)
    {
        if (gameSession.validateReinforceInput(
            1,
            gameState))
        {
            gameSession.updateReinforceOrder(
                true,
                gameState);

            gameState.updateReinforcePool(
                1);

            reinforceControls->setRemainingTroops(
                gameState.getReinforcePool());
        }
    }


    void ReinforceUI::removeTroop(
        GameSession& gameSession,
        GameState& gameState)
    {
        int troopCount =
            gameState
            .getLastReinforceOrder()
            .getReinforceTroopCount();

        if (troopCount == 1)
        {
            gameSession.undoReinforceOrder(
                gameState);

            TerritoryID noSelection =
                TerritoryID::None;

            gameState.setToSelection(
                noSelection);

            gameState.updateReinforcePool(
                -1);

            reinforceControls->setRemainingTroops(
                gameState.getReinforcePool());

            return;
        }

        gameSession.updateReinforceOrder(
            false,
            gameState);

        gameState.updateReinforcePool(
            -1);

        reinforceControls->setRemainingTroops(
            gameState.getReinforcePool());
    }


    void ReinforceUI::back(
        GameSession& gameSession,
        GameState& gameState)
    {
        int troopCount =
            gameState
            .getLastReinforceOrder()
            .getReinforceTroopCount();

        gameState.updateReinforcePool(
            -troopCount);

        gameSession.undoReinforceOrder(
            gameState);

        TerritoryID noSelection =
            TerritoryID::None;

        gameState.setToSelection(
            noSelection);

        reinforceControls->setRemainingTroops(
            gameState.getReinforcePool());
    }


    void ReinforceUI::confirm(
        GameSession& gameSession,
        GameState& gameState)
    {
        int troopCount =
            gameState
            .getLastReinforceOrder()
            .getReinforceTroopCount();

        gameSession.executeReinforceOrder(
            gameState);

        TerritoryID noSelection =
            TerritoryID::None;

        gameState.setToSelection(
            noSelection);

        if (!gameState.getReinforcePool())
        {
            gameState.setPhase(
                PhaseType::Attack);
        }
    }


    void ReinforceUI::handleReinforceEvent(
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

            if (cardContainer->getTabBounds().contains(
                mousePosition))
            {
                if (cardContainer->isOpen())
                {
                    cardContainer->closeContainer();
                }
                else
                {
                    cardContainer->openContainer();
                }

                return;
            }

            if (cardContainer->isOpen())
            {
                cardContainer->selectCard(
                    mousePosition);
            }
        }

        handleTroops(
            event,
            window,
            gameSession,
            gameState,
            territoryGraphicsMap);
    }


    void ReinforceUI::draw(
        sf::RenderWindow& window,
        std::vector<PlayerGraphics>& playerGraphics,
        GameState& gameState)
    {
        phaseTitle.setPosition({
            static_cast<float>(
                window.getSize().x) / 2.0f,
            20.0f
            });

        window.draw(
            phaseTitle);

        for (auto& player : playerGraphics)
        {
            player.draw(window);
        }

        playerIndicator->draw(
            window);

        if (gameState.getToTerritorySelection() !=
            TerritoryID::None)
        {
            reinforceControls->draw(
                window);
        }

        cardContainer->draw(
            window);
    }

} // namespace risk