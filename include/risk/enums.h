#pragma once

namespace risk
{   
    // Enums for Continent and Territory IDs
    enum class ContinentID
    {
        NorthAmerica,
        SouthAmerica,
        Europe,
        Africa,
        Asia,
        Australia,
        None
    };

    enum class TerritoryID
    {
        // North America
        Alaska,
        Alberta,
        CentralAmerica,
        EasternUnitedStates,
        Greenland,
        NorthwestTerritory,
        Ontario,
        Quebec,
        WesternUnitedStates,

        // South America
        Argentina,
        Brazil,
        Peru,
        Venezuela,

        // Europe
        GreatBritain,
        Iceland,
        NorthernEurope,
        Scandinavia,
        SouthernEurope,
        Ukraine,
        WesternEurope,

        // Africa
        Congo,
        EastAfrica,
        Egypt,
        Madagascar,
        NorthAfrica,
        SouthAfrica,

        // Asia
        Afghanistan,
        China,
        India,
        Irkutsk,
        Japan,
        Kamchatka,
        MiddleEast,
        Mongolia,
        Siam,
        Siberia,
        Ural,
        Yakutsk,

        // Australia
        EasternAustralia,
        Indonesia,
        NewGuinea,
        WesternAustralia
    };
    // Enums for Card Types and Set Types
    enum class CardType
    {
        Infantry,
        Cavalry,
        Artillery,
        Wild
    };
    
    enum class SetType {
      InfantrySet,
      CavalrySet,
      ArtillerySet,
      MixedSet
    };
    // Enums for ai behavior and game state
    enum class PlayStyle {
    Unknown,
    Passive,
    Defensive,
    Aggressive,
    Opportunistic
    };

    enum class ThreatLevel {
    None,
    Low,
    Medium,
    High,
    Critical
    };
    
    enum class RiskPlayerType {
    None,

    // --- Weak / Poor Play ---
    Inexperienced,          // poor play
    MissesOpportunities,    // overly passive / low risk-taking

    // --- Neutral ---
    Steady,                 // consistent, predictable

    // --- Behavioural Risks ---
    DisadvantagedAttacker,  // attacks while weak
    Opportunistic,          // targets easy wins
    HighRiskHighReward,     // targets are high value but high risk
    Expansionist            // rapid growth leaves defensive vulnerabilities
    };

    enum class GoalPrediction{
    None
    };

    // Enums for actions and management
    enum class OrderType {
    Attack,
    Reinforce,
    Fortify,
    MoveTroops,
    CashSet,
    RollDice,
    EndTurn       
    };

    enum class AttackOutcome {
        None,
        Captured,
        AttackerGain,
        DefenderGain,
        Draw
    };


   
}



// namespace risk