#pragma once

#include <SFML/Graphics.hpp>

#include <optional>
#include <string>

namespace risk {

class AttackWindow {

private:
  //---------------------------------------------------------
  // Container
  //---------------------------------------------------------

  sf::RectangleShape attackWindow;

  //---------------------------------------------------------
  // From Territory
  //---------------------------------------------------------

  std::optional<sf::Text> fromTerritoryText;
  std::optional<sf::Text> fromPlayerText;
  std::optional<sf::Text> fromTroopText;

  //---------------------------------------------------------
  // From Player Avatar
  //---------------------------------------------------------

  sf::Texture fromAvatarTexture;
  std::optional<sf::Sprite> fromAvatar;

  //---------------------------------------------------------
  // To Territory
  //---------------------------------------------------------

  std::optional<sf::Text> toTerritoryText;
  std::optional<sf::Text> toPlayerText;
  std::optional<sf::Text> toTroopText;

  //---------------------------------------------------------
  // To Player Avatar
  //---------------------------------------------------------

  sf::Texture toAvatarTexture;
  std::optional<sf::Sprite> toAvatar;

  //---------------------------------------------------------
  // Dice
  //---------------------------------------------------------

  std::optional<sf::Text> attackerDiceText;
  std::optional<sf::Text> defenderDiceText;

  //---------------------------------------------------------
  // Result
  //---------------------------------------------------------

  std::optional<sf::Text> attackResultText;

  //---------------------------------------------------------
  // Controls
  //---------------------------------------------------------

  sf::RectangleShape quitAttackButton;
  std::optional<sf::Text> quitAttackText;

  sf::RectangleShape attackButton;
  std::optional<sf::Text> attackButtonText;

public:
  AttackWindow(const sf::Font &font);

  //---------------------------------------------------------
  // Position
  //---------------------------------------------------------

  void setPosition(sf::Vector2f position);

  //---------------------------------------------------------
  // From Territory
  //---------------------------------------------------------

  void setFromTerritoryName(const std::string &name);

  void setFromPlayerName(const std::string &name);

  void setFromTroopCount(int troopCount);

  void setFromAvatar(const std::string &avatarPath);

  //---------------------------------------------------------
  // To Territory
  //---------------------------------------------------------

  void setToTerritoryName(const std::string &name);

  void setToPlayerName(const std::string &name);

  void setToTroopCount(int troopCount);

  void setToAvatar(const std::string &avatarPath);

  //---------------------------------------------------------
  // Dice
  //---------------------------------------------------------

  void setAttackerDice(int diceCount);

  void setDefenderDice(int diceCount);

  int getAttackerDiceSelection(sf::Vector2f mousePosition) const;

  //---------------------------------------------------------
  // Result
  //---------------------------------------------------------

  void setAttackResult(const std::string &result);

  //---------------------------------------------------------
  // Bounds
  //---------------------------------------------------------

  sf::FloatRect getQuitAttackBounds() const;

  sf::FloatRect getAttackBounds() const;

  //---------------------------------------------------------
  // Draw
  //---------------------------------------------------------

  void draw(sf::RenderWindow &window);
};

} // namespace risk