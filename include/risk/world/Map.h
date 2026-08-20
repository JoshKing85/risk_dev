#pragma once

#include "risk/entities/Territory.h"
#include "risk/world/Continent.h"
#include "risk/enums.h"

#include <unordered_map>

namespace risk {

class Map {
private:
    std::unordered_map<TerritoryID, Territory> territories;
    std::unordered_map<ContinentID, Continent> continents;

public:
    Territory &getTerritory(TerritoryID id);
    const Territory &getTerritory(TerritoryID id) const;

    Continent &getContinent(ContinentID id);
    const Continent &getContinent(ContinentID id) const;
    const std::unordered_map<TerritoryID, Territory> &getTerritories() const;

    void addTerritory(const Territory& territory);
    void addContinent(const Continent& continent);
};

} // namespace risk