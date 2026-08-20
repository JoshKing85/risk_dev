#include "risk/core/managers/AttackManager.h"
#include "risk/core/managers/GameStateManager.h"

#include "risk/core/orders/AttackOrder.h"
#include "risk/core/orders/MoveTroopsOrder.h"
#include "risk/core/orders/RollDiceOrder.h"

#include <algorithm>
#include <vector>

namespace risk {

    //=========================================================
    // Constructor
    //=========================================================

    AttackManager::AttackManager(
        int playerID,
        GameStateManager& gameStateManager
    )
        : playerID(playerID),
        gameStateManager(gameStateManager)
    {
    }

    //=========================================================
    // Attack order
    //=========================================================

    void AttackManager::createAttack(
        TerritoryID fromTerritory,
        TerritoryID toTerritory,
        int attackingTroopCount,
        int defendingTroopCount
    )
    {
        attackOrders.emplace_back(
            playerID,
            fromTerritory,
            toTerritory,
            attackingTroopCount,
            defendingTroopCount
        );
    }

    void AttackManager::undoAttack()
    {
        if (!attackOrders.empty())
        {
            attackOrders.pop_back();
        }
    }

    //=========================================================
    // Dice-roll order
    //=========================================================

    void AttackManager::createRollDiceOrder(
        int attackDiceCount
    )
    {
        AttackOrder& currentAttack =
            attackOrders.back();

        const int defendDiceCount =
            (currentAttack.getDefendingTroopCount() >= 2)
            ? 2
            : 1;

        rollDiceOrders.emplace_back(
            playerID,
            attackDiceCount,
            defendDiceCount
        );
    }

    void AttackManager::createRollDiceOrder(
        const std::vector<int>& attackingDice,
        const std::vector<int>& defendingDice
    )
    {
        rollDiceOrders.emplace_back(
            playerID,
            attackingDice,
            defendingDice
        );
    }

    void AttackManager::undoRollDiceOrder()
    {
        if (!rollDiceOrders.empty())
        {
            rollDiceOrders.pop_back();
        }
    }

    //=========================================================
    // Attack execution
    //=========================================================

    void AttackManager::executeAttackOrder()
    {
        AttackOrder& currentAttack =
            attackOrders.back();

        const RollDiceOrder& currentRoll =
            rollDiceOrders.back();

        resolveAttack(
            currentAttack,
            currentRoll
        );
    }

    void AttackManager::resolveAttack(
        AttackOrder& currentAttack,
        const RollDiceOrder& currentRoll
    )
    {
        const int attackingTroopCount =
            currentAttack.getAttackingTroopCount();

        const int defendingTroopCount =
            currentAttack.getDefendingTroopCount();

        const std::vector<int>& attackingDice =
            currentRoll.getAttackingDice();

        const std::vector<int>& defendingDice =
            currentRoll.getDefendingDice();

        int attackLosses = 0;
        int defendLosses = 0;

        //-----------------------------------------------------
        // Compare dice
        //-----------------------------------------------------

        const std::size_t diceComparisons =
            std::min(
                attackingDice.size(),
                defendingDice.size()
            );

        for (std::size_t i = 0;
            i < diceComparisons;
            ++i)
        {
            if (attackingDice[i] > defendingDice[i])
            {
                ++defendLosses;
            }
            else
            {
                ++attackLosses;
            }
        }

        //-----------------------------------------------------
        // Build attack result
        //-----------------------------------------------------

        AttackResult result;

        result.attackerLosses =
            attackLosses;

        result.defenderLosses =
            defendLosses;

        result.attackingTroopCount =
            attackingTroopCount - attackLosses;

        result.defendingTroopCount =
            defendingTroopCount - defendLosses;

        //-----------------------------------------------------
        // Determine outcome
        //-----------------------------------------------------

        if (result.defendingTroopCount == 0)
        {
            result.attackOutcome =
                AttackOutcome::Captured;
        }
        else if (
            result.attackerLosses >
            result.defenderLosses
            )
        {
            result.attackOutcome =
                AttackOutcome::DefenderGain;
        }
        else if (
            result.attackerLosses <
            result.defenderLosses
            )
        {
            result.attackOutcome =
                AttackOutcome::AttackerGain;
        }
        else
        {
            result.attackOutcome =
                AttackOutcome::Draw;
        }

        //-----------------------------------------------------
        // Complete attack
        //-----------------------------------------------------

        currentAttack.setResult(result);

        //-----------------------------------------------------
        // Apply troop losses
        //-----------------------------------------------------

        if (defendLosses > 0)
        {
            int defenderID =
                gameStateManager.getTerritoryOwnerID(
                    currentAttack.getAttackingTo()
                );

            gameStateManager.updateTerritoryTroopCount(
                currentAttack.getAttackingTo(),
                -defendLosses
            );

            gameStateManager.updatePlayerTroopCount(
                defenderID,
                -defendLosses
            );
        }

        if (attackLosses > 0)
        {
            gameStateManager.updateTerritoryTroopCount(
                currentAttack.getAttackingFrom(),
                -attackLosses
            );

            gameStateManager.updatePlayerTroopCount(
                playerID,
                -attackLosses
            );
        }

        //-----------------------------------------------------
        // Capture territory
        //-----------------------------------------------------

        if (
            result.attackOutcome ==
            AttackOutcome::Captured
            )
        {
            gameStateManager.updateTerritoryOwner(
                currentAttack.getAttackingTo(),
                playerID
            );
        }
    }

    //=========================================================
    // Post-capture troop movement
    //=========================================================

    void AttackManager::createMoveTroopsOrder(
        TerritoryID fromTerritory,
        TerritoryID toTerritory,
        int moveTroopCount
    )
    {
        moveTroopsOrders.emplace_back(
            playerID,
            fromTerritory,
            toTerritory,
            moveTroopCount
        );
    }

    void AttackManager::undoMoveTroopsOrder()
    {
        if (!moveTroopsOrders.empty())
        {
            moveTroopsOrders.pop_back();
        }
    }

    void AttackManager::executeMoveTroopsOrder()
    {
        const MoveTroopsOrder& currentMove =
            moveTroopsOrders.back();

        gameStateManager.updateTerritoryTroopCount(
            currentMove.getFromTerritory(),
            -currentMove.getTroopsMoved()
        );

        gameStateManager.updateTerritoryTroopCount(
            currentMove.getToTerritory(),
            currentMove.getTroopsMoved()
        );
    }

    //=========================================================
    // Getters
    //=========================================================

    const AttackOrder&
        AttackManager::getLastAttackOrder() const
    {
        return attackOrders.back();
    }

    const RollDiceOrder&
        AttackManager::getLastRollDiceOrder() const
    {
        return rollDiceOrders.back();
    }

    const MoveTroopsOrder&
        AttackManager::getLastMoveTroopsOrder() const
    {
        return moveTroopsOrders.back();
    }

    const std::vector<AttackOrder>&
        AttackManager::getAttackOrders() const
    {
        return attackOrders;
    }

    const std::vector<RollDiceOrder>&
        AttackManager::getRollDiceOrders() const
    {
        return rollDiceOrders;
    }

    const std::vector<MoveTroopsOrder>&
        AttackManager::getMoveTroopsOrders() const
    {
        return moveTroopsOrders;
    }

} // namespace risk