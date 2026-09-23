#include "risk/graphics/ui/GameSetupUI.h"

namespace risk {

    //---------------------------------------------------------
    // Initialization
    //---------------------------------------------------------

    void GameSetupUI::initialize(
        GameSession& gameSession,
        sf::Font& font,
        std::vector<PlayerGraphics>& playerGraphics)
    {
        profileUI.emplace(font);
        playerIndicator.emplace(font);
        setupControls.emplace(font);

        //-----------------------------------------------------
        // Phase title
        //-----------------------------------------------------

        phaseTitle.emplace(font);

        phaseTitle->setString(
            "INITIAL REINFORCEMENT PHASE");

        phaseTitle->setCharacterSize(
            28);

        phaseTitle->setStyle(
            sf::Text::Bold);

        phaseTitle->setFillColor(
            sf::Color::Black);

        sf::FloatRect titleBounds =
            phaseTitle->getLocalBounds();

        phaseTitle->setOrigin({
            titleBounds.position.x +
                titleBounds.size.x / 2.0f,
            titleBounds.position.y
            });

        //-----------------------------------------------------
        // Player setup
        //-----------------------------------------------------

        std::vector<int> playerIDs =
            gameSession.getPlayerIDs();

        std::vector<int> troopCounts =
            gameSession.getTroopCounts();

        std::vector<int> remainingTroops =
            gameSession.getRemainingTroops();

        for (const auto playerID : playerIDs)
        {
            gameSetupState.addPlayerProfile(
                playerID,
                remainingTroops[playerID]);

            playerGraphics.emplace_back(
                playerID,
                troopCounts[playerID],
                font);
        }
    }


    //---------------------------------------------------------
    // Draw
    //---------------------------------------------------------

    void GameSetupUI::draw(
        sf::RenderWindow& window,
        std::vector<PlayerGraphics>& playerGraphics)
    {
        //-------------------------------------------------------
        // Profile setup
        //-------------------------------------------------------

        if (!gameSetupState.getProfilesReady())
        {
            int playerID =
                gameSetupState.getCurrentProfileID();

            profileUI->profileUIdraw(
                window,
                playerID);

            return;
        }

        //-------------------------------------------------------
        // Phase title
        //-------------------------------------------------------

        phaseTitle->setPosition({
            static_cast<float>(
                window.getSize().x) / 2.0f,
            20.0f
            });

        window.draw(
            *phaseTitle);

        //-------------------------------------------------------
        // Current setup player
        //-------------------------------------------------------

        int currentPlayerID =
            gameSetupState.getCurrentProfileID();

        for (auto& playerGraphic : playerGraphics)
        {
            playerGraphic.setActive(
                playerGraphic.getPlayerID() ==
                currentPlayerID);

            playerGraphic.draw(window);
        }

        //-------------------------------------------------------
        // Player indicator
        //-------------------------------------------------------

        playerIndicator->setPosition(
            currentPlayerID);

        playerIndicator->draw(
            window);

        //-------------------------------------------------------
        // Setup controls
        //-------------------------------------------------------

        if (gameSetupState.getTerritorySelected() !=
            TerritoryID::None)
        {
            setupControls->draw(
                window);
        }
    }


    //---------------------------------------------------------
    // Event Handling
    //---------------------------------------------------------

    void GameSetupUI::handleEvent(
        const sf::Event& event,
        sf::RenderWindow& window,
        GameSession& gameSession,
        GameState& gameState,
        std::vector<PlayerGraphics>& playerGraphics,
        std::unordered_map<TerritoryID, TerritoryGraphics>
        & territoryGraphicsMap)
    {
        if (!gameSetupState.getProfilesReady())
        {
            int playerID =
                gameSetupState.getCurrentProfileID();

            profileUI->handleEvent(
                event,
                window,
                playerID,
                playerGraphics[playerID],
                gameSetupState);

            return;
        }

        handleTroops(
            event,
            gameSession,
            gameState,
            territoryGraphicsMap);
    }


