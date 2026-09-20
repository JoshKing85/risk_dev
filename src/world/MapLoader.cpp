#include "risk/world/MapLoader.h"
#include "risk/utils/TerritoryConverter.h"
#include "risk/utils/ContinentConverter.h"

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace risk
{
    Map loadMap(const std::string& filename)
    {
        Map map;

        std::ifstream file(filename);

        if (!file.is_open())
        {
            throw std::runtime_error("Could not open map file: " + filename);
        }

        json mapData;
        file >> mapData;

        for (const auto& continentData : mapData["continents"])
        {
            std::string continentName =
                continentData["cont_id"].get<std::string>();

            ContinentID continentID =
                stringToContinentID(continentName);

            int bonus =
                continentData["bonus"].get<int>();

            std::vector<TerritoryID> continentTerritories;
            std::vector<TerritoryID> borderTerritories;

            for (const auto& borderTerritory :
                continentData["border_territories"])
            {
                borderTerritories.push_back(
                    stringToTerritoryID(
                        borderTerritory.get<std::string>()
                    )
                );
            }

            for (const auto& territoryData :
                continentData["territories"])
            {
                std::string territoryName =
                    territoryData["id"].get<std::string>();

                TerritoryID territoryID =
                    stringToTerritoryID(territoryName);

                continentTerritories.push_back(territoryID);

                std::vector<TerritoryID> adjacentTerritories;

                for (const auto& neighbour :
                    territoryData["neighbors"])
                {
                    adjacentTerritories.push_back(
                        stringToTerritoryID(
                            neighbour.get<std::string>()
                        )
                    );
                }

                Territory territory(
                    territoryID,
                    continentID,
                    adjacentTerritories
                );

                map.addTerritory(territory);
            }

            Continent continent(
                continentID,
                bonus,
                continentTerritories,
                borderTerritories
            );

            map.addContinent(continent);
        }

        return map;
    }
}