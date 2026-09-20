#pragma once

#include <SFML/Graphics.hpp>

#include <string>

namespace risk {

class PlayerGraphics {
private:
  int playerID;
  int troopCount;
  int cardCount = 0;

  sf::Vector2f playerPosition;
  sf::Color playerColour;

  sf::RectangleShape playerPanel;

  sf::Texture avatarTexture;
  sf::Sprite avatarSprite;

  sf::Text playerNameText;
  sf::Text troopCountText;
  sf::Text cardCountText;

  const std::string blankAvatarPath =
      "C:/Users/joshk/programming/risk_V1/data/graphics/avatars/blank.png";

  const sf::Vector2f panelSize = {320.0f, 245.0f};
  const sf::Vector2f avatarSize = {150.0f, 150.0f};

public:
  PlayerGraphics(int playerID, int troopCount, const sf::Font &font);

  void setPlayerID(int newPlayerID);

  void setName(const std::string &name);

  void setTroopCount(int newCount);

  void setCardCount(int newCount);

  void setAvatar(int avatarID);

  void setActive(bool active);

  void draw(sf::RenderWindow &window) const;

  int getPlayerID() const;
};

} // namespace risk