#include "risk/world/Continent.h"


namespace risk {

    Continent::Continent(
        ContinentID id,
        int bonus,
        const std::vector<TerritoryID>& territoryIDs,
        const std::vector<TerritoryID>& borderTerritoryIDs
    )
        : continentID(id),
        controlBonus(bonus),
        territories(territoryIDs),
        borderTerritories(borderTerritoryIDs),
        ownerID(-1)
    {
    }


    // Getters
    ContinentID Continent::getContinentID() const
    {
        return continentID;
    };

    int Continent::getControlBonus() const
    {
        return controlBonus;
    };

    int Continent::getOwnerID() const
    {
        return ownerID;
    }

    const std::vector<TerritoryID>& Continent::getTerritories() const
    {
        return territories;
    };

    const std::vector<TerritoryID>& Continent::getBorderTerritories() const
    {
        return borderTerritories;
    };


    // Setters
    void Continent::setOwner(int newOwner)
    {
        ownerID = newOwner;
    };

}