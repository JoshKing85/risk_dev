#include "risk/core/validation/ValidateReinforceInput.h"

namespace risk {

    bool isReinforceValid(int troopsToReinforce, int totalTroopPool) {
        if (troopsToReinforce <= totalTroopPool && troopsToReinforce > 0) {
            return true;
        }
        return false;
    }
}

