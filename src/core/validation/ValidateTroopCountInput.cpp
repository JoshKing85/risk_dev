#include "risk/core/validation/ValidateTroopCountInput.h"

namespace risk {

    bool isTroopCountValid(int troopCount, int troopPool) {
        if (troopCount <= troopPool && troopCount > 0) {
            return true;
        }
        return false;
    }
}

