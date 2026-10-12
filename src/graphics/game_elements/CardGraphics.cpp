
#include "risk/graphics/game_elements/CardGraphics.h"

#include <algorithm>

#include "risk/utils/PolygonTriangulator.h"

namespace risk
{

CardGraphics::CardGraphics(CardType cardType,
                           const std::vector<std::vector<sf::Vector2f>>& territoryVertices,
                           const sf::Font& font)
    : cardType(cardType), cardTypeText(font)
{
    //---------------------------------------------------------
    // Card
    //---------------------------------------------------------

    cardShape.setSize({140.0f, 200.0f});

    cardShape.setFillColor(sf::Color(230, 225, 210));

    cardShape.setOutlineColor(sf::Color::Black);

    cardShape.setOutlineThickness(2.0f);

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
    // Territory Shapes
    //---------------------------------------------------------

    territoryShapes.reserve(territoryVertices.size());

    for (const auto& polygonVertices : territoryVertices)
    {
        if (polygonVertices.size() < 3)
        {
            continue;
        }

        std::vector<sf::Vertex> triangles = polyTri(polygonVertices);

        sf::VertexArray territoryShape(sf::PrimitiveType::Triangles);

        for (auto vertex : triangles)
        {
            vertex.color = sf::Color(80, 80, 80);

            territoryShape.append(vertex);
        }

        territoryShapes.push_back(std::move(territoryShape));
    }
}

//---------------------------------------------------------
// Position
//---------------------------------------------------------

void CardGraphics::setPosition(sf::Vector2f position)
{
    cardShape.setPosition(position);

    cardTypeText.setPosition({position.x + 10.0f, position.y + 10.0f});

    if (territoryShapes.empty())
    {
        return;
    }

    //---------------------------------------------------------
    // Combined Territory Bounds
    //---------------------------------------------------------

    bool boundsSet = false;

    float minX = 0.0f;
    float maxX = 0.0f;
    float minY = 0.0f;
    float maxY = 0.0f;

    for (const auto& shape : territoryShapes)
    {
        for (std::size_t i = 0; i < shape.getVertexCount(); ++i)
        {
            sf::Vector2f point = shape[i].position;

            if (!boundsSet)
            {
                minX = maxX = point.x;
                minY = maxY = point.y;
                boundsSet = true;
            }
            else
            {
                minX = std::min(minX, point.x);
                maxX = std::max(maxX, point.x);
                minY = std::min(minY, point.y);
                maxY = std::max(maxY, point.y);
            }
        }
    }

    if (!boundsSet)
    {
        return;
    }

    float width = maxX - minX;
    float height = maxY - minY;

    if (width <= 0.0f || height <= 0.0f)
    {
        return;
    }

    //---------------------------------------------------------
    // Shared Scale
    //---------------------------------------------------------

    float maxWidth = 100.0f;
    float maxHeight = 120.0f;

    float scaleX = maxWidth / width;
    float scaleY = maxHeight / height;

    territoryScale = std::min(scaleX, scaleY);

    float scaledWidth = width * territoryScale;

    //---------------------------------------------------------
    // Shared Position
    //---------------------------------------------------------

    float territoryX = position.x + (140.0f - scaledWidth) / 2.0f;

    float territoryY = position.y + 55.0f;

    territoryPosition = {territoryX - minX * territoryScale, territoryY - minY * territoryScale};
}

//---------------------------------------------------------
// Rotation
//---------------------------------------------------------

void CardGraphics::setRotation(sf::Angle rotation)
{
    cardShape.setRotation(rotation);
    cardTypeText.setRotation(rotation);

    territoryRotation = rotation;
}

//---------------------------------------------------------
// Selection
//---------------------------------------------------------

void CardGraphics::setSelected(bool newSelected)
{
    selected = newSelected;

    if (selected)
    {
        cardShape.setOutlineColor(sf::Color::White);

        cardShape.setOutlineThickness(5.0f);
    }
    else
    {
        cardShape.setOutlineColor(sf::Color::Black);

        cardShape.setOutlineThickness(2.0f);
    }
}

bool CardGraphics::isSelected() const { return selected; }

//---------------------------------------------------------
// Access
//---------------------------------------------------------

CardType CardGraphics::getCardType() const { return cardType; }

sf::FloatRect CardGraphics::getBounds() const { return cardShape.getGlobalBounds(); }

bool CardGraphics::contains(sf::Vector2f point) const
{
    return cardShape.getGlobalBounds().contains(point);
}

//---------------------------------------------------------
// Draw
//---------------------------------------------------------

void CardGraphics::draw(sf::RenderWindow& window) const
{
    window.draw(cardShape);

    sf::Transform transform;

    transform.translate(territoryPosition);
    transform.rotate(territoryRotation);
    transform.scale({territoryScale, territoryScale});

    sf::RenderStates states;
    states.transform = transform;

    for (const auto& territoryShape : territoryShapes)
    {
        window.draw(territoryShape, states);
    }

    window.draw(cardTypeText);
}

}  // namespace risk
