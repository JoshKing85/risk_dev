#pragma once

#include "risk/entities/Card.h"
#include "risk/enums.h"
#include "risk/graphics/game_elements/CardGraphics.h"
#include "risk/graphics/game_elements/TerritoryGraphics.h"

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <vector>

namespace risk {

class CardContainer {
private:
  //---------------------------------------------------------
  // Container Graphics
  //---------------------------------------------------------

  sf::RectangleShape container;

  sf::RectangleShape tab;
  sf::Text tabText;

  sf::RectangleShape cashSetButton;
  sf::Text cashSetButtonText;

  //---------------------------------------------------------
  // Card Graphics
  //---------------------------------------------------------

  std::vector<CardGraphics> cardGraphics;

  //---------------------------------------------------------
  // State
  //---------------------------------------------------------

  bool open = false;

  std::vector<int> selectedCards;

  //---------------------------------------------------------
  // Card Handling
  //---------------------------------------------------------

  void setContainer(const std::unordered_map<TerritoryID, TerritoryGraphics>
                        &territoryGraphicsMap,
                    const std::vector<Card> &playerSet, const sf::Font &font);

  void setCardPositions();

public:
  CardContainer(const sf::Font &font,
                const std::unordered_map<TerritoryID, TerritoryGraphics>
                    &territoryGraphicsMap,
                const std::vector<Card> &playerSet);

  //---------------------------------------------------------
  // Open / Close
  //---------------------------------------------------------

  void openContainer();
  void closeContainer();

  bool isOpen() const;

  //---------------------------------------------------------
  // Selection
  //---------------------------------------------------------

  void selectCard(sf::Vector2f mousePosition);

  const std::vector<int> &getSelectedCards() const;

  void clearSelectedCards();

  //---------------------------------------------------------
  // Bounds
  //---------------------------------------------------------

  sf::FloatRect getTabBounds() const;

  sf::FloatRect getCashSetBounds() const;

  //---------------------------------------------------------
  // Update
  //---------------------------------------------------------

  void updateCards(const std::unordered_map<TerritoryID, TerritoryGraphics>
                       &territoryGraphicsMap,
                   const std::vector<Card> &playerSet, const sf::Font &font);

  //---------------------------------------------------------
  // Clear
  //---------------------------------------------------------

  void clear();

  //---------------------------------------------------------
  // Draw
  //---------------------------------------------------------

  void draw(sf::RenderWindow &window) const;
};

} // namespace risk