#pragma once

#include "risk/enums.h"

#include <vector>

namespace risk {

bool isValidTerritorySelection(
    const TerritoryID &territorySelected,
    const std::vector<TerritoryID> &territoriesOwnedByPlayer);

} // namespace risk