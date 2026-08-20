#pragma once

#include "risk/world/Map.h"
#include <string>

namespace risk {

Map loadMap(const std::string& filename);
ContinentID stringToContinentID(const std::string &name);
TerritoryID stringToTerritoryID(const std::string &name);

}


