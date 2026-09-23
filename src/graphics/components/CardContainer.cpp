#include "risk/graphics/components/CardContainer.h"

#include <algorithm>

namespace risk {

    CardContainer::CardContainer(
        const sf::Font& font,
        const std::unordered_map<TerritoryID, TerritoryGraphics>&
        territoryGraphicsMap,
        const std::vector<Card>& playerSet)
        : tabText(font),
        cashSetButtonText(font)
    {
        //---------------------------------------------------------
        // Container
        //---------------------------------------------------------

        container.setSize(
            { 1000.0f, 300.0f });

        container.setPosition(
            { 460.0f, 740.0f });

        container.setFillColor(
            sf::Color(30, 40, 50, 240));

        container.setOutlineColor(
            sf::Color::White);

        container.setOutlineThickness(
            2.0f);

        //---------------------------------------------------------
        // Tab
        //---------------------------------------------------------

        tab.setSize(
            { 120.0f, 40.0f });

        tab.setPosition(
            { 900.0f, 700.0f });

        tab.setFillColor(
            sf::Color(50, 70, 85));

        tabText.setString("Cards");

        tabText.setCharacterSize(20);

        tabText.setFillColor(
            sf::Color::White);

        tabText.setPosition(
            { 930.0f, 708.0f });

        //---------------------------------------------------------
        // Cash Set Button
        //---------------------------------------------------------

        cashSetButton.setSize(
            { 120.0f, 40.0f });

        cashSetButton.setPosition(
            { 900.0f, 990.0f });

        cashSetButton.setFillColor(
            sf::Color(50, 70, 85));

        cashSetButtonText.setString(
            "Cash Set");

        cashSetButtonText.setCharacterSize(
            18);

        cashSetButtonText.setFillColor(
            sf::Color::White);

        cashSetButtonText.setPosition(
            { 920.0f, 998.0f });

        //---------------------------------------------------------
        // Cards
        //---------------------------------------------------------

        setContainer(
            territoryGraphicsMap,
            playerSet,
            font);
    }


    //---------------------------------------------------------
    // Card Setup
    //---------------------------------------------------------

    void CardContainer::setContainer(
        const std::unordered_map<TerritoryID, TerritoryGraphics>&
        territoryGraphicsMap,
        const std::vector<Card>& playerSet,
        const sf::Font& font)
    {
        cardGraphics.clear();
        selectedCards.clear();

        std::size_t cardCount =
            std::min<std::size_t>(
                playerSet.size(),
                8);

        for (std::size_t i = 0;
            i < cardCount;
            i++)
        {
            const Card& card =
                playerSet[i];

            std::vector<sf::Vector2f>
                territoryVertices;

            if (card.hasTerritory())
            {
                std::optional<TerritoryID>
                    territoryID =
                    card.getTerritoryID();

                if (territoryID.has_value())
                {
                    auto territoryIterator =
                        territoryGraphicsMap.find(
                            territoryID.value());

                    if (territoryIterator !=
                        territoryGraphicsMap.end())
                    {
                        territoryVertices =
                            territoryIterator
                            ->second
                            .getVertices();
                    }
                }
            }

            cardGraphics.emplace_back(
                card.getCardType(),
                territoryVertices,
                font);
        }

        setCardPositions();
    }


    //---------------------------------------------------------
    // Card Positioning
    //---------------------------------------------------------

    void CardContainer::setCardPositions()
    {
        if (cardGraphics.empty())
        {
            return;
        }

        //---------------------------------------------------------
        // Hand Layout
        //---------------------------------------------------------

        float centreX = 960.0f;
        float cardSpacing = 90.0f;

        float centreIndex =
            static_cast<float>(
                cardGraphics.size() - 1) /
            2.0f;

        for (std::size_t i = 0;
            i < cardGraphics.size();
            i++)
        {
            float offset =
                static_cast<float>(i) -
                centreIndex;

            //-----------------------------------------------------
            // Grow outwards from center
            //-----------------------------------------------------

            float x =
                centreX +
                (offset * cardSpacing) -
                70.0f;

            //-----------------------------------------------------
            // Slight arc
            //-----------------------------------------------------

            float y =
                770.0f +
                (offset * offset * 4.0f);

            //-----------------------------------------------------
            // Fan rotation
            //-----------------------------------------------------

            float rotation =
                offset * 3.0f;

            cardGraphics[i].setPosition(
                { x, y });

            cardGraphics[i].setRotation(
                sf::degrees(rotation));
        }
    }


    //---------------------------------------------------------
    // Open / Close
    //---------------------------------------------------------

    void CardContainer::openContainer()
    {
        open = true;
    }


    void CardContainer::closeContainer()
    {
        open = false;
    }


    bool CardContainer::isOpen() const
    {
        return open;
    }


    //---------------------------------------------------------
    // Selection
    //---------------------------------------------------------

    void CardContainer::selectCard(
        sf::Vector2f mousePosition)
    {
        if (!open)
        {
            return;
        }

        //---------------------------------------------------------
        // Work backwards because cards overlap
        //---------------------------------------------------------

        for (int i =
            static_cast<int>(
                cardGraphics.size()) - 1;
            i >= 0;
            i--)
        {
            if (cardGraphics[i].contains(
                mousePosition))
            {
                bool selected =
                    cardGraphics[i]
                    .isSelected();

                cardGraphics[i].setSelected(
                    !selected);

                auto selectedIterator =
                    std::find(
                        selectedCards.begin(),
                        selectedCards.end(),
                        i);

                if (selected)
                {
                    if (selectedIterator !=
                        selectedCards.end())
                    {
                        selectedCards.erase(
                            selectedIterator);
                    }
                }
                else
                {
                    selectedCards.push_back(i);
                }

                break;
            }
        }
    }


    const std::vector<int>&
        CardContainer::getSelectedCards() const
    {
        return selectedCards;
    }


    void CardContainer::clearSelectedCards()
    {
        selectedCards.clear();

        for (auto& card : cardGraphics)
        {
            card.setSelected(false);
        }
    }


    //---------------------------------------------------------
    // Bounds
    //---------------------------------------------------------

    sf::FloatRect
        CardContainer::getTabBounds() const
    {
        return tab.getGlobalBounds();
    }


    sf::FloatRect
        CardContainer::getCashSetBounds() const
    {
        return cashSetButton
            .getGlobalBounds();
    }


    //---------------------------------------------------------
    // Update
    //---------------------------------------------------------

    void CardContainer::updateCards(
        const std::unordered_map<TerritoryID, TerritoryGraphics>&
        territoryGraphicsMap,
        const std::vector<Card>& playerSet,
        const sf::Font& font)
    {
        setContainer(
            territoryGraphicsMap,
            playerSet,
            font);
    }


    //---------------------------------------------------------
    // Clear
    //---------------------------------------------------------

    void CardContainer::clear()
    {
        cardGraphics.clear();
        selectedCards.clear();

        open = false;
    }


    //---------------------------------------------------------
    // Draw
    //---------------------------------------------------------

    void CardContainer::draw(
        sf::RenderWindow& window) const
    {
        //---------------------------------------------------------
        // Tab always exists
        //---------------------------------------------------------

        window.draw(tab);
        window.draw(tabText);

        if (!open)
        {
            return;
        }

        //---------------------------------------------------------
        // Open Container
        //---------------------------------------------------------

        window.draw(container);

        for (const auto& card :
            cardGraphics)
        {
            card.draw(window);
        }

        window.draw(cashSetButton);
        window.draw(cashSetButtonText);
    }

} // namespace risk