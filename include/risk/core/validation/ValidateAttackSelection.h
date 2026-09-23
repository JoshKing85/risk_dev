#pragma once

#include "risk/enums.h"
#include "risk/world/Map.h"

#include <vector>

namespace risk {

bool isValidAttackSelection(int playerID, const TerritoryID &territorySelection, Map &map);

} // namespace risk