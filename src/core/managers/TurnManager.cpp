// managers
#include "risk/core/managers/TurnManager.h"
#include "risk/core/managers/GameStateManager.h"
#include "risk/core/managers/TroopManager.h"
#include "risk/core/managers/AttackManager.h"
#include "risk/core/managers/LogManager.h"

// entities and world
#include "risk/entities/Player.h"
#include "risk/world/Map.h"
#include "risk/entities/Territory.h"
#include "risk/entities/Card.h"
#include "risk/world/Deck.h"

// orders
#include "risk/core/orders/ReinforceOrder.h"
#include "risk/core/orders/FortifyOrder.h"
#include "risk/core/orders/CashSetOrder.h"
#include "risk/core/orders/AttackOrder.h"
#include "risk/core/orders/RollDiceOrder.h"
#include "risk/core/orders/MoveTroopsOrder.h"

// validation
#include "risk/core/validation/ValidateAttackInput.h"
#include "risk/core/validation/ValidateFortifyInput.h"
#include "risk/core/validation/ValidateReinforceInput.h"
#include "risk/core/validation/ValidateSetInput.h"
#include "risk/core/validation/ValidateDiceInput.h"
#include "risk/core/validation/ValidateTerritorySelection.h"

// utilities
#include <vector>

namespace risk {

    //=========================================================
    // Constructor
    //=========================================================

    TurnManager::TurnManager(
        Player& currentPlayer,
        std::vector<Player>& players,
        Map& map,
        Deck& deck
    )
        : playerID(currentPlayer.getPlayerID()),
        currentPlayer(currentPlayer),
        map(map),
        deck(deck),
        gameStateManager(map, players),
        attackManager(playerID, gameStateManager),
        troopManager(
            playerID,
            gameStateManager,
            currentPlayer
        ),
        logManager(playerID)
    {
        runTurn();
    }

    //=========================================================
    // RUN TURN
    //=========================================================

    void TurnManager::runTurn()
    {
        reinforcePhase();
        attackPhase();
        fortifyPhase();
        logPhase();
    }

    //=========================================================
    // REINFORCE PHASE
    //=========================================================

