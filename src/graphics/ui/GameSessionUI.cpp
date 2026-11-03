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

    if (!frameTexture.loadFromFile("data/graphics/board/BoardFrame4.png"))
    {
        throw std::runtime_error("Could not load game frame");
    }

    frameSprite.setTexture(frameTexture, true);
    frameSprite.setScale({1.f, 1.f});
    //frameSprite.setPosition();

    //---------------------------------------------------------
    // Shared phase title banner
    //---------------------------------------------------------

    if (!phaseBannerTexture.loadFromFile(
            "data/graphics/board/PhaseTitleBanner.png"))
    {
        throw std::runtime_error("Could not load phase title banner");
    }

    phaseBannerSprite.setTexture(phaseBannerTexture, true);
    phaseBannerSprite.setTexture(phaseBannerTexture, true);

    phaseBannerSprite.setTexture(phaseBannerTexture, true);

    phaseBannerSprite.setScale({1.f, 1.f});

    phaseBannerSprite.setPosition({
        (1920.f - 650.f) / 2.f,
        0.f
    });

    if (!phaseTitleFont.openFromFile("C:/Windows/Fonts/georgiab.ttf"))
    {
        throw std::runtime_error("Could not load phase title font");
    }

    phaseTitleText.setCharacterSize(28);
    phaseTitleText.setFillColor(sf::Color(235, 210, 155));

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
        "grainStrength", 0.045f);

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

    void GameSessionUI::initialLoading(GameSession& gameSession, GameState& gameState, int humanPlayers,
                                   int aiPlayers, const std::vector<PlayerProfile>& playerProfiles)
{
    humanPlayerNumbers = humanPlayers;
    aiPlayerNumbers = aiPlayers;

    try
    {
        const std::string boardFilename = "data/graphics/europe/europe_board.json";

        std::ifstream boardFile(boardFilename);

        if (!boardFile.is_open())
        {
            throw std::runtime_error("Could not open board graphics file: " + boardFilename);
        }

        nlohmann::json boardJson;
        boardFile >> boardJson;

        const auto& boardData = boardJson.at("board");

        const std::string mapImagePath = boardData.at("background_texture").get<std::string>();

        static sf::Font font;

        if (!font.openFromFile("C:/Windows/Fonts/georgia.ttf"))
        {
            throw std::runtime_error("Could not load font");
        }

        const std::string featureFileName = "data/graphics/europe/map_features.json";



        //-------------------------------------------------
        // Board
        //-------------------------------------------------

        boardGraphics.emplace(mapImagePath, font);

        //-------------------------------------------------
        // Features
        //-------------------------------------------------

        featureGraphics.emplace(loadFeatures(featureFileName));
        //-------------------------------------------------
        // Faction troop textures
        //-------------------------------------------------

        factionTroopCounters.clear();
        factionTroopCounters.reserve(6);

        // Napoleon
        sf::Texture napoleonCounter;

        if (!napoleonCounter.loadFromFile("data/graphics/factions/NapoleonTroopCounter.png"))
        {
            throw std::runtime_error("Could not load Napoleon troop counter");
        }

        factionTroopCounters.push_back(std::move(napoleonCounter));

        // Wellington
        sf::Texture wellingtonCounter;

        if (!wellingtonCounter.loadFromFile("data/graphics/factions/WellingtonTroopCounter.png"))
        {
            throw std::runtime_error("Could not load Wellington troop counter");
        }

        factionTroopCounters.push_back(std::move(wellingtonCounter));

        // Bulcher
        sf::Texture blucherCounter;

        if (!blucherCounter.loadFromFile("data/graphics/factions/BlucherTroopCounter.png"))
        {
            throw std::runtime_error("Could not load Blucher troop counter");
        }

        factionTroopCounters.push_back(std::move(blucherCounter));

        // Von Osterriech
        sf::Texture vonCounter;

        if (!vonCounter.loadFromFile("data/graphics/factions/VonTroopCounter.png"))
        {
            throw std::runtime_error("Could not load Von troop counter");
        }

        factionTroopCounters.push_back(std::move(vonCounter));

        // La Needle
        sf::Texture needleCounter;

        if (!needleCounter.loadFromFile("data/graphics/factions/NeedleTroopCounter.png"))
        {
            throw std::runtime_error("Could not load Needle troop counter");
        }

        factionTroopCounters.push_back(std::move(needleCounter));

        // Alexander
        sf::Texture alexCounter;

        if (!alexCounter.loadFromFile("data/graphics/factions/AlexTroopCounter.png"))
        {
            throw std::runtime_error("Could not load Alex troop counter");
        }

        factionTroopCounters.push_back(std::move(alexCounter));
        //-------------------------------------------------
        // Shared game graphics
        //-------------------------------------------------

        createTerritoryGraphicsMap(gameSession.getMap());

        screenTexture.resize({1920, 1080});
        screenSprite.emplace(screenTexture);

        if (!playerSlotsTexture.loadFromFile(
            "data/graphics/components/PlayerSlots.png"))
        {
            throw std::runtime_error(
                "Could not load player slots texture");
        }
        playerSlotsSprite.setScale({1.02f, 1.0f});
        playerSlotsSprite.setTexture(playerSlotsTexture, true);
        playerSlotsSprite.setPosition({30.f, 750.f});

        

        //-------------------------------------------------
        // Game setup UI
        //-------------------------------------------------

        gameSetupUI.emplace();

        gameSetupUI->initialize(gameSession, font, playerGraphics, playerProfiles);

        gameState.setPhase(PhaseType::GameSetup);
    }
    catch (const std::exception& exception)
    {
        std::cerr << "GameSessionUI initialization error: " << exception.what() << std::endl;
        throw std::runtime_error(std::string("GameSessionUI initial loading failed: ") +
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
        // Territory geometry
        //-----------------------------------------------------

        for (const auto& [territoryID, territory] : territoryGraphicsMap)
        {
            territory.draw(window);
        }

        //-----------------------------------------------------
        // Geographical features
        //-----------------------------------------------------

        if (featureGraphics.has_value())
        {
            featureGraphics->draw(window);
        }

        //-----------------------------------------------------
        // Territory labels and troop counts
        //-----------------------------------------------------

        for (const auto& [territoryID, territory] : territoryGraphicsMap)
        {
            territory.drawLabels(window);
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
       
        window.draw(playerSlotsSprite);

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

        //-----------------------------------------------------
        // Shared phase title (rendered over the board frame)
        //-----------------------------------------------------

        std::string title;
        switch (gameState.getPhase())
        {
        case PhaseType::GameSetup:
            title = "INITIAL REINFORCEMENT PHASE";
            break;
        case PhaseType::Reinforce:
            title = "REINFORCEMENT PHASE";
            break;
        case PhaseType::Attack:
            title = "ATTACK PHASE";
            break;
        case PhaseType::Fortify:
            title = "FORTIFICATION PHASE";
            break;
        default:
            break;
        }

        if (!title.empty())
        {
            phaseTitleText.setString(title);
            const sf::FloatRect bounds = phaseTitleText.getLocalBounds();
            phaseTitleText.setOrigin({
                bounds.position.x + bounds.size.x / 2.f,
                bounds.position.y + bounds.size.y / 2.f
            });
            // Keep the text centred within the banner as phases change.
            const sf::FloatRect bannerBounds = phaseBannerSprite.getGlobalBounds();
            phaseTitleText.setPosition({
                bannerBounds.position.x + bannerBounds.size.x / 2.f,
                bannerBounds.position.y + bannerBounds.size.y / 2.f
            });
            window.draw(phaseBannerSprite);
            window.draw(phaseTitleText);
        }

        //-----------------------------------------------------
        // Region dropdown
        //-----------------------------------------------------

        if (boardGraphics.has_value())
        {
            boardGraphics->drawRegionUI(window);
        }
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
        // Region dropdown interaction
        //-----------------------------------------------------

        if (const auto* mousePressed =
            event.getIf<sf::Event::MouseButtonPressed>())
        {
            if (mousePressed->button == sf::Mouse::Button::Left &&
                boardGraphics.has_value())
            {
                sf::Vector2f mousePosition =
                    window.mapPixelToCoords(mousePressed->position);

                if (boardGraphics->handleRegionClick(mousePosition))
                {
                    return;
                }
            }
        }
        //-----------------------------------------------------
        // Territory hover
        //-----------------------------------------------------

        if (const auto* mouseMoved = event.getIf<sf::Event::MouseMoved>())
        {
            sf::Vector2f mousePosition = window.mapPixelToCoords(mouseMoved->position);
            mousePosition.y -= 15.0f;

            for (auto& [territoryID, territory] : territoryGraphicsMap)
            {
                territory.setHovered(territory.contains(mousePosition));
            }
        }

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
                            font,
                            factionTroopCounters));

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