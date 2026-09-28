#pragma once
#include "risk/core/orders/AttackOrder.h"
#include <SFML/Graphics.hpp>
#include <optional>
#include <string>
#include <vector>

namespace risk {

class AttackWindow {

private:
  sf::RectangleShape attackWindow;
  sf::Vector2f position;

  std::optional<sf::Text> fromTerritoryText;
  std::optional<sf::Text> fromPlayerText;
  std::optional<sf::Text> fromTroopText;
  sf::ConvexShape fromTerritoryShape;

  sf::Texture fromAvatarTexture;
  std::optional<sf::Sprite> fromAvatar;

  std::optional<sf::Text> toTerritoryText;
  std::optional<sf::Text> toPlayerText;
  std::optional<sf::Text> toTroopText;
  sf::ConvexShape toTerritoryShape;

  sf::Texture toAvatarTexture;
  std::optional<sf::Sprite> toAvatar;

  //---------------------------------------------------------
  // Dice
  //---------------------------------------------------------

  std::optional<sf::Text> attackerDiceText;
  std::optional<sf::Text> defenderDiceText;

  std::vector<sf::RectangleShape> attackerDiceButtons;
  std::vector<sf::Text> attackerDiceNumbers;

  std::vector<sf::RectangleShape> defenderDiceBoxes;
  std::vector<sf::Text> defenderDiceNumbers;

  int selectedAttackerDice = 0;
  int selectedDefenderDice = 0;

  std::optional<sf::Text> attackResultText;
  std::vector<sf::RectangleShape> attackerResultDice;
  std::vector<sf::Text> attackerResultDiceNumbers;

  std::vector<sf::RectangleShape> defenderResultDice;
  std::vector<sf::Text> defenderResultDiceNumbers;

  sf::RectangleShape quitAttackButton;
  std::optional<sf::Text> quitAttackText;

  sf::RectangleShape attackButton;
  std::optional<sf::Text> attackButtonText;

  sf::RectangleShape addTroopButton;
  std::optional<sf::Text> addTroopText;

  sf::RectangleShape removeTroopButton;
  std::optional<sf::Text> removeTroopText;

  sf::RectangleShape confirmMoveButton;
  std::optional<sf::Text> confirmMoveText;

  std::optional<sf::Text> moveTroopCountText;

public:
  AttackWindow(const sf::Font &font);

  void setPosition(sf::Vector2f position);

  void setFromTerritoryName(const std::string &name);
  void setFromPlayerName(const std::string &name);
  void setFromTroopCount(int troopCount);
  void setFromAvatar(int avatarID);
  void setFromVertices(const std::vector<sf::Vector2f> &vertices);

  void setToTerritoryName(const std::string &name);
  void setToPlayerName(const std::string &name);
  void setToTroopCount(int troopCount);
  void setToAvatar(int avatarID);
  void setToVertices(const std::vector<sf::Vector2f> &vertices);

  void setMoveTroopCount(int troopCount);

  void setAttackerDice(int diceCount);
  void setDefenderDice(int diceCount);

  int getAttackerDiceSelection(sf::Vector2f mousePosition) const;

  void clearDice();

  void setAttackResult(
    const AttackResult &result,
    const std::vector<int> &attackingDice,
    const std::vector<int> &defendingDice);

  sf::FloatRect getQuitAttackBounds() const;
  sf::FloatRect getAttackBounds() const;
  sf::FloatRect getAddTroopBounds() const;
  sf::FloatRect getRemoveTroopBounds() const;
  sf::FloatRect getConfirmMoveBounds() const;

  void draw(sf::RenderWindow &window);
};

} // namespace risk