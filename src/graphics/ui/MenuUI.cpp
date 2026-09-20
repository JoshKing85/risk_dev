#include "risk/graphics/ui/MenuUI.h"

namespace risk {

    MenuUI::MenuUI()
        : mapSelection(MapType::Classic),
        humanPlayerNumbers(1),
        aiPlayerNumbers(2),
        title(font),
        mapSelectionTitle(font),
        classicMapText(font),
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
        // Main menu box
        //=====================================================

        menuBox.setSize({ 700.f, 600.f });
        menuBox.setPosition({ 250.f, 60.f });
        menuBox.setFillColor(sf::Color::White);
        menuBox.setOutlineColor(sf::Color::Black);
        menuBox.setOutlineThickness(3.f);

        //=====================================================
        // Font
        //=====================================================

        font.openFromFile("C:/Windows/Fonts/arial.ttf");

        //=====================================================
        // Menu title
        //=====================================================

        title.setString("MENU");
        title.setCharacterSize(40);
        title.setFillColor(sf::Color::Black);
        title.setPosition({ 535.f, 80.f });

        //=====================================================
        // Map selection title
        //=====================================================

        mapSelectionTitle.setString("Map Selection");
        mapSelectionTitle.setCharacterSize(24);
        mapSelectionTitle.setFillColor(sf::Color::Black);
        mapSelectionTitle.setPosition({ 525.f, 135.f });

        //=====================================================
        // Classic map button
        //=====================================================

        classicMapBox.setSize({ 150.f, 50.f });
        classicMapBox.setPosition({ 320.f, 175.f });
        classicMapBox.setFillColor(sf::Color::White);
        classicMapBox.setOutlineColor(sf::Color::Red);
        classicMapBox.setOutlineThickness(2.f);

        classicMapText.setString("Classic");
        classicMapText.setCharacterSize(22);
        classicMapText.setFillColor(sf::Color::Black);
        classicMapText.setPosition({ 355.f, 185.f });

        //=====================================================
        // Number of players title
        //=====================================================

        numberOfPlayersTitle.setString("Number of Players");
        numberOfPlayersTitle.setCharacterSize(24);
        numberOfPlayersTitle.setFillColor(sf::Color::Black);
        numberOfPlayersTitle.setPosition({ 520.f, 260.f });

        //=====================================================
        // Human players title
        //=====================================================

        humanPlayersTitle.setString("Human Players");
        humanPlayersTitle.setCharacterSize(20);
        humanPlayersTitle.setFillColor(sf::Color::Black);
        humanPlayersTitle.setPosition({ 525.f, 300.f });

        //=====================================================
        // Human player selection boxes
        //=====================================================

        for (int i = 0; i < humanPlayerBoxes.size(); i++)
        {
            humanPlayerBoxes[i].setSize({ 70.f, 50.f });

            humanPlayerBoxes[i].setPosition({
                328.f + (i * 95.f),
                335.f
                });

            humanPlayerBoxes[i].setFillColor(sf::Color::White);
            humanPlayerBoxes[i].setOutlineColor(sf::Color::Black);
            humanPlayerBoxes[i].setOutlineThickness(2.f);
        }

        // Default human player selection
        humanPlayerBoxes[0].setOutlineColor(sf::Color::Red);

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

        for (int i = 0; i < 6; i++)
        {
            humanPlayerTexts[i]->setCharacterSize(22);
            humanPlayerTexts[i]->setFillColor(sf::Color::Black);

            humanPlayerTexts[i]->setPosition({
                357.f + (i * 95.f),
                345.f
                });
        }

        //=====================================================
        // AI players title
        //=====================================================

        aiPlayersTitle.setString("AI Players");
        aiPlayersTitle.setCharacterSize(20);
        aiPlayersTitle.setFillColor(sf::Color::Black);
        aiPlayersTitle.setPosition({ 550.f, 410.f });

        //=====================================================
        // AI player selection boxes
        //=====================================================

        for (int i = 0; i < aiPlayerBoxes.size(); i++)
        {
            aiPlayerBoxes[i].setSize({ 70.f, 50.f });

            aiPlayerBoxes[i].setPosition({
                328.f + (i * 95.f),
                445.f
                });

            aiPlayerBoxes[i].setFillColor(sf::Color::White);
            aiPlayerBoxes[i].setOutlineColor(sf::Color::Black);
            aiPlayerBoxes[i].setOutlineThickness(2.f);
        }

        // Default AI selection = 2
        aiPlayerBoxes[2].setOutlineColor(sf::Color::Red);

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

        for (int i = 0; i < 6; i++)
        {
            aiPlayerTexts[i]->setCharacterSize(22);
            aiPlayerTexts[i]->setFillColor(sf::Color::Black);

            aiPlayerTexts[i]->setPosition({
                357.f + (i * 95.f),
                455.f
                });
        }
        //=====================================================
		// Start button
        //=====================================================
		startButton.setSize({ 150.f, 50.f });
        startButton.setPosition({ 500.f, 600.f });
		startButton.setFillColor(sf::Color::White);
		startButton.setOutlineColor(sf::Color::Black);
		startButton.setOutlineThickness(2.f);

