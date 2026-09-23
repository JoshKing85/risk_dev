#include "risk/core/session/GameSession.h"

#include "risk/core/session/GameInitializer.h"

// managers
#include "risk/core/managers/AttackManager.h"
#include "risk/core/managers/GameStateManager.h"
#include "risk/core/managers/TroopManager.h"

// entity and world
#include "risk/entities/Player.h"

#include "risk/world/Deck.h"
#include "risk/world/Map.h"

// validation
#include "risk/core/validation/ValidateTerritorySelection.h"
#include "risk/core/validation/ValidateAttackInput.h"
#include "risk/core/validation/ValidateAttackSelection.h"
#include "risk/core/validation/ValidateDiceInput.h"
#include "risk/core/validation/ValidateFortifyInput.h"
#include "risk/core/validation/ValidateReinforceInput.h"
#include "risk/core/validation/ValidateSetInput.h"

#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

namespace risk {

    //=========================================================
    // CONSTRUCTOR
    //=========================================================

    GameSession::GameSession()
        : gameStateManager(map, players)
    {
    }


    //=========================================================
    // CREATE GAME
    //=========================================================

    void GameSession::createGame(
        std::string& filename,
        int playerNumbers,
        int aiNumbers
    )
    {
        //-----------------------------------------------------
        // Create base game state
        //-----------------------------------------------------

        GameInitializer gameInitializer;

        std::tie(map, players, deck) =
            gameInitializer.initializeGame(
                filename,
                playerNumbers,
                aiNumbers
            );

        //-----------------------------------------------------
        // Deal initial territories
        //-----------------------------------------------------

        gameInitializer.dealDeck(
            deck,
            players,
            map,
            gameStateManager
        );

        //-----------------------------------------------------
        // Calculate remaining starting troops
        //-----------------------------------------------------

        remainingTroops.clear();

        for (auto& player : players)
        {
            int troops =
                static_cast<int>(
                    60 / players.size()
                    )
                -
                static_cast<int>(
                    player.getTerritoriesHeld().size()
                    );

            if (players.size() == 6)
            {
                troops++;
            }

            remainingTroops.push_back(
                troops
            );
        }

        //-----------------------------------------------------
        // Initial troop placement handled through
        // GameState and UI events.
        //-----------------------------------------------------
    }


    //=========================================================
    // END TURN
    //=========================================================

    void GameSession::endTurn(GameState& gameState)
    {
        // 1. Log completed turn
        //LogManager logManager(/* current player */);
        // log attackManager + troopManager orders

        // 2. Remove this turn's orders
        attackManager.clearOrders();
        troopManager.clearOrders();

        // 3. Reset/advance turn state
        // gameState.clear/reset...
        // gameState advance player...
    }


    //=========================================================
    // VALIDATION
    //=========================================================

    bool GameSession::validateSelection(
        TerritoryID selectedTerritory,
        std::vector<TerritoryID> territories
    )
    {
        return isValidTerritorySelection(
            selectedTerritory,
            territories
        );
    }

    bool GameSession::validateAttackSelection(
        int playerID,
        TerritoryID& territorySelection
    )
    {
        return isValidAttackSelection(
            playerID,
            territorySelection,
            map
        );
    }

    bool GameSession::validateAttackInput(
        TerritoryID toSelection,
        TerritoryID fromSelection
    )
    {
        return isValidAttackInput(
            toSelection,
            map.getTerritory(
                fromSelection
            ).getAdjacentTerritories(),
            map.getTerritory(
                fromSelection
            ).getTroopCount()
        );
    }


    bool GameSession::validateReinforceInput(
        int troopCount,
        GameState& gameState)
    {
        return isReinforceValid(
            troopCount,
            gameState.getReinforcePool());
    }


    bool GameSession::validateDiceInput(
        int diceCount,
        GameState& gameState
    )
    {
        return isValidDiceInput(
            diceCount,
            map.getTerritory(
                gameState.getFromTerritorySelection()
            ).getTroopCount()
        );
    }


    bool GameSession::validateFortifySelection(
        TerritoryID fromSelection,
        TerritoryID toSelection,
        GameState& gameState
    )
    {
        return isFortifyValid(
            map,
            fromSelection,
            toSelection,
            gameState.getPlayerTurnID()
        );
    }


    bool GameSession::validateCashSet(
        const std::vector<Card>& cards
    )
    {
        return isValidSet(
            cards
        );
    }


    //=========================================================
    // REINFORCE ORDER
    //=========================================================

    void GameSession::createReinforceOrder(
        TerritoryID territoryID,
        int troopCount,
        GameState& gameState
    )
    {
        troopManager.createReinforceOrder(
            gameState.getPlayerTurnID(),
            territoryID,
            troopCount
        );

        gameState.addReinforceOrder(
            troopManager.getLastReinforceOrder()
        );
    }


    void GameSession::executeReinforceOrder(
        GameState& gameState
    )
    {
        troopManager.executeReinforceOrder(
            gameStateManager
        );
    }


    void GameSession::undoReinforceOrder(
        GameState& gameState
    )
    {
        gameState.removeLastReinforceOrder();

        troopManager.undoReinforceOrder();
    }


    void GameSession::updateReinforceOrder(
        bool add,
        GameState& gameState
    )
    {
        troopManager.updateReinforceOrder(
            add
        );
    }


    //=========================================================
    // CASH SET ORDER
    //=========================================================

    void GameSession::createCashSetOrder(
        SetType setType,
        const std::vector<Card>& cards,
        GameState& gameState
    )
    {
        troopManager.createCashSetOrder(
            gameState.getPlayerTurnID(),
            setType,
            cards
        );
    }


