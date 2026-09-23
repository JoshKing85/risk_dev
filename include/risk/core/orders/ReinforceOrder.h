#pragma once

#include "risk/core/orders/Order.h"
#include "risk/enums.h"

namespace risk {

	class ReinforceOrder : public Order {

		private:
          TerritoryID territoryID;
          int reinforceTroopCount;

		public:

			ReinforceOrder(
				int playerID, 
				TerritoryID territoryID,
                int reinforceTroopCount);

			TerritoryID getTerritoryID() const;
            int getReinforceTroopCount() const;
			void setReinforceTroopCount(int reinforceTroopCount);
	};
}// namespace risk