#include "risk/core/session/GameInitializer.h"

#include "risk/world/MapLoader.h"
#include "risk/world/DeckLoader.h"

namespace risk {

    //=========================================================
    // Constructor
    //=========================================================

    GameInitializer::GameInitializer()
        : gameStateManager(
            GIMap,
            GIPlayers
        )
    {
    }

    //=========================================================
    // Initialize Game
    //=========================================================

    std::tuple<Map, std::vector<Player>, Deck>
        GameInitializer::initializeGame(
            std::string& filename,
            int playerNumbers,
            int aiNumbers
        )
    {
        //-----------------------------------------------------
        // Create map
        //-----------------------------------------------------

        GIMap = loadMap(filename);

        //-----------------------------------------------------
        // Create deck
        //-----------------------------------------------------

        Deck deck =
            createDeck(GIMap);

        //-----------------------------------------------------
        // Create players
        //-----------------------------------------------------

        GIPlayers.clear();

        for (int i = 0; i < playerNumbers; ++i)
        {
            GIPlayers.emplace_back(i);
        }

        //-----------------------------------------------------
        // Deal initial territories
        //-----------------------------------------------------

        dealDeck(
            deck,
            GIPlayers
        );

        //-----------------------------------------------------
        // AI setup added later
        //-----------------------------------------------------

        (void)aiNumbers;

        //-----------------------------------------------------
        // Return initialized game state
        //-----------------------------------------------------

        return {
            GIMap,
            GIPlayers,
            deck
        };
    }

    //=========================================================
    // Player Setup
    //=========================================================

    void GameInitializer::updatePlayer(
        Player& player,
        const std::string& name
    )
    {
        player.setPlayerName(name);
    }

    //=========================================================
    // Initial Territory Deal
    //=========================================================

    void GameInitializer::dealDeck(
        Deck& deck,
        std::vector<Player>& players
    )
    {
        const int territoryCount =
            static_cast<int>(
                GIMap.getTerritories().size());

        int territoriesDealt = 0;
        int playerIndex = 0;

        while (territoriesDealt < territoryCount)
        {
            Card& card =
                deck.getNextCard(true);


            TerritoryID territoryID =
                card.getTerritoryID().value();

            Player& currentPlayer =
                players[playerIndex];

            //-------------------------------------------------
            // Assign ownership.
            //-------------------------------------------------

            gameStateManager.updateTerritoryOwner(
                territoryID,
                currentPlayer.getPlayerID()
            );

            //-------------------------------------------------
            // Place initial territory troop.
            //-------------------------------------------------

            gameStateManager.updateTerritoryTroopCount(
                territoryID,
                1
            );

            gameStateManager.updatePlayerTroopCount(
                currentPlayer.getPlayerID(),
                1
            );

            //-------------------------------------------------
            // Next player.
            //-------------------------------------------------

            ++territoriesDealt;
            ++playerIndex;

            if (
                playerIndex >=
                static_cast<int>(players.size())
                )
            {
                playerIndex = 0;
            }
        }
    }

    //=========================================================
    // Initial Troop Placement
    //=========================================================

    void GameInitializer::addTroop(
        Player& player,
        TerritoryID territoryID
    )
    {
        gameStateManager.updateTerritoryTroopCount(
            territoryID,
            1
        );

        gameStateManager.updatePlayerTroopCount(
            player.getPlayerID(),
            1
        );
    }

} // namespace risk