    //---------------------------------------------------------
    // Troop Placement
    //---------------------------------------------------------

    void GameSetupUI::handleTroops(
        const sf::Event& event,
        GameSession& gameSession,
        GameState& gameState,
        std::unordered_map<TerritoryID, TerritoryGraphics>
        & territoryGraphicsMap)
    {
        if (gameSetupState.getTerritorySelected() ==
            TerritoryID::None)
        {
            troopPlacement(
                event,
                gameSession,
                territoryGraphicsMap);

            return;
        }

        back(event);

        if (gameSetupState.getTerritorySelected() !=
            TerritoryID::None)
        {
            confirm(
                event,
                gameSession,
                gameState);
        }
    }


    void GameSetupUI::troopPlacement(
        const sf::Event& event,
        GameSession& gameSession,
        std::unordered_map<TerritoryID, TerritoryGraphics>
        & territoryGraphicsMap)
    {
        if (const auto* mousePressed =
            event.getIf<
            sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition = {
                static_cast<float>(
                    mousePressed->position.x),
                static_cast<float>(
                    mousePressed->position.y) };

            for (auto& [territoryID, territoryGraphics] :
                territoryGraphicsMap)
            {
                if (territoryGraphics.contains(
                    mousePosition))
                {
                    const std::vector<TerritoryID>& territories =
                        gameSession
                        .getPlayer(
                            gameSetupState
                            .getCurrentProfileID())
                        .getTerritoriesHeld();

                    if (gameSession.validateSelection(
                        territoryID,
                        territories))
                    {
                        gameSetupState.setTerritorySelected(
                            territoryID);

                        sf::FloatRect bounds =
                            territoryGraphics.getBounds();

                        setupControls->setConfirmPosition({
                            bounds.position.x +
                                bounds.size.x +
                                10.0f,
                            bounds.position.y });

                        setupControls->setBackPosition({
                            bounds.position.x +
                                bounds.size.x +
                                10.0f,
                            bounds.position.y +
                                50.0f });
                    }

                    break;
                }
            }
        }
    }


    //---------------------------------------------------------
    // Setup Controls
    //---------------------------------------------------------

    void GameSetupUI::back(
        const sf::Event& event)
    {
        if (const auto* mousePressed =
            event.getIf<
            sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition = {
                static_cast<float>(
                    mousePressed->position.x),
                static_cast<float>(
                    mousePressed->position.y) };

            if (setupControls->getBackBounds().contains(
                mousePosition))
            {
                gameSetupState.setTerritorySelected(
                    TerritoryID::None);
            }
        }
    }


    void GameSetupUI::confirm(
        const sf::Event& event,
        GameSession& gameSession,
        GameState& gameState)
    {
        if (const auto* mousePressed =
            event.getIf<
            sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition = {
                static_cast<float>(
                    mousePressed->position.x),
                static_cast<float>(
                    mousePressed->position.y) };

            if (setupControls->getConfirmBounds().contains(
                mousePosition))
            {
                int playerID =
                    gameSetupState
                    .getCurrentProfileID();

                TerritoryID selectedTerritory =
                    gameSetupState
                    .getTerritorySelected();

                gameSession.addTroop(
                    selectedTerritory,
                    playerID);

                gameSetupState.removeTroop(
                    playerID);

                gameSetupState.setTerritorySelected(
                    TerritoryID::None);

                if (gameSetupState.allTroopsPlaced())
                {
                    gameState.setPhase(
                        PhaseType::Reinforce);

                    return;
                }

                gameSetupState.setCurrentProfile(
                    gameSetupState
                    .getCurrentProfileID());
            }
        }
    }


    //---------------------------------------------------------
    // State Access
    //---------------------------------------------------------

    GameSetupState&
        GameSetupUI::getGameSetupState()
    {
        return gameSetupState;
    }

} // namespace risk