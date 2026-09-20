#include "risk/graphics/game_elements/TerritoryGraphics.h"

#include <string>

namespace risk
{
    TerritoryGraphics::TerritoryGraphics(
        TerritoryID territoryID,
        ContinentID continentID,
        int playerID,
        const std::string& title,
        const std::vector<sf::Vector2f>& vertices,
        sf::Vector2f titlePosition,
        sf::Vector2f troopCountPosition,
        unsigned int titleCharacterSize,
        unsigned int troopCharacterSize,
        float outlineThickness,
        const sf::Font& font
    )
        : territoryID(territoryID),
        continentID(continentID),
        playerID(playerID),
        vertices(vertices),
        titleText(font),
        troopCountText(font),
        outlineThickness(outlineThickness)
    {
        shape.setPointCount(vertices.size());

        for (std::size_t i = 0; i < vertices.size(); i++)
        {
            shape.setPoint(i, vertices[i]);
        }

        shape.setOutlineThickness(outlineThickness);
        shape.setOutlineColor(sf::Color::Black);

        titleText.setString(title);
        titleText.setCharacterSize(titleCharacterSize);
        titleText.setPosition(titlePosition);
        titleText.setFillColor(sf::Color::White);

        troopCountText.setString("0");
        troopCountText.setCharacterSize(troopCharacterSize);
        troopCountText.setPosition(troopCountPosition);
        troopCountText.setFillColor(sf::Color::White);

        setPlayerID(playerID);
    }


    void TerritoryGraphics::setPlayerID(int newPlayerID)
    {
        playerID = newPlayerID;

        switch (playerID)
        {
        case 0:
            shape.setFillColor(sf::Color(180, 60, 60));
            break;

        case 1:
            shape.setFillColor(sf::Color(60, 100, 180));
            break;

        case 2:
            shape.setFillColor(sf::Color(60, 160, 80));
            break;

        case 3:
            shape.setFillColor(sf::Color(180, 150, 60));
            break;

        case 4:
            shape.setFillColor(sf::Color(130, 70, 170));
            break;

        case 5:
            shape.setFillColor(sf::Color(60, 160, 160));
            break;

        default:
            shape.setFillColor(sf::Color(100, 100, 100));
            break;
        }
    }


    void TerritoryGraphics::setTroopCount(int troopCount)
    {
        troopCountText.setString(
            std::to_string(troopCount)
        );
    }


    void TerritoryGraphics::setSelected(bool selected)
    {
        if (selected)
        {
            shape.setOutlineColor(
                sf::Color::White
            );

            shape.setOutlineThickness(
                5.0f
            );
        }
        else
        {
            shape.setOutlineColor(
                sf::Color::Black
            );

            shape.setOutlineThickness(
                outlineThickness
            );
        }
    }


    void TerritoryGraphics::draw(
        sf::RenderWindow& window
    ) const
    {
        window.draw(shape);
        window.draw(titleText);
        window.draw(troopCountText);
    }


    TerritoryID TerritoryGraphics::getTerritoryID() const
    {
        return territoryID;
    }


    int TerritoryGraphics::getPlayerID() const
    {
        return playerID;
    }


    sf::FloatRect TerritoryGraphics::getBounds() const
    {
        return shape.getGlobalBounds();
    }


    bool TerritoryGraphics::contains(
        sf::Vector2f point
    ) const
    {
        // Quick rejection first
        if (!shape.getGlobalBounds().contains(point))
        {
            return false;
        }

        bool inside = false;

        std::size_t pointCount =
            shape.getPointCount();

        for (std::size_t i = 0, j = pointCount - 1;
            i < pointCount;
            j = i++)
        {
            sf::Vector2f pointI =
                shape.getTransform().transformPoint(
                    shape.getPoint(i)
                );

            sf::Vector2f pointJ =
                shape.getTransform().transformPoint(
                    shape.getPoint(j)
                );

            bool intersects =
                ((pointI.y > point.y) !=
                    (pointJ.y > point.y)) &&
                (point.x <
                    (pointJ.x - pointI.x) *
                    (point.y - pointI.y) /
                    (pointJ.y - pointI.y) +
                    pointI.x);

            if (intersects)
            {
                inside = !inside;
            }
        }

        return inside;
    }

} // namespace risk