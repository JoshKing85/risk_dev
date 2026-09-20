#include "risk/utils/ContinentConverter.h"

#include <stdexcept>

namespace risk
{
    ContinentID stringToContinentID(const std::string& continentName)
    {
            if (continentName == "NorthAmerica") return ContinentID::NorthAmerica;
            if (continentName == "SouthAmerica") return ContinentID::SouthAmerica;
            if (continentName == "Europe") return ContinentID::Europe;
            if (continentName == "Africa") return ContinentID::Africa;
            if (continentName == "Asia") return ContinentID::Asia;
            if (continentName == "Australia") return ContinentID::Australia;
            throw std::invalid_argument("Unknown continent name: " + continentName);
        }
    };