#pragma once

#include "risk/enums.h"
#include "risk/world/Map.h"

#include <vector>

namespace risk {

class Player;
class Territory;
class Card;

class GameStateManager {
		private:
			Map &map;
			std::vector<Player> &players;

		public:// change later just player
			GameStateManager(Map &map, std::vector<Player> &players);

			// Territory methods
			void updateTerritoryOwner(TerritoryID territoryID, int newOwnerID);
			void updateTerritoryTroopCount(TerritoryID territoryID, int newTroopCount);


			// Continent methods
			void updateContinentOwner(ContinentID continentID, int newOwnerID);
			ContinentID checkContinentOwnership(int playerID, ContinentID continentID);


			// Player methods
			void updatePlayerTerritories(int playerID, const Territory &territory, bool gainTerritory);
			void updatePlayerContinentOwnership(int playerID, ContinentID continentID, bool gainOwnership);
			void updatePlayerTroopCount(int playerID, int newTroopCount);
			void updatePlayerSet(int playerID, const std::vector<Card> &newSet);

			// Getter methods
			int getTerritoryOwnerID(TerritoryID territoryID) const;
	};

} // namespace risk