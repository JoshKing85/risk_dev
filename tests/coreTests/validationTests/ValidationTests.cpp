#include <gtest/gtest.h>

#include "risk/core/validation/ValidateTerritorySelection.h"
#include "risk/core/validation/ValidateAttackInput.h"
#include "risk/core/validation/ValidateDiceInput.h"
#include "risk/core/validation/ValidateReinforceInput.h"
#include "risk/core/validation/ValidateSetInput.h"
#include "risk/core/validation/ValidateFortifyInput.h"

#include "risk/entities/Card.h"
#include "risk/entities/Territory.h"
#include "risk/world/Map.h"



#include "risk/enums.h"

#include <vector>

using namespace risk;

// --------------------------------------------------
// Territory Selection Validation Tests
// --------------------------------------------------

TEST(ValidationTests, TerritorySelectionReturnsTrueWhenTerritoryIsOwned)
{
    const std::vector<TerritoryID> territoriesOwned = {
        TerritoryID::Bearus,
        TerritoryID::Rockies,
        TerritoryID::Tairono
    };

    EXPECT_TRUE(
        isValidTerritorySelection(
            TerritoryID::Rockies,
            territoriesOwned
        )
    );
}

TEST(ValidationTests, TerritorySelectionReturnsFalseWhenTerritoryIsNotOwned)
{
    const std::vector<TerritoryID> territoriesOwned = {
        TerritoryID::Bearus,
        TerritoryID::Rockies,
        TerritoryID::Tairono
    };

    EXPECT_FALSE(
        isValidTerritorySelection(
            TerritoryID::Amazonia,
            territoriesOwned
        )
    );
}

TEST(ValidationTests, TerritorySelectionReturnsFalseWhenOwnedTerritoriesIsEmpty)
{
    const std::vector<TerritoryID> territoriesOwned;

    EXPECT_FALSE(
        isValidTerritorySelection(
            TerritoryID::Bearus,
            territoriesOwned
        )
    );
}

TEST(ValidationTests, TerritorySelectionFindsTerritoryLaterInVector)
{
    const std::vector<TerritoryID> territoriesOwned = {
        TerritoryID::Bearus,
        TerritoryID::Rockies,
        TerritoryID::Tairono
    };

    EXPECT_TRUE(
        isValidTerritorySelection(
            TerritoryID::Tairono,
            territoriesOwned
        )
    );
}

// --------------------------------------------------
// Attack Input Validation Tests
// --------------------------------------------------

TEST(ValidationTests, AttackInputReturnsTrueWhenTargetIsAdjacentAndEnoughTroops)
{
    const std::vector<TerritoryID> adjacentTerritories = {
        TerritoryID::Rockies,
        TerritoryID::Yukon
    };

    EXPECT_TRUE(
        isValidAttackInput(
            TerritoryID::Rockies,
            adjacentTerritories,
            3
        )
    );
}

TEST(ValidationTests, AttackInputReturnsTrueWithMinimumTwoTroops)
{
    const std::vector<TerritoryID> adjacentTerritories = {
        TerritoryID::Rockies
    };

    EXPECT_TRUE(
        isValidAttackInput(
            TerritoryID::Rockies,
            adjacentTerritories,
            2
        )
    );
}

TEST(ValidationTests, AttackInputReturnsFalseWhenOnlyOneTroopAvailable)
{
    const std::vector<TerritoryID> adjacentTerritories = {
        TerritoryID::Rockies
    };

    EXPECT_FALSE(
        isValidAttackInput(
            TerritoryID::Rockies,
            adjacentTerritories,
            1
        )
    );
}

TEST(ValidationTests, AttackInputReturnsFalseWhenTargetIsNotAdjacent)
{
    const std::vector<TerritoryID> adjacentTerritories = {
        TerritoryID::Rockies,
        TerritoryID::Yukon
    };

    EXPECT_FALSE(
        isValidAttackInput(
            TerritoryID::Amazonia,
            adjacentTerritories,
            5
        )
    );
}

TEST(ValidationTests, AttackInputReturnsFalseWhenAdjacentTerritoriesIsEmpty)
{
    const std::vector<TerritoryID> adjacentTerritories;

    EXPECT_FALSE(
        isValidAttackInput(
            TerritoryID::Rockies,
            adjacentTerritories,
            5
        )
    );
}

