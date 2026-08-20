#pragma once

#include "risk/enums.h"
#include "risk/world/Deck.h"
#include "risk/world/Map.h"

namespace risk {

Deck createDeck(const Map &map);

}