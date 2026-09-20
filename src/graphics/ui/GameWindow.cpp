#include <iostream>

#include "risk/graphics/ui/GameWindow.h"
#include "risk/utils/FilePathConverter.h"

namespace risk {

    GameWindow::GameWindow(
        sf::VideoMode videoMode,
        std::string title
    )
        : window(videoMode, title),
        gameState(),
        gameSession(),
        exchangeLUI()
    {
    }


    void GameWindow::run()
    {
        bool startGame = false;

        while (window.isOpen())
        {
            // -------------------------
            // Handle events
            // -------------------------

            while (const std::optional event =
                window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }


                // -------------------------
                // Menu events
                // -------------------------

                if (!startGame)
                {
                    menuUI.handleEvent(
                        *event,
                        window
                    );
                }


                // -------------------------
                // Game setup events
                // -------------------------

                else if (
                    gameState.getPhase() ==
                    PhaseType::GameSetup)
                {
                    exchangeLUI.handleGameSetupEvent(
                        *event,
                        window,
                        gameSetupUI,
                        gameSession,
                        gameState
                    );
                }
            }


            // -------------------------
            // Create game
            // -------------------------

            if (!startGame &&
                menuUI.isGameStarted())
            {
                std::cout
                    << "Before createGame\n";

                try
                {
                    gameSession.createGame(
                        mapTypeToFilename(
                            menuUI.getMapSelection()
                        ),
                        menuUI.getHumanPlayerNumbers(),
                        menuUI.getAiPlayerNumbers()
                    );

                    std::cout
                        << "After createGame\n";

                    loadingClock.restart();
                    loadingStarted = true;
                    startGame = true;
                }
                catch (const std::exception& exception)
                {
                    std::cerr
                        << "Game creation failed: "
                        << exception.what()
                        << '\n';

                    window.close();
                }
            }


            // -------------------------
            // Update graphics
            // -------------------------

            if (gameState.getPhase() ==
                PhaseType::GameSetup)
            {
                std::vector<PlayerGraphics>& playerGraphics =
                    gameSetupUI.getPlayerGraphics();

                std::unordered_map<TerritoryID, TerritoryGraphics>&
                    territoryGraphicsMap =
                    gameSetupUI.getTerritoryGraphics();

                const std::vector<Player>& players =
                    gameSession.getPlayers();

                const Map& map =
                    gameSession.getMap();

                GameSetupState& gameSetupState =
                    gameSetupUI.getGameSetupState();

                exchangeLUI.updateGraphics(
                    map,
                    players,
                    gameState,
                    territoryGraphicsMap,
                    playerGraphics,
                    &gameSetupState
                );
            }


            // -------------------------
            // Draw current UI
            // -------------------------

            window.clear();

            if (!startGame)
            {
                menuUI.draw(
                    window
                );
            }
            else
            {
                // -------------------------
                // Loading
                // -------------------------

                if (gameState.getPhase() ==
                    PhaseType::Loading)
                {
                    exchangeLUI.loading(
                        window,
                        loadingUI
                    );

                    if (loadingStarted &&
                        loadingClock
                        .getElapsedTime()
                        .asSeconds() >= 2.f)
                    {
                        exchangeLUI.initialLoading(
                            gameSession,
                            gameSetupUI,
                            gameState,
                            menuUI.getHumanPlayerNumbers(),
                            menuUI.getAiPlayerNumbers(),
                            menuUI.getMapSelection()
                        );
                    }
                }


                // -------------------------
                // Game setup
                // -------------------------

                else if (
                    gameState.getPhase() ==
                    PhaseType::GameSetup)
                {
                    exchangeLUI.gameSetupDraw(
                        window,
                        gameSetupUI
                    );

                    // GameSetupUI handles
                    // profile setup and initial
                    // troop placement.
                }


                // -------------------------
                // Reinforce
                // -------------------------

                else if (
                    gameState.getPhase() ==
                    PhaseType::Reinforce)
                {
                    // SessionUI draws base game screen.
                    // ReinforceUI handles reinforce controls.
                }


                // -------------------------
                // Attack
                // -------------------------

                else if (
                    gameState.getPhase() ==
                    PhaseType::Attack)
                {
                    // SessionUI draws base game screen.
                    // AttackUI handles attack controls.
                }


                // -------------------------
                // Fortify
                // -------------------------

                else if (
                    gameState.getPhase() ==
                    PhaseType::Fortify)
                {
                    // SessionUI draws base game screen.
                    // FortifyUI handles fortify controls.
                }


                // -------------------------
                // Game won
                // -------------------------

                else if (
                    gameState.getPhase() ==
                    PhaseType::GameWon)
                {
                    // SessionUI draws base game screen.
                    // GameWonUI handles game won controls.
                }


                // -------------------------
                // Game quit
                // -------------------------

                else if (
                    gameState.getPhase() ==
                    PhaseType::GameQuit)
                {
                    // SessionUI draws base game screen.
                    // GameQuitUI handles game quit controls.
                }
            }

            window.display();
        }
    }

} // namespace risk