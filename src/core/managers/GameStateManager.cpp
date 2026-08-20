#include "risk/core/managers/GameStateManager.h"

#include "risk/entities/Player.h"

namespace risk {

    //=========================================================
    // Constructor
    //=========================================================

    GameStateManager::GameStateManager(
        Map& map,
        std::vector<Player>& players
    )
        : map(map),
        players(players)
    {
    }

    //=========================================================
    // Territory methods
    //=========================================================

    void GameStateManager::updateTerritoryOwner(
        TerritoryID territoryID,
        int newOwnerID
    )
    {
        Territory& territory =
            map.getTerritory(territoryID);

        const int oldOwnerID =
            territory.getOwnerID();

        const ContinentID continentID =
            territory.getContinentID();

        if (oldOwnerID == newOwnerID)
        {
            return;
        }

        //-----------------------------------------------------
        // Remove territory from previous owner.
        //-----------------------------------------------------

        if (oldOwnerID >= 0)
        {
            updatePlayerTerritories(
                oldOwnerID,
                territory,
                false
            );
        }

        //-----------------------------------------------------
        // Update territory owner.
        //-----------------------------------------------------

        territory.setOwner(newOwnerID);

        //-----------------------------------------------------
        // Give territory to new owner.
        //-----------------------------------------------------

        updatePlayerTerritories(
            newOwnerID,
            territory,
            true
        );

        //-----------------------------------------------------
        // Check whether the previous owner lost control
        // of the continent.
        //-----------------------------------------------------

        if (
            oldOwnerID >= 0 &&
            map.getContinent(continentID).getOwnerID() == oldOwnerID &&
            checkContinentOwnership(
                oldOwnerID,
                continentID
            ) == ContinentID::None
            )
        {
            updatePlayerContinentOwnership(
                oldOwnerID,
                continentID,
                false
            );

            map.getContinent(continentID).setOwner(-1);
        }

        //-----------------------------------------------------
        // Check whether the new owner gained control
        // of the continent.
        //-----------------------------------------------------

        if (
            checkContinentOwnership(
                newOwnerID,
                continentID
            ) != ContinentID::None
            )
        {
            updateContinentOwner(
                continentID,
                newOwnerID
            );
        }
    }

    void GameStateManager::updateTerritoryTroopCount(
        TerritoryID territoryID,
        int troopChange
    )
    {
        Territory& territory =
            map.getTerritory(territoryID);

        if (troopChange > 0)
        {
            territory.addTroops(troopChange);
        }
        else if (troopChange < 0)
        {
            territory.removeTroops(-troopChange);
        }
    }

    //=========================================================
    // Continent methods
    //=========================================================

    void GameStateManager::updateContinentOwner(
        ContinentID continentID,
        int newOwnerID
    )
    {
        Continent& continent =
            map.getContinent(continentID);

        const int oldOwnerID =
            continent.getOwnerID();

        if (oldOwnerID == newOwnerID)
        {
            return;
        }

        if (oldOwnerID >= 0)
        {
            updatePlayerContinentOwnership(
                oldOwnerID,
                continentID,
                false
            );
        }

        updatePlayerContinentOwnership(
            newOwnerID,
            continentID,
            true
        );

        continent.setOwner(newOwnerID);
    }

    ContinentID GameStateManager::checkContinentOwnership(
        int playerID,
        ContinentID continentID
    )
    {
        const Continent& continent =
            map.getContinent(continentID);

        const std::vector<TerritoryID>& territories =
            continent.getTerritories();

        for (const TerritoryID territoryID : territories)
        {
            const Territory& territory =
                map.getTerritory(territoryID);

            if (territory.getOwnerID() != playerID)
            {
                return ContinentID::None;
            }
        }

        return continentID;
    }

    //=========================================================
    // Player methods
    //=========================================================

    void GameStateManager::updatePlayerTerritories(
        int playerID,
        const Territory& territory,
        bool gainTerritory
    )
    {
        Player& player =
            players[playerID];

        if (gainTerritory)
        {
            player.addTerritory(
                territory.getID()
            );
        }
        else
        {
            player.removeTerritory(
                territory.getID()
            );
        }
    }

    void GameStateManager::updatePlayerContinentOwnership(
        int playerID,
        ContinentID continentID,
        bool gainOwnership
    )
    {
        Player& player =
            players[playerID];

        if (gainOwnership)
        {
            player.addContinent(continentID);
        }
        else
        {
            player.removeContinent(continentID);
        }
    }

    void GameStateManager::updatePlayerTroopCount(
        int playerID,
        int troopChange
    )
    {
        Player& player =
            players[playerID];

        if (troopChange > 0)
        {
            player.addTroops(troopChange);
        }
        else if (troopChange < 0)
        {
            player.removeTroops(-troopChange);
        }
    }

    void GameStateManager::updatePlayerSet(
        int playerID,
        const std::vector<Card>& newSet
    )
    {
        Player& player =
            players[playerID];

        player.setPlayerSet(newSet);
    }
    //=========================================================
    // Player methods
    //=========================================================
    int GameStateManager::getTerritoryOwnerID(
        TerritoryID territoryID
    ) const
    {
        return map.getTerritory(territoryID).getOwnerID();
    }

} // namespace risk