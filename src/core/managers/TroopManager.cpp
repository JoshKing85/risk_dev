#include "risk/core/managers/TroopManager.h"
#include "risk/core/managers/GameStateManager.h"

#include "risk/core/orders/CashSetOrder.h"
#include "risk/core/orders/FortifyOrder.h"
#include "risk/core/orders/ReinforceOrder.h"

#include "risk/entities/Card.h"
#include "risk/entities/Player.h"
#include "risk/entities/Territory.h"

#include <algorithm>
#include <vector>

namespace risk {

    //=========================================================
    // Constructor
    //=========================================================

    // Stores the current player ID and references to the
    // persistent game-state manager and player.
    TroopManager::TroopManager(
        int playerID,
        GameStateManager& gameStateManager,
        Player& player
    )
        : playerID(playerID),
        gameStateManager(gameStateManager),
        player(player)
    {
    }

    //=========================================================
    // Order creation
    //=========================================================

    // Creates a pending reinforcement order.
    // Validation is handled by TurnManager before this point.
    void TroopManager::createReinforceOrder(
        TerritoryID territoryID,
        int reinforceTroopCount
    )
    {
        reinforceOrders.emplace_back(
            playerID,
            territoryID,
            reinforceTroopCount
        );
    }

    // Creates a pending fortification order.
    void TroopManager::createFortifyOrder(
        TerritoryID fromTerritory,
        TerritoryID toTerritory,
        int fortifyTroopCount
    )
    {
        fortifyOrders.emplace_back(
            playerID,
            fromTerritory,
            toTerritory,
            fortifyTroopCount
        );
    }

    // Creates a pending card-set cashing order.
    void TroopManager::createCashSetOrder(
        SetType setType,
        std::vector<Card> cards
    )
    {
        cashSetOrders.emplace_back(
            playerID,
            setType,
            cards
        );
    }

    //=========================================================
    // Reinforcement calculation
    //=========================================================

    int TroopManager::calculateReinforcements(
        int playerID
    )
    {
        const std::vector<TerritoryID>& playerTerritories =
            player.getTerritoriesHeld();

        return std::max(
            3,
            static_cast<int>(playerTerritories.size()) / 3
        );
    }

    //=========================================================
    // Reinforcement execution
    //=========================================================

    // Executes the latest reinforcement order by applying
    // the troop delta through GameStateManager.
    void TroopManager::executeReinforceOrder()
    {
        ReinforceOrder& currentReinforceOrder =
            reinforceOrders.back();

        gameStateManager.updateTerritoryTroopCount(
            currentReinforceOrder.getTerritoryID(),
            currentReinforceOrder.getReinforceTroopCount()
        );

        currentReinforceOrder.complete();
    }

    //=========================================================
    // Fortification execution
    //=========================================================

    // Executes the latest fortification order.
    //
    // Troops are removed from the source territory and added
    // to the destination territory using delta updates.
    void TroopManager::executeFortifyOrder()
    {
        FortifyOrder& currentFortifyOrder =
            fortifyOrders.back();

        gameStateManager.updateTerritoryTroopCount(
            currentFortifyOrder.getFromTerritory(),
            -currentFortifyOrder.getFortifyTroopCount()
        );

        gameStateManager.updateTerritoryTroopCount(
            currentFortifyOrder.getToTerritory(),
            currentFortifyOrder.getFortifyTroopCount()
        );

        currentFortifyOrder.complete();
    }

    //=========================================================
    // Cash-set execution
    //=========================================================

    // Executes the latest cash-set order.
    //
    // The selected cards are removed from a copy of the player's current hand. 
    int TroopManager::executeCashSetOrder()
    {
        CashSetOrder& currentCashSetOrder =
            cashSetOrders.back();

        std::vector<Card> currentPlayerSet =
            player.getPlayerSet();

        std::vector<Card> cardsToRemove =
            currentCashSetOrder.getCards();

        //-----------------------------------------------------
        // Remove each cashed card from the player's hand
        //-----------------------------------------------------

        for (const Card& cardToRemove : cardsToRemove)
        {
            auto it = std::find_if(
                currentPlayerSet.begin(),
                currentPlayerSet.end(),
                [&](const Card& playerCard)
                {
                    return
                        playerCard.getCardType() ==
                        cardToRemove.getCardType()
                        &&
                        playerCard.getTerritoryID() ==
                        cardToRemove.getTerritoryID()
                        &&
                        playerCard.getContinentID() ==
                        cardToRemove.getContinentID();
                }
            );

            // TurnManager has already validated that the cards
            // belong to the player. Erase the matching instance.
            if (it != currentPlayerSet.end())
            {
                currentPlayerSet.erase(it);
            }
        }

        //-----------------------------------------------------
        // Apply updated player state
        //-----------------------------------------------------

        gameStateManager.updatePlayerSet(
            playerID,
            currentPlayerSet
        );

        //-----------------------------------------------------
        // Complete order
        //-----------------------------------------------------

        currentCashSetOrder.complete();

        return currentCashSetOrder.getSetValue();
    }

    //=========================================================
    // Undo reinforcement
    //=========================================================

    // Removes the latest pending reinforcement order.
    // TurnManager ensures undo is only available before execution.
    void TroopManager::undoReinforceOrder()
    {
        if (!reinforceOrders.empty())
        {
            reinforceOrders.pop_back();
        }
    }

    //=========================================================
    // Undo fortification
    //=========================================================

    // Removes the latest pending fortification order.
    void TroopManager::undoFortifyOrder()
    {
        if (!fortifyOrders.empty())
        {
            fortifyOrders.pop_back();
        }
    }

    //=========================================================
    // Undo cash set
    //=========================================================

    // Removes the latest pending cash-set order.
    void TroopManager::undoCashSetOrder()
    {
        if (!cashSetOrders.empty())
        {
            cashSetOrders.pop_back();
        }
    }
    //=========================================================
// Getters
//=========================================================

    const std::vector<ReinforceOrder>&
        TroopManager::getReinforceOrders() const
    {
        return reinforceOrders;
    }

    const std::vector<FortifyOrder>&
        TroopManager::getFortifyOrders() const
    {
        return fortifyOrders;
    }

    const std::vector<CashSetOrder>&
        TroopManager::getCashSetOrders() const
    {
        return cashSetOrders;
    }

    const ReinforceOrder&
        TroopManager::getLastReinforceOrder() const
    {
        return reinforceOrders.back();
    }

    const FortifyOrder&
        TroopManager::getLastFortifyOrder() const
    {
        return fortifyOrders.back();
    }

    const CashSetOrder&
        TroopManager::getLastCashSetOrder() const
    {
        return cashSetOrders.back();
    }

} // namespace risk