TEST(ValidationTests, AttackInputFindsTargetLaterInAdjacentVector)
{
    const std::vector<TerritoryID> adjacentTerritories = {
        TerritoryID::Rockies,
        TerritoryID::Yukon,
        TerritoryID::EasternPeninsula
    };

    EXPECT_TRUE(
        isValidAttackInput(
            TerritoryID::EasternPeninsula,
            adjacentTerritories,
            5
        )
    );
}

// --------------------------------------------------
// Dice Input Validation Tests
// --------------------------------------------------

TEST(ValidationTests, DiceInputAllowsOneDieWithTwoTroops)
{
    EXPECT_TRUE(
        isValidDiceInput(
            1,
            2
        )
    );
}

TEST(ValidationTests, DiceInputAllowsTwoDiceWithThreeTroops)
{
    EXPECT_TRUE(
        isValidDiceInput(
            2,
            3
        )
    );
}

TEST(ValidationTests, DiceInputAllowsThreeDiceWithFourTroops)
{
    EXPECT_TRUE(
        isValidDiceInput(
            3,
            4
        )
    );
}

TEST(ValidationTests, DiceInputReturnsFalseWhenTooManyDiceForTroops)
{
    EXPECT_FALSE(
        isValidDiceInput(
            3,
            3
        )
    );
}

TEST(ValidationTests, DiceInputReturnsFalseForZeroDice)
{
    EXPECT_FALSE(
        isValidDiceInput(
            0,
            5
        )
    );
}

TEST(ValidationTests, DiceInputReturnsFalseForNegativeDice)
{
    EXPECT_FALSE(
        isValidDiceInput(
            -1,
            5
        )
    );
}

TEST(ValidationTests, DiceInputReturnsFalseForMoreThanThreeDice)
{
    EXPECT_FALSE(
        isValidDiceInput(
            4,
            10
        )
    );
}

// --------------------------------------------------
// Reinforce Input Validation Tests
// --------------------------------------------------

TEST(ValidationTests, ReinforceInputReturnsTrueWhenReinforcingWithinTroopPool)
{
    EXPECT_TRUE(
        isReinforceValid(
            3,
            5
        )
    );
}

TEST(ValidationTests, ReinforceInputReturnsTrueWhenUsingEntireTroopPool)
{
    EXPECT_TRUE(
        isReinforceValid(
            5,
            5
        )
    );
}

TEST(ValidationTests, ReinforceInputReturnsFalseWhenExceedingTroopPool)
{
    EXPECT_FALSE(
        isReinforceValid(
            6,
            5
        )
    );
}

TEST(ValidationTests, ReinforceInputReturnsFalseForZeroTroops)
{
    EXPECT_FALSE(
        isReinforceValid(
            0,
            5
        )
    );
}

TEST(ValidationTests, ReinforceInputReturnsFalseForNegativeTroops)
{
    EXPECT_FALSE(
        isReinforceValid(
            -1,
            5
        )
    );
}
// --------------------------------------------------
// Set Validation Tests
// --------------------------------------------------

TEST(ValidationTests, SetReturnsTrueForThreeInfantryCards)
{
    const std::vector<Card> cards = {
        Card(CardType::Infantry),
        Card(CardType::Infantry),
        Card(CardType::Infantry)
    };

    EXPECT_TRUE(
        isValidSet(cards)
    );
}

TEST(ValidationTests, SetReturnsTrueForThreeCavalryCards)
{
    const std::vector<Card> cards = {
        Card(CardType::Cavalry),
        Card(CardType::Cavalry),
        Card(CardType::Cavalry)
    };

    EXPECT_TRUE(
        isValidSet(cards)
    );
}

TEST(ValidationTests, SetReturnsTrueForThreeArtilleryCards)
{
    const std::vector<Card> cards = {
        Card(CardType::Artillery),
        Card(CardType::Artillery),
        Card(CardType::Artillery)
    };

    EXPECT_TRUE(
        isValidSet(cards)
    );
}

TEST(ValidationTests, SetReturnsTrueForMixedSet)
{
    const std::vector<Card> cards = {
        Card(CardType::Infantry),
        Card(CardType::Cavalry),
        Card(CardType::Artillery)
    };

    EXPECT_TRUE(
        isValidSet(cards)
    );
}

TEST(ValidationTests, SetReturnsTrueWhenSetContainsWild)
{
    const std::vector<Card> cards = {
        Card(CardType::Infantry),
        Card(CardType::Infantry),
        Card(CardType::Wild)
    };

    EXPECT_TRUE(
        isValidSet(cards)
    );
}