    void TurnManager::reinforcePhase(
        bool calculateBaseReinforcements
    )
    {
        int reinforcementPool = 0;

        std::vector<Card> setToCash;
        SetType selectedSetType;

        bool phaseActive = true;

        //=====================================================
        // Normal reinforcement phase
        //=====================================================

        if (calculateBaseReinforcements)
        {
            reinforcementPool =
                currentPlayer.calculateReinforcements();

            // USER INPUT:
            // Player chooses whether they want to cash a card set.
            bool cashSetSelected = false;

            // cashSetSelected = ...

            if (cashSetSelected)
            {
                // USER SELECTION:
                // Selected cards are stored in setToCash.
                //
                // setToCash = ...

                // USER SELECTION:
                // Selected set type is stored in selectedSetType.
                //
                // selectedSetType = ...

                if (isSetValid(setToCash))
                {
                    troopManager.createCashSetOrder(
                        selectedSetType,
                        setToCash
                    );

                    // USER INPUT:
                    // Player may undo the CashSetOrder here
                    // before confirming execution.
                    //
                    // if (undoCashSetSelected)
                    // {
                    //     troopManager.undoCashSetOrder();
                    // }

                    const CashSetOrder& lastCashSetOrder =
                        troopManager.getLastCashSetOrder();

                    if (!lastCashSetOrder.isCompleted())
                    {
                        int additionalReinforcements =
                            troopManager.executeCashSetOrder();

                        reinforcementPool +=
                            additionalReinforcements;
                    }
                }
            }

            gameStateManager.updatePlayerTroopCount(
                playerID,
                reinforcementPool
            );
        }

        //=====================================================
        // Forced reinforcement during attack phase
        //=====================================================

        else
        {
            int playerSetSize =
                currentPlayer.getPlayerSet().size();

            while (playerSetSize >= 5)
            {
                // USER SELECTION:
                // Player must select a valid set of cards.
                //
                // setToCash = ...

                // USER SELECTION:
                // Selected set type.
                //
                // selectedSetType = ...

                if (isSetValid(setToCash))
                {
                    troopManager.createCashSetOrder(
                        selectedSetType,
                        setToCash
                    );

                    // USER INPUT:
                    // Player may undo the CashSetOrder here
                    // before confirming execution.
                    //
                    // if (undoCashSetSelected)
                    // {
                    //     troopManager.undoCashSetOrder();
                    //     continue;
                    // }

                    const CashSetOrder& lastCashSetOrder =
                        troopManager.getLastCashSetOrder();

                    if (!lastCashSetOrder.isCompleted())
                    {
                        int additionalReinforcements =
                            troopManager.executeCashSetOrder();

                        reinforcementPool +=
                            additionalReinforcements;

                        gameStateManager.updatePlayerTroopCount(
                            playerID,
                            additionalReinforcements
                        );
                    }
                }

                playerSetSize =
                    currentPlayer.getPlayerSet().size();
            }
        }

        //=====================================================
        // Reinforcement placement
        //=====================================================

        while (phaseActive)
        {
            // USER SELECTION:
            // Player selects one of their territories.
            TerritoryID territoryID;

            // territoryID = ...

            if (isValidTerritorySelection(
                territoryID,
                currentPlayer.getTerritories()))
            {
                // USER INPUT:
                // Player chooses how many troops to reinforce with.
                int reinforceTroopCount = 0;

                // reinforceTroopCount = ...

                if (isReinForceValid(
                    reinforceTroopCount,
                    reinforcementPool))
                {
                    troopManager.createReinforceOrder(
                        territoryID,
                        reinforceTroopCount
                    );

                    // USER INPUT:
                    // Player may undo the ReinforceOrder here
                    // before confirming execution.
                    //
                    // if (undoReinforceSelected)
                    // {
                    //     troopManager.undoReinforceOrder();
                    //     continue;
                    // }

                    const ReinforceOrder& lastReinforceOrder =
                        troopManager.getLastReinforceOrder();

                    if (!lastReinforceOrder.isCompleted())
                    {
                        troopManager.executeReinforceOrder();

                        reinforcementPool -=
                            reinforceTroopCount;
                    }
                }
            }

            // USER INPUT:
            // End Reinforcement Phase button.
            //
            // When selected:
            //
            // phaseActive = false;
        }
    }

    //=========================================================
    // ATTACK PHASE
    //=========================================================

