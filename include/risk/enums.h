#pragma once

namespace risk
{   // Enums for Map Types
    enum class MapType
    {
        Classic,
        Europe,
        None };

    // Enums for phase types
    enum class PhaseType 
    {
        Loading,
        Reinforce,
        Attack,
        Fortify,
        GameWon,
        GameQuit,
        GameSetup
    };
    // Enums for auxiliary phases
    enum class AuxiliaryPhase 
    { 
        None, 
        CashSet, 
        MoveTroops };

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

    // Enums for Territory IDs
    enum class TerritoryID {
     
        
        // North America
      Bearus,
      Rockies,
      Mexico,
      GreatLakes,
      ArcticIsle,
      Yukon,
      Tairono,
      StLawrence,
      California,

      // South America
      Patagonia,
      Amazonia,
      Andes,
      Orinoco,

      // Europe
      GreatBritain,
      Iceland,
      Germany,
      Scandinavia,
      Iberia,
      Russia,
      France,

      // Africa
      CentralBasin,
      Riftlands,
      Nilelands,
      LemurIsland,
      WestAfrica,
      CapeRegion,

      // Asia
      Highlands,
      China,
      Induslands,
      BaikalRegion,
      IslandEmpire,
      EasternPeninsula,
      ArabianRegion,
      GreatSteppe,
      Indochina,
      NorthernExpanse,
      UralRange,
      FarNortheast,

      // Australia
      NewSouthWales,
      Komodo,
      Philippines,
      WesternAustralia,

      None
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