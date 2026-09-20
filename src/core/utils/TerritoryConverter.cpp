#include "risk/utils/TerritoryConverter.h"

#include <stdexcept>

namespace risk
{
    TerritoryID stringToTerritoryID(const std::string& territoryName)
    {
        // North America
        if (territoryName == "Bearus")
            return TerritoryID::Bearus;

        if (territoryName == "Rockies")
            return TerritoryID::Rockies;

        if (territoryName == "Mexico")
            return TerritoryID::Mexico;

        if (territoryName == "GreatLakes")
            return TerritoryID::GreatLakes;

        if (territoryName == "ArcticIsle")
            return TerritoryID::ArcticIsle;

        if (territoryName == "Yukon")
            return TerritoryID::Yukon;

        if (territoryName == "Tairono")
            return TerritoryID::Tairono;

        if (territoryName == "StLawrence")
            return TerritoryID::StLawrence;

        if (territoryName == "California")
            return TerritoryID::California;


        // South America
        if (territoryName == "Patagonia")
            return TerritoryID::Patagonia;

        if (territoryName == "Amazonia")
            return TerritoryID::Amazonia;

        if (territoryName == "Andes")
            return TerritoryID::Andes;

        if (territoryName == "Orinoco")
            return TerritoryID::Orinoco;


        // Europe
        if (territoryName == "GreatBritain")
            return TerritoryID::GreatBritain;

        if (territoryName == "Iceland")
            return TerritoryID::Iceland;

        if (territoryName == "Germany")
            return TerritoryID::Germany;

        if (territoryName == "Scandinavia")
            return TerritoryID::Scandinavia;

        if (territoryName == "Iberia")
            return TerritoryID::Iberia;

        if (territoryName == "Russia")
            return TerritoryID::Russia;

        if (territoryName == "France")
            return TerritoryID::France;


        // Africa
        if (territoryName == "CentralBasin")
            return TerritoryID::CentralBasin;

        if (territoryName == "Riftlands")
            return TerritoryID::Riftlands;

        if (territoryName == "Nilelands")
            return TerritoryID::Nilelands;

        if (territoryName == "LemurIsland")
            return TerritoryID::LemurIsland;

        if (territoryName == "WestAfrica")
            return TerritoryID::WestAfrica;

        if (territoryName == "CapeRegion")
            return TerritoryID::CapeRegion;


        // Asia
        if (territoryName == "Highlands")
            return TerritoryID::Highlands;

        if (territoryName == "China")
            return TerritoryID::China;

        if (territoryName == "Induslands")
            return TerritoryID::Induslands;

        if (territoryName == "BaikalRegion")
            return TerritoryID::BaikalRegion;

        if (territoryName == "IslandEmpire")
            return TerritoryID::IslandEmpire;

        if (territoryName == "EasternPeninsula")
            return TerritoryID::EasternPeninsula;

        if (territoryName == "ArabianRegion")
            return TerritoryID::ArabianRegion;

        if (territoryName == "GreatSteppe")
            return TerritoryID::GreatSteppe;

        if (territoryName == "Indochina")
            return TerritoryID::Indochina;

        if (territoryName == "NorthernExpanse")
            return TerritoryID::NorthernExpanse;

        if (territoryName == "UralRange")
            return TerritoryID::UralRange;

        if (territoryName == "FarNortheast")
            return TerritoryID::FarNortheast;


        // Australia
        if (territoryName == "NewSouthWales")
            return TerritoryID::NewSouthWales;

        if (territoryName == "Komodo")
            return TerritoryID::Komodo;

        if (territoryName == "Philippines")
            return TerritoryID::Philippines;

        if (territoryName == "WesternAustralia")
            return TerritoryID::WesternAustralia;


        throw std::invalid_argument(
            "Unknown territory: " + territoryName
        );
    }
}