#include "risk/core/validation/ValidateFortifyInput.h"

#include <vector>
#include <stack>
#include <algorithm>



namespace risk {

    bool isFortifyValid(
        const Map& map,
        const TerritoryID& fromTerritory,
        const TerritoryID& toTerritory,
        int playerID){


		std::vector<TerritoryID> visited;
		std::stack<TerritoryID> depthStack;

        depthStack.push(fromTerritory);
        

        while (!depthStack.empty()){
            TerritoryID currentTerritory = depthStack.top();
            depthStack.pop();
            visited.push_back(currentTerritory);
            std::vector<TerritoryID> currentAdjTerritories = map.getTerritory(currentTerritory).getAdjacentTerritories();

            for (const auto& territory : currentAdjTerritories) {
                if (territory == toTerritory && map.getTerritory(territory).getOwnerID() == playerID) {
                    return true;
                }
                else if (
                    (map.getTerritory(territory).getOwnerID() == playerID) &&
                    (std::find(visited.begin(), visited.end(), territory) == visited.end())
                    ) {
                        depthStack.push(territory);
                }
            }
            
        }
        return false;
    }
            
}
        



