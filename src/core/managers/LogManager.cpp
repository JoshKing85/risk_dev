#include "risk/core/managers/LogManager.h"

#include "risk/core/orders/AttackOrder.h"
#include "risk/core/orders/FortifyOrder.h"
#include "risk/core/orders/ReinforceOrder.h"
#include "risk/core/orders/MoveTroopsOrder.h"

namespace risk {
	LogManager::LogManager(int playerID) : playerID(playerID) {}

	void LogManager::logAttackOrders(const std::vector<AttackOrder>& attackOrders) {
		for (const auto& order : attackOrders) {
			// Log the attack order details
			// Example: std::cout << "Player " << playerID << " attacks from " << order.getSourceTerritory() << " to " << order.getTargetTerritory() << std::endl;
		}
	}
	void LogManager::logFortifyOrders(const std::vector<FortifyOrder>& fortifyOrders) {
		for (const auto& order : fortifyOrders) {
			// Log the fortify order details
			// Example: std::cout << "Player " << playerID << " fortifies from " << order.getSourceTerritory() << " to " << order.getTargetTerritory() << std::endl;
		}
	}
	void LogManager::logReinforceOrders(const std::vector<ReinforceOrder>& reinforceOrders) {
		for (const auto& order : reinforceOrders) {
			// Log the reinforce order details
			// Example: std::cout << "Player " << playerID << " reinforces territory " << order.getTerritory() << " with " << order.getTroopCount() << " troops" << std::endl;
		}
	}
	void LogManager::logMoveTroopsOrders(const std::vector<MoveTroopsOrder>& moveTroopsOrders) {
		for (const auto& order : moveTroopsOrders) {
			// Log the move troops order details
			// Example: std::cout << "Player " << playerID << " moves troops from " << order.getSourceTerritory() << " to " << order.getTargetTerritory() << std::endl;
		}
	}
} // namespace risk