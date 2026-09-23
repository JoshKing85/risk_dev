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
                // Game events
                // -------------------------

                else if (
                    gameState.getPhase() !=
                    PhaseType::Loading)
                {
                    gameSessionUI.handleEvent(
                        *event,
                        window,
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
            std::vector<PlayerGraphics>& playerGraphics =
                gameSessionUI.getPlayerGraphics();

            std::unordered_map<TerritoryID, TerritoryGraphics>&
                territoryGraphicsMap =
                gameSessionUI.getTerritoryGraphics();

            const std::vector<Player>& players =
                gameSession.getPlayers();

            const Map& map =
                gameSession.getMap();

            
            if (gameState.getPhase() == PhaseType::GameSetup)
            {
                GameSetupState& gameSetupState =
                    gameSessionUI.getGameSetupState();

                exchangeLUI.updateGraphics(
                    map,
                    players,
                    gameState,
                    territoryGraphicsMap,
                    playerGraphics,
                    &gameSetupState
                );
            }
            else
            {
                exchangeLUI.updateGraphics(
                    map,
                    players,
                    gameState,
                    territoryGraphicsMap,
                    playerGraphics
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


            // -------------------------
            // Loading
            // -------------------------

            else if (
                gameState.getPhase() ==
                PhaseType::Loading)
            {
                loadingUI.draw(
                    window
                );

                if (loadingStarted &&
                    loadingClock
                    .getElapsedTime()
                    .asSeconds() >= 2.f)
                {
                    gameSessionUI.initialLoading(
                        gameSession,
                        gameState,
                        menuUI.getHumanPlayerNumbers(),
                        menuUI.getAiPlayerNumbers(),
                        menuUI.getMapSelection()
                    );
                }
            }


            // -------------------------
            // Game UI
            // -------------------------

            else
            {
                gameSessionUI.draw(
                    window,
                    gameState,
                    gameSession
                );
            }

            window.display();
        }
    }

} // namespace risk