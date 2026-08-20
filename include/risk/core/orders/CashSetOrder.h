#pragma once

#include "risk/core/orders/Order.h"
#include "risk/entities/Card.h"
#include "risk/enums.h"

#include <vector>

namespace risk {

class CashSetOrder : public Order {
private:
  SetType setType;
  std::vector<Card> cards;
  int setValue = 0;

public:
  CashSetOrder(int playerID, SetType setType, std::vector<Card> cards);

  const std::vector<Card> &getCards() const;
  int getSetValue() const;


private:
 static int calculateSetValue(SetType setType);
};

} // namespace risk