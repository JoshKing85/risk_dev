#include "risk/entities/Card.h"

namespace risk
{

    Card::Card(
        CardType cardType,
        std::optional<TerritoryID> territoryID,
        std::optional<ContinentID> continentID
    )
        : cardType(cardType),
        territoryID(territoryID),
        continentID(continentID)
    {
    }

    CardType Card::getCardType() const
    {
        return cardType;
    }

    bool Card::hasTerritory() const
    {
        return territoryID.has_value();
    }

    std::optional<TerritoryID> Card::getTerritoryID() const
    {
        return territoryID;
    }

    std::optional<ContinentID> Card::getContinentID() const
    {
        return continentID;
	}

}