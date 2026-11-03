
#include "risk/graphics/game_elements/PlayerGraphics.h"

#include <stdexcept>

namespace risk {

//-------------------------------------------------
// Constructor
//-------------------------------------------------

PlayerGraphics::PlayerGraphics(
    int playerID,
    int troopCount,
    const sf::Font& font)
    : playerID(playerID),
      troopCount(troopCount),
      TroopIconSprite(TroopIconTexture),
      CardIconSprite(CardIconTexture),
      avatarSprite(avatarTexture),
      troopSprite(troopTexture),
      playerNameText(font),
      troopCountText(font),
      cardCountText(font)
{
    playerColour = sf::Color(100, 100, 100);

    //-------------------------------------------------
    // Troop icon
    //-------------------------------------------------

    if (!TroopIconTexture.loadFromFile(
        "data/graphics/components/TroopIcon.png"))
    {
        throw std::runtime_error(
            "Could not load troop icon");
    }

    TroopIconSprite.setTexture(
        TroopIconTexture, true);

    //-------------------------------------------------
    // Card icon
    //-------------------------------------------------

    if (!CardIconTexture.loadFromFile(
        "data/graphics/components/CardIcon.png"))
    {
        throw std::runtime_error(
            "Could not load card icon");
    }

    CardIconSprite.setTexture(
        CardIconTexture, true);

    //-------------------------------------------------
    // Count boxes
    //-------------------------------------------------

    troopCountBox.setSize({80.f, 42.f});
    troopCountBox.setFillColor(
        sf::Color(10, 25, 36, 220));
    troopCountBox.setOutlineColor(
        sf::Color(185, 145, 65));
    troopCountBox.setOutlineThickness(1.5f);

    cardCountBox.setSize({80.f, 42.f});
    cardCountBox.setFillColor(
        sf::Color(10, 25, 36, 220));
    cardCountBox.setOutlineColor(
        sf::Color(185, 145, 65));
    cardCountBox.setOutlineThickness(1.5f);

    //-------------------------------------------------
    // Player name
    //-------------------------------------------------

    playerName =
        "Player " + std::to_string(playerID + 1);

    playerNameText.setString(playerName);
    playerNameText.setCharacterSize(26);

    playerNameText.setFillColor(
        sf::Color(245, 224, 175));

    playerNameText.setOutlineColor(
        sf::Color(35, 25, 15, 230));

    playerNameText.setOutlineThickness(1.5f);

    //-------------------------------------------------
    // Troop count
    //-------------------------------------------------

    troopCountText.setString(
        std::to_string(troopCount));

    troopCountText.setCharacterSize(22);
    troopCountText.setFillColor(
        sf::Color(235, 215, 170));

    //-------------------------------------------------
    // Card count
    //-------------------------------------------------

    cardCountText.setString(
        std::to_string(cardCount));

    cardCountText.setCharacterSize(22);
    cardCountText.setFillColor(
        sf::Color(235, 215, 170));

    //-------------------------------------------------
    // Initial layout
    //-------------------------------------------------

    setPlayerID(playerID);
}

//-------------------------------------------------
// Position player in wooden slot
//-------------------------------------------------

void PlayerGraphics::setPlayerID(int newPlayerID)
{
    playerID = newPlayerID;

    constexpr float startX = 50.f;
    constexpr float startY = 770.f;

    playerPosition = {
        startX + static_cast<float>(playerID) * slotWidth,
        startY
    };

    //-------------------------------------------------
    // Avatar
    //-------------------------------------------------

    avatarSprite.setPosition({
        playerPosition.x +12.f,
        playerPosition.y + 40.f
    });

    //-------------------------------------------------
    // Player name
    //-------------------------------------------------

    playerNameText.setPosition({
        playerPosition.x + 23.f,
        playerPosition.y + 8.f
    });

    //-------------------------------------------------
    // Troop count
    //-------------------------------------------------

    troopCountBox.setPosition({
        playerPosition.x + 210.f,
        playerPosition.y + 12.f
    });

    TroopIconSprite.setPosition({
        playerPosition.x + 212.f,
        playerPosition.y + 7.f
    });

    troopCountText.setPosition({
        playerPosition.x + 263.f,
        playerPosition.y + 19.f
    });

    //-------------------------------------------------
    // Card count
    //-------------------------------------------------

    cardCountBox.setPosition({
        playerPosition.x + 210.f,
        playerPosition.y + 47.f
    });

    CardIconSprite.setPosition({
        playerPosition.x + 212.f,
        playerPosition.y + 44.f
    });

    cardCountText.setPosition({
        playerPosition.x + 263.f,
        playerPosition.y + 54.f
    });
}

//-------------------------------------------------
// Player name
//-------------------------------------------------

void PlayerGraphics::setName(
    const std::string& name)
{
    playerName = name;
    playerNameText.setString(playerName);
}

//-------------------------------------------------
// Troop count
//-------------------------------------------------

void PlayerGraphics::setTroopCount(int newCount)
{
    troopCount = newCount;

    troopCountText.setString(
        std::to_string(troopCount));
}

//-------------------------------------------------
// Card count
//-------------------------------------------------

void PlayerGraphics::setCardCount(int newCount)
{
    cardCount = newCount;

    cardCountText.setString(
        std::to_string(cardCount));
}

//-------------------------------------------------
// Avatar and faction
//-------------------------------------------------

void PlayerGraphics::setAvatar(int newAvatarID)
{
    avatarID = newAvatarID;

    std::string avatarPath;
    std::string troopPath;

    sf::Vector2f troopOffset = {208.f, 105.f};

    switch (avatarID)
    {
    case 0:
        avatarPath =
            "data/graphics/factions/NapoleonBoardAvatar.png";
        troopPath =
            "data/graphics/factions/NapoleonTroop.png";
        playerColour = sf::Color(60, 100, 180);
        troopOffset = {213.f, 105.f};
        break;

    case 1:
        avatarPath =
            "data/graphics/factions/WellingtonBoardAvatar.png";
        troopPath =
            "data/graphics/factions/WellingtonTroop.png";
        playerColour = sf::Color(180, 60, 60);
        troopOffset = {210.f, 105.f};
        break;

    case 2:
        avatarPath =
            "data/graphics/factions/BlucherBoardAvatar.png";
        troopPath =
            "data/graphics/factions/BlucherTroop.png";
        playerColour = sf::Color(35, 35, 35);
        troopOffset = {217.f, 105.f};
        break;

    case 3:
        avatarPath =
            "data/graphics/factions/VonBoardAvatar.png";
        troopPath =
            "data/graphics/factions/VonTroop.png";
        playerColour = sf::Color(220, 220, 210);
        troopOffset = {215.f, 105.f};
        break;

    case 4:
        avatarPath =
            "data/graphics/factions/NeedleBoardAvatar.png";
        troopPath =
            "data/graphics/factions/NeedleTroop.png";
        playerColour = sf::Color(190, 155, 45);
        troopOffset = {197.f, 115.f};
        break;

    case 5:
        avatarPath =
            "data/graphics/factions/AlexanderBoardAvatar.png";
        troopPath =
            "data/graphics/factions/AlexanderTroop.png";
        playerColour = sf::Color(60, 140, 75);
        troopOffset = {210.f, 105.f};
        break;

    default:
        avatarPath = blankAvatarPath;
        troopPath = "";
        playerColour = sf::Color(100, 100, 100);
        troopOffset = {208.f, 105.f};
        break;
    }

    //-------------------------------------------------
    // Load avatar
    //-------------------------------------------------

    if (!avatarTexture.loadFromFile(avatarPath))
    {
        throw std::runtime_error(
            "Could not load avatar: " + avatarPath);
    }

    avatarSprite.setTexture(avatarTexture, true);
    avatarTexture.setSmooth(true);

    //-------------------------------------------------
    // Load troop miniature
    //-------------------------------------------------

    if (!troopPath.empty())
    {
        if (!troopTexture.loadFromFile(troopPath))
        {
            throw std::runtime_error(
                "Could not load troop: " + troopPath);
        }

        troopSprite.setTexture(troopTexture, true);

        troopSprite.setPosition({
            playerPosition.x + troopOffset.x,
            playerPosition.y + troopOffset.y
        });
    }
}

//-------------------------------------------------
// Active player
//-------------------------------------------------

void PlayerGraphics::setActive(bool active)
{
    // Active-player treatment remains unchanged.
}

//-------------------------------------------------
// Draw
//-------------------------------------------------

void PlayerGraphics::draw(
    sf::RenderWindow& window) const
{
    // Commander portrait
    window.draw(avatarSprite);

    // Troop miniature
    if (avatarID >= 0 && avatarID <= 5)
    {
        window.draw(troopSprite);
    }

    // Player information
    window.draw(playerNameText);

    // Count boxes
    window.draw(troopCountBox);
    window.draw(cardCountBox);

    // Icons and values
    window.draw(TroopIconSprite);
    window.draw(troopCountText);

    window.draw(CardIconSprite);
    window.draw(cardCountText);
}

//-------------------------------------------------
// Getters
//-------------------------------------------------

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
