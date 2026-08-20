#include "risk/core/validation/ValidateDiceInput.h"

namespace risk {

    bool isValidDiceInput(
        int diceInput,
        int territoryTroopCount
    )
    {
        if (
            (territoryTroopCount - 1 >= diceInput) &&
            (diceInput >= 1 && diceInput <= 3)
            )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

} // namespace risk