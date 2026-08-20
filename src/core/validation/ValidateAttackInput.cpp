#include "risk/core/validation/ValidateAttackInput.h"

namespace risk {

    bool isValidAttackInput(
        const TerritoryID& territoryToAttack,
        const std::vector<TerritoryID>& adjacentTerritories,
        int territorySelectedTroopCount
    )
    {
        if (territorySelectedTroopCount < 2)
        {
            return false;
        }

        for (const auto& territory : adjacentTerritories)
        {
            if (territory == territoryToAttack)
            {
                return true;
            }
        }

        return false;
    }

} // namespace risk