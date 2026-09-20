#include "risk/core/session/GameState.h"

namespace risk {

    GameState::GameState()
    {
    }

    //=========================================================
    // SETTERS
    //=========================================================

    void GameState::setPhase(PhaseType newPhase)
    {
        phase = newPhase;
    }

    void GameState::calcSetCount(int setCount)
    {
        this->setCount = setCount;
    }

    void GameState::setPlayerCards(
        std::vector<Card>& playerSet)
    {
        playerCards = playerSet;
    }

    void GameState::addSelectedCard(Card& card)
    {
        SelectedCards.push_back(card);
    }

    void GameState::setPlayerTurn(int playerID)
    {
        playerTurn = playerID;
    }

    void GameState::setAuxPhase(
        AuxiliaryPhase auxPhase)
    {
        this->auxPhase = auxPhase;
    }

    void GameState::setReinforcePool(
        int reinforcePool)
    {
        this->reinforcePool = reinforcePool;
    }

    void GameState::setTempToSelection(
        TerritoryID& territoryID)
    {
        tempToSelection = territoryID;
    }

    void GameState::setTempFromSelection(
        TerritoryID& territoryID)
    {
        tempFromSelection = territoryID;
    }

    void GameState::setTempReinforceCount(
        int count)
    {
        tempReinforceCount = count;
    }

    //=========================================================
    // GETTERS
    //=========================================================

    PhaseType GameState::getPhase() const
    {
        return phase;
    }

    int GameState::getPlayerTurn()
    {
        return playerTurn;
    }

    int GameState::getSetCount()
    {
        return setCount;
    }

    int GameState::getReinforcePool()
    {
        return reinforcePool;
    }

    int GameState::getTempReinforceCount()
    {
        return tempReinforceCount;
    }

    TerritoryID GameState::getTempToTerritorySelection()
    {
        return tempToSelection;
    }

    TerritoryID GameState::getTempFromTerritorySelection()
    {
        return tempFromSelection;
    }

} // namespace risk