#include "risk/core/orders/MoveTroopsOrder.h"

namespace risk {

	MoveTroopsOrder::MoveTroopsOrder(int playerID, TerritoryID fromTerritory, TerritoryID toTerritory, int troopsMoved)
		: Order(playerID, OrderType::MoveTroops),
		fromTerritory(fromTerritory),
		toTerritory(toTerritory),
		troopsMoved(troopsMoved) {
	}

	TerritoryID MoveTroopsOrder::getFromTerritory() const {
		return fromTerritory;
	}

	TerritoryID MoveTroopsOrder::getToTerritory() const {
		return toTerritory;
	}

	int MoveTroopsOrder::getTroopsMoved() const {
		return troopsMoved;
	}
}