TEST(ValidationTests, SetReturnsFalseForInvalidCombination)
{
    const std::vector<Card> cards = {
        Card(CardType::Infantry),
        Card(CardType::Infantry),
        Card(CardType::Cavalry)
    };

    EXPECT_FALSE(
        isValidSet(cards)
    );
}

TEST(ValidationTests, SetReturnsFalseWithFewerThanThreeCards)
{
    const std::vector<Card> cards = {
        Card(CardType::Infantry),
        Card(CardType::Infantry)
    };

    EXPECT_FALSE(
        isValidSet(cards)
    );
}

TEST(ValidationTests, SetReturnsFalseWithMoreThanThreeCards)
{
    const std::vector<Card> cards = {
        Card(CardType::Infantry),
        Card(CardType::Infantry),
        Card(CardType::Infantry),
        Card(CardType::Infantry)
    };

    EXPECT_FALSE(
        isValidSet(cards)
    );
}
// --------------------------------------------------
// Fortify Validation Tests
// --------------------------------------------------

TEST(ValidationTests, FortifyReturnsTrueForDirectOwnedConnection)
{
    Map map;

    Territory alaska(
        TerritoryID::Bearus,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Rockies
        }
    );

    Territory alberta(
        TerritoryID::Rockies,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Bearus
        }
    );

    alaska.setOwner(0);
    alberta.setOwner(0);

    map.addTerritory(alaska);
    map.addTerritory(alberta);

    EXPECT_TRUE(
        isFortifyValid(
            map,
            TerritoryID::Bearus,
            TerritoryID::Rockies,
            0
        )
    );
}

TEST(ValidationTests, FortifyReturnsTrueForIndirectOwnedPath)
{
    Map map;

    Territory alaska(
        TerritoryID::Bearus,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Rockies
        }
    );

    Territory alberta(
        TerritoryID::Rockies,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Bearus,
            TerritoryID::Tairono
        }
    );

    Territory ontario(
        TerritoryID::Tairono,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Rockies
        }
    );

    alaska.setOwner(0);
    alberta.setOwner(0);
    ontario.setOwner(0);

    map.addTerritory(alaska);
    map.addTerritory(alberta);
    map.addTerritory(ontario);

    EXPECT_TRUE(
        isFortifyValid(
            map,
            TerritoryID::Bearus,
            TerritoryID::Tairono,
            0
        )
    );
}

TEST(ValidationTests, FortifyReturnsFalseWhenEnemyTerritoryBlocksPath)
{
    Map map;

    Territory alaska(
        TerritoryID::Bearus,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Rockies
        }
    );

    Territory alberta(
        TerritoryID::Rockies,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Bearus,
            TerritoryID::Tairono
        }
    );

    Territory ontario(
        TerritoryID::Tairono,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Rockies
        }
    );

    alaska.setOwner(0);
    alberta.setOwner(1);
    ontario.setOwner(0);

    map.addTerritory(alaska);
    map.addTerritory(alberta);
    map.addTerritory(ontario);

    EXPECT_FALSE(
        isFortifyValid(
            map,
            TerritoryID::Bearus,
            TerritoryID::Tairono,
            0
        )
    );
}

TEST(ValidationTests, FortifyReturnsFalseWhenDestinationIsEnemyOwned)
{
    Map map;

    Territory alaska(
        TerritoryID::Bearus,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Rockies
        }
    );

    Territory alberta(
        TerritoryID::Rockies,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Bearus
        }
    );

    alaska.setOwner(0);
    alberta.setOwner(1);

    map.addTerritory(alaska);
    map.addTerritory(alberta);

    EXPECT_FALSE(
        isFortifyValid(
            map,
            TerritoryID::Bearus,
            TerritoryID::Rockies,
            0
        )
    );
}

TEST(ValidationTests, FortifyReturnsFalseWhenNoPathExists)
{
    Map map;

    Territory alaska(
        TerritoryID::Bearus,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Rockies
        }
    );

    Territory alberta(
        TerritoryID::Rockies,
        ContinentID::NorthAmerica,
        {
            TerritoryID::Bearus
        }
    );

    Territory ontario(
        TerritoryID::Tairono,
        ContinentID::NorthAmerica,
        {}
    );

    alaska.setOwner(0);
    alberta.setOwner(0);
    ontario.setOwner(0);

    map.addTerritory(alaska);
    map.addTerritory(alberta);
    map.addTerritory(ontario);

    EXPECT_FALSE(
        isFortifyValid(
            map,
            TerritoryID::Bearus,
            TerritoryID::Tairono,
            0
        )
    );
}