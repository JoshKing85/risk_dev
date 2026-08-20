#pragma once

#include "risk/enums.h"
#include "risk/entities/Player.h"
#include <unordered_map>
#include <string>

namespace risk {
struct Personality {

  
};

struct AISelfProfile {
    PlayerID player;

    float aggression; // 0.0 - 1.0
    float risk;       // 0.0 - 1.0
    float loyalty;    // 0.0 - 1.0
    float greed;      // 0.0 - 1.0
    float pettiness;  // 0.0 - 1.0
    float analytical; // 0.0 - 1.0
    float shrewdness; // 0.0 - 1.0
};

struct PlayerProfile {
    PlayerID player;

    PlayStyle playstyle;
    ThreatLevel threatLevel;
    RiskPlayerType riskType;
};

struct PlayerModel {
    PlayerID player;

    bool weakerThanMe;
    bool strongerThanMe;
    float averageTroopsPerTerritory;
    float futureStrength;

    bool weakBordersVsSelf;
    bool weakBordersVsNeighbours;
    bool weakBordersVsAllies;
    bool weakBordersVsEnemies;

    bool weakAgainstNeighbours;
    bool weakAgainstAllies;
    bool weakAgainstEnemies;

    float futureNeighbourStrength;
    float futureEnemyStrength;

    bool isTurtling;
    bool isHorde;
    bool isStacking;
    bool isExpanding;
    bool isBoardPolice;

    float goalOrientation;
    GoalPrediction goalPrediction;

    int numberOfCards;

    bool isExplicitAlly;
    float implicitAllyProbability;
    float implicitEnemyProbability;
};

struct AIPlayerState {
    PlayerID player;

    int totalTroops;
    int territoryCount;
    float averageTroopsPerTerritory;

    int borderTerritoryCount;
    bool isOverextended;
    bool hasStrongDefense;

    float troopGrowthRate;
    float territoryGrowthRate;

    bool isLeading;
    bool isWeakest;

    bool vulnerableToAttack;
    bool canAttackEffectively;

    int numberOfCards;
    bool hasSet;
    SetType setType;

    GoalPrediction currentGoal; 
    float likelyGoalAttainment;
};

class AIPlayer : public Player {
private:
    std::unordered_map<PlayerID, PlayerModel> playermodel;
    std::unordered_map<PlayerID, PlayerProfile> playerProfiles;

    AISelfProfile selfProfile;
    AIPlayerState selfState;

public:
    AIPlayer(const std::string& name);

    void updatePlayerStates();
    void updatePlayerProfiles();
    void updateSelfState();
    //void updateAISelfProfile();

    /*const AIPlayerState& getSelfState() const;
    const AISelfProfile& getSelfProfile() const;*/

  /*  const std::unordered_map<PlayerID, PlayerModel>& getPlayerModels() const;
    const std::unordered_map<PlayerID, PlayerProfile>& getPlayerProfiles() const;*/
};

}