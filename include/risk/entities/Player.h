#pragma once
#include <vector>
#include <string>
#include "risk/enums.h"
#include "risk/entities/Card.h"

namespace risk {

using PlayerID = int;

class Player {

private:
    static PlayerID nextID;

    PlayerID playerID;
    std::string playerName;
    int troopCount;

    std::vector<Card> currentSet;
    std::vector<TerritoryID> territoriesHeld;
    std::vector<ContinentID> continentsOwned;
    std::vector<PlayerID> allies;

public:
    // Constructor
    Player(PlayerID playerID);

    // --- Getters ---
    PlayerID getPlayerID() const;
    std::string getPlayerName() const;
    int getTroopCount() const;

    const std::vector<Card>& getPlayerSet() const;
    const std::vector<TerritoryID>& getTerritoriesHeld() const;
    const std::vector<ContinentID> &getContinentsOwned() const;
    const std::vector<PlayerID>& getAllies() const;

    // --- Troop management ---
    void addTroops(int amount);
    void removeTroops(int amount);

    // --- Player Management ---
    void setPlayerName(const std::string& name);

    // --- Card management ---
    void setPlayerSet(const std::vector<Card>& newSet);

    // --- Territory management ---
    void addTerritory(TerritoryID territory);
    void removeTerritory(TerritoryID territory);

    // --- Continent management ---
    void addContinent(ContinentID continent);
    void removeContinent(ContinentID continent);

    // --- Alliance management ---
    void addAlly(PlayerID allyID);
    void removeAlly(PlayerID allyID);
};

}