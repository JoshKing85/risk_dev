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
        // -----------------------------
        // Default colour
        // -----------------------------

        playerColour =
            sf::Color(100, 100, 100);

        // -----------------------------
        // Player panel
        // -----------------------------

        playerPanel.setSize(
            panelSize
        );

        playerPanel.setFillColor(
            sf::Color(0, 0, 0, 100)
        );

        playerPanel.setOutlineColor(
            playerColour
        );

        playerPanel.setOutlineThickness(
            3.0f
        );

        // -----------------------------
        // Avatar
        // -----------------------------

        if (!avatarTexture.loadFromFile(
            blankAvatarPath
        ))
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

        playerName =
            "Player " +
            std::to_string(
                playerID + 1
            );

        playerNameText.setString(
            playerName
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
            std::to_string(
                troopCount
            )
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
            std::to_string(
                cardCount
            )
        );

        cardCountText.setCharacterSize(
            18
        );

        cardCountText.setFillColor(
            sf::Color::White
        );

        // -----------------------------
        // Position player graphics
        // -----------------------------

        setPlayerID(
            playerID
        );
    }


    void PlayerGraphics::setPlayerID(
        int newPlayerID
    )
    {
        playerID =
            newPlayerID;

        // -----------------------------
        // Player position
        // -----------------------------

        switch (playerID)
        {
        case 0:
            playerPosition = {
                0.0f,
                835.0f
            };
            break;

        case 1:
            playerPosition = {
                320.0f,
                835.0f
            };
            break;

        case 2:
            playerPosition = {
                640.0f,
                835.0f
            };
            break;

        case 3:
            playerPosition = {
                960.0f,
                835.0f
            };
            break;

        case 4:
            playerPosition = {
                1280.0f,
                835.0f
            };
            break;

        case 5:
            playerPosition = {
                1600.0f,
                835.0f
            };
            break;

        default:
            playerPosition = {
                0.0f,
                0.0f
            };
            break;
        }

        // -----------------------------
        // Panel
        // -----------------------------

        playerPanel.setPosition(
            playerPosition
        );

        // -----------------------------
        // Avatar
        // -----------------------------

        avatarSprite.setPosition(
            {
                playerPosition.x +
                    15.0f,

                playerPosition.y +
                    45.0f
            }
        );

        // -----------------------------
        // Text
        // -----------------------------

        playerNameText.setPosition(
            {
                playerPosition.x +
                    180.0f,

                playerPosition.y +
                    45.0f
            }
        );

        troopCountText.setPosition(
            {
                playerPosition.x +
                    180.0f,

                playerPosition.y +
                    90.0f
            }
        );

        cardCountText.setPosition(
            {
                playerPosition.x +
                    180.0f,

                playerPosition.y +
                    125.0f
            }
        );
    }


    void PlayerGraphics::setName(
        const std::string& name
    )
    {
        playerName =
            name;

        playerNameText.setString(
            playerName
        );
    }


    void PlayerGraphics::setTroopCount(
        int newCount
    )
    {
        troopCount =
            newCount;

        troopCountText.setString(
            "Troops: " +
            std::to_string(
                troopCount
            )
        );
    }


    void PlayerGraphics::setCardCount(
        int newCount
    )
    {
        cardCount =
            newCount;

        cardCountText.setString(
            "Cards: " +
            std::to_string(
                cardCount
            )
        );
    }


    void PlayerGraphics::setAvatar(
        int newAvatarID
    )
    {
        avatarID =
            newAvatarID;

        std::string avatarPath;

        // -----------------------------
        // Avatar / faction
        // -----------------------------

        switch (avatarID)
        {
            // Napoleon - France
        case 0:
            avatarPath =
                "data/graphics/avatars/NapoleonAvatar.png";

            playerColour =
                sf::Color(
                    60,
                    100,
                    180
                );
            break;

            // Wellington - Britain
        case 1:
            avatarPath =
                "data/graphics/avatars/WellingtonAvatar.png";

            playerColour =
                sf::Color(
                    180,
                    60,
                    60
                );
            break;

            // Blucher - Prussia
        case 2:
            avatarPath =
                "data/graphics/avatars/BulcherAvatar.png";

            playerColour =
                sf::Color(
                    35,
                    35,
                    35
                );
            break;

            // Austria
        case 3:
            avatarPath =
                "data/graphics/avatars/VonAvatar.png";

            playerColour =
                sf::Color(
                    220,
                    220,
                    210
                );
            break;

            // Spain
        case 4:
            avatarPath =
                "data/graphics/avatars/NeedleAvatar.png";

            playerColour =
                sf::Color(
                    190,
                    155,
                    45
                );
            break;

            // Alexander - Russia
        case 5:
            avatarPath =
                "data/graphics/avatars/AlexanderAvatar.png";

            playerColour =
                sf::Color(
                    60,
                    140,
                    75
                );
            break;

        default:
            avatarPath =
                blankAvatarPath;

            playerColour =
                sf::Color(
                    100,
                    100,
                    100
                );
            break;
        }

        // -----------------------------
        // Load avatar
        // -----------------------------

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
                        avatarTexture
                            .getSize().x
                    ),

                    static_cast<int>(
                        avatarTexture
                            .getSize().y
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
        // Apply faction colour
        // -----------------------------

        playerPanel.setOutlineColor(
            playerColour
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
        sf::RenderWindow& window) const
    {
        window.draw(
            playerPanel
        );

        window.draw(
            avatarSprite
        );

        window.draw(
            playerNameText
        );

        window.draw(
            troopCountText
        );

        window.draw(
            cardCountText
        );
    }


    int PlayerGraphics::getPlayerID() const
    {
        return playerID;
    }


    int PlayerGraphics::getAvatarID() const
    {
        return avatarID;
    }


    std::string PlayerGraphics::getName() const
    {
        return playerName;
    }

} // namespace risk