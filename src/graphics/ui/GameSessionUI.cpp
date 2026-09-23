#include "risk/graphics/ui/GameSessionUI.h"
#include "risk/graphics/game_elements/TerritoryGraphics.h"

#include "risk/core/session/GameState.h"
#include "risk/entities/Territory.h"
#include "risk/utils/FilePathConverter.h"
#include "risk/utils/TerritoryConverter.h"

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

namespace risk {

    //---------------------------------------------------------
    // Initial Loading
    //---------------------------------------------------------

    void GameSessionUI::initialLoading(
        GameSession& gameSession,
        GameState& gameState,
        int humanPlayers,
        int aiPlayers,
        MapType mapSelection)
    {
        humanPlayerNumbers = humanPlayers;
        aiPlayerNumbers = aiPlayers;
        this->mapSelection = mapSelection;

        try
        {
            const std::string boardFilename =
                mapTypeToBoardFilename(mapSelection);

            std::ifstream boardFile(boardFilename);

            if (!boardFile.is_open())
            {
                throw std::runtime_error(
                    "Could not open board graphics file: " +
                    boardFilename
                );
            }

            nlohmann::json boardJson;
            boardFile >> boardJson;

            const auto& boardData =
                boardJson.at("board");

            const std::string mapImagePath =
                boardData.at(
                    "background_texture"
                ).get<std::string>();

            static sf::Font font;

            if (!font.openFromFile(
                "C:/Windows/Fonts/arial.ttf"))
            {
                throw std::runtime_error(
                    "Could not load font"
                );
            }

            //-------------------------------------------------
            // Board
            //-------------------------------------------------

            boardGraphics.emplace(
                mapImagePath,
                font
            );

            //-------------------------------------------------
            // Continent values
            //-------------------------------------------------

            for (const auto& continent :
                boardData.at("continent_values"))
            {
                std::string continentName =
                    continent.at(
                        "continent"
                    ).get<std::string>();

                int continentValue =
                    continent.at(
                        "value"
                    ).get<int>();

                const auto& positionData =
                    continent.at("position");

                sf::Vector2f position(
                    positionData.at(0).get<float>(),
                    positionData.at(1).get<float>()
                );

                const auto& sizeData =
                    continent.at("size");

                sf::Vector2f size(
                    sizeData.at(0).get<float>(),
                    sizeData.at(1).get<float>()
                );

                unsigned int characterSize =
                    continent.at(
                        "character_size"
                    ).get<unsigned int>();

                boardGraphics->addContinentValue(
                    continentName,
                    continentValue,
                    position,
                    size,
                    characterSize,
                    font
                );
            }

            //-------------------------------------------------
            // Shared game graphics
            //-------------------------------------------------

            createTerritoryGraphicsMap(
                gameSession.getMap(),
                mapSelection
            );

            //-------------------------------------------------
            // Game setup UI
            //-------------------------------------------------

            gameSetupUI.emplace();

            gameSetupUI->initialize(
                gameSession,
                font,
                playerGraphics
            );

            gameState.setPhase(
                PhaseType::GameSetup
            );
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string(
                    "GameSessionUI initial loading failed: "
                ) +
                exception.what()
            );
        }
    }

    //---------------------------------------------------------
    // UI Routing
    //---------------------------------------------------------

    void GameSessionUI::draw(
        sf::RenderWindow& window,
        GameState& gameState,
        GameSession& gameSession)
    {
        //-----------------------------------------------------
        // Shared game graphics
        //-----------------------------------------------------

        if (boardGraphics.has_value())
        {
            boardGraphics->draw(
                window);
        }

        for (const auto& [territoryID, territory] :
            territoryGraphicsMap)
        {
            territory.draw(
                window);
        }


        //-----------------------------------------------------
        // Game Setup
        //-----------------------------------------------------

        if (gameState.getPhase() ==
            PhaseType::GameSetup)
        {
            if (gameSetupUI.has_value())
            {
                gameSetupUI->draw(
                    window,
                    playerGraphics);
            }

            return;
        }


        //-----------------------------------------------------
        // Reinforce
        //-----------------------------------------------------

        if (gameState.getPhase() ==
            PhaseType::Reinforce)
        {
            if (!reinforceUI.has_value())
            {
                static sf::Font font;

                if (!font.openFromFile(
                    "C:/Windows/Fonts/arial.ttf"))
                {
                    throw std::runtime_error(
                        "Could not load font");
                }

                reinforceUI.emplace(
                    font,
                    territoryGraphicsMap,
                    gameState,
                    gameSession);
            }

            reinforceUI->draw(
                window,
                playerGraphics,
                gameState);
        }
    }


    void GameSessionUI::handleEvent(
        const sf::Event& event,
        sf::RenderWindow& window,
        GameSession& gameSession,
        GameState& gameState)
    {
        //-----------------------------------------------------
        // Game Setup
        //-----------------------------------------------------

        if (gameState.getPhase() ==
            PhaseType::GameSetup)
        {
            if (gameSetupUI.has_value())
            {
                gameSetupUI->handleEvent(
                    event,
                    window,
                    gameSession,
                    gameState,
                    playerGraphics,
                    territoryGraphicsMap);
            }

            return;
        }


        //-----------------------------------------------------
        // Reinforce
        //-----------------------------------------------------

        if (gameState.getPhase() ==
            PhaseType::Reinforce)
        {
            if (reinforceUI.has_value())
            {
                reinforceUI->handleReinforceEvent(
                    event,
                    window,
                    gameSession,
                    gameState,
                    playerGraphics,
                    territoryGraphicsMap);
            }
        }
    }


    //---------------------------------------------------------
    // Shared Game Graphics
    //---------------------------------------------------------

    void GameSessionUI::createTerritoryGraphicsMap(
        Map& territoryMap,
        MapType mapSelection)
    {
        try
        {
            const std::string boardFilename =
                mapTypeToBoardFilename(
                    mapSelection
                );

            std::ifstream boardFile(
                boardFilename
            );

            if (!boardFile.is_open())
            {
                throw std::runtime_error(
                    "Could not open board graphics file: " +
                    boardFilename
                );
            }

            nlohmann::json boardJson;
            boardFile >> boardJson;

            const auto& boardData =
                boardJson.at("board");

            const auto& territoriesData =
                boardData.at("territories");

            static sf::Font font;

            if (!font.openFromFile(
                "C:/Windows/Fonts/arial.ttf"))
            {
                throw std::runtime_error(
                    "Could not load font"
                );
            }

            territoryGraphicsMap.clear();

            for (const auto& territoryData :
                territoriesData)
            {
                TerritoryID territoryID =
                    stringToTerritoryID(
                        territoryData.at(
                            "territory"
                        ).get<std::string>()
                    );

                const auto& pointsData =
                    territoryData.at("points");

                std::vector<sf::Vector2f> vertices;

                for (const auto& pointData :
                    pointsData)
                {
                    sf::Vector2f point(
                        pointData.at(0).get<float>(),
                        pointData.at(1).get<float>()
                    );

                    vertices.push_back(point);
                }

                Territory& territory =
                    territoryMap.getTerritory(
                        territoryID
                    );

                int playerID =
                    territory.getOwnerID();

                ContinentID continentID =
                    territory.getContinentID();

                std::string title =
                    territoryData.at(
                        "territory"
                    ).get<std::string>();

                const auto& titlePositionData =
                    territoryData.at(
                        "title_position"
                    );

                sf::Vector2f titlePosition(
                    titlePositionData.at(0).get<float>(),
                    titlePositionData.at(1).get<float>()
                );

                const auto& troopPositionData =
                    territoryData.at(
                        "troop_count_position"
                    );

                sf::Vector2f troopCountPosition(
                    troopPositionData.at(0).get<float>(),
                    troopPositionData.at(1).get<float>()
                );

                unsigned int titleCharacterSize =
                    territoryData.at(
                        "title_character_size"
                    ).get<unsigned int>();

                unsigned int troopCharacterSize =
                    territoryData.at(
                        "troop_character_size"
                    ).get<unsigned int>();

                float outlineThickness =
                    territoryData.at(
                        "outline_thickness"
                    ).get<float>();

                auto [iterator, inserted] =
                    territoryGraphicsMap.emplace(
                        territoryID,
                        TerritoryGraphics(
                            territoryID,
                            continentID,
                            playerID,
                            title,
                            vertices,
                            titlePosition,
                            troopCountPosition,
                            titleCharacterSize,
                            troopCharacterSize,
                            outlineThickness,
                            font
                        )
                    );

                iterator->second.setTroopCount(
                    territory.getTroopCount()
                );
            }
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string(
                    "territory graphics map creation failed: "
                ) +
                exception.what()
            );
        }
    }


    //---------------------------------------------------------
    // UI State Access
    //---------------------------------------------------------

    GameSetupState&
        GameSessionUI::getGameSetupState()
    {
        return gameSetupUI
            ->getGameSetupState();
    }


    BoardGraphics&
        GameSessionUI::getBoardGraphics()
    {
        return boardGraphics.value();
    }


    std::unordered_map<
        TerritoryID,
        TerritoryGraphics
    >& GameSessionUI::getTerritoryGraphics()
    {
        return territoryGraphicsMap;
    }


    std::vector<PlayerGraphics>&
        GameSessionUI::getPlayerGraphics()
    {
        return playerGraphics;
    }

} // namespace risk