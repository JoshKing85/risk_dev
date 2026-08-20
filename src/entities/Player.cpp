#include "risk/entities/Player.h"
#include <vector>
#include <algorithm>

namespace risk {

	// Constructor
	// Constructor
	Player::Player(
		PlayerID playerID
	)
		: playerID(playerID),
		troopCount(0)
	{
	}

	// --- Getters ---
	PlayerID Player::getPlayerID() const {
		return playerID;
	}

	std::string Player::getPlayerName()const {
		return playerName;
	}

	int Player::getTroopCount()const {

		return troopCount;
	}

	const std::vector<Card>& Player::getPlayerSet() const {
		return currentSet;
	}

	const std::vector<TerritoryID>& Player::getTerritoriesHeld() const {
		return territoriesHeld;
	}
	const std::vector<PlayerID>& Player::getAllies() const {
		return allies;
	}
	const std::vector<ContinentID>& Player::getContinentsOwned() const {
		return continentsOwned;
	}


	// --- Troop management ---
	void Player::addTroops(int amount) {
		troopCount += amount;
	}

	void Player::removeTroops(int amount) {
		troopCount = std::max(0, troopCount - amount);
	}

	// --- Card management ---
	void Player::setPlayerSet(const std::vector<Card>& newSet) {
		currentSet = newSet;
	}
	// --- Player Management ---
	void Player::setPlayerName(const std::string& name) {
		playerName = name;
	}

	// --- Territory management ---
	void Player::addTerritory(TerritoryID territory) {
		if (std::find(territoriesHeld.begin(), territoriesHeld.end(), territory) == territoriesHeld.end()) {
			territoriesHeld.push_back(territory);
		}
	}
	
	void Player::removeTerritory(TerritoryID territory) {
		territoriesHeld.erase(
			std::remove(territoriesHeld.begin(), territoriesHeld.end(), territory),
			territoriesHeld.end()
		);
	}
	// --- Continent management ---
	
	void Player::addContinent(ContinentID continent) {
		if (std::find(continentsOwned.begin(), continentsOwned.end(), continent) == continentsOwned.end()) {
			continentsOwned.push_back(continent);
		}
	}
	void Player::removeContinent(ContinentID continent) {
		continentsOwned.erase(
			std::remove(continentsOwned.begin(), continentsOwned.end(), continent),
			continentsOwned.end()
		);
	}
	// --- Alliance management ---
	void Player::addAlly(PlayerID allyID) {
		if (allyID == playerID) return;

		if (std::find(allies.begin(), allies.end(), allyID) == allies.end()) {
			allies.push_back(allyID);
		}
	}

	void Player::removeAlly(PlayerID allyID) {
		allies.erase(
			std::remove(allies.begin(), allies.end(), allyID),
			allies.end()
		);
	}

}