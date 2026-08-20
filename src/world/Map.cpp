#include "risk/world/Map.h"

namespace risk {

    Territory& Map::getTerritory(TerritoryID id)
    {
        return territories.at(id);
    }

    const Territory& Map::getTerritory(TerritoryID id) const
    {
        return territories.at(id);
    }

    Continent& Map::getContinent(ContinentID id)
    {
        return continents.at(id);
    }

    const Continent& Map::getContinent(ContinentID id) const
    {
        return continents.at(id);
    }
    const std::unordered_map<TerritoryID, Territory>& Map::getTerritories() const
    {
        return territories;
    }

    void Map::addTerritory(const Territory& territory)
    {
        territories.emplace(
            territory.getID(),
            territory
        );
    }

    void Map::addContinent(const Continent& continent)
    {
        continents.emplace(
            continent.getContinentID(),
            continent
        );
    }

} // namespace risk