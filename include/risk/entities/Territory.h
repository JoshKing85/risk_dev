#pragma once

#include "risk/enums.h"
#include <vector>

namespace risk {

class Territory {
private:
  TerritoryID territoryID;
  ContinentID continentID;
  std::vector<TerritoryID> adjacentTerritories;

  int troopCount;
  int ownerID;

public:
  Territory(TerritoryID id, ContinentID continent,
            const std::vector<TerritoryID> &adjacentIDs);

  TerritoryID getID() const;
  ContinentID getContinentID() const;
  const std::vector<TerritoryID> &getAdjacentTerritories() const;

  int getTroopCount() const;
  int getOwnerID() const;
  TerritoryID getTerritoryID() const;

  void setOwner(int newOwnerID);
  void addTroops(int amount);
  void removeTroops(int amount);
};
} // namespace risk