#include "risk/utils/ContinentConverter.h"

#include <stdexcept>

namespace risk
{
    ContinentID stringToContinentID(
        const std::string& continentName)
    {
        if (continentName == "BritishIsles")
            return ContinentID::BritishIsles;

        if (continentName == "WesternEurope")
            return ContinentID::WesternEurope;

        if (continentName == "GermanStates")
            return ContinentID::GermanStates;

        if (continentName == "AustrianEmpire")
            return ContinentID::AustrianEmpire;

        if (continentName == "ItalianStates")
            return ContinentID::ItalianStates;

        if (continentName == "Scandinavia")
            return ContinentID::Scandinavia;

        if (continentName == "RussianEmpire")
            return ContinentID::RussianEmpire;

        throw std::invalid_argument(
            "Unknown continent name: " +
            continentName);
    }
};