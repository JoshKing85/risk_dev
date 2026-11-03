#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace risk {

class PlayerGraphics {
private:
    int playerID;
    int troopCount;
    int cardCount = 0;
    int avatarID = -1;

    std::string playerName;

    sf::Vector2f playerPosition;
    sf::Color playerColour;

    // Navy background within wooden slot
    sf::RectangleShape playerPanel;

    sf::Texture TroopIconTexture;
    sf::Sprite TroopIconSprite;

    sf::Texture CardIconTexture;
    sf::Sprite CardIconSprite;

    sf::RectangleShape troopCountBox;
    sf::RectangleShape cardCountBox;

    sf::Texture avatarTexture;
    sf::Sprite avatarSprite;

    sf::Texture troopTexture;
    sf::Sprite troopSprite;

    sf::Text playerNameText;
    sf::Text troopCountText;
    sf::Text cardCountText;

    const std::string blankAvatarPath =
        "data/graphics/avatars/blank.png";

    // Wooden strip: 1820 / 6
    static constexpr float slotWidth = 1820.f / 6.f;
    static constexpr float slotHeight = 300.f;

public:
    PlayerGraphics(
        int playerID,
        int troopCount,
        const sf::Font& font);

    void setPlayerID(int newPlayerID);

    void setName(const std::string& name);

    void setTroopCount(int newCount);

    void setCardCount(int newCount);

    void setAvatar(int avatarID);

    void setActive(bool active);

    void draw(sf::RenderWindow& window) const;

    int getPlayerID() const;

    int getAvatarID() const;

    std::string getName() const;
};

} // namespace risk