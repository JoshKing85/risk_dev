#include "risk/core/orders/FortifyOrder.h"

namespace risk {
	FortifyOrder::FortifyOrder(
		int playerID,
		TerritoryID fromTerritory,
		TerritoryID toTerritory,
		int troopCount)
		: Order(playerID, OrderType::Fortify),
		fromTerritory(fromTerritory),
		toTerritory(toTerritory),
		troopCount(troopCount)
	{
	}

	TerritoryID FortifyOrder::getFromTerritory() const{

		return fromTerritory;
	}

	TerritoryID FortifyOrder::getToTerritory() const {

		return toTerritory;
	}

	int FortifyOrder::getFortifyTroopCount() const {

		return troopCount;
	}

	void FortifyOrder::updateFortifyOrder(bool add)
	{
		if (add)
		{
			troopCount++;
		}
		else
		{
			troopCount--;
		}
	}
	
}