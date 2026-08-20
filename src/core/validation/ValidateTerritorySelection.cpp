#include "risk/core/validation/ValidateTerritorySelection.h"

namespace risk {

    bool isValidTerritorySelection(
        const TerritoryID& territorySelected,
        const std::vector<TerritoryID>& territoriesOwnedByPlayer
    )
    {
        for (const auto& territory : territoriesOwnedByPlayer)
        {
            if (territory == territorySelected)
            {
                return true;
            }
        }

        return false;
    }

} // namespace risk