		startButtonText.setString("Start Game");
        startButtonText.setCharacterSize(22);
        startButtonText.setFillColor(sf::Color::Black);
		startButtonText.setPosition({ 520.f, 610.f });
    }

    //=========================================================
    // Menu draw method
    //=========================================================

    void MenuUI::draw(sf::RenderWindow& window)
    {
        window.draw(menuBox);

        //=====================================================
        // Menu title
        //=====================================================

        window.draw(title);

        //=====================================================
        // Map selection
        //=====================================================

        window.draw(mapSelectionTitle);
        window.draw(classicMapBox);
        window.draw(classicMapText);

        //=====================================================
        // Player selection title
        //=====================================================

        window.draw(numberOfPlayersTitle);

        //=====================================================
        // Human player selection
        //=====================================================

        window.draw(humanPlayersTitle);

        for (auto& box : humanPlayerBoxes)
        {
            window.draw(box);
        }

        window.draw(humanPlayer1Text);
        window.draw(humanPlayer2Text);
        window.draw(humanPlayer3Text);
        window.draw(humanPlayer4Text);
        window.draw(humanPlayer5Text);
        window.draw(humanPlayer6Text);

        //=====================================================
        // AI player selection
        //=====================================================

        window.draw(aiPlayersTitle);

        for (auto& box : aiPlayerBoxes)
        {
            window.draw(box);
        }

        window.draw(aiPlayer0Text);
        window.draw(aiPlayer1Text);
        window.draw(aiPlayer2Text);
        window.draw(aiPlayer3Text);
        window.draw(aiPlayer4Text);
        window.draw(aiPlayer5Text);

       //=====================================================
       // start Button
       //=====================================================
		window.draw(startButton);
		window.draw(startButtonText);
    }

    //=========================================================
    // Event handling method
    //=========================================================

    void MenuUI::handleEvent(
        const sf::Event& event,
        sf::RenderWindow& window
    )
    {
        if (const auto* mousePressed =
            event.getIf<sf::Event::MouseButtonPressed>())
        {
            if (mousePressed->button == sf::Mouse::Button::Left)
            {
                sf::Vector2f mousePosition =
                    window.mapPixelToCoords(mousePressed->position);

                //=============================================
                // Map selection
                //=============================================

                if (classicMapBox.getGlobalBounds().contains(mousePosition))
                {
                    setMapSelection(MapType::Classic);
                    classicMapBox.setOutlineColor(sf::Color::Red);
                }

                //=============================================
                // Human player selection
                //=============================================

                for (int i = 0; i < humanPlayerBoxes.size(); i++)
                {
                    if (humanPlayerBoxes[i]
                        .getGlobalBounds()
                        .contains(mousePosition))
                    {
                        setHumanPlayerNumbers(i + 1);

                        // Reset human box outlines
                        for (auto& box : humanPlayerBoxes)
                        {
                            box.setOutlineColor(sf::Color::Black);
                        }

                        humanPlayerBoxes[i]
                            .setOutlineColor(sf::Color::Red);

                        // Maximum AI players allowed
                        int maximumAiPlayers =
                            6 - humanPlayerNumbers;

                        // If current AI selection is now invalid,
                        // reduce it to the maximum valid amount
                        if (aiPlayerNumbers > maximumAiPlayers)
                        {
                            setAiPlayerNumbers(maximumAiPlayers);
                        }

                        // Reset AI outlines
                        for (auto& box : aiPlayerBoxes)
                        {
                            box.setOutlineColor(sf::Color::Black);
                        }

                        // Highlight current AI selection
                        aiPlayerBoxes[aiPlayerNumbers]
                            .setOutlineColor(sf::Color::Red);

                        // Update AI numbers / X values
                        sf::Text* aiPlayerTexts[] = {
                            &aiPlayer0Text,
                            &aiPlayer1Text,
                            &aiPlayer2Text,
                            &aiPlayer3Text,
                            &aiPlayer4Text,
                            &aiPlayer5Text
                        };

                        for (int ai = 0; ai < 6; ai++)
                        {
                            if (ai > maximumAiPlayers)
                            {
                                aiPlayerTexts[ai]->setString("X");
                            }
                            else
                            {
                                aiPlayerTexts[ai]
                                    ->setString(std::to_string(ai));
                            }
                        }
                    }
                }

                //=============================================
                // AI player selection
                //=============================================

                for (int i = 0; i < aiPlayerBoxes.size(); i++)
                {
                    if (aiPlayerBoxes[i]
                        .getGlobalBounds()
                        .contains(mousePosition))
                    {
                        int maximumAiPlayers =
                            6 - humanPlayerNumbers;

                        // Only allow valid AI selections
                        if (i <= maximumAiPlayers)
                        {
                            setAiPlayerNumbers(i);

                            for (auto& box : aiPlayerBoxes)
                            {
                                box.setOutlineColor(sf::Color::Black);
                            }

                            aiPlayerBoxes[i]
                                .setOutlineColor(sf::Color::Red);
                        }
                    }
                }

                //=============================================
				// Start button selection
                //=============================================

                if (startButton.getGlobalBounds().contains(mousePosition))
                {
					GameStarted = true;
                    startButton.setOutlineColor(sf::Color::Red);
                }
            }
        }
    }

    //=========================================================
    // Setter methods
    //=========================================================

    void MenuUI::setMapSelection(MapType mapSelection)
    {
        this->mapSelection = mapSelection;
    }

    void MenuUI::setHumanPlayerNumbers(int number)
    {
        humanPlayerNumbers = number;
    }

    void MenuUI::setAiPlayerNumbers(int number)
    {
        aiPlayerNumbers = number;
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
}