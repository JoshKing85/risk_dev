#pragma once

#include "risk/enums.h"

#include <optional>

namespace risk {
class Card {
private:
  CardType cardType;
  std::optional<TerritoryID> territoryID;
  std::optional<ContinentID> continentID;

public:
  Card(CardType cardType,
       std::optional<TerritoryID> territoryID = std::nullopt,
       std::optional<ContinentID> continentID = std::nullopt
  );

  CardType getCardType() const;

  bool hasTerritory() const;


  std::optional<TerritoryID> getTerritoryID() const;
  std::optional<ContinentID> getContinentID() const;
};
} // namespace risk