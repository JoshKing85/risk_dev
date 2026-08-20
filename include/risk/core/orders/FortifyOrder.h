#pragma once

#include "risk/core/orders/Order.h"
#include "risk/enums.h"

namespace risk {

	class FortifyOrder : public Order {

		private:

			TerritoryID fromTerritory;
            TerritoryID toTerritory;
            int fortifyTroopCount;

		public:
            FortifyOrder(
				int playerID,
				TerritoryID fromTerritory, 
				TerritoryID toTerritory,
                int fortifyTroopCount);

			TerritoryID getFromTerritory() const;
			TerritoryID getToTerritory() const;
			int getFortifyTroopCount() const;




	};
}// namespace risk