#include "risk/graphics/game_elements/PlayerGraphics.h"

#include <stdexcept>

namespace risk
{

    PlayerGraphics::PlayerGraphics(
        int playerID,
        int troopCount,
        const sf::Font& font
    )
        : playerID(playerID),
        troopCount(troopCount),
        avatarSprite(avatarTexture),
        playerNameText(font),
        troopCountText(font),
        cardCountText(font)
    {
        setPlayerID(playerID);

        // -----------------------------
        // Player panel
        // -----------------------------

        playerPanel.setSize(panelSize);

        playerPanel.setFillColor(
            sf::Color(0, 0, 0, 100)
        );

        playerPanel.setOutlineColor(
            playerColour
        );

        playerPanel.setOutlineThickness(
            3.0f
        );

        playerPanel.setPosition(
            playerPosition
        );

        // -----------------------------
        // Avatar
        // -----------------------------

        if (!avatarTexture.loadFromFile(blankAvatarPath))
        {
            throw std::runtime_error(
                "Could not load blank avatar: " +
                blankAvatarPath
            );
        }

        avatarSprite.setTexture(
            avatarTexture
        );

        avatarSprite.setTextureRect(
            sf::IntRect(
                { 0, 0 },
                {
                    static_cast<int>(
                        avatarTexture.getSize().x
                    ),
                    static_cast<int>(
                        avatarTexture.getSize().y
                    )
                }
            )
        );

        sf::Vector2u textureSize =
            avatarTexture.getSize();

        avatarSprite.setScale(
            {
                avatarSize.x /
                    static_cast<float>(
                        textureSize.x
                    ),

                avatarSize.y /
                    static_cast<float>(
                        textureSize.y
                    )
            }
        );

        // -----------------------------
        // Player name
        // -----------------------------

        playerNameText.setString(
            "Player " +
            std::to_string(playerID + 1)
        );

        playerNameText.setCharacterSize(
            22
        );

        playerNameText.setFillColor(
            sf::Color::White
        );

        // -----------------------------
        // Troop count
        // -----------------------------

        troopCountText.setString(
            "Troops: " +
            std::to_string(troopCount)
        );

        troopCountText.setCharacterSize(
            18
        );

        troopCountText.setFillColor(
            sf::Color::White
        );

        // -----------------------------
        // Card count
        // -----------------------------

        cardCountText.setString(
            "Cards: " +
            std::to_string(cardCount)
        );

        cardCountText.setCharacterSize(
            18
        );

        cardCountText.setFillColor(
            sf::Color::White
        );

        // Position everything now that
        // all graphical objects exist.
        setPlayerID(playerID);
    }


    void PlayerGraphics::setPlayerID(
        int newPlayerID
    )
    {
        playerID = newPlayerID;

        switch (playerID)
        {
        case 0:
            playerPosition = {
                0.0f,
                835.0f
            };

            playerColour =
                sf::Color(180, 60, 60);

            break;

        case 1:
            playerPosition = {
                320.0f,
                835.0f
            };

            playerColour =
                sf::Color(60, 100, 180);

            break;

        case 2:
            playerPosition = {
                640.0f,
                835.0f
            };

            playerColour =
                sf::Color(60, 160, 80);

            break;

        case 3:
            playerPosition = {
                960.0f,
                835.0f
            };

            playerColour =
                sf::Color(180, 150, 60);

            break;

        case 4:
            playerPosition = {
                1280.0f,
                835.0f
            };

            playerColour =
                sf::Color(130, 70, 170);

            break;

        case 5:
            playerPosition = {
                1600.0f,
                835.0f
            };

            playerColour =
                sf::Color(60, 160, 160);

            break;

        default:
            playerPosition = {
                0.0f,
                0.0f
            };

            playerColour =
                sf::Color(100, 100, 100);

            break;
        }

        // -----------------------------
        // Panel
        // -----------------------------

        playerPanel.setPosition(
            playerPosition
        );

        playerPanel.setOutlineColor(
            playerColour
        );

        // -----------------------------
        // Avatar
        // -----------------------------

        avatarSprite.setPosition(
            {
                playerPosition.x + 15.0f,
                playerPosition.y + 45.0f
            }
        );

        // -----------------------------
        // Text
        // -----------------------------

        playerNameText.setPosition(
            {
                playerPosition.x + 180.0f,
                playerPosition.y + 45.0f
            }
        );

        troopCountText.setPosition(
            {
                playerPosition.x + 180.0f,
                playerPosition.y + 90.0f
            }
        );

        cardCountText.setPosition(
            {
                playerPosition.x + 180.0f,
                playerPosition.y + 125.0f
            }
        );
    }


    void PlayerGraphics::setName(
        const std::string& name
    )
    {
        playerNameText.setString(
            name
        );
    }


    void PlayerGraphics::setTroopCount(
        int newCount
    )
    {
        troopCount = newCount;

        troopCountText.setString(
            "Troops: " +
            std::to_string(troopCount)
        );
    }


    void PlayerGraphics::setCardCount(
        int newCount
    )
    {
        cardCount = newCount;

        cardCountText.setString(
            "Cards: " +
            std::to_string(cardCount)
        );
    }


    void PlayerGraphics::setAvatar(
        int avatarID
    )
    {
        std::string avatarPath;

        switch (avatarID)
        {
        case 0:
            avatarPath =
                "C:/Users/joshk/programming/risk_V1/data/graphics/avatars/nelson.png";
            break;

        case 1:
            avatarPath =
                "C:/Users/joshk/programming/risk_V1/data/graphics/avatars/samurai.png";
            break;

        case 2:
            avatarPath =
                "C:/Users/joshk/programming/risk_V1/data/graphics/avatars/viking.png";
            break;

        default:
            avatarPath =
                "C:/Users/joshk/programming/risk_V1/data/graphics/avatars/blank.png";
            break;
        }

        if (!avatarTexture.loadFromFile(
            avatarPath
        ))
        {
            throw std::runtime_error(
                "Could not load avatar: " +
                avatarPath
            );
        }

        avatarSprite.setTexture(
            avatarTexture
        );

        avatarSprite.setTextureRect(
            sf::IntRect(
                { 0, 0 },
                {
                    static_cast<int>(
                        avatarTexture.getSize().x
                    ),
                    static_cast<int>(
                        avatarTexture.getSize().y
                    )
                }
            )
        );

        sf::Vector2u textureSize =
            avatarTexture.getSize();

        avatarSprite.setScale(
            {
                avatarSize.x /
                    static_cast<float>(
                        textureSize.x
                    ),

                avatarSize.y /
                    static_cast<float>(
                        textureSize.y
                    )
            }
        );
    }
    void PlayerGraphics::setActive(
        bool active
    )
    {
        if (active)
        {
            playerPanel.setOutlineColor(
                sf::Color::White
            );

            playerPanel.setOutlineThickness(
                7.0f
            );
        }
        else
        {
            playerPanel.setOutlineColor(
                playerColour
            );

            playerPanel.setOutlineThickness(
                3.0f
            );
        }
    }

    void PlayerGraphics::draw(
        sf::RenderWindow& window
    ) const
    {
        window.draw(playerPanel);
        window.draw(avatarSprite);
        window.draw(playerNameText);
        window.draw(troopCountText);
        window.draw(cardCountText);
    }


    int PlayerGraphics::getPlayerID() const
    {
        return playerID;
    }

} // namespace risk