    void GameSession::executeCashSetOrder(
        GameState& gameState
    )
    {
        int reinforcementBonus =
            troopManager.executeCashSetOrder(
                getPlayer(
                    gameState.getPlayerTurnID()
                ),
                gameStateManager
            );

        gameState.setInitialReinforceCount(
            gameState.getReinforcePool()
            +
            reinforcementBonus
        );
    }


    void GameSession::undoCashSetOrder(
        GameState& gameState
    )
    {
        troopManager.undoCashSetOrder();
    }


    //=========================================================
    // ATTACK ORDER
    //=========================================================

    void GameSession::createAttackOrder(
        GameState& gameState)
    {
        TerritoryID fromTerritory =
            gameState.getFromTerritorySelection();

        TerritoryID toTerritory =
            gameState.getToTerritorySelection();

        int attackingTroops =
            map.getTerritory(
                fromTerritory
            ).getTroopCount() - 1;

        attackManager.createAttack(
            gameState.getPlayerTurnID(),
            fromTerritory,
            toTerritory,
            attackingTroops,
            map.getTerritory(
                toTerritory
            ).getTroopCount()
        );

        gameState.addAttackOrder(
            attackManager.getLastAttackOrder()
        );
    }


    void GameSession::executeAttackOrder(
        GameState& gameState
    )
    {
        attackManager.executeAttackOrder(
            gameStateManager
        );
    }


    void GameSession::undoAttackOrder(
        GameState& gameState
    )
    {
        gameState.removeLastAttackOrder();

        attackManager.undoAttack();
    }


    //=========================================================
    // ROLL DICE ORDER
    //=========================================================

    void GameSession::createRollDiceOrder(
        int diceCount,
        GameState& gameState
    )
    {
        attackManager.createRollDiceOrder(
            diceCount
        );

        gameState.addRollDiceOrder(
            attackManager.getLastRollDiceOrder()
        );
    }


    void GameSession::executeRollDiceOrder(
        GameState& gameState
    )
    {
        // AttackManager resolves the latest RollDiceOrder
        // when executeAttackOrder() is called.
    }


    void GameSession::undoRollDiceOrder(
        GameState& gameState
    )
    {
        gameState.removeLastRollDiceOrder();

        attackManager.undoRollDiceOrder();
    }


    //=========================================================
    // MOVE TROOPS ORDER
    //=========================================================

    void GameSession::createMoveTroopsOrder(
        TerritoryID fromTerritory,
        TerritoryID toTerritory,
        int troopCount,
        GameState& gameState
    )
    {
        attackManager.createMoveTroopsOrder(
            gameState.getPlayerTurnID(),
            fromTerritory,
            toTerritory,
            troopCount
        );

        gameState.addMoveTroopsOrder(
            attackManager.getLastMoveTroopsOrder()
        );
    }


    void GameSession::executeMoveTroopsOrder(
        GameState& gameState
    )
    {
        attackManager.executeMoveTroopsOrder(
            gameStateManager
        );
    }


    void GameSession::undoMoveTroopsOrder(
        GameState& gameState
    )
    {
        gameState.removeLastMoveTroopsOrder();

        attackManager.undoMoveTroopsOrder();
    }


    //=========================================================
    // FORTIFY ORDER
    //=========================================================

    void GameSession::createFortifyOrder(
        TerritoryID fromTerritory,
        TerritoryID toTerritory,
        int troopCount,
        GameState& gameState
    )
    {
        troopManager.createFortifyOrder(
            gameState.getPlayerTurnID(),
            fromTerritory,
            toTerritory,
            troopCount
        );

        gameState.addFortifyOrder(
            troopManager.getLastFortifyOrder()
        );
    }


    void GameSession::executeFortifyOrder(
        GameState& gameState
    )
    {
        troopManager.executeFortifyOrder(
            gameStateManager
        );
    }


    void GameSession::undoFortifyOrder(
        GameState& gameState
    )
    {
        gameState.removeLastFortifyOrder();

        troopManager.undoFortifyOrder();
    }


    //=========================================================
    // GETTERS
    //=========================================================

    Map& GameSession::getMap()
    {
        return map;
    }


    std::vector<Player>& GameSession::getPlayers()
    {
        return players;
    }


    std::vector<int> GameSession::getPlayerIDs() const
    {
        std::vector<int> playerIDs;

        for (const auto& player : players)
        {
            playerIDs.push_back(
                player.getPlayerID()
            );
        }

        return playerIDs;
    }


    std::vector<int> GameSession::getTroopCounts() const
    {
        std::vector<int> troopCounts;

        for (const auto& player : players)
        {
            troopCounts.push_back(
                player.getTroopCount()
            );
        }

        return troopCounts;
    }


    std::vector<int> GameSession::getRemainingTroops() const
    {
        return remainingTroops;
    }


    Player& GameSession::getPlayer(
        int playerID
    )
    {
        for (auto& player : players)
        {
            if (player.getPlayerID() ==
                playerID)
            {
                return player;
            }
        }

        throw std::runtime_error(
            "Player ID not found"
        );
    }


    //=========================================================
    // SETTERS
    //=========================================================

    void GameSession::addTroop(
        TerritoryID territoryID,
        int playerID)
    {
        gameStateManager.updateTerritoryTroopCount(
            territoryID,
            1);

        gameStateManager.updatePlayerTroopCount(
            playerID,
            1);
    }


    void GameSession::setReinforcePool(
        GameState& gameState
    )
    {
        int playerID =
            gameState.getPlayerTurnID();

        int reinforcementPool =
            troopManager.calculateReinforcements(
                players[playerID]
            );

        gameState.setInitialReinforceCount(
            reinforcementPool
        );
    }

} // namespace risk