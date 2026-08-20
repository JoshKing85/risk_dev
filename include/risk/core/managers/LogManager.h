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

			void LogAttackOrders(const std::vector<AttackOrder>& attackOrders);
			void LogFortifyOrders(const std::vector<FortifyOrder>& fortiyOrders);
			void LogReinforceOrders(const std::vector<ReinforceOrder>& reinforceOrders);
			void LogMoveTroopsOrders(const std::vector<MoveTroopsOrder>& moveTroopsOrders);
	};
}