#include "risk/graphics/ui/GameSessionUI.h"

#include "risk/graphics/game_elements/TerritoryGraphics.h"

#include "risk/core/session/GameState.h"
#include "risk/entities/Territory.h"
#include "risk/utils/TerritoryConverter.h"
#include "risk/world/FeatureLoader.h"
#include "risk/graphics/components/Feature.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

namespace risk
{

GameSessionUI::GameSessionUI()
    : frameSprite(frameTexture), devMapSprite(devMapTexture)
{
    //---------------------------------------------------------
    // Frame
    //---------------------------------------------------------

    if (!frameTexture.loadFromFile("data/graphics/board/BoardFrame3.png"))
    {
        throw std::runtime_error("Could not load game frame");
    }

    frameSprite.setTexture(frameTexture, true);

    //---------------------------------------------------------
    // DEV - Map Reference
    //---------------------------------------------------------

    if (!devMapTexture.loadFromFile("data/graphics/devMap.png"))
    {
        throw std::runtime_error("Could not load dev map");
    }

    devMapSprite.setTexture(devMapTexture, true);

    devMapSprite.setScale({1.f, 1.f});

    devMapSprite.setPosition({100.0f, 0.f});

    //---------------------------------------------------------
    // DEV - Fine Mesh
    //---------------------------------------------------------

    fineMesh.emplace();

    ///---------------------------------------------------------
    // Filter - Paper Grain
    //---------------------------------------------------------

    if (!paperGrainShader.loadFromFile(
        "data/graphics/shaders/paper_grain.frag",
        sf::Shader::Type::Fragment))
    {
        throw std::runtime_error(
            "Could not load paper grain shader");
    }

    paperGrainShader.setUniform(
        "grainStrength", 0.06f);

    paperGrainShader.setUniform(
        "currentTexture",
        sf::Shader::CurrentTexture);

    if (!screenTexture.resize({1920, 1080}))
    {
        throw std::runtime_error(
            "Could not create screen capture texture");
    }

    screenSprite.emplace(screenTexture);
}

    //---------------------------------------------------------
    // Initial Loading
    //---------------------------------------------------------

    void GameSessionUI::initialLoading(
        GameSession& gameSession,
        GameState& gameState,
        int humanPlayers,
        int aiPlayers,
        const std::vector<PlayerProfile>& playerProfiles)
    {
        humanPlayerNumbers = humanPlayers;
        aiPlayerNumbers = aiPlayers;

        try
        {
            const std::string boardFilename =
                "data/graphics/europe/europe_board.json";

            std::ifstream boardFile(
                boardFilename);

            if (!boardFile.is_open())
            {
                throw std::runtime_error(
                    "Could not open board graphics file: " +
                    boardFilename);
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
                    "Could not load font");
            }

            const std::string featureFileName =
                "data/graphics/europe/map_features.json";

            //-------------------------------------------------
            // Board
            //-------------------------------------------------

            boardGraphics.emplace(
                mapImagePath,
                font);

            //-------------------------------------------------
            // Features
            //-------------------------------------------------

            featureGraphics.emplace(loadFeatures(featureFileName));

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
                    positionData.at(1).get<float>());

                const auto& sizeData =
                    continent.at("size");

