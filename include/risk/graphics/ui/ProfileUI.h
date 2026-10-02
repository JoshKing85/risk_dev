#pragma once

#include <SFML/Graphics.hpp>

#include "risk/graphics/components/DebugGrid.h"
#include "risk/graphics/components/PlayerProfile.h"

#include <array>
#include <optional>
#include <string>
#include <vector>

namespace risk {

class ProfileUI {

private:
  //---------------------------------------------------------
  // State
  //---------------------------------------------------------

  std::optional<DebugGrid> debugGrid;

  //---------------------------------------------------------
  // Resources
  //---------------------------------------------------------

  sf::Font &font;

  //---------------------------------------------------------
  // Background
  //---------------------------------------------------------

  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;

  //---------------------------------------------------------
  // Muster Board
  //---------------------------------------------------------

  sf::Texture musterBoardTexture;
  sf::Sprite musterBoardSprite;

  //---------------------------------------------------------
  // Text
  //---------------------------------------------------------

  sf::Text playerText;
  sf::Text playerNumberText;

  sf::Text nameLabel;
  sf::Text nameText;

  sf::Text avatarLabel;

  sf::Text startText;

  //---------------------------------------------------------
  // Name Entry
  //---------------------------------------------------------

  sf::RectangleShape nameBox;

  //---------------------------------------------------------
  // Avatar Selection
  //---------------------------------------------------------

  std::array<sf::RectangleShape, 6> avatarBoxes;
  std::array<sf::Texture, 6> avatarTextures;
  std::array<sf::Sprite, 6> avatarSprites;
  
  //---------------------------------------------------------
  // Start
  //---------------------------------------------------------

  sf::RectangleShape startButton;

  //---------------------------------------------------------
  // Event Handlers
  //---------------------------------------------------------

  void handleNameEntry(
      const sf::Event &event, 
      PlayerProfile &profile);

  void handleAvatarSelection(
      const sf::Event &event, 
      sf::RenderWindow &window,
      PlayerProfile &profile,
      const std::vector<PlayerProfile> &profiles);

  void handleStart(const 
      sf::Event &event, 
      sf::RenderWindow &window,
      PlayerProfile &profile);

  //---------------------------------------------------------
  // Actions
  //---------------------------------------------------------

  void setAvatar(int avatarID, PlayerProfile &profile);

  void confirmProfile(PlayerProfile &profile);

public:
  //---------------------------------------------------------
  // Constructor
  //---------------------------------------------------------

  ProfileUI(sf::Font &font);

  //---------------------------------------------------------
  // Event Router
  //---------------------------------------------------------

  void handleEvent(const sf::Event &event, sf::RenderWindow &window,
                   PlayerProfile &profile,
                   const std::vector<PlayerProfile> &profiles);

  //---------------------------------------------------------
  // State
  //---------------------------------------------------------

  void resetProfile();

  //---------------------------------------------------------
  // Draw
  //---------------------------------------------------------

  void profileUIdraw(sf::RenderWindow &window, int playerID,
                     const std::vector<PlayerProfile> &profiles);
};

} // namespace risk