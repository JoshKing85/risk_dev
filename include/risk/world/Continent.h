#pragma once

#include "risk/enums.h"
#include <vector>

namespace risk {

class Continent {
private:
  ContinentID continentID;
  int controlBonus;

  std::vector<TerritoryID> territories;
  std::vector<TerritoryID> borderTerritories;

  int ownerID;

public:
  Continent(ContinentID id, int bonus,
            const std::vector<TerritoryID> &territories,
            const std::vector<TerritoryID> &borderTerritories);

  // Getters
  ContinentID getContinentID() const;
  int getControlBonus() const;
  const std::vector<TerritoryID> &getTerritories() const;
  const std::vector<TerritoryID> &getBorderTerritories() const;
  int getOwnerID() const;

  // Setter
  void setOwner(int newOwnerID);
};

} // namespace risk