#include "risk/entities/Territory.h"

#include <algorithm>

namespace risk
{
    Territory::Territory(
        TerritoryID id,
        ContinentID continent,
        const std::vector<TerritoryID>& adjacentIDs
    )
        : territoryID(id),
        continentID(continent),
        adjacentTerritories(adjacentIDs),
        troopCount(0),
        ownerID(-1)
    {
    }

    // --- Getters ---

    TerritoryID Territory::getID() const
    {
        return territoryID;
    }

    const std::vector<TerritoryID>& Territory::getAdjacentTerritories() const
    {
        return adjacentTerritories;
    }

    int Territory::getTroopCount() const
    {
        return troopCount;
    }
    int Territory::getOwnerID() const
    {
        return ownerID;
	}

    ContinentID Territory::getContinentID() const
    {
        return continentID;
    }
    

    // --- Setters ---

    void Territory::setOwner(int newOwnerID)
    {
        ownerID = newOwnerID;
    }

    void Territory::addTroops(int amount)
    {
        troopCount += amount;
    }

    void Territory::removeTroops(int amount)
    {
        troopCount = std::max(0, troopCount - amount);
    }
}