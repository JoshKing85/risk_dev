#include "risk/graphics/ui/GameSetupUI.h"
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

    void GameSetupUI::initialLoading(
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

            profileUI.emplace(font);

            boardGraphics.emplace(
                mapImagePath,
                font
            );

            //-------------------------------------------------
            // Setup Back / Confirm buttons
            //-------------------------------------------------

            backButton.setSize(
                { 120.0f, 40.0f }
            );

            confirmButton.setSize(
                { 120.0f, 40.0f }
            );

            backButton.setFillColor(
                sf::Color(50, 70, 85)
            );

            confirmButton.setFillColor(
                sf::Color(50, 70, 85)
            );

            backButtonText.emplace(font);
            confirmButtonText.emplace(font);

            backButtonText->setString("Back");
            confirmButtonText->setString("Confirm");

            backButtonText->setCharacterSize(20);
            confirmButtonText->setCharacterSize(20);

            backButtonText->setFillColor(
                sf::Color::White
            );

            confirmButtonText->setFillColor(
                sf::Color::White
            );

            //-------------------------------------------------
            // Current player placement indicator
            //-------------------------------------------------

            currentPlayerBox.setSize(
                { 220.0f, 45.0f }
            );

            currentPlayerBox.setFillColor(
                sf::Color(30, 40, 50, 230)
            );

            currentPlayerBox.setOutlineColor(
                sf::Color::White
            );

            currentPlayerBox.setOutlineThickness(
                2.0f
            );

            currentPlayerText.emplace(font);

            currentPlayerText->setString(
                "PLACE YOUR TROOP"
            );

            currentPlayerText->setCharacterSize(
                18
            );

            currentPlayerText->setFillColor(
                sf::Color::White
            );

            //-------------------------------------------------
            // Downward arrow
            //-------------------------------------------------

            currentPlayerArrow.setPointCount(3);

            currentPlayerArrow.setPoint(
                0,
                { 0.0f, 0.0f }
            );

            currentPlayerArrow.setPoint(
                1,
                { 30.0f, 0.0f }
            );

            currentPlayerArrow.setPoint(
                2,
                { 15.0f, 20.0f }
            );

            currentPlayerArrow.setFillColor(
                sf::Color::White
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

            createTerritoryGraphicsMap(
                gameSession.getMap(),
                mapSelection
            );

            setupState(
                gameSession,
                font
            );

            gameState.setPhase(
                PhaseType::GameSetup
            );
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string(
                    "GameSetupUI initial loading failed: "
                ) +
                exception.what()
            );
        }
    }


    void GameSetupUI::draw(
        sf::RenderWindow& window)
    {
        //-----------------------------------------------------
        // Profile setup
        //-----------------------------------------------------

        if (!gameSetupState.getProfilesReady())
        {
            int playerID =
                gameSetupState.getCurrentProfileID();

            profileUI->profileUIdraw(
                window,
                playerID
            );

            return;
        }

        //-----------------------------------------------------
        // Board
        //-----------------------------------------------------

        if (boardGraphics.has_value())
        {
            boardGraphics->draw(window);
        }

        for (const auto& [territoryID, territory] :
            territoryGraphicsMap)
        {
            territory.draw(window);
        }

        //-----------------------------------------------------
        // Current setup player
        //-----------------------------------------------------

        int currentPlayerID =
            gameSetupState.getCurrentProfileID();

        //-----------------------------------------------------
        // Highlight active player
        //-----------------------------------------------------

        for (auto& playerGraphic :
            playerGraphics)
        {
            playerGraphic.setActive(
                playerGraphic.getPlayerID() ==
                currentPlayerID
            );

            playerGraphic.draw(window);
        }

        //-----------------------------------------------------
        // Position prompt above current player's panel
        //
        // Player panels are 320 pixels apart and begin at
        // x = 0. The prompt is centred over that panel.
        //-----------------------------------------------------

        float playerX =
            static_cast<float>(
                currentPlayerID * 320
                );

        float boxX =
            playerX + 50.0f;

        float boxY =
            755.0f;

        currentPlayerBox.setPosition(
            { boxX, boxY }
        );

        if (currentPlayerText.has_value())
        {
            currentPlayerText->setPosition(
                {
                    boxX + 20.0f,
                    boxY + 11.0f
                }
            );
        }

        currentPlayerArrow.setPosition(
            {
                playerX + 145.0f,
                boxY + 48.0f
            }
        );

        //-----------------------------------------------------
        // Draw current-player indicator
        //-----------------------------------------------------

        window.draw(
            currentPlayerBox
        );

        if (currentPlayerText.has_value())
        {
            window.draw(
                *currentPlayerText
            );
        }

        window.draw(
            currentPlayerArrow
        );

        //-----------------------------------------------------
        // Only show Back / Confirm while territory selected
        //-----------------------------------------------------

        if (gameSetupState.getTerritorySelected() !=
            TerritoryID::None)
        {
            window.draw(backButton);
            window.draw(confirmButton);

            if (backButtonText.has_value())
            {
                window.draw(*backButtonText);
            }

            if (confirmButtonText.has_value())
            {
                window.draw(*confirmButtonText);
            }
        }
    }


    void GameSetupUI::handleEvent(
        const sf::Event& event,
        sf::RenderWindow& window,
        GameSession& gameSession,
        GameState& gameState)
    {
        if (!gameSetupState.getProfilesReady())
        {
            int playerID =
                gameSetupState.getCurrentProfileID();

            profileUI->handleEvent(
                event,
                window,
                playerID,
                playerGraphics[playerID],
                gameSetupState
            );

            return;
        }

        handleTroops(
            event,
            gameSession,
            gameState
        );
    }


    void GameSetupUI::createTerritoryGraphicsMap(
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


    void GameSetupUI::setupState(
        GameSession& gameSession,
        const sf::Font& font)
    {
        std::vector<int> playerIDs =
            gameSession.getPlayerIDs();

        std::vector<int> troopCounts =
            gameSession.getTroopCounts();

        std::vector<int> remainingTroops =
            gameSession.getRemainingTroops();

        for (const auto playerID : playerIDs)
        {
            gameSetupState.addPlayerProfile(
                playerID,
                remainingTroops[playerID]
            );

            playerGraphics.emplace_back(
                playerID,
                troopCounts[playerID],
                font
            );
        }
    }


    void GameSetupUI::handleTroops(
        const sf::Event& event,
        GameSession& gameSession,
        GameState& gameState)
    {
        if (gameSetupState.getTerritorySelected() ==
            TerritoryID::None)
        {
            troopPlacement(
                event,
                gameSession
            );

            return;
        }

        back(event);

        if (gameSetupState.getTerritorySelected() !=
            TerritoryID::None)
        {
            confirm(
                event,
                gameSession,
                gameState
            );
        }
    }


    void GameSetupUI::troopPlacement(
        const sf::Event& event,
        GameSession& gameSession)
    {
        if (const auto* mousePressed =
            event.getIf<
            sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition = {
                static_cast<float>(
                    mousePressed->position.x
                ),
                static_cast<float>(
                    mousePressed->position.y
                )
            };

            for (auto& [territoryID, territoryGraphics] :
                territoryGraphicsMap)
            {
                if (territoryGraphics.contains(
                    mousePosition))
                {
                    const std::vector<TerritoryID>& territories =
                        gameSession
                        .getPlayer(
                            gameSetupState
                            .getCurrentProfileID()
                        )
                        .getTerritoriesHeld();

                    if (gameSession.validateSelection(
                        territoryID,
                        territories))
                    {
                        gameSetupState.setTerritorySelected(
                            territoryID
                        );

                        sf::FloatRect bounds =
                            territoryGraphics.getBounds();

                        setConfirmPosition({
                            bounds.position.x +
                                bounds.size.x +
                                10.0f,
                            bounds.position.y
                            });

                        setBackPosition({
                            bounds.position.x +
                                bounds.size.x +
                                10.0f,
                            bounds.position.y +
                                50.0f
                            });
                    }

                    break;
                }
            }
        }
    }


    void GameSetupUI::back(
        const sf::Event& event)
    {
        if (const auto* mousePressed =
            event.getIf<
            sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition = {
                static_cast<float>(
                    mousePressed->position.x
                ),
                static_cast<float>(
                    mousePressed->position.y
                )
            };

            if (getBackBounds().contains(
                mousePosition))
            {
                gameSetupState.setTerritorySelected(
                    TerritoryID::None
                );
            }
        }
    }


    void GameSetupUI::confirm(
        const sf::Event& event,
        GameSession& gameSession,
        GameState& gameState)
    {
        if (const auto* mousePressed =
            event.getIf<
            sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition = {
                static_cast<float>(
                    mousePressed->position.x
                ),
                static_cast<float>(
                    mousePressed->position.y
                )
            };

            if (getConfirmBounds().contains(
                mousePosition))
            {
                int playerID =
                    gameSetupState
                    .getCurrentProfileID();

                TerritoryID selectedTerritory =
                    gameSetupState
                    .getTerritorySelected();

                //-------------------------------------------------
                // Commit +1 troop
                //-------------------------------------------------

                gameSession.addTroop(
                    selectedTerritory
                );

                //-------------------------------------------------
                // Remove one from setup troop pool
                //-------------------------------------------------

                gameSetupState.removeTroop(
                    playerID
                );

                //-------------------------------------------------
                // Clear pending selection
                //-------------------------------------------------

                gameSetupState.setTerritorySelected(
                    TerritoryID::None
                );

                //-------------------------------------------------
                // Setup finished
                //-------------------------------------------------

                if (gameSetupState.allTroopsPlaced())
                {
                    gameState.setPhase(
                        PhaseType::Reinforce
                    );

                    return;
                }

                //-------------------------------------------------
                // Next unfinished player
                //-------------------------------------------------

                gameSetupState.setCurrentProfile(
                    gameSetupState
                    .getCurrentProfileID()
                );
            }
        }
    }


    void GameSetupUI::setBackPosition(
        sf::Vector2f position)
    {
        backButton.setPosition(position);

        if (backButtonText.has_value())
        {
            backButtonText->setPosition({
                position.x + 10.0f,
                position.y + 8.0f
                });
        }
    }


    void GameSetupUI::setConfirmPosition(
        sf::Vector2f position)
    {
        confirmButton.setPosition(position);

        if (confirmButtonText.has_value())
        {
            confirmButtonText->setPosition({
                position.x + 10.0f,
                position.y + 8.0f
                });
        }
    }


    sf::FloatRect GameSetupUI::getBackBounds() const
    {
        return backButton.getGlobalBounds();
    }


    sf::FloatRect GameSetupUI::getConfirmBounds() const
    {
        return confirmButton.getGlobalBounds();
    }


    BoardGraphics& GameSetupUI::getBoardGraphics()
    {
        return boardGraphics.value();
    }


    std::unordered_map<
        TerritoryID,
        TerritoryGraphics
    >& GameSetupUI::getTerritoryGraphics()
    {
        return territoryGraphicsMap;
    }


    std::vector<PlayerGraphics>&
        GameSetupUI::getPlayerGraphics()
    {
        return playerGraphics;
    }


    GameSetupState&
        GameSetupUI::getGameSetupState()
    {
        return gameSetupState;
    }

} // namespace risk