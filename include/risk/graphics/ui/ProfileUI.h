#pragma once

#include <SFML/Graphics.hpp>

#include <array>
#include <string>

namespace risk {

class GameSetupState;
class PlayerGraphics;

class ProfileUI {
private:
  int selectedAvatar = -1;

  sf::Font &font;

  // Stores the name currently being typed during profile setup
  std::string playerName;

  // Main panel
  sf::RectangleShape backgroundPanel;

  // Text
  sf::Text titleText;
  sf::Text nameLabel;
  sf::Text avatarLabel;
  sf::Text startGameText;

  // Name input
  sf::RectangleShape nameInputBox;
  sf::Text nameInputText;

  // Avatar selection
  std::array<sf::RectangleShape, 3> avatarBoxes;
  std::array<sf::Texture, 3> avatarTextures;
  std::array<sf::Sprite, 3> avatarSprites;

  // Start button
  sf::RectangleShape startGameButton;

public:
  ProfileUI(sf::Font &font);

  // Draws the profile setup screen for the current player
  void profileUIdraw(sf::RenderWindow &window, int playerID);

  // Handles keyboard and mouse input for the profile screen.
  // Updates PlayerGraphics and GameSetupState when selections are made.
  void handleEvent(const sf::Event &event, sf::RenderWindow &window,
                   int playerID, PlayerGraphics &playerGraphics,
                   GameSetupState &gameSetupState);

  // Highlights the selected avatar and updates the player's displayed avatar
  void setAvatar(int avatarID, PlayerGraphics &playerGraphics);

  // Updates the player's displayed name and marks name selection complete
  void setPlayerName(int playerID, PlayerGraphics &playerGraphics,
                     GameSetupState &gameSetupState);

  // Completes the current player's profile and moves setup to the next profile
  void setGameSetupStateProfile(int playerID, GameSetupState &gameSetupState);
};

} // namespace risk