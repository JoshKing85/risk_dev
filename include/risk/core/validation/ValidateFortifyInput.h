#pragma once

#include "risk/enums.h"
#include "risk/world/Map.h"

#include <vector>

namespace risk {

    bool isFortifyValid(
        const Map &map, 
        const TerritoryID &fromTerritory,
        const TerritoryID &toTerritory,
        int playerID);

} // namespace risk