#include "risk/graphics/ui/LUIExchange.h"

namespace risk {

    LUIExchange::LUIExchange()
    {
    }


    void LUIExchange::loading(
        sf::RenderWindow& window,
        LoadingUI& loadingUI
    )
    {
        loadingUI.draw(window);
    }


    void LUIExchange::initialLoading(
        GameSession& gameSession,
        GameSetupUI& gameSetupUI,
        GameState& gameState,
        int humanPlayers,
        int aiPlayers,
        MapType mapSelection
    )
    {
        gameSetupUI.initialLoading(
            gameSession,
            gameState,
            humanPlayers,
            aiPlayers,
            mapSelection
        );
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

                bool selected =
                    gameSetupState != nullptr &&
                    gameSetupState->getTerritorySelected() ==
                    territoryID;

                // Show pending setup troop
                if (selected)
                {
                    troopCount++;
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


    void LUIExchange::gameSetupDraw(
        sf::RenderWindow& window,
        GameSetupUI& gameSetupUI
    )
    {
        gameSetupUI.draw(window);
    }


    void LUIExchange::handleGameSetupEvent(
        const sf::Event& event,
        sf::RenderWindow& window,
        GameSetupUI& gameSetupUI,
        GameSession& gameSession,
        GameState& gameState
    )
    {
        gameSetupUI.handleEvent(
            event,
            window,
            gameSession,
            gameState
        );
    }

} // namespace risk