#include <iostream>

#include "risk/graphics/ui/GameWindow.h"
#include "risk/utils/FilePathConverter.h"

namespace risk {

    //---------------------------------------------------------
    // Construction
    //---------------------------------------------------------

    GameWindow::GameWindow(
        sf::VideoMode videoMode,
        std::string title)
        : window(videoMode, title),
        gameState(),
        gameSession(),
        exchangeLUI()
    {
        //-----------------------------------------------------
        // Profile UI
        //-----------------------------------------------------

        if (!profileFont.openFromFile(
            "C:/Windows/Fonts/georgia.ttf"))
        {
            throw std::runtime_error(
                "Could not load profile font");
        }

        profileUI.emplace(
            profileFont);
    }


    //---------------------------------------------------------
    // Main Loop
    //---------------------------------------------------------

    void GameWindow::run()
    {
        bool menuActive = true;
        bool profilesActive = false;
        bool gameCreated = false;

        while (window.isOpen())
        {
            //-------------------------------------------------
            // Handle events
            //-------------------------------------------------

            while (const std::optional event =
                window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }

                //---------------------------------------------
                // Menu events
                //---------------------------------------------

                if (menuActive)
                {
                    menuUI.handleEvent(
                        *event,
                        window);
                }

                //---------------------------------------------
                // Profile events
                //---------------------------------------------

                else if (profilesActive)
                {
                    if (currentProfile <
                        static_cast<int>(
                            playerProfiles.size()))
                    {
                        PlayerProfile& profile =
                            playerProfiles[
                                currentProfile];

                        bool wasConfirmed =
                            profile.confirmed;

                        profileUI->handleEvent(
                            *event,
                            window,
                            profile,
                            playerProfiles);

                        //-------------------------------------
                        // Avatar selected
                        //-------------------------------------

                        if (!wasConfirmed &&
                            profile.confirmed)
                        {
                            currentProfile++;

                            //---------------------------------
                            // All profiles complete
                            //---------------------------------

                            if (currentProfile >=
                                static_cast<int>(
                                    playerProfiles.size()))
                            {
                                try
                                {
                                    gameSession.createGame(
                                        mapTypeToFilename(
                                            menuUI
                                            .getMapSelection()),
                                        menuUI
                                        .getHumanPlayerNumbers(),
                                        menuUI
                                        .getAiPlayerNumbers());

                                    gameCreated = true;
                                    profilesActive = false;

                                    loadingClock.restart();
                                    loadingStarted = true;
                                }
                                catch (
                                    const std::exception&
                                    exception)
                                {
                                    std::cerr
                                        << "Game creation failed: "
                                        << exception.what()
                                        << '\n';

                                    window.close();
                                }
                            }
                        }
                    }
                }

                //---------------------------------------------
                // Game events
                //---------------------------------------------

                else if (
                    gameCreated &&
                    gameState.getPhase() !=
                    PhaseType::Loading)
                {
                    gameSessionUI.handleEvent(
                        *event,
                        window,
                        gameSession,
                        gameState);
                }
            }


            //-------------------------------------------------
            // Leave menu and create profiles
            //-------------------------------------------------

            if (menuActive &&
                menuUI.isGameStarted())
            {
                menuActive = false;
                profilesActive = true;

                playerProfiles.clear();

                currentProfile = 0;

                int humanPlayers =
                    menuUI.getHumanPlayerNumbers();

                for (int playerID = 0;
                    playerID < humanPlayers;
                    ++playerID)
                {
                    PlayerProfile profile;

                    profile.playerID =
                        playerID;

                    playerProfiles.push_back(
                        profile);
                }
            }


            //-------------------------------------------------
            // Update game graphics
            //-------------------------------------------------

            if (gameCreated &&
                gameState.getPhase() !=
                PhaseType::Loading)
            {
                std::vector<PlayerGraphics>&
                    playerGraphics =
                    gameSessionUI
                    .getPlayerGraphics();

                std::unordered_map<
                    TerritoryID,
                    TerritoryGraphics>&
                    territoryGraphicsMap =
                    gameSessionUI
                    .getTerritoryGraphics();

                const std::vector<Player>& players =
                    gameSession.getPlayers();

                const Map& map =
                    gameSession.getMap();

                //---------------------------------------------
                // Initial troop placement
                //---------------------------------------------

                if (gameState.getPhase() ==
                    PhaseType::GameSetup)
                {
                    GameSetupState& gameSetupState =
                        gameSessionUI
                        .getGameSetupState();

                    exchangeLUI.updateGraphics(
                        map,
                        players,
                        gameState,
                        territoryGraphicsMap,
                        playerGraphics,
                        &gameSetupState);
                }

                //---------------------------------------------
                // Normal game phases
                //---------------------------------------------

                else
                {
                    exchangeLUI.updateGraphics(
                        map,
                        players,
                        gameState,
                        territoryGraphicsMap,
                        playerGraphics);
                }
            }


            //-------------------------------------------------
            // Draw
            //-------------------------------------------------

            window.clear();


            //-------------------------------------------------
            // Menu
            //-------------------------------------------------

            if (menuActive)
            {
                menuUI.draw(
                    window);
            }


            //-------------------------------------------------
            // Profiles
            //-------------------------------------------------

            else if (profilesActive)
            {
                if (currentProfile <
                    static_cast<int>(
                        playerProfiles.size()))
                {
                    profileUI->profileUIdraw(
                        window,
                        currentProfile,
                        playerProfiles);
                }
            }


            //-------------------------------------------------
            // Loading
            //-------------------------------------------------

            else if (
                gameCreated &&
                gameState.getPhase() ==
                PhaseType::Loading)
            {
                loadingUI.draw(
                    window,
                    loadingClock
                    .getElapsedTime()
                    .asSeconds());

                if (loadingStarted &&
                    loadingClock
                    .getElapsedTime()
                    .asSeconds() >= 3.f)
                {
                    gameSessionUI.initialLoading(
                        gameSession,
                        gameState,
                        menuUI.getHumanPlayerNumbers(),
                        menuUI.getAiPlayerNumbers(),
                        menuUI.getMapSelection(),
                        playerProfiles);

                    loadingStarted = false;
                }
            }


            //-------------------------------------------------
            // Game
            //-------------------------------------------------

            else if (gameCreated)
            {
                gameSessionUI.draw(
                    window,
                    gameState,
                    gameSession);
            }


            window.display();
        }
    }

} // namespace risk