#include "risk/core/orders/FortifyOrder.h"

namespace risk {
	FortifyOrder::FortifyOrder(
		int playerID,
		TerritoryID fromTerritory,
		TerritoryID toTerritory,
		int fortifyTroopCount)
		: Order(playerID, OrderType::Fortify),
		fromTerritory(fromTerritory),
		toTerritory(toTerritory),
		fortifyTroopCount(fortifyTroopCount)
	{
	}

	TerritoryID FortifyOrder::getFromTerritory() const{

		return fromTerritory;
	}

	TerritoryID FortifyOrder::getToTerritory() const {

		return toTerritory;
	}

	int FortifyOrder::getFortifyTroopCount() const {

		return fortifyTroopCount;
	}
	
}