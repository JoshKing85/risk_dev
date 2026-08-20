// Order.h
#pragma once

#include "risk/enums.h"

namespace risk {

class Order {
private:
  int playerID;
  OrderType orderType;
  bool completed = false;

public:
  Order(int playerID, OrderType orderType);
  virtual ~Order() = default;

  int getPlayerID() const;
  OrderType getOrderType() const;
  bool isCompleted() const;

  void complete();

protected:
  void markCompleted();
};

} // namespace risk