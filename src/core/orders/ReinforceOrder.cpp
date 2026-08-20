#include "risk/core/orders/ReinforceOrder.h"

namespace risk {
	ReinforceOrder::ReinforceOrder(
		int playerID, 
		TerritoryID territoryID,
		int reinforceTroopCount)
		: Order(playerID, OrderType::Reinforce),
		  territoryID(territoryID),
		  reinforceTroopCount(reinforceTroopCount)
	{
	}

	TerritoryID ReinforceOrder::getTerritoryID() const {
		return territoryID;
	}

	int ReinforceOrder::getReinforceTroopCount() const {
		return reinforceTroopCount;
	}
}