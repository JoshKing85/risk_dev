#pragma once

#include "risk/core/orders/Order.h"
#include "risk/enums.h"

namespace risk {

	class FortifyOrder : public Order {

		private:

			TerritoryID fromTerritory;
            TerritoryID toTerritory;
            int troopCount;

		public:
            FortifyOrder(
				int playerID,
				TerritoryID fromTerritory, 
				TerritoryID toTerritory,
                int fortifyTroopCount);

			TerritoryID getFromTerritory() const;
			TerritoryID getToTerritory() const;
			int getFortifyTroopCount() const;

			void updateFortifyOrder(bool add);




	};
}// namespace risk