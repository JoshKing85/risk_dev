#include "risk/graphics/game_elements/CardGraphics.h"

#include <algorithm>

namespace risk {

    CardGraphics::CardGraphics(
        CardType cardType,
        const std::vector<sf::Vector2f>& territoryVertices,
        const sf::Font& font)
        : cardType(cardType),
        cardTypeText(font)
    {
        //---------------------------------------------------------
        // Card
        //---------------------------------------------------------

        cardShape.setSize(
            { 140.0f, 200.0f });

        cardShape.setFillColor(
            sf::Color(230, 225, 210));

        cardShape.setOutlineColor(
            sf::Color::Black);

        cardShape.setOutlineThickness(
            2.0f);

        //---------------------------------------------------------
        // Card Type
        //---------------------------------------------------------

        switch (cardType)
        {
        case CardType::Infantry:
            cardTypeText.setString("Infantry");
            break;

        case CardType::Cavalry:
            cardTypeText.setString("Cavalry");
            break;

        case CardType::Artillery:
            cardTypeText.setString("Artillery");
            break;

        case CardType::Wild:
            cardTypeText.setString("Wild");
            break;
        }

        cardTypeText.setCharacterSize(18);
        cardTypeText.setFillColor(sf::Color::Black);

        //---------------------------------------------------------
        // Territory Shape
        //---------------------------------------------------------

        if (!territoryVertices.empty())
        {
            territoryShape.setPointCount(
                territoryVertices.size());

            for (std::size_t i = 0;
                i < territoryVertices.size();
                i++)
            {
                territoryShape.setPoint(
                    i,
                    territoryVertices[i]);
            }

            territoryShape.setFillColor(
                sf::Color(80, 80, 80));
        }
    }


    //---------------------------------------------------------
    // Position
    //---------------------------------------------------------

    void CardGraphics::setPosition(
        sf::Vector2f position)
    {
        cardShape.setPosition(position);

        cardTypeText.setPosition(
            {
                position.x + 10.0f,
                position.y + 10.0f
            });

        //---------------------------------------------------------
        // Fit territory inside card
        //---------------------------------------------------------

        if (territoryShape.getPointCount() > 0)
        {
            sf::FloatRect bounds =
                territoryShape.getLocalBounds();

            float maxWidth = 100.0f;
            float maxHeight = 120.0f;

            float scaleX =
                maxWidth / bounds.size.x;

            float scaleY =
                maxHeight / bounds.size.y;

            float scale =
                std::min(scaleX, scaleY);

            territoryShape.setScale(
                { scale, scale });

            sf::FloatRect scaledBounds =
                territoryShape.getGlobalBounds();

            float territoryX =
                position.x +
                (140.0f - scaledBounds.size.x) /
                2.0f;

            float territoryY =
                position.y + 55.0f;

            territoryShape.setPosition(
                {
                    territoryX -
                        scaledBounds.position.x,
                    territoryY -
                        scaledBounds.position.y
                });
        }
    }


    void CardGraphics::setRotation(
        sf::Angle rotation)
    {
        cardShape.setRotation(rotation);
        cardTypeText.setRotation(rotation);
        territoryShape.setRotation(rotation);
    }


    //---------------------------------------------------------
    // Selection
    //---------------------------------------------------------

    void CardGraphics::setSelected(
        bool newSelected)
    {
        selected = newSelected;

        if (selected)
        {
            cardShape.setOutlineColor(
                sf::Color::White);

            cardShape.setOutlineThickness(
                5.0f);
        }
        else
        {
            cardShape.setOutlineColor(
                sf::Color::Black);

            cardShape.setOutlineThickness(
                2.0f);
        }
    }


    bool CardGraphics::isSelected() const
    {
        return selected;
    }


    //---------------------------------------------------------
    // Access
    //---------------------------------------------------------

    CardType CardGraphics::getCardType() const
    {
        return cardType;
    }


    sf::FloatRect CardGraphics::getBounds() const
    {
        return cardShape.getGlobalBounds();
    }


    bool CardGraphics::contains(
        sf::Vector2f point) const
    {
        return cardShape
            .getGlobalBounds()
            .contains(point);
    }


    //---------------------------------------------------------
    // Draw
    //---------------------------------------------------------

    void CardGraphics::draw(
        sf::RenderWindow& window) const
    {
        window.draw(cardShape);

        if (territoryShape.getPointCount() > 0)
        {
            window.draw(territoryShape);
        }

        window.draw(cardTypeText);
    }

} // namespace risk