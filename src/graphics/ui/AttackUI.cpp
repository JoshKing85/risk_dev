#include "risk/graphics/ui/AttackUI.h"


namespace risk {

    AttackUI::AttackUI(
        const sf::Font& font,
        const std::unordered_map<TerritoryID, TerritoryGraphics>
        & territoryGraphicsMap,
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
        if (gameState.getFromTerritorySelection() == TerritoryID::None ||
            gameState.getToTerritorySelection() == TerritoryID::None)
        {
            territorySelection(
                event,
                gameSession,
                gameState,
                territoryGraphicsMap);
        }

        else if (gameState.getAttackConfirmed() == false &&
            gameState.getToTerritorySelection() != TerritoryID::None)
        {
            preAttack(
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
                gameSession,
                gameState,
                playerGraphics);
        }
    }

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
                        if (gameSession.validateAttackSelection(
                            gameState.getPlayerTurnID(),
                            territoryID))
                        {
                            gameState.setFromSelection(
                                territoryID);
                        }

                        return;
                    }

                    //-------------------------------------------------
                    // TO selection
                    //-------------------------------------------------

                    if (gameSession.validateAttackInput(
                        fromTerritory,
                        territoryID))
                    {
                        gameState.setToSelection(
                            territoryID);

                        sf::FloatRect bounds =
                            territoryGraphics.getBounds();

                        sf::FloatRect bounds =
                            territoryGraphics.getBounds();

                        float boxX =
                            bounds.position.x +
                            bounds.size.x +
                            10.0f;

                        float boxY =
                            bounds.position.y;

                        if (boxX + 400.0f >
                            static_cast<float>(window.getSize().x))
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
    void AttackUI::preAttack(
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
                    gameState);

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
        GameState& gameState,
        GameSession& gameSession)
    {
        gameState.setAttackConfirmed(true);

        gameSession.createAttackOrder(
            gameState);
    }
}// namespace risk
