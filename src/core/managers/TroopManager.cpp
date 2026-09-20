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

    TroopManager::TroopManager(
        GameStateManager& gameStateManager
    )
        : gameStateManager(gameStateManager)
    {
    }

    //=========================================================
    // Order creation
    //=========================================================

    void TroopManager::createReinforceOrder(
        int playerID,
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

    void TroopManager::createFortifyOrder(
        int playerID,
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

    void TroopManager::createCashSetOrder(
        int playerID,
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
        const Player& player
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

    int TroopManager::executeCashSetOrder(
        const Player& player
    )
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

            if (it != currentPlayerSet.end())
            {
                currentPlayerSet.erase(it);
            }
        }

        //-----------------------------------------------------
        // Apply updated player state
        //-----------------------------------------------------

        gameStateManager.updatePlayerSet(
            currentCashSetOrder.getPlayerID(),
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

    void TroopManager::undoCashSetOrder()
    {
        if (!cashSetOrders.empty())
        {
            cashSetOrders.pop_back();
        }
    }
   //=========================================================
   // clear orders
   //=========================================================
    void TroopManager::clearOrders()
    {
        reinforceOrders.clear();
        fortifyOrders.clear();
        cashSetOrders.clear();
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