                sf::Vector2f size(
                    sizeData.at(0).get<float>(),
                    sizeData.at(1).get<float>());

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
                    font);
            }

            //-------------------------------------------------
            // Shared game graphics
            //-------------------------------------------------

            createTerritoryGraphicsMap(
                gameSession.getMap());

            screenTexture.resize({1920, 1080});
            screenSprite.emplace(screenTexture);

            //-------------------------------------------------
            // Game setup UI
            //-------------------------------------------------

            gameSetupUI.emplace();

            gameSetupUI->initialize(
                gameSession,
                font,
                playerGraphics,
                playerProfiles);

            gameState.setPhase(
                PhaseType::GameSetup);
        }
        catch (const std::exception& exception)
        {
            std::cerr << "GameSessionUI initialization error: "
                << exception.what()
                << std::endl;
            throw std::runtime_error(
                std::string(
                    "GameSessionUI initial loading failed: "
                ) +
                exception.what());
        }
    }

    //---------------------------------------------------------
    // Draw
    //---------------------------------------------------------

    void GameSessionUI::draw(
        sf::RenderWindow& window,
        GameState& gameState,
        GameSession& gameSession)
    {
        //-----------------------------------------------------
        // Board
        //-----------------------------------------------------

        if (boardGraphics.has_value())
        {
            boardGraphics->draw(
                window);
        }

        //-----------------------------------------------------
        // Territories
        //-----------------------------------------------------

        for (const auto& [territoryID, territory] :
            territoryGraphicsMap)
        {
            territory.draw(
                window);
        }

        //-----------------------------------------------------
        // Features
        //-----------------------------------------------------

        if (featureGraphics.has_value())
        {
            featureGraphics->draw(
                window);
        }

        //-----------------------------------------------------
        // Paper Grain Filter
        //-----------------------------------------------------

        // Capture the completed map.
        screenTexture.update(window);

        // Apply the paper grain shader.
        sf::RenderStates states;
        states.shader = &paperGrainShader;

        // Draw the filtered image back onto the window.
        window.draw(
            *screenSprite,
            states);

        //-----------------------------------------------------
        // Players
        //-----------------------------------------------------

        for (auto& playerGraphic :
            playerGraphics)
        {
            playerGraphic.draw(
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
                    window);
            }
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

            if (!gameState.getTurnStarted())
            {
                reinforceUI->setPlayerState(
                    gameState,
                    gameSession,
                    territoryGraphicsMap);
            }

            reinforceUI->draw(
                window,
                gameState);
        }

        //-----------------------------------------------------
        // Attack
        //-----------------------------------------------------

        if (gameState.getPhase() ==
            PhaseType::Attack)
        {
            if (!attackUI.has_value())
            {
                static sf::Font font;

                if (!font.openFromFile(
                    "C:/Windows/Fonts/arial.ttf"))
                {
                    throw std::runtime_error(
                        "Could not load font");
                }

                attackUI.emplace(
                    font,
                    territoryGraphicsMap,
                    gameState,
                    gameSession);
            }

            attackUI->draw(
                window,
                gameState);
        }

        //-----------------------------------------------------
        // Fortify
        //-----------------------------------------------------

        if (gameState.getPhase() ==
            PhaseType::Fortify)
        {
            if (!fortifyUI.has_value())
            {
                static sf::Font font;

                if (!font.openFromFile(
                    "C:/Windows/Fonts/arial.ttf"))
                {
                    throw std::runtime_error(
                        "Could not load font");
                }

                fortifyUI.emplace(
                    font,
                    gameState);
            }

            fortifyUI->draw(
                window,
                gameState);
        }

        //-----------------------------------------------------
        // Frame
        //-----------------------------------------------------

        /*window.draw(
            devMapSprite);*/

        /*fineMesh->draw(
            window);*/

        window.draw(
            frameSprite);

        /*
        debugGrid->draw(
            window);
        */
    }

    //---------------------------------------------------------
    // Event Routing
    //---------------------------------------------------------

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
                    territoryGraphicsMap);
            }
        }

        //-----------------------------------------------------
        // Attack
        //-----------------------------------------------------

        if (gameState.getPhase() ==
            PhaseType::Attack)
        {
            if (attackUI.has_value())
            {
                attackUI->handleAttackEvent(
                    event,
                    window,
                    gameSession,
                    gameState,
                    playerGraphics,
                    territoryGraphicsMap);
            }
        }

        //-----------------------------------------------------
        // Fortify
        //-----------------------------------------------------

        if (gameState.getPhase() ==
            PhaseType::Fortify)
        {
            if (fortifyUI.has_value())
            {
                fortifyUI->handleFortifyEvent(
                    event,
                    window,
                    gameSession,
                    gameState,
                    territoryGraphicsMap);
            }
        }
    }

    //---------------------------------------------------------
    // Shared Game Graphics
    //---------------------------------------------------------

    void GameSessionUI::createTerritoryGraphicsMap(
        Map& territoryMap)
    {
        try
        {
            const std::string boardFilename =
                "data/graphics/europe/europe_board.json";

            std::ifstream boardFile(
                boardFilename);

            if (!boardFile.is_open())
            {
                throw std::runtime_error(
                    "Could not open board graphics file: " +
                    boardFilename);
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
                    "Could not load font");
            }

            territoryGraphicsMap.clear();

            for (const auto& territoryData :
                territoriesData)
            {
                TerritoryID territoryID =
                    stringToTerritoryID(
                        territoryData.at(
                            "territory"
                        ).get<std::string>());

                //-------------------------------------------------
                // Territory polygons
                //-------------------------------------------------

                const auto& polygonsData =
                    territoryData.at("polygons");

                std::vector<
                    std::vector<sf::Vector2f>>
                    vertices;

                for (const auto& polygonData :
                    polygonsData)
                {
                    std::vector<sf::Vector2f>
                        polygonVertices;

                    for (const auto& pointData :
                        polygonData)
                    {
                        sf::Vector2f point(
                            pointData.at(0).get<float>(),
                            pointData.at(1).get<float>());

                        polygonVertices.push_back(
                            point);
                    }

                    vertices.push_back(
                        polygonVertices);
                }

                //-------------------------------------------------
                // Domain territory
                //-------------------------------------------------

                Territory& territory =
                    territoryMap.getTerritory(
                        territoryID);

                int playerID =
                    territory.getOwnerID();

                ContinentID continentID =
                    territory.getContinentID();

                //-------------------------------------------------
                // Territory graphics data
                //-------------------------------------------------

                std::string title =
                    territoryData.at(
                        "territory"
                    ).get<std::string>();

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

                //-------------------------------------------------
                // Create territory graphics
                //-------------------------------------------------
                std::cout << "[DEBUG] Triangulating territory: " << title << std::endl;
                auto [iterator, inserted] =
                    territoryGraphicsMap.emplace(
                        territoryID,
                        TerritoryGraphics(
                            territoryID,
                            continentID,
                            playerID,
                            title,
                            vertices,
                            titleCharacterSize,
                            troopCharacterSize,
                            outlineThickness,
                            font));

                iterator->second.setTroopCount(
                    territory.getTroopCount());
            }
        }
        catch (const std::exception& exception)
        {
            throw std::runtime_error(
                std::string(
                    "territory graphics map creation failed: "
                ) +
                exception.what());
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