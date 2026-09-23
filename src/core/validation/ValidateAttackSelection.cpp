#include "risk/core/validation/ValidateAttackSelection.h"
#include "risk/world/Map.h"
#include <vector>

namespace risk {

	bool isValidAttackSelection(int playerID, const TerritoryID& territorySelection, Map& map) {
		
		if (map.getTerritory(territorySelection).getTroopCount() < 2) {
			return false;
		}
		else {
			std::vector<TerritoryID> adjacentTerritories = map.getTerritory(territorySelection).getAdjacentTerritories();

			for (const auto& territory : adjacentTerritories)
			{
				if (map.getTerritory(territory).getOwnerID != playerID)
				{
					return true;
				}
			}
			return false;
		}
		
	}

}// namespace risk