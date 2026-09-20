#include "risk/graphics/ui/ProfileUI.h"

#include "risk/core/session/GameSetupState.h"
#include "risk/graphics/game_elements/PlayerGraphics.h"

#include <stdexcept>
#include <string>
#include <iostream>

namespace risk {

    ProfileUI::ProfileUI(
        sf::Font& font
    )
        : font(font),
        titleText(font),
        nameLabel(font),
        avatarLabel(font),
        startGameText(font),
        nameInputText(font),
        avatarSprites{
            sf::Sprite(avatarTextures[0]),
            sf::Sprite(avatarTextures[1]),
            sf::Sprite(avatarTextures[2])
        }
    {
        // -------------------------
        // Main panel
        // -------------------------

        backgroundPanel.setSize({
            900.0f,
            650.0f
            });

        backgroundPanel.setPosition({
            510.0f,
            180.0f
            });

        backgroundPanel.setFillColor(
            sf::Color(20, 55, 75, 230)
        );

        backgroundPanel.setOutlineThickness(3.0f);

        backgroundPanel.setOutlineColor(
            sf::Color(110, 150, 170)
        );


        // -------------------------
        // Title
        // -------------------------

        titleText.setCharacterSize(42);

        titleText.setFillColor(
            sf::Color::White
        );

        titleText.setPosition({
            760.0f,
            210.0f
            });


        // -------------------------
        // Name input
        // -------------------------

        nameLabel.setString(
            "Enter your name:"
        );

        nameLabel.setCharacterSize(20);

        nameLabel.setFillColor(
            sf::Color::White
        );

        nameLabel.setPosition({
            650.0f,
            300.0f
            });


        nameInputBox.setSize({
            620.0f,
            55.0f
            });

        nameInputBox.setPosition({
            650.0f,
            330.0f
            });

        nameInputBox.setFillColor(
            sf::Color(15, 40, 55)
        );

        nameInputBox.setOutlineThickness(2.0f);

        nameInputBox.setOutlineColor(
            sf::Color(170, 190, 200)
        );


        nameInputText.setString(
            "Player Name..."
        );

        nameInputText.setCharacterSize(20);

        nameInputText.setFillColor(
            sf::Color(140, 150, 160)
        );

        nameInputText.setPosition({
            665.0f,
            345.0f
            });


        // -------------------------
        // Avatar heading
        // -------------------------

        avatarLabel.setString(
            "CHOOSE YOUR AVATAR"
        );

        avatarLabel.setCharacterSize(24);

        avatarLabel.setFillColor(
            sf::Color::White
        );

        avatarLabel.setPosition({
            810.0f,
            420.0f
            });


        // -------------------------
        // Avatar boxes
        // -------------------------

        const float avatarWidth = 170.0f;
        const float avatarHeight = 170.0f;
        const float avatarGap = 30.0f;

        const float startX = 675.0f;
        const float startY = 470.0f;

        for (int i = 0; i < 3; ++i)
        {
            avatarBoxes[i].setSize({
                avatarWidth,
                avatarHeight
                });

            avatarBoxes[i].setPosition({
                startX + (i * (avatarWidth + avatarGap)),
                startY
                });

            avatarBoxes[i].setFillColor(
                sf::Color(20, 50, 70)
            );

            avatarBoxes[i].setOutlineThickness(2.0f);

            avatarBoxes[i].setOutlineColor(
                sf::Color(120, 150, 170)
            );
        }


        // -------------------------
        // Avatar images
        // -------------------------

        const std::array<std::string, 3> avatarPaths =
        {
            "C:/Users/joshk/programming/risk_V1/data/graphics/avatars/nelson.png",
            "C:/Users/joshk/programming/risk_V1/data/graphics/avatars/samurai.png",
            "C:/Users/joshk/programming/risk_V1/data/graphics/avatars/viking.png"
        };

        for (int i = 0; i < 3; ++i)
        {
            if (!avatarTextures[i].loadFromFile(
                avatarPaths[i]
            ))
            {
                throw std::runtime_error(
                    "Could not load avatar: " +
                    avatarPaths[i]
                );
            }

            std::cout << "Avatar " << i
                << " loaded: "
                << avatarTextures[i].getSize().x
                << " x "
                << avatarTextures[i].getSize().y
                << '\n';

            avatarSprites[i].setTexture(
                avatarTextures[i]
            );

            avatarSprites[i].setTextureRect(
                sf::IntRect(
                    { 0, 0 },
                    {
                        static_cast<int>(
                            avatarTextures[i].getSize().x
                        ),
                        static_cast<int>(
                            avatarTextures[i].getSize().y
                        )
                    }
                )
            );

            sf::Vector2u textureSize =
                avatarTextures[i].getSize();

            avatarSprites[i].setScale({
                150.0f /
                    static_cast<float>(textureSize.x),

                150.0f /
                    static_cast<float>(textureSize.y)
                });

            avatarSprites[i].setPosition({
                startX +
                    (i * (avatarWidth + avatarGap)) +
                    10.0f,

                startY + 10.0f
                });
        }


        // -------------------------
        // Start Game button
        // -------------------------

        startGameButton.setSize({
            300.0f,
            65.0f
            });

        startGameButton.setPosition({
            810.0f,
            690.0f
            });

        startGameButton.setFillColor(
            sf::Color(90, 115, 130)
        );

        startGameButton.setOutlineThickness(2.0f);

        startGameButton.setOutlineColor(
            sf::Color(170, 190, 200)
        );


        startGameText.setString(
            "START GAME"
        );

        startGameText.setCharacterSize(22);

        startGameText.setFillColor(
            sf::Color::White
        );

        startGameText.setPosition({
            885.0f,
            710.0f
            });
    }


    // -------------------------
    // Handle profile input
    // -------------------------

    void ProfileUI::handleEvent(
        const sf::Event& event,
        sf::RenderWindow& window,
        int playerID,
        PlayerGraphics& playerGraphics,
        GameSetupState& gameSetupState
    )
    {
        // -------------------------
        // Mouse input
        // -------------------------

        if (const auto* mouseButton =
            event.getIf<sf::Event::MouseButtonPressed>())
        {
            sf::Vector2f mousePosition =
                window.mapPixelToCoords(
                    mouseButton->position
                );

            // -------------------------
            // Check avatar selection
            // -------------------------

            for (int avatarID = 0; avatarID < 3; ++avatarID)
            {
                if (avatarBoxes[avatarID]
                    .getGlobalBounds()
                    .contains(mousePosition))
                {
                    setAvatar(
                        avatarID,
                        playerGraphics
                    );

                    gameSetupState.updateAvatar(
                        playerID
                    );

                    return;
                }
            }


            // -------------------------
            // Check Start Game button
            // -------------------------

            if (startGameButton
                .getGlobalBounds()
                .contains(mousePosition))
            {
                if (!playerName.empty())
                {
                    setPlayerName(
                        playerID,
                        playerGraphics,
                        gameSetupState
                    );
                }

                setGameSetupStateProfile(
                    playerID,
                    gameSetupState
                );

                return;
            }
        }


        // -------------------------
        // Keyboard / name input
        // -------------------------

        if (const auto* textEntered =
            event.getIf<sf::Event::TextEntered>())
        {
            char32_t unicode =
                textEntered->unicode;


            // -------------------------
            // Backspace
            // -------------------------

            if (unicode == 8)
            {
                if (!playerName.empty())
                {
                    playerName.pop_back();
                }
            }


            // -------------------------
            // Enter
            // -------------------------

            else if (unicode == 13)
            {
                if (!playerName.empty())
                {
                    setPlayerName(
                        playerID,
                        playerGraphics,
                        gameSetupState
                    );
                }
            }


            // -------------------------
            // Normal printable characters
            // -------------------------

            else if (unicode >= 32 &&
                unicode <= 126)
            {
                playerName +=
                    static_cast<char>(unicode);
            }


            // -------------------------
            // Update displayed text
            // -------------------------

            if (playerName.empty())
            {
                nameInputText.setString(
                    "Player Name..."
                );

                nameInputText.setFillColor(
                    sf::Color(140, 150, 160)
                );
            }
            else
            {
                nameInputText.setString(
                    playerName
                );

                nameInputText.setFillColor(
                    sf::Color::White
                );
            }
        }
    }


    // -------------------------
    // Set avatar
    // -------------------------

    void ProfileUI::setAvatar(
        int avatarID,
        PlayerGraphics& playerGraphics
    )
    {
        selectedAvatar = avatarID;

        // Reset all avatar outlines
        for (auto& avatarBox : avatarBoxes)
        {
            avatarBox.setOutlineThickness(
                2.0f
            );

            avatarBox.setOutlineColor(
                sf::Color(120, 150, 170)
            );
        }

        // Highlight selected avatar
        avatarBoxes[avatarID].setOutlineThickness(
            6.0f
        );

        avatarBoxes[avatarID].setOutlineColor(
            sf::Color::White
        );

        // Update PlayerGraphics
        playerGraphics.setAvatar(
            avatarID
        );
    }


    // -------------------------
    // Set player name
    // -------------------------

    void ProfileUI::setPlayerName(
        int playerID,
        PlayerGraphics& playerGraphics,
        GameSetupState& gameSetupState
    )
    {
        playerGraphics.setName(
            playerName
        );

        gameSetupState.updateName(
            playerID
        );
    }


    // -------------------------
    // Complete current profile
    // -------------------------

    void ProfileUI::setGameSetupStateProfile(
        int playerID,
        GameSetupState& gameSetupState
    )
    {
        // DEBUG
        std::cout
            << "START GAME clicked - playerID: "
            << playerID
            << '\n';

        std::cout
            << "profilesDone: "
            << gameSetupState.profilesDone()
            << '\n';


        if (gameSetupState.profilesDone())
        {
            // DEBUG
            std::cout
                << "Setting profilesReady TRUE\n";

            gameSetupState.resetCurrentProfile();
            gameSetupState.updateProfilesReady();
        }
        else
        {
            // DEBUG
            std::cout
                << "Advancing profile from: "
                << playerID
                << '\n';

            gameSetupState.setCurrentProfile(
                playerID
            );

            // DEBUG
            std::cout
                << "Current profile is now: "
                << gameSetupState.getCurrentProfileID()
                << '\n';


            // Reset temporary ProfileUI state
            playerName.clear();
            selectedAvatar = -1;

            nameInputText.setString(
                "Player Name..."
            );

            nameInputText.setFillColor(
                sf::Color(140, 150, 160)
            );

            // Reset avatar outlines
            for (auto& avatarBox : avatarBoxes)
            {
                avatarBox.setOutlineThickness(
                    2.0f
                );

                avatarBox.setOutlineColor(
                    sf::Color(120, 150, 170)
                );
            }
        }
    }


    // -------------------------
    // Draw profile UI
    // -------------------------

    void ProfileUI::profileUIdraw(
        sf::RenderWindow& window,
        int playerID
    )
    {
        titleText.setString(
            "PLAYER " +
            std::to_string(playerID + 1) +
            " SETUP"
        );

        window.draw(backgroundPanel);

        window.draw(titleText);

        window.draw(nameLabel);
        window.draw(nameInputBox);
        window.draw(nameInputText);

        window.draw(avatarLabel);

        for (int i = 0; i < 3; ++i)
        {
            window.draw(avatarBoxes[i]);
            window.draw(avatarSprites[i]);
        }

        window.draw(startGameButton);
        window.draw(startGameText);
    }

} // namespace risk