    void TurnManager::attackPhase()
    {
        bool phaseActive = true;

        while (phaseActive)
        {
            //=================================================
            // Check player set size and force reinforcement
            //=================================================

            int setSize =
                currentPlayer.getSetSize();

            if (setSize >= 5)
            {
                reinforcePhase(false);
            }

            //=================================================
            // Select attacking territory
            //=================================================

            // USER SELECTION:
            // Player selects one of their territories to attack from.
            TerritoryID fromTerritory;

            // fromTerritory = ...

            if (isValidTerritorySelection(
                fromTerritory,
                currentPlayer.getTerritories()))
            {
                //=============================================
                // Select defending territory
                //=============================================

                // USER SELECTION:
                // Player selects an enemy territory to attack.
                TerritoryID toTerritory;

                // toTerritory = ...

                if (isValidAttackInput(
                    toTerritory,
                    map.getTerritory(fromTerritory)
                    .getAdjacentTerritories(),
                    map.getTerritory(fromTerritory)
                    .getTroopCount()))
                {
                    bool attackContinues = true;

                    //=========================================
                    // Repeated attack against selected target
                    //=========================================

                    while (attackContinues)
                    {
                        attackManager.createAttack(
                            fromTerritory,
                            toTerritory,
                            map.getTerritory(fromTerritory)
                            .getTroopCount() - 1,
                            map.getTerritory(toTerritory)
                            .getTroopCount()
                        );

                        // USER INPUT:
                        // Player may undo the AttackOrder here
                        // before continuing.
                        //
                        // if (undoAttackSelected)
                        // {
                        //     attackManager.undoAttack();
                        //     continue;
                        // }

                        //=====================================
                        // Dice selection
                        //=====================================

                        bool diceRolled = false;

                        while (!diceRolled)
                        {
                            // USER INPUT:
                            // Player chooses number of attacker dice.
                            int attackDiceCount;

                            // attackDiceCount = ...

                            if (isValidDiceInput(
                                attackDiceCount,
                                map.getTerritory(fromTerritory)
                                .getTroopCount()))
                            {
                                attackManager.createRollDiceOrder(
                                    attackDiceCount
                                );

                                // USER INPUT:
                                // Player may undo the RollDiceOrder here
                                // before confirming execution.
                                //
                                // if (undoDiceSelected)
                                // {
                                //     attackManager.undoRollDiceOrder();
                                //     continue;
                                // }

                                diceRolled = true;
                            }
                        }

                        //=====================================
                        // Execute attack
                        //=====================================

                        const AttackOrder& pendingAttackOrder =
                            attackManager.getLastAttackOrder();

                        const RollDiceOrder& pendingRollDiceOrder =
                            attackManager.getLastRollDiceOrder();

                        if (
                            !pendingAttackOrder.isCompleted() &&
                            !pendingRollDiceOrder.isCompleted()
                            )
                        {
                            attackManager.executeAttackOrder();
                        }

                        // GRAPHICS:
                        // Read getLastRollDiceOrder() and display
                        // the dice-roll animation.
                        //
                        // Then read getLastAttackOrder() and
                        // display troop-loss/capture animation.

                        const AttackOrder& lastAttack =
                            attackManager.getLastAttackOrder();

                        //=====================================
                        // Territory captured
                        //=====================================

                        if (
                            lastAttack.getResult().attackOutcome ==
                            AttackOutcome::Captured
                            )
                        {
                            const int minimumMoveTroops =
                                static_cast<int>(
                                    attackManager
                                    .getLastRollDiceOrder()
                                    .getAttackingDice()
                                    .size()
                                    );

                            const int maximumMoveTroops =
                                map.getTerritory(fromTerritory)
                                .getTroopCount() - 1;

                            bool movedTroops = false;

                            //=================================
                            // Player has movement choice
                            //=================================

                            if (
                                maximumMoveTroops >
                                minimumMoveTroops
                                )
                            {
                                while (!movedTroops)
                                {
                                    // USER INPUT:
                                    // Player chooses troop movement.
                                    int moveTroopCount;

                                    // moveTroopCount = ...

                                    if (
                                        moveTroopCount >=
                                        minimumMoveTroops
                                        &&
                                        moveTroopCount <=
                                        maximumMoveTroops
                                        )
                                    {
                                        attackManager
                                            .createMoveTroopsOrder(
                                                fromTerritory,
                                                toTerritory,
                                                moveTroopCount
                                            );

                                        // USER INPUT:
                                        // Player may undo the
                                        // MoveTroopsOrder here.
                                        //
                                        // if (undoMoveSelected)
                                        // {
                                        //     attackManager
                                        //         .undoMoveTroopsOrder();
                                        //
                                        //     continue;
                                        // }

                                        const MoveTroopsOrder&
                                            lastMoveTroopsOrder =
                                            attackManager
                                            .getLastMoveTroopsOrder();

                                        if (
                                            !lastMoveTroopsOrder
                                            .isCompleted()
                                            )
                                        {
                                            attackManager
                                                .executeMoveTroopsOrder();

                                            movedTroops = true;
                                        }
                                    }
                                }
                            }

                            //=================================
                            // Only minimum movement possible
                            //=================================

                            else
                            {
                                attackManager.createMoveTroopsOrder(
                                    fromTerritory,
                                    toTerritory,
                                    minimumMoveTroops
                                );

                                const MoveTroopsOrder&
                                    lastMoveTroopsOrder =
                                    attackManager
                                    .getLastMoveTroopsOrder();

                                if (
                                    !lastMoveTroopsOrder
                                    .isCompleted()
                                    )
                                {
                                    attackManager
                                        .executeMoveTroopsOrder();

                                    movedTroops = true;
                                }
                            }

                            // Captured territory ends this
                            // particular attack sequence.
                            attackContinues = false;
                        }

                        //=====================================
                        // Attack can no longer continue
                        //=====================================

                        else if (
                            map.getTerritory(fromTerritory)
                            .getTroopCount() < 2
                            )
                        {
                            attackContinues = false;
                        }

                        //=====================================
                        // Otherwise attackContinues remains true
                        //=====================================
                        //
                        // A new AttackOrder will automatically
                        // be created on the next iteration using
                        // the updated troop counts.
                    }
                }
            }

            //=================================================
            // End attack phase
            //=================================================

            // USER INPUT:
            // End Attack Phase button.
            //
            // if (endAttackPhaseSelected)
            // {
            //     phaseActive = false;
            // }
        }
    }

