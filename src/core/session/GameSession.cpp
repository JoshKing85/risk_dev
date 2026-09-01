#include "risk/core/session/GameSession.h"
#include "risk/core/session/GameInitializer.h"

// managers
#include "risk/core/managers/GameStateManager.h"
#include "risk/core/mangages/TurnManager.h"

//entity and world
#include "risk/entities/Player.h"

#include "risk/world/Deck.h"
#include "risk/world/Map.h"

#include "risk/core/validation/ValidateTerritorySelection.h"

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

namespace risk {

    //=========================================================
    // Constructor
    //=========================================================

    GameSession::GameSession()
    {
    }

    //=========================================================
    // Create Game
    //=========================================================

    void GameSession::createGame(
        std::string& filename,
        int playerNumbers,
        int aiNumbers
    )
    {
        bool createActive = true;

        while (createActive)
        {
            //-------------------------------------------------
            // Create base game state
            //-------------------------------------------------

            GameInitializer gameInitializer;

            std::tie(map, players, deck) =
                gameInitializer.initializeGame(
                    filename,
                    playerNumbers,
                    aiNumbers
                );

            //-------------------------------------------------
            // Game state manager for setup
            //-------------------------------------------------

            GameStateManager gameStateManager(
                map,
                players
            );

            //-------------------------------------------------
            // Player names
            //-------------------------------------------------

            for (auto& player : players)
            {
                // USER INPUT
                // Enter name of user player

                std::string name;

                gameInitializer.updatePlayer(
                    player,
                    name
                );
            }

            //-------------------------------------------------
            // Deal initial territories
            //-------------------------------------------------

            gameInitializer.dealDeck(
                deck,
                players,
                map,
                gameStateManager
            );

            //-------------------------------------------------
            // Calculate remaining starting troops
            //-------------------------------------------------

            std::vector<int> remainingTroops;

            for (auto& player : players)
            {
                int troops =
                    static_cast<int>(
                        120 / players.size()
                        )
                    -
                    static_cast<int>(
                        player.getTerritories().size()
                        );

                remainingTroops.push_back(
                    troops
                );
            }

            //-------------------------------------------------
            // Initial troop placement
            //-------------------------------------------------

            int playerCount = 0;
            bool setupComplete = false;

            while (!setupComplete)
            {
                if (remainingTroops[playerCount] > 0)
                {
                    // USER INPUT
                    // Current player selects one of their
                    // owned territories.

                    TerritoryID territorySelection;

                    if (isValidTerritorySelection(
                        territorySelection,
                        players[playerCount].getTerritories()
                    ))
                    {
                        gameStateManager.updateTerritoryTroopCount(
                            territorySelection,
                            1
                        );

                        gameStateManager.updatePlayerTroopCount(
                            players[playerCount].getPlayerID(),
                            1
                        );

                        remainingTroops[playerCount]--;
                    }
                }

                //-------------------------------------------------
                // Next player
                //-------------------------------------------------

                playerCount++;

                if (
                    playerCount >=
                    static_cast<int>(players.size())
                    )
                {
                    playerCount = 0;

                    setupComplete =
                        std::all_of(
                            remainingTroops.begin(),
                            remainingTroops.end(),
                            [](int troops)
                            {
                                return troops == 0;
                            }
                        );
                }
            }

            //-------------------------------------------------
            // Game setup complete
            //-------------------------------------------------

            createActive = false;
        }
    };

    void GameSession::runGame()
    {
        bool gameActive = true;
        int playerCount = 0;

        while (gameActive)
        {
            // USER INPUT
            // Need option to quit game.

            TurnManager currentTurn(
                players[playerCount],
                players,
                map,
                deck
            );

            playerCount++;

            if (playerCount >= players.size())
            {
                playerCount = 0;
            }
        }
    }
        
} // namespace risk