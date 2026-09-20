#pragma once

#include "risk/enums.h"

#include <vector>

namespace risk {
class AttackOrder;
class FortifyOrder;
class ReinforceOrder;
class MoveTroopsOrder;

	class LogManager {
		
		private:

			int playerID;

		public:
			LogManager(int playerID);

			void logAttackOrders(const std::vector<AttackOrder>& attackOrders);
			void logFortifyOrders(const std::vector<FortifyOrder>& fortiyOrders);
			void logReinforceOrders(const std::vector<ReinforceOrder>& reinforceOrders);
			void logMoveTroopsOrders(const std::vector<MoveTroopsOrder>& moveTroopsOrders);
	};
}