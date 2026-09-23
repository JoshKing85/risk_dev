#include "risk/core/session/GameState.h"

namespace risk {

    GameState::GameState()
    {
    }


    //=========================================================
    // SETTERS
    //=========================================================

    void GameState::setPhase(
        PhaseType newPhase)
    {
        phase = newPhase;
    }


    void GameState::setPlayerTurnID(
        int playerID)
    {
        playerTurnID = playerID;
    }


    void GameState::setToSelection(
        TerritoryID territoryID)
    {
        ToSelection = territoryID;
    }


    void GameState::setFromSelection(
        TerritoryID territoryID)
    {
        FromSelection = territoryID;
    }


    void GameState::setAttackerDice(
        int diceCount)
    {
        attackerDice = diceCount;
    }


    void GameState::setAttackConfirmed(
        bool confirmed)
    {
        attackConfirmed = confirmed;
    }


    void GameState::setInitialReinforceCount(
        int troopCount)
    {
        reinforcePool = troopCount;
    }


    void GameState::updateReinforcePool(
        int troopCount)
    {
        reinforcePool =
            reinforcePool - troopCount;
    }


    void GameState::setReinforceComplete(
        bool complete)
    {
        initReinforceComplete = complete;
    }


    void GameState::setPlayerCards(
        std::vector<Card>& playerSet)
    {
        playerCards = playerSet;
    }


    //=========================================================
    // ADD ORDERS
    //=========================================================

    void GameState::addReinforceOrder(
        const ReinforceOrder& order)
    {
        reinforceOrders.push_back(&order);
    }


    void GameState::addAttackOrder(
        const AttackOrder& order)
    {
        attackOrders.push_back(&order);
    }


    void GameState::addRollDiceOrder(
        const RollDiceOrder& order)
    {
        rollDiceOrders.push_back(&order);
    }


    void GameState::addMoveTroopsOrder(
        const MoveTroopsOrder& order)
    {
        moveTroopsOrders.push_back(&order);
    }


    void GameState::addFortifyOrder(
        const FortifyOrder& order)
    {
        fortifyOrders.push_back(&order);
    }


    //=========================================================
    // REMOVE LAST ORDERS
    //=========================================================

    void GameState::removeLastReinforceOrder()
    {
        reinforceOrders.pop_back();
    }


    void GameState::removeLastAttackOrder()
    {
        attackOrders.pop_back();
    }


    void GameState::removeLastRollDiceOrder()
    {
        rollDiceOrders.pop_back();
    }


    void GameState::removeLastMoveTroopsOrder()
    {
        moveTroopsOrders.pop_back();
    }


    void GameState::removeLastFortifyOrder()
    {
        fortifyOrders.pop_back();
    }


    //=========================================================
    // CLEARERS
    //=========================================================

    void GameState::clearOrders()
    {
        reinforceOrders.clear();
        attackOrders.clear();
        rollDiceOrders.clear();
        moveTroopsOrders.clear();
        fortifyOrders.clear();
    }

    void GameState::clearAttack()
    {
        fromTerritorySelection = TerritoryID::None;
        toTerritorySelection = TerritoryID::None;
        attackerDice = 0;
        attackConfirmed = false;
    }

    //=========================================================
    // GETTERS
    //=========================================================

    PhaseType GameState::getPhase() const
    {
        return phase;
    }


    int GameState::getPlayerTurnID()
    {
        return playerTurnID;
    }


    int GameState::getReinforcePool()
    {
        return reinforcePool;
    }


    bool GameState::getReinforceComplete()
    {
        return initReinforceComplete;
    }


    int GameState::calcSetCount()
    {
        setCount =
            static_cast<int>(
                playerCards.size());

        return setCount;
    }


    TerritoryID
        GameState::getToTerritorySelection() const
    {
        return ToSelection;
    }


    TerritoryID
        GameState::getFromTerritorySelection() const
    {
        return FromSelection;
    }


    int GameState::getAttackerDice() const
    {
        return attackerDice;
    }


    bool GameState::getAttackConfirmed() const
    {
        return attackConfirmed;
    }


    std::vector<Card>
        GameState::getPlayerCards()
    {
        return playerCards;
    }


    //=========================================================
    // ORDER GETTERS
    //=========================================================

    const ReinforceOrder&
        GameState::getLastReinforceOrder() const
    {
        return *reinforceOrders.back();
    }


    const AttackOrder&
        GameState::getLastAttackOrder() const
    {
        return *attackOrders.back();
    }


    const RollDiceOrder&
        GameState::getLastRollDiceOrder() const
    {
        return *rollDiceOrders.back();
    }


    const MoveTroopsOrder&
        GameState::getLastMoveTroopsOrder() const
    {
        return *moveTroopsOrders.back();
    }


    const FortifyOrder&
        GameState::getLastFortifyOrder() const
    {
        return *fortifyOrders.back();
    }

} // namespace risk