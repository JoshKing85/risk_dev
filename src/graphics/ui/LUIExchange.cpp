#include "risk/graphics/ui/LUIExchange.h"

namespace risk {

    LUIExchange::LUIExchange()
    {
    }


    void LUIExchange::updateGraphics(
        const Map& map,
        const std::vector<Player>& players,
        const GameState& gameState,
        std::unordered_map<TerritoryID, TerritoryGraphics>& territoryGraphicsMap,
        std::vector<PlayerGraphics>& playerGraphics,
        const GameSetupState* gameSetupState
    )
    {
        // Update territory graphics
        for (const auto& [territoryID, territory] :
            map.getTerritories())
        {
            auto graphicsTerritory =
                territoryGraphicsMap.find(territoryID);

            if (graphicsTerritory !=
                territoryGraphicsMap.end())
            {
                int troopCount =
                    territory.getTroopCount();

                bool selected = false;


                // ---------------------------------------------
                // Game Setup pending troop
                // ---------------------------------------------

                if (gameSetupState != nullptr &&
                    gameSetupState->getTerritorySelected() ==
                    territoryID)
                {
                    selected = true;
                    troopCount++;
                }


                // ---------------------------------------------
                // Reinforce pending troops
                // ---------------------------------------------

                if (gameState.getPhase() ==
                    PhaseType::Reinforce &&
                    gameState.getToTerritorySelection() ==
                    territoryID)
                {
                    selected = true;

                    troopCount +=
                        gameState
                        .getLastReinforceOrder()
                        .getReinforceTroopCount();
                }


                // ---------------------------------------------
                // Attack territory selections
                // ---------------------------------------------

                if (gameState.getPhase() ==
                    PhaseType::Attack)
                {
                    if (gameState.getFromTerritorySelection() ==
                        territoryID)
                    {
                        selected = true;
                    }

                    if (gameState.getToTerritorySelection() ==
                        territoryID)
                    {
                        selected = true;
                    }
                }


                // ---------------------------------------------
                // Fortify pending troops
                // ---------------------------------------------

                if (gameState.getPhase() ==
                    PhaseType::Fortify)
                {
                    if (gameState.getFromTerritorySelection() ==
                        territoryID)
                    {
                        selected = true;

                        if (gameState.getToTerritorySelection() !=
                            TerritoryID::None)
                        {
                            troopCount -=
                                gameState
                                .getLastFortifyOrder()
                                .getFortifyTroopCount();
                        }
                    }

                    if (gameState.getToTerritorySelection() ==
                        territoryID)
                    {
                        selected = true;

                        troopCount +=
                            gameState
                            .getLastFortifyOrder()
                            .getFortifyTroopCount();
                    }
                }


                graphicsTerritory->second.setTroopCount(
                    troopCount
                );

                graphicsTerritory->second.setPlayerID(
                    territory.getOwnerID()
                );

                graphicsTerritory->second.setSelected(
                    selected
                );
            }
        }

        // Update player graphics
        for (const auto& player : players)
        {
            for (auto& graphicsPlayer : playerGraphics)
            {
                if (graphicsPlayer.getPlayerID() ==
                    player.getPlayerID())
                {
                    graphicsPlayer.setTroopCount(
                        player.getTroopCount()
                    );

                    graphicsPlayer.setCardCount(
                        static_cast<int>(
                            player.getPlayerSet().size()
                            )
                    );

                    break;
                }
            }
        }
    }

} // namespace risk