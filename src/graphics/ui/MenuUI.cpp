#include "risk/graphics/ui/MenuUI.h"

#include <stdexcept>
#include <string>

namespace risk {

    MenuUI::MenuUI()
        : mapSelection(MapType::Classic),
        humanPlayerNumbers(1),
        aiPlayerNumbers(2),
        backgroundSprite(backgroundTexture),
        menuFrameSprite(menuFrameTexture),
        title(font),
        mapSelectionTitle(font),
        numberOfPlayersTitle(font),
        humanPlayersTitle(font),
        humanPlayer1Text(font),
        humanPlayer2Text(font),
        humanPlayer3Text(font),
        humanPlayer4Text(font),
        humanPlayer5Text(font),
        humanPlayer6Text(font),
        aiPlayersTitle(font),
        aiPlayer0Text(font),
        aiPlayer1Text(font),
        aiPlayer2Text(font),
        aiPlayer3Text(font),
        aiPlayer4Text(font),
        aiPlayer5Text(font),
        startButtonText(font)
    {
        //=====================================================
        // Colours
        //=====================================================

        const sf::Color brass(
            128,
            105,
            65);

        const sf::Color parchment(
            218,
            194,
            145,
            245);

        const sf::Color textColour(
            55,
            47,
            38);

        const sf::Color selectedColour(
            155,
            70,
            55);

        //=====================================================
        // Menu background
        //=====================================================

        if (backgroundTexture.loadFromFile(
            "data/graphics/components/BattleScene1.png"))
        {
            backgroundSprite.emplace(
                backgroundTexture);

            sf::Vector2u size =
                backgroundTexture.getSize();

            backgroundSprite->setScale({
                1920.0f / size.x,
                1080.0f / size.y
                });

            backgroundSprite->setPosition({
                0.0f,
                0.0f
                });
        }

        //=====================================================
        // Background dampener
        //=====================================================

        backgroundDampener.setPrimitiveType(
            sf::PrimitiveType::TriangleStrip);

        backgroundDampener.resize(
            4);

        const sf::Color dampenerColour(
            225,
            215,
            195,
            60);

        backgroundDampener[0].position = {
            0.f,
            0.f
        };

        backgroundDampener[1].position = {
            0.f,
            1080.f
        };

        backgroundDampener[2].position = {
            1920.f,
            0.f
        };

        backgroundDampener[3].position = {
            1920.f,
            1080.f
        };

        for (std::size_t i = 0;
            i < backgroundDampener.getVertexCount();
            i++)
        {
            backgroundDampener[i].color =
                dampenerColour;
        }

        //=====================================================
        // Menu frame
        //=====================================================

        if (menuFrameTexture.loadFromFile(
            "data/graphics/components/MenuFrame.png"))
        {
            menuFrameSprite.emplace(
                menuFrameTexture);

            menuFrameTexture.setSmooth(
                true);

            sf::Vector2u size =
                menuFrameTexture.getSize();

            float targetWidth =
                880.0f;

            float scale =
                targetWidth /
                static_cast<float>(size.x);

            menuFrameSprite->setScale({
                scale,
                scale
                });

            sf::FloatRect bounds =
                menuFrameSprite->getGlobalBounds();

            menuFrameSprite->setPosition({
                (1920.0f - bounds.size.x) / 2.0f,
                (1080.0f - bounds.size.y) / 2.0f
                });
        }

        //=====================================================
        // Font
        //=====================================================

        if (!font.openFromFile(
            "C:/Windows/Fonts/georgia.ttf"))
        {
            throw std::runtime_error(
                "Could not load font");
        }

        //=====================================================
        // Map selector
        //=====================================================

        mapSelector.emplace(
            font);

        //=====================================================
        // Menu backing
        //=====================================================

        parchmentBacking.setSize({
            620.f,
            760.f
            });

        parchmentBacking.setPosition({
            650.f,
            200.f
            });

        parchmentBacking.setFillColor(
            parchment);

        //=====================================================
        // Menu title
        //=====================================================

        title.setString(
            "MENU");

        title.setCharacterSize(
            36);

        title.setFillColor(
            textColour);

        sf::FloatRect titleBounds =
            title.getLocalBounds();

        title.setOrigin({
            titleBounds.position.x +
                titleBounds.size.x / 2.f,

            titleBounds.position.y +
                titleBounds.size.y / 2.f
            });

        title.setPosition({
            960.f,
            215.f
            });

        title.setStyle(
            sf::Text::Bold);

        //=====================================================
        // Map selection title
        //=====================================================

        mapSelectionTitle.setString(
            "MAP SELECTION");

        mapSelectionTitle.setCharacterSize(
            26);

        mapSelectionTitle.setStyle(
            sf::Text::Regular);

        mapSelectionTitle.setFillColor(
            textColour);

        sf::FloatRect mapTitleBounds =
            mapSelectionTitle.getLocalBounds();

        mapSelectionTitle.setOrigin({
            mapTitleBounds.position.x +
                mapTitleBounds.size.x / 2.f,

            mapTitleBounds.position.y +
                mapTitleBounds.size.y / 2.f
            });

        mapSelectionTitle.setPosition({
            960.f,
            280.f
            });

        //=====================================================
        // Divider texture
        //=====================================================

        if (!dividerTexture.loadFromFile(
            "data/graphics/components/MenuSmallDivider.png"))
        {
            throw std::runtime_error(
                "Could not load menu divider");
        }

        dividerTexture.setSmooth(
            true);

        //=====================================================
        // Map selection dividers
        //=====================================================

        leftDivider.emplace(
            dividerTexture);

        rightDivider.emplace(
            dividerTexture);

        const float dividerScale =
            0.24f;

        leftDivider->setScale({
            dividerScale,
            dividerScale
            });

        rightDivider->setScale({
            -dividerScale,
            dividerScale
            });

        leftDivider->setPosition({
            710.f,
            263.f
            });

        rightDivider->setPosition({
            1210.f,
            263.f
            });

        //=====================================================
        // Number of players title
        //=====================================================

        numberOfPlayersTitle.setString(
            "NUMBER OF PLAYERS");

        numberOfPlayersTitle.setCharacterSize(
            26);

        numberOfPlayersTitle.setFillColor(
            textColour);

        sf::FloatRect numberTitleBounds =
            numberOfPlayersTitle.getLocalBounds();

        numberOfPlayersTitle.setOrigin({
            numberTitleBounds.position.x +
                numberTitleBounds.size.x / 2.f,

            numberTitleBounds.position.y +
                numberTitleBounds.size.y / 2.f
            });

        numberOfPlayersTitle.setPosition({
            960.f,
            565.f
            });

        //=====================================================
        // Number of players dividers
        //=====================================================

        playerLeftDivider.emplace(
            dividerTexture);

        playerRightDivider.emplace(
            dividerTexture);

        const float playerDividerScale =
            0.22f;

        playerLeftDivider->setScale({
            playerDividerScale,
            playerDividerScale
            });

        playerRightDivider->setScale({
            -playerDividerScale,
            playerDividerScale
            });

        playerLeftDivider->setPosition({
            690.f,
            553.f
            });

        playerRightDivider->setPosition({
            1235.f,
            553.f
            });

        //=====================================================
        // Human players title
        //=====================================================

        humanPlayersTitle.setString(
            "HUMAN PLAYERS");

        humanPlayersTitle.setCharacterSize(
            20);

        humanPlayersTitle.setFillColor(
            textColour);

        sf::FloatRect humanTitleBounds =
            humanPlayersTitle.getLocalBounds();

        humanPlayersTitle.setOrigin({
            humanTitleBounds.position.x +
                humanTitleBounds.size.x / 2.f,

            humanTitleBounds.position.y +
                humanTitleBounds.size.y / 2.f
            });

        humanPlayersTitle.setPosition({
            960.f,
            620.f
            });

        //=====================================================
        // Human player selection boxes
        //=====================================================

        const float boxWidth =
            58.f;

        const float boxHeight =
            48.f;

        const float boxGap =
            15.f;

        const float totalBoxWidth =
            (6.f * boxWidth) +
            (5.f * boxGap);

        const float boxStartX =
            960.f -
            (totalBoxWidth / 2.f);

        const float humanBoxY =
            645.f;

        for (int i = 0;
            i < humanPlayerBoxes.size();
            i++)
        {
            humanPlayerBoxes[i].setSize({
                boxWidth,
                boxHeight
                });

            humanPlayerBoxes[i].setPosition({
                boxStartX +
                    (i * (boxWidth + boxGap)),
                humanBoxY
                });

            humanPlayerBoxes[i].setFillColor(
                parchment);

            humanPlayerBoxes[i].setOutlineColor(
                brass);

            humanPlayerBoxes[i].setOutlineThickness(
                2.f);
        }

        humanPlayerBoxes[0].setOutlineColor(
            selectedColour);

        humanPlayerBoxes[0].setOutlineThickness(
            3.f);

        //=====================================================
        // Human player numbers
        //=====================================================

        humanPlayer1Text.setString("1");
        humanPlayer2Text.setString("2");
        humanPlayer3Text.setString("3");
        humanPlayer4Text.setString("4");
        humanPlayer5Text.setString("5");
        humanPlayer6Text.setString("6");

        sf::Text* humanPlayerTexts[] = {
            &humanPlayer1Text,
            &humanPlayer2Text,
            &humanPlayer3Text,
            &humanPlayer4Text,
            &humanPlayer5Text,
            &humanPlayer6Text
        };

        for (int i = 0;
            i < 6;
            i++)
        {
            humanPlayerTexts[i]
                ->setCharacterSize(
                    22);

            humanPlayerTexts[i]
                ->setFillColor(
                    textColour);

            sf::FloatRect bounds =
                humanPlayerTexts[i]
                ->getLocalBounds();

            humanPlayerTexts[i]
                ->setOrigin({
                    bounds.position.x +
                        bounds.size.x / 2.f,

                    bounds.position.y +
                        bounds.size.y / 2.f
                    });

            humanPlayerTexts[i]
                ->setPosition({
                    boxStartX +
                        (i * (boxWidth + boxGap)) +
                        (boxWidth / 2.f),

                    humanBoxY +
                        (boxHeight / 2.f)
                    });
        }

        //=====================================================
        // AI players title
        //=====================================================

        aiPlayersTitle.setString(
            "AI PLAYERS");

        aiPlayersTitle.setCharacterSize(
            20);

        aiPlayersTitle.setFillColor(
            textColour);

        sf::FloatRect aiTitleBounds =
            aiPlayersTitle.getLocalBounds();

        aiPlayersTitle.setOrigin({
            aiTitleBounds.position.x +
                aiTitleBounds.size.x / 2.f,

            aiTitleBounds.position.y +
                aiTitleBounds.size.y / 2.f
            });

        aiPlayersTitle.setPosition({
            960.f,
            730.f
            });

        //=====================================================
        // AI player selection boxes
        //=====================================================

        const float aiBoxY =
            755.f;

        for (int i = 0;
            i < aiPlayerBoxes.size();
            i++)
        {
            aiPlayerBoxes[i].setSize({
                boxWidth,
                boxHeight
                });

            aiPlayerBoxes[i].setPosition({
                boxStartX +
                    (i * (boxWidth + boxGap)),
                aiBoxY
                });

            aiPlayerBoxes[i].setFillColor(
                parchment);

            aiPlayerBoxes[i].setOutlineColor(
                brass);

            aiPlayerBoxes[i].setOutlineThickness(
                2.f);
        }

        aiPlayerBoxes[2].setOutlineColor(
            selectedColour);

        aiPlayerBoxes[2].setOutlineThickness(
            3.f);

        //=====================================================
        // AI player numbers
        //=====================================================

        aiPlayer0Text.setString("0");
        aiPlayer1Text.setString("1");
        aiPlayer2Text.setString("2");
        aiPlayer3Text.setString("3");
        aiPlayer4Text.setString("4");
        aiPlayer5Text.setString("5");

        sf::Text* aiPlayerTexts[] = {
            &aiPlayer0Text,
            &aiPlayer1Text,
            &aiPlayer2Text,
            &aiPlayer3Text,
            &aiPlayer4Text,
            &aiPlayer5Text
        };

        for (int i = 0;
            i < 6;
            i++)
        {
            aiPlayerTexts[i]
                ->setCharacterSize(
                    22);

            aiPlayerTexts[i]
                ->setFillColor(
                    textColour);

            sf::FloatRect bounds =
                aiPlayerTexts[i]
                ->getLocalBounds();

            aiPlayerTexts[i]
                ->setOrigin({
                    bounds.position.x +
                        bounds.size.x / 2.f,

                    bounds.position.y +
                        bounds.size.y / 2.f
                    });

            aiPlayerTexts[i]
                ->setPosition({
                    boxStartX +
                        (i * (boxWidth + boxGap)) +
                        (boxWidth / 2.f),

                    aiBoxY +
                        (boxHeight / 2.f)
                    });
        }

        //=====================================================
        // Start button
        //=====================================================

        startButton.setSize({
            240.f,
            60.f
            });

        startButton.setPosition({
            840.f,
            850.f
            });

        startButton.setFillColor(
            parchment);

        startButton.setOutlineColor(
            brass);

        startButton.setOutlineThickness(
            2.f);

        startButtonText.setString(
            "START GAME");

        startButtonText.setCharacterSize(
            22);

        startButtonText.setFillColor(
            textColour);

        sf::FloatRect startTextBounds =
            startButtonText.getLocalBounds();

        startButtonText.setOrigin({
            startTextBounds.position.x +
                startTextBounds.size.x / 2.f,

            startTextBounds.position.y +
                startTextBounds.size.y / 2.f
            });

        startButtonText.setPosition({
            960.f,
            880.f
            });

        //=====================================================
        // Debug grid
        //=====================================================

        debugGrid.emplace();
    }
    //=========================================================
    // Menu draw method
    //=========================================================

    void MenuUI::draw(
        sf::RenderWindow& window)
    {
        if (backgroundSprite)
        {
            window.draw(
                *backgroundSprite,
                &desaturationShader);
        }

        // Background haze
        window.draw(
            backgroundDampener);

        // Parchment sits behind decorative frame
        window.draw(
            parchmentBacking);

        if (menuFrameSprite)
        {
            window.draw(
                *menuFrameSprite);
        }

        //=====================================================
        // Menu title
        //=====================================================

        window.draw(
            title);

        //=====================================================
        // Map selection
        //=====================================================

        if (leftDivider)
        {
            window.draw(
                *leftDivider);
        }

        if (rightDivider)
        {
            window.draw(
                *rightDivider);
        }

        window.draw(
            mapSelectionTitle);

        if (mapSelector)
        {
            mapSelector->draw(
                window);
        }

        //=====================================================
        // Number of players
        //=====================================================

        if (playerLeftDivider)
        {
            window.draw(
                *playerLeftDivider);
        }

        if (playerRightDivider)
        {
            window.draw(
                *playerRightDivider);
        }

        window.draw(
            numberOfPlayersTitle);

        //=====================================================
        // Human players
        //=====================================================

        window.draw(
            humanPlayersTitle);

        for (const auto& box :
            humanPlayerBoxes)
        {
            window.draw(
                box);
        }

        window.draw(
            humanPlayer1Text);

        window.draw(
            humanPlayer2Text);

        window.draw(
            humanPlayer3Text);

        window.draw(
            humanPlayer4Text);

        window.draw(
            humanPlayer5Text);

        window.draw(
            humanPlayer6Text);

        //=====================================================
        // AI players
        //=====================================================

        window.draw(
            aiPlayersTitle);

        for (const auto& box :
            aiPlayerBoxes)
        {
            window.draw(
                box);
        }

        window.draw(
            aiPlayer0Text);

        window.draw(
            aiPlayer1Text);

        window.draw(
            aiPlayer2Text);

        window.draw(
            aiPlayer3Text);

        window.draw(
            aiPlayer4Text);

        window.draw(
            aiPlayer5Text);

        //=====================================================
        // Start button
        //=====================================================

        window.draw(
            startButton);

        window.draw(
            startButtonText);

        //=====================================================
        // Debug grid - always last
        //=====================================================

        /*if (debugGrid)
        {
            debugGrid->draw(
                window);
        }*/
    }

    //=========================================================
    // Event handling method
    //=========================================================

    void MenuUI::handleEvent(
        const sf::Event& event,
        sf::RenderWindow& window)
    {
        if (const auto* mousePressed =
            event.getIf<
            sf::Event::MouseButtonPressed>())
        {
            if (mousePressed->button ==
                sf::Mouse::Button::Left)
            {
                sf::Vector2f mousePosition =
                    window.mapPixelToCoords(
                        mousePressed->position);

                //=============================================
                // Human player selection
                //=============================================

                for (int i = 0;
                    i < humanPlayerBoxes.size();
                    i++)
                {
                    if (humanPlayerBoxes[i]
                        .getGlobalBounds()
                        .contains(mousePosition))
                    {
                        setHumanPlayerNumbers(
                            i + 1);

                        for (auto& box :
                            humanPlayerBoxes)
                        {
                            box.setOutlineColor(
                                sf::Color(
                                    128,
                                    105,
                                    65));

                            box.setOutlineThickness(
                                2.f);
                        }

                        humanPlayerBoxes[i]
                            .setOutlineColor(
                                sf::Color(
                                    155,
                                    70,
                                    55));

                        humanPlayerBoxes[i]
                            .setOutlineThickness(
                                3.f);

                        int maximumAiPlayers =
                            6 -
                            humanPlayerNumbers;

                        if (aiPlayerNumbers >
                            maximumAiPlayers)
                        {
                            setAiPlayerNumbers(
                                maximumAiPlayers);
                        }

                        for (auto& box :
                            aiPlayerBoxes)
                        {
                            box.setOutlineColor(
                                sf::Color(
                                    128,
                                    105,
                                    65));

                            box.setOutlineThickness(
                                2.f);
                        }

                        aiPlayerBoxes[
                            aiPlayerNumbers]
                            .setOutlineColor(
                                sf::Color(
                                    155,
                                    70,
                                    55));

                        aiPlayerBoxes[
                            aiPlayerNumbers]
                            .setOutlineThickness(
                                3.f);

                        sf::Text* aiPlayerTexts[] = {
                            &aiPlayer0Text,
                            &aiPlayer1Text,
                            &aiPlayer2Text,
                            &aiPlayer3Text,
                            &aiPlayer4Text,
                            &aiPlayer5Text
                        };

                        for (int ai = 0;
                            ai < 6;
                            ai++)
                        {
                            if (ai >
                                maximumAiPlayers)
                            {
                                aiPlayerTexts[ai]
                                    ->setString("X");
                            }
                            else
                            {
                                aiPlayerTexts[ai]
                                    ->setString(
                                        std::to_string(
                                            ai));
                            }
                        }
                    }
                }

                //=============================================
                // AI player selection
                //=============================================

                for (int i = 0;
                    i < aiPlayerBoxes.size();
                    i++)
                {
                    if (aiPlayerBoxes[i]
                        .getGlobalBounds()
                        .contains(mousePosition))
                    {
                        int maximumAiPlayers =
                            6 -
                            humanPlayerNumbers;

                        if (i <=
                            maximumAiPlayers)
                        {
                            setAiPlayerNumbers(
                                i);

                            for (auto& box :
                                aiPlayerBoxes)
                            {
                                box.setOutlineColor(
                                    sf::Color(
                                        128,
                                        105,
                                        65));

                                box.setOutlineThickness(
                                    2.f);
                            }

                            aiPlayerBoxes[i]
                                .setOutlineColor(
                                    sf::Color(
                                        155,
                                        70,
                                        55));

                            aiPlayerBoxes[i]
                                .setOutlineThickness(
                                    3.f);
                        }
                    }
                }

                //=============================================
                // Start button selection
                //=============================================

                if (startButton
                    .getGlobalBounds()
                    .contains(mousePosition))
                {
                    GameStarted = true;

                    startButton.setOutlineColor(
                        sf::Color(
                            155,
                            70,
                            55));

                    startButton.setOutlineThickness(
                        3.f);
                }
            }
        }
    }

    //=========================================================
    // Setter methods
    //=========================================================

    void MenuUI::setMapSelection(
        MapType mapSelection)
    {
        this->mapSelection =
            mapSelection;
    }

    void MenuUI::setHumanPlayerNumbers(
        int number)
    {
        humanPlayerNumbers =
            number;
    }

    void MenuUI::setAiPlayerNumbers(
        int number)
    {
        aiPlayerNumbers =
            number;
    }

    void MenuUI::setGameStarted()
    {
        GameStarted = true;
    }

    //=========================================================
    // Getter methods
    //=========================================================

    MapType MenuUI::getMapSelection() const
    {
        return mapSelection;
    }

    int MenuUI::getHumanPlayerNumbers() const
    {
        return humanPlayerNumbers;
    }

    int MenuUI::getAiPlayerNumbers() const
    {
        return aiPlayerNumbers;
    }

    bool MenuUI::isGameStarted() const
    {
        return GameStarted;
    }

} // namespace risk