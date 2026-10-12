#include "risk/world/MapLoader.h"

#include "risk/utils/ContinentConverter.h"
#include "risk/utils/TerritoryConverter.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace risk {

    Map loadMap(const std::string& filename)
    {
        Map map;

        std::cout
            << "[DEBUG] Loading map file: "
            << filename
            << '\n';

        std::ifstream file(filename);

        if (!file.is_open())
        {
            throw std::runtime_error(
                "Could not open map file: " +
                filename);
        }

        json mapData;
        file >> mapData;

        //---------------------------------------------------------
        // Continents
        //---------------------------------------------------------

        for (const auto& continentData :
            mapData.at("continents"))
        {
            std::string continentName =
                continentData.at("cont_id")
                .get<std::string>();

            ContinentID continentID =
                stringToContinentID(
                    continentName);

            int bonus =
                continentData.at("bonus")
                .get<int>();

            std::vector<TerritoryID>
                continentTerritories;

            std::vector<TerritoryID>
                borderTerritories;

            //-----------------------------------------------------
            // Border territories
            //-----------------------------------------------------

            for (const auto& borderTerritory :
                continentData.at(
                    "border_territories"))
            {
                borderTerritories.push_back(
                    stringToTerritoryID(
                        borderTerritory
                        .get<std::string>()));
            }

            //-----------------------------------------------------
            // Territories
            //-----------------------------------------------------

            for (const auto& territoryData :
                continentData.at("territories"))
            {
                std::string territoryName =
                    territoryData.at("id")
                    .get<std::string>();

                TerritoryID territoryID =
                    stringToTerritoryID(
                        territoryName);

                continentTerritories.push_back(
                    territoryID);

                std::vector<TerritoryID>
                    adjacentTerritories;

                //---------------------------------------------
                // Adjacent territories
                //---------------------------------------------

                for (const auto& neighbour :
                    territoryData.at("neighbors"))
                {
                    adjacentTerritories.push_back(
                        stringToTerritoryID(
                            neighbour
                            .get<std::string>()));
                }

                Territory territory(
                    territoryID,
                    continentID,
                    adjacentTerritories);

                map.addTerritory(
                    territory);
            }

            //-----------------------------------------------------
            // Continent
            //-----------------------------------------------------

            Continent continent(
                continentID,
                bonus,
                continentTerritories,
                borderTerritories);

            map.addContinent(
                continent);
        }

        return map;
    }

} // namespace risk