#pragma once
#include "risk/core/orders/CashSetOrder.h"
#include "risk/core/orders/FortifyOrder.h"
#include "risk/core/orders/ReinforceOrder.h"

#include <vector>

namespace risk {

	class GameStateManager;
	class Player;
	class TroopManager {

		int playerID;
		GameStateManager& gameStateManager;
		Player& player;
		std::vector<ReinforceOrder> reinforceOrders;
		std::vector<FortifyOrder> fortifyOrders;
		std::vector<CashSetOrder> cashSetOrders;

		public:
		
			TroopManager(int playerID, GameStateManager& gameStateManager, Player& player);

			// calculate additional reinforcements
			int calculateReinforcements(int playerID);

			// create orders
			void createReinforceOrder(TerritoryID territoryID, int reinforceTroopCount);
			void createFortifyOrder(TerritoryID fromTerritory, TerritoryID toTerritory, int fortifyTroopCount);
			void createCashSetOrder(SetType setType, std::vector<Card> cards);

			// execute orders
			void executeReinforceOrder();
			void executeFortifyOrder();
			int executeCashSetOrder();

			// undo orders
			void undoReinforceOrder();
			void undoFortifyOrder();
			void undoCashSetOrder();

			// getters
			const std::vector<ReinforceOrder>& getReinforceOrders() const;
			const std::vector<FortifyOrder>& getFortifyOrders() const;
			const std::vector<CashSetOrder>& getCashSetOrders() const;

			const ReinforceOrder &getLastReinforceOrder() const;
			const FortifyOrder &getLastFortifyOrder() const;
			const CashSetOrder &getLastCashSetOrder() const;


        };
}