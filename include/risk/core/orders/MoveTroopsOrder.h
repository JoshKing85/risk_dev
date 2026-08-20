#pragma once

#include "risk/core/orders/Order.h"
#include "risk/enums.h"

namespace risk {

class MoveTroopsOrder : public Order {

private:
  TerritoryID fromTerritory;
  TerritoryID toTerritory;
  int troopsMoved;

public:
  MoveTroopsOrder(int playerID, TerritoryID fromTerritory,
                  TerritoryID toTerritory, int troopsMoved);

  TerritoryID getFromTerritory() const;
  TerritoryID getToTerritory() const;
  int getTroopsMoved() const;
};

} // namespace risk