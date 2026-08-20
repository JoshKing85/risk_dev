#pragma once

#include "risk/enums.h"

#include <vector>

namespace risk {

bool isValidAttackInput(
    const TerritoryID &territoryToAttack,
    const std::vector<TerritoryID> &adjacentTerritories,
    int territorySelectedTroopCount);

} // namespace risk