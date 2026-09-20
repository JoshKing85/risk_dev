#pragma once

#include "risk/enums.h"
#include <string>

namespace risk {
TerritoryID stringToTerritoryID(const std::string &territoryName);
}