#include "risk/graphics/game_elements/PlayerGraphics.h"

#include <stdexcept>

namespace risk {

    PlayerGraphics::PlayerGraphics(
        int playerID,
        int troopCount,
        const sf::Font& font)
        : playerID(playerID),
        troopCount(troopCount),
        panelSprite(panelTexture),
        avatarSprite(avatarTexture),
        troopSprite(troopTexture),
        TroopIconSprite(TroopIconTexture),
        CardIconSprite(CardIconTexture),
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
            { 309.0f, 270.0f });

        playerPanel.setFillColor(
            sf::Color(18, 39, 54, 235));

        playerPanel.setOutlineThickness(
            0.0f);

        // -----------------------------
        // Brass panel border
        // -----------------------------

        if (!panelTexture.loadFromFile(
            "data/graphics/components/PanelBorder.png"))
        {
            throw std::runtime_error(
                "Could not load player panel border");
        }

        panelSprite.setTexture(
            panelTexture,
            true);
        

        // -----------------------------
        // Troop icon
        // -----------------------------

        if (!TroopIconTexture.loadFromFile(
            "data/graphics/components/TroopIcon.png"))
        {
            throw std::runtime_error(
                "Could not load troop icon");
        }

        TroopIconSprite.setTexture(
            TroopIconTexture,
            true);

        // -----------------------------
        // Card icon
        // -----------------------------

        if (!CardIconTexture.loadFromFile(
            "data/graphics/components/CardIcon.png"))
        {
            throw std::runtime_error(
                "Could not load card icon");
        }

        CardIconSprite.setTexture(
            CardIconTexture,
            true);

        // -----------------------------
        // Count boxes
        // -----------------------------

        troopCountBox.setSize(
            { 80.0f, 42.0f });

        troopCountBox.setFillColor(
            sf::Color(10, 25, 36, 220));

        troopCountBox.setOutlineColor(
            sf::Color(185, 145, 65));

        troopCountBox.setOutlineThickness(
            1.5f);

        cardCountBox.setSize(
            { 80.0f, 42.0f });

        cardCountBox.setFillColor(
            sf::Color(10, 25, 36, 220));

        cardCountBox.setOutlineColor(
            sf::Color(185, 145, 65));

        cardCountBox.setOutlineThickness(
            1.5f);

        // -----------------------------
        // Player name
        // -----------------------------

        playerName =
            "Player " +
            std::to_string(
                playerID + 1);

        playerNameText.setString(
            playerName);

        playerNameText.setCharacterSize(
            26);

        playerNameText.setFillColor(
            sf::Color(245, 224, 175));

        playerNameText.setOutlineColor(
            sf::Color(35, 25, 15, 230));

        playerNameText.setOutlineThickness(
            1.5f);

        // -----------------------------
        // Troop count
        // -----------------------------

        troopCountText.setString(
            std::to_string(
                troopCount));

        troopCountText.setCharacterSize(
            22);

        troopCountText.setFillColor(
            sf::Color(235, 215, 170));

        // -----------------------------
        // Card count
        // -----------------------------

        cardCountText.setString(
            std::to_string(
                cardCount));

        cardCountText.setCharacterSize(
            22);

        cardCountText.setFillColor(
            sf::Color(235, 215, 170));

        // -----------------------------
        // Position graphics
        // -----------------------------

        setPlayerID(
            playerID);
    }


    void PlayerGraphics::setPlayerID(
        int newPlayerID)
    {
        playerID =
            newPlayerID;

        // -----------------------------
        // Layout
        // -----------------------------

        constexpr float startX =
            30.0f;

        constexpr float startY =
            785.0f;

        constexpr float panelWidth =
            309.0f;

        constexpr float panelHeight =
            270.0f;

        constexpr float gap =
            0.0f;

        playerPosition = {
            startX +
                static_cast<float>(
                    playerID) *
                (panelWidth + gap),

            startY
        };

        // -----------------------------
        // Panel
        // -----------------------------

        playerPanel.setSize(
            {
                panelWidth,
                panelHeight
            });

        playerPanel.setPosition(
            playerPosition);

        // -----------------------------
        // Brass border
        // -----------------------------

        panelSprite.setPosition(
            {
                playerPosition.x,
                playerPosition.y - 5.0f
            });

        panelSprite.setScale(
            {
                1.0f,
                1.0f
            });

        // -----------------------------
        // Avatar
        // -----------------------------

        avatarSprite.setPosition(
            {
                playerPosition.x + 6.0f,
                playerPosition.y + 40.0f
            });

        // -----------------------------
        // Player name
        // -----------------------------

        playerNameText.setPosition(
            {
                playerPosition.x + 23.0f,
                playerPosition.y + 8.0f
            });

        // -----------------------------
        // Troop count
        // -----------------------------

        troopCountBox.setPosition(
            {
                playerPosition.x + 210.0f,
                playerPosition.y + 10.0f
            });

        TroopIconSprite.setPosition(
            {
                playerPosition.x + 212.0f,
                playerPosition.y + 5.0f
            });

        troopCountText.setPosition(
            {
                playerPosition.x + 263.0f,
                playerPosition.y + 17.0f
            });

        // -----------------------------
        // Card count
        // -----------------------------

        cardCountBox.setPosition(
            {
                playerPosition.x + 210.0f,
                playerPosition.y + 45.0f
            });

        CardIconSprite.setPosition(
            {
                playerPosition.x + 212.0f,
                playerPosition.y + 42.0f
            });

        cardCountText.setPosition(
            {
                playerPosition.x + 263.0f,
                playerPosition.y + 52.0f
            });
    }


    void PlayerGraphics::setName(
        const std::string& name)
    {
        playerName =
            name;

        playerNameText.setString(
            playerName);
    }


    void PlayerGraphics::setTroopCount(
        int newCount)
    {
        troopCount =
            newCount;

        troopCountText.setString(
            std::to_string(
                troopCount));
    }


    void PlayerGraphics::setCardCount(
        int newCount)
    {
        cardCount =
            newCount;

        cardCountText.setString(
            std::to_string(
                cardCount));
    }


    void PlayerGraphics::setAvatar(
        int newAvatarID)
    {
        avatarID =
            newAvatarID;

        std::string avatarPath;
        std::string troopPath;

        sf::Vector2f troopOffset =
        { 208.0f, 105.0f };

        // -----------------------------
        // Avatar / faction / troop
        // -----------------------------

        switch (avatarID)
        {
        case 0:
            avatarPath =
                "data/graphics/board/NapoleonBoardAvatar.png";

            troopPath =
                "data/graphics/board/NapoleonTroop.png";

            playerColour =
                sf::Color(
                    60,
                    100,
                    180);

            troopOffset =
            { 213.0f, 105.0f };
            break;

        case 1:
            avatarPath =
                "data/graphics/board/WellingtonBoardAvatar.png";

            troopPath =
                "data/graphics/board/WellingtonTroop.png";

            playerColour =
                sf::Color(
                    180,
                    60,
                    60);

            troopOffset =
            { 210.0f, 105.0f };
            break;

        case 2:
            avatarPath =
                "data/graphics/board/BulcherBoardAvatar.png";

            troopPath =
                "data/graphics/board/BulcherTroop.png";

            playerColour =
                sf::Color(
                    35,
                    35,
                    35);

            troopOffset =
            { 217.0f, 105.0f };
            break;

        case 3:
            avatarPath =
                "data/graphics/board/VonBoardAvatar.png";

            troopPath =
                "data/graphics/board/VonTroop.png";

            playerColour =
                sf::Color(
                    220,
                    220,
                    210);

            troopOffset =
            { 215.0f, 105.0f };
            break;

        case 4:
            avatarPath =
                "data/graphics/board/NeedleBoardAvatar.png";

            troopPath =
                "data/graphics/board/NeedleTroop.png";

            playerColour =
                sf::Color(
                    190,
                    155,
                    45);

            troopOffset =
            { 197.0f, 115.0f };
            break;

        case 5:
            avatarPath =
                "data/graphics/board/AlexanderBoardAvatar.png";

            troopPath =
                "data/graphics/board/AlexanderTroop.png";

            playerColour =
                sf::Color(
                    60,
                    140,
                    75);

            troopOffset =
            { 210.0f, 105.0f };
            break;

        default:
            avatarPath =
                blankAvatarPath;

            troopPath =
                "";

            playerColour =
                sf::Color(
                    100,
                    100,
                    100);

            troopOffset =
            { 208.0f, 105.0f };
            break;
        }

        // -----------------------------
        // Load avatar
        // -----------------------------

        if (!avatarTexture.loadFromFile(
            avatarPath))
        {
            throw std::runtime_error(
                "Could not load avatar: " +
                avatarPath);
        }

        avatarSprite.setTexture(
            avatarTexture,
            true);

        avatarTexture.setSmooth(true);

        // -----------------------------
        // Load troop
        // -----------------------------

        if (!troopPath.empty())
        {
            if (!troopTexture.loadFromFile(
                troopPath))
            {
                throw std::runtime_error(
                    "Could not load troop: " +
                    troopPath);
            }

            troopSprite.setTexture(
                troopTexture,
                true);

            // -----------------------------
            // Individual troop position
            // -----------------------------

            troopSprite.setPosition(
                {
                    playerPosition.x +
                        troopOffset.x,

                    playerPosition.y +
                        troopOffset.y
                });
        }
    }


    void PlayerGraphics::setActive(
        bool active)
    {
        // Active-player treatment will be
        // handled separately from the old
        // faction-coloured panel outline.
    }


    void PlayerGraphics::draw(
        sf::RenderWindow& window) const
    {
        // Navy panel
        window.draw(
            playerPanel);

        // Brass border
        window.draw(
            panelSprite);

        // Commander portrait
        window.draw(
            avatarSprite);

        // Troop miniature
        window.draw(
            troopSprite);

        // Player information
        window.draw(
            playerNameText);

        // Count boxes
        window.draw(
            troopCountBox);

        window.draw(
            cardCountBox);

        // Icons and values
        window.draw(
            TroopIconSprite);

        window.draw(
            troopCountText);

        window.draw(
            CardIconSprite);

        window.draw(
            cardCountText);
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