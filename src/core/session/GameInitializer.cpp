#include "risk/core/session/GameInitializer.h"

#include "risk/world/MapLoader.h"
#include "risk/world/DeckLoader.h"

namespace risk {

    //=========================================================
    // Constructor
    //=========================================================

    GameInitializer::GameInitializer()
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

        Map map =
            loadMap(filename);

        //-----------------------------------------------------
        // Create deck
        //-----------------------------------------------------

        Deck deck =
            createDeck(map);

        //-----------------------------------------------------
        // Create players
        //-----------------------------------------------------

        std::vector<Player> players;

        for (int i = 0; i < playerNumbers; ++i)
        {
            players.emplace_back(i);
        }

        //-----------------------------------------------------
        // AI setup added later
        //-----------------------------------------------------

        (void)aiNumbers;

        //-----------------------------------------------------
        // Return base game state
        //-----------------------------------------------------

        return {
            map,
            players,
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
        std::vector<Player>& players,
        Map& map,
        GameStateManager& gameStateManager
    )
    {
        const int territoryCount =
            static_cast<int>(
                map.getTerritories().size()
                );

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
            // Assign ownership
            //-------------------------------------------------

            gameStateManager.updateTerritoryOwner(
                territoryID,
                currentPlayer.getPlayerID()
            );

            //-------------------------------------------------
            // Place initial territory troop
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
            // Next player
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

} // namespace risk