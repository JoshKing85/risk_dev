#include "risk/utils/TerritoryConverter.h"

#include <stdexcept>

namespace risk
{
    TerritoryID stringToTerritoryID(
        const std::string& territoryName)
    {
        // British Isles
        if (territoryName == "England")
            return TerritoryID::England;

        if (territoryName == "Scotland")
            return TerritoryID::Scotland;

        if (territoryName == "Wales")
            return TerritoryID::Wales;

        if (territoryName == "Ireland")
            return TerritoryID::Ireland;


        // Western Europe
        if (territoryName == "Portugal")
            return TerritoryID::Portugal;

        if (territoryName == "Spain")
            return TerritoryID::Spain;

        if (territoryName == "France")
            return TerritoryID::France;

        if (territoryName == "Netherlands")
            return TerritoryID::Netherlands;

        if (territoryName == "Corsica")
            return TerritoryID::Corsica;

        if (territoryName == "Sardinia")
            return TerritoryID::Sardinia;


        // German States
        if (territoryName == "Prussia")
            return TerritoryID::Prussia;

        if (territoryName == "Poland")
            return TerritoryID::Poland;

        if (territoryName == "Hanover")
            return TerritoryID::Hanover;

        if (territoryName == "Saxony")
            return TerritoryID::Saxony;

        if (territoryName == "Westphalia")
            return TerritoryID::Westphalia;

        if (territoryName == "Bavaria")
            return TerritoryID::Bavaria;


        // Austrian Empire
        if (territoryName == "Austria")
            return TerritoryID::Austria;

        if (territoryName == "Hungary")
            return TerritoryID::Hungary;

        if (territoryName == "Serbia")
            return TerritoryID::Serbia;

        if (territoryName == "Wallachia")
            return TerritoryID::Wallachia;

        if (territoryName == "Bulgaria")
            return TerritoryID::Bulgaria;

        if (territoryName == "Greece")
            return TerritoryID::Greece;

        if (territoryName == "Bohemia")
            return TerritoryID::Bohemia;


        // Italian States
        if (territoryName == "Piedmont")
            return TerritoryID::Piedmont;

        if (territoryName == "Lombardy")
            return TerritoryID::Lombardy;

        if (territoryName == "Tuscany")
            return TerritoryID::Tuscany;

        if (territoryName == "Naples")
            return TerritoryID::Naples;

        if (territoryName == "Sicily")
            return TerritoryID::Sicily;


        // Scandinavia
        if (territoryName == "Denmark")
            return TerritoryID::Denmark;

        if (territoryName == "Norway")
            return TerritoryID::Norway;

        if (territoryName == "Sweden")
            return TerritoryID::Sweden;

        if (territoryName == "Finland")
            return TerritoryID::Finland;


        // Russian Empire
        if (territoryName == "StPetersburg")
            return TerritoryID::StPetersburg;

        if (territoryName == "Novgorod")
            return TerritoryID::Novgorod;

        if (territoryName == "Moscow")
            return TerritoryID::Moscow;

        if (territoryName == "Smolensk")
            return TerritoryID::Smolensk;

        if (territoryName == "Lithuania")
            return TerritoryID::Lithuania;

        if (territoryName == "Belarus")
            return TerritoryID::Belarus;

        if (territoryName == "Ukraine")
            return TerritoryID::Ukraine;

        if (territoryName == "Moldavia")
            return TerritoryID::Moldavia;

        if (territoryName == "Crimea")
            return TerritoryID::Crimea;

        if (territoryName == "EasternRussia")
            return TerritoryID::EasternRussia;


        throw std::invalid_argument(
            "Unknown territory: " + territoryName
        );
    }
}