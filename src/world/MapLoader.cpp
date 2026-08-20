#include "risk/world/MapLoader.h"
#include "risk/enums.h"

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace risk {

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
            std::string continentName = continentData["cont_id"].get<std::string>();
            ContinentID continentID = stringToContinentID(continentName);

            int bonus = continentData["bonus"].get<int>();

            std::vector<TerritoryID> continentTerritories;
            std::vector<TerritoryID> borderTerritories;

            for (const auto& borderTerritory : continentData["border_territories"])
            {
                borderTerritories.push_back(
                    stringToTerritoryID(borderTerritory.get<std::string>())
                );
            }

            for (const auto& territoryData : continentData["territories"])
            {
                std::string territoryName = territoryData["id"].get<std::string>();
                TerritoryID territoryID = stringToTerritoryID(territoryName);

                continentTerritories.push_back(territoryID);

                std::vector<TerritoryID> adjacentTerritories;

                for (const auto& neighbour : territoryData["neighbors"])
                {
                    adjacentTerritories.push_back(
                        stringToTerritoryID(neighbour.get<std::string>())
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



	ContinentID stringToContinentID(const std::string& name) {
		if (name == "NorthAmerica") return ContinentID::NorthAmerica;
		if (name == "SouthAmerica") return ContinentID::SouthAmerica;
		if (name == "Europe") return ContinentID::Europe;
		if (name == "Africa") return ContinentID::Africa;
		if (name == "Asia") return ContinentID::Asia;
		if (name == "Australia") return ContinentID::Australia;
		throw std::invalid_argument("Unknown continent name: " + name);
	}

	TerritoryID stringToTerritoryID(const std::string& name) {
		if (name == "Alaska") return TerritoryID::Alaska;
		if (name == "Alberta") return TerritoryID::Alberta;
		if (name == "CentralAmerica") return TerritoryID::CentralAmerica;
		if (name == "EasternUnitedStates") return TerritoryID::EasternUnitedStates;
		if (name == "Greenland") return TerritoryID::Greenland;
		if (name == "NorthwestTerritory") return TerritoryID::NorthwestTerritory;
		if (name == "Ontario") return TerritoryID::Ontario;
		if (name == "Quebec") return TerritoryID::Quebec;
		if (name == "WesternUnitedStates") return TerritoryID::WesternUnitedStates;

		if (name == "Argentina") return TerritoryID::Argentina;
		if (name == "Brazil") return TerritoryID::Brazil;
		if (name == "Peru") return TerritoryID::Peru;
		if (name == "Venezuela") return TerritoryID::Venezuela;

		if (name == "GreatBritain") return TerritoryID::GreatBritain;
		if (name == "Iceland") return TerritoryID::Iceland;
		if (name == "NorthernEurope") return TerritoryID::NorthernEurope;
		if (name == "Scandinavia") return TerritoryID::Scandinavia;
		if (name == "SouthernEurope") return TerritoryID::SouthernEurope;
		if (name == "Ukraine") return TerritoryID::Ukraine;
		if (name == "WesternEurope") return TerritoryID::WesternEurope;

        if (name == "Congo") return TerritoryID::Congo;
        if (name == "EastAfrica") return TerritoryID::EastAfrica;
        if (name == "Egypt") return TerritoryID::Egypt;
        if (name == "Madagascar") return TerritoryID::Madagascar;
        if (name == "NorthAfrica") return TerritoryID::NorthAfrica;
        if (name == "SouthAfrica") return TerritoryID::SouthAfrica;

        if (name == "Afghanistan") return TerritoryID::Afghanistan;
        if (name == "China") return TerritoryID::China;
        if (name == "India") return TerritoryID::India;
        if (name == "Irkutsk") return TerritoryID::Irkutsk;
        if (name == "Japan") return TerritoryID::Japan;
        if (name == "Kamchatka") return TerritoryID::Kamchatka;
        if (name == "MiddleEast") return TerritoryID::MiddleEast;
        if (name == "Mongolia") return TerritoryID::Mongolia;
        if (name == "Siam") return TerritoryID::Siam;
        if (name == "Siberia") return TerritoryID::Siberia;
        if (name == "Ural") return TerritoryID::Ural;
        if (name == "Yakutsk") return TerritoryID::Yakutsk;

        if (name == "EasternAustralia") return TerritoryID::EasternAustralia;
        if (name == "Indonesia") return TerritoryID::Indonesia;
        if (name == "NewGuinea") return TerritoryID::NewGuinea;
        if (name == "WesternAustralia") return TerritoryID::WesternAustralia;
		throw std::invalid_argument("Unknown territory name: " + name);
	}
}