    //=========================================================
    // FORTIFY PHASE
    //=========================================================

    void TurnManager::fortifyPhase()
    {
        bool phaseActive = true;

        std::vector<TerritoryID> playerTerritories =
            currentPlayer.getTerritories();

        while (phaseActive)
        {
            //=================================================
            // Select territory to fortify from
            //=================================================

            // USER SELECTION:
            // Player selects one of their territories.
            TerritoryID fromTerritory;

            // fromTerritory = ...

            if (isValidTerritorySelection(
                fromTerritory,
                playerTerritories))
            {
                if (
                    map.getTerritory(fromTerritory)
                    .getTroopCount() > 1
                    )
                {
                    // USER INPUT:
                    // Player may cancel this selection here
                    // and continue to the next loop iteration.

                    //=========================================
                    // Select destination territory
                    //=========================================

                    // USER SELECTION:
                    // Player selects one of their territories.
                    TerritoryID toTerritory;

                    // toTerritory = ...

                    if (isValidTerritorySelection(
                        toTerritory,
                        playerTerritories))
                    {
                        //=====================================
                        // Check owned connectivity
                        //=====================================

                        if (isFortifyValid(
                            map,
                            fromTerritory,
                            toTerritory,
                            currentPlayer.getPlayerID()))
                        {
                            // USER INPUT:
                            // Player may cancel this selection
                            // and restart the phase.

                            //=================================
                            // Select troop count
                            //=================================

                            // USER INPUT:
                            // Player selects number of troops.
                            int troopCount;

                            // troopCount = ...

                            if (
                                troopCount > 0 &&
                                troopCount <
                                map.getTerritory(fromTerritory)
                                .getTroopCount()
                                )
                            {
                                troopManager.createFortifyOrder(
                                    fromTerritory,
                                    toTerritory,
                                    troopCount
                                );

                                // USER INPUT:
                                // Player may undo the FortifyOrder
                                // here before confirming execution.
                                //
                                // if (undoFortifySelected)
                                // {
                                //     troopManager
                                //         .undoFortifyOrder();
                                //
                                //     continue;
                                // }

                                const FortifyOrder&
                                    lastFortifyOrder =
                                    troopManager
                                    .getLastFortifyOrder();

                                if (
                                    !lastFortifyOrder
                                    .isCompleted()
                                    )
                                {
                                    troopManager
                                        .executeFortifyOrder();

                                    for (const AttackOrder& attackOrder :
                                        attackManager.getAttackOrders())
                                    {
                                        if (
                                            attackOrder.getResult().attackOutcome ==
                                            AttackOutcome::Captured
                                            )
                                        {
                                            Card newCard =
                                                deck.getNextCard();

                                            std::vector<Card> tempSet =
                                                currentPlayer.getPlayerSet();

                                            tempSet.emplace_back(newCard);

                                            gameStateManager.updatePlayerSet(
                                                playerID,
                                                tempSet
                                            );

                                            break;
                                        }
                                    }
                                    phaseActive = false;
                                }
                            }
                        }
                    }
                }
            }

            // USER INPUT:
            // End Fortify Phase button.
            //
            // if (endFortifyPhaseSelected)
            // {
            //     phaseActive = false;
            // }
        }
    }

    //=========================================================
    // LOG PHASE
    //=========================================================

    void TurnManager::logPhase()
    {
        logManager.logReinforceOrders(
            troopManager.getReinforceOrders()
        );

        logManager.logAttackOrders(
            attackManager.getAttackOrders()
        );

        logManager.logMoveTroopOrders(
            attackManager.getMoveTroopsOrders()
        );

        logManager.logFortifyOrders(
            troopManager.getFortifyOrders()
        );
    }

} // namespace risk