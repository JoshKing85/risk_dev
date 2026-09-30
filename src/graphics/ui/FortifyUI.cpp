#include "risk/graphics/ui/FortifyUI.h"
#include "risk/core/validation/ValidateTroopCountInput.h"

namespace risk {

    //---------------------------------------------------------
    // Constructor
    //---------------------------------------------------------

    FortifyUI::FortifyUI(
        const sf::Font& font,
        GameState &gameState)
        : phaseTitle(font)
    {
        //-----------------------------------------------------
        // Phase Title
        //-----------------------------------------------------

        phaseTitle.setString(
            "FORTIFY PHASE");

        phaseTitle.setCharacterSize(
            28);

        phaseTitle.setFillColor(
            sf::Color::Black);

        phaseTitle.setStyle(
            sf::Text::Bold);

        sf::FloatRect titleBounds =
            phaseTitle.getLocalBounds();

        phaseTitle.setOrigin(
            {
                titleBounds.position.x +
                    titleBounds.size.x / 2.0f,
                titleBounds.position.y
            });

        phaseTitle.setPosition(
            {
                960.0f,
                20.0f
            });

        //-----------------------------------------------------
        // Fortify Controls
        //-----------------------------------------------------

        fortifyControls.emplace(
            font);

        playerIndicator.emplace(
            font);

        playerIndicator->setPosition(
            gameState.getPlayerTurnID());
    }
    //---------------------------------------------------------
    // Handle Event
    //---------------------------------------------------------

    void FortifyUI::handleFortifyEvent(
        const sf::Event& event,
        sf::RenderWindow& window,
        GameSession& gameSession,
        GameState& gameState,
        std::vector<PlayerGraphics>& playerGraphics,
        std::unordered_map<
        TerritoryID,
        TerritoryGraphics>& territoryGraphicsMap)
    {
        //-----------------------------------------------------
        // Territory Selection
        //-----------------------------------------------------

        if (gameState.getFromTerritorySelection() ==
            TerritoryID::None ||
            gameState.getToTerritorySelection() ==
            TerritoryID::None)
        {
            territorySelection(
                event,
                window,
                gameSession,
                gameState,
                territoryGraphicsMap);

            return;
        }

        //-----------------------------------------------------
        // Fortify Controls
        //-----------------------------------------------------

        if (const auto* mousePressed =
            event.getIf<sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition = {
                static_cast<float>(
                    mousePressed->position.x),
                static_cast<float>(
                    mousePressed->position.y)
            };

            if (fortifyControls->getAddTroopsBounds().contains(
                mousePosition))
            {
                addTroop(
                    gameSession,
                    gameState);

                return;
            }

            if (fortifyControls->getRemoveTroopsBounds().contains(
                mousePosition))
            {
                removeTroop(
                    gameSession,
                    gameState);

                return;
            }

            if (fortifyControls->getBackBounds().contains(
                mousePosition))
            {
                back(
                    gameSession,
                    gameState);

                return;
            }

            if (fortifyControls->getConfirmBounds().contains(
                mousePosition))
            {
                confirm(
                    gameSession,
                    gameState);

                return;
            }
        }
    }
    //---------------------------------------------------------
    // Territory Selection
    //---------------------------------------------------------

    void FortifyUI::territorySelection(
        const sf::Event& event,
        sf::RenderWindow& window,
        GameSession& gameSession,
        GameState& gameState,
        std::unordered_map<
        TerritoryID,
        TerritoryGraphics>& territoryGraphicsMap)
    {
        TerritoryID fromTerritory =
            gameState.getFromTerritorySelection();

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
                    // FROM Selection
                    //-------------------------------------------------

                    if (fromTerritory ==
                        TerritoryID::None)
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
                            gameState.setFromSelection(
                                territoryID);
                        }

                        return;
                    }

                    //-------------------------------------------------
                    // TO Selection
                    //-------------------------------------------------

                    if (gameSession.validateFortifySelection(
                        fromTerritory,
                        territoryID,
                        gameState))
                    {
                        gameState.setToSelection(
                            territoryID);

                        gameSession.createFortifyOrder(
                            fromTerritory,
                            territoryID,
                            1,
                            gameState);

                        fortifyControls->setTroopCount(
                            1);

                        sf::FloatRect bounds =
                            territoryGraphics.getBounds();

                        float boxX =
                            bounds.position.x +
                            bounds.size.x +
                            10.0f;

                        float boxY =
                            bounds.position.y;

                        if (boxX + 250.0f >
                            static_cast<float>(
                                window.getSize().x))
                        {
                            boxX =
                                bounds.position.x -
                                250.0f -
                                10.0f;
                        }

                        fortifyControls->setTroopControlsPosition(
                            {
                                boxX,
                                boxY
                            });

                        return;
                    }

                    //-------------------------------------------------
                    // Change FROM Selection
                    //-------------------------------------------------

                    const std::vector<TerritoryID>& territories =
                        gameSession
                        .getPlayer(
                            gameState.getPlayerTurnID())
                        .getTerritoriesHeld();

                    if (gameSession.validateSelection(
                        territoryID,
                        territories))
                    {
                        gameState.setFromSelection(
                            territoryID);
                    }

                    return;
                }
            }
        }
    }
    //---------------------------------------------------------
    // Back
    //---------------------------------------------------------

    void FortifyUI::back(
        GameSession& gameSession,
        GameState& gameState)
    {
        gameSession.undoFortifyOrder(
            gameState);

        gameState.setFromSelection(
            TerritoryID::None);

        gameState.setToSelection(
            TerritoryID::None);
    }
    //---------------------------------------------------------
    // Confirm
    //---------------------------------------------------------

    void FortifyUI::confirm(
        GameSession& gameSession,
        GameState& gameState)
    {
        gameSession.executeFortifyOrder(
            gameState);

        gameSession.endTurn(
            gameState);
    }
    //---------------------------------------------------------
    // Add Troop
    //---------------------------------------------------------

    void FortifyUI::addTroop(
        GameSession& gameSession,
        GameState& gameState)
    {
        int troopCount =
            gameState.getLastFortifyOrder()
            .getFortifyTroopCount() + 1;

        int troopPool =
            gameSession.getMap()
            .getTerritory(
                gameState.getFromTerritorySelection())
            .getTroopCount() - 1;

        if (isTroopCountValid(
            troopCount,
            troopPool))
        {
            gameSession.updateFortifyOrder(
                true);

            fortifyControls->setTroopCount(
                gameState.getLastFortifyOrder()
                .getFortifyTroopCount());
        }
    }
    //---------------------------------------------------------
    // Remove Troop
    //---------------------------------------------------------

    void FortifyUI::removeTroop(
        GameSession& gameSession,
        GameState& gameState)
    {
        int troopCount =
            gameState.getLastFortifyOrder()
            .getFortifyTroopCount();

        if (troopCount > 1)
        {
            gameSession.updateFortifyOrder(
                false);

            fortifyControls->setTroopCount(
                gameState.getLastFortifyOrder()
                .getFortifyTroopCount());
        }
    }
    //---------------------------------------------------------
    // Draw
    //---------------------------------------------------------

    void FortifyUI::draw(
        sf::RenderWindow& window,
        std::vector<PlayerGraphics>& playerGraphics,
        GameState& gameState)
    {
        phaseTitle.setPosition(
            {
                static_cast<float>(
                    window.getSize().x) / 2.0f,
                20.0f
            });

        window.draw(
            phaseTitle);

        //-----------------------------------------------------
        // Players
        //-----------------------------------------------------

        for (auto& player :
            playerGraphics)
        {
            player.draw(
                window);
        }

        //-----------------------------------------------------
        // Fortify Controls
        //-----------------------------------------------------

        if (gameState.getFromTerritorySelection() !=
            TerritoryID::None &&
            gameState.getToTerritorySelection() !=
            TerritoryID::None)
        {
            fortifyControls->draw(
                window);
        }

        //-----------------------------------------------------
        // Player Indicator
        //-----------------------------------------------------
        if (playerIndicator)
        {
            playerIndicator->draw(
                window);
        }
    }

} // namespace risk