#include "risk/core/validation/ValidateAttackSelection.h"
#include "risk/world/Map.h"

#include <vector>

namespace risk {

    bool isValidAttackSelection(
        int playerID,
        const TerritoryID& territorySelection,
        Map& map)
    {
        int ownerID =
            map.getTerritory(
                territorySelection)
            .getOwnerID();

        if (ownerID != playerID)
        {
            return false;
        }

        int troopCount =
            map.getTerritory(
                territorySelection)
            .getTroopCount();

        if (troopCount < 2)
        {
            return false;
        }

        std::vector<TerritoryID> adjacentTerritories =
            map.getTerritory(
                territorySelection)
            .getAdjacentTerritories();

        for (const auto& territory : adjacentTerritories)
        {
            int adjacentOwnerID =
                map.getTerritory(
                    territory)
                .getOwnerID();

            if (adjacentOwnerID != playerID)
            {
                return true;
            }
        }

        return false;
    }

} // namespace risk