
#include "risk/graphics/game_elements/TerritoryGraphics.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <string>

#include "risk/utils/PolygonTriangulator.h"

namespace risk
{

    TerritoryGraphics::TerritoryGraphics(TerritoryID territoryID, ContinentID continentID, int playerID,
                                     const std::string& title,
                                     const std::vector<std::vector<sf::Vector2f>>& vertices,
                                     unsigned int titleCharacterSize,
                                     unsigned int troopCharacterSize, float outlineThickness,
                                     const sf::Font& font)
    : territoryID(territoryID),
      continentID(continentID),
      playerID(playerID),
      title(title),
      vertices(vertices),
      titleText(font),
      troopCountText(font),
      outlineThickness(outlineThickness)
{
        //---------------------------------------------------------
        // Territory fills
        //---------------------------------------------------------

        fills.reserve(vertices.size());
        outlines.reserve(vertices.size());

        for (const auto& polygonVertices : vertices)
        {
            std::vector<sf::Vertex> triangles = polyTri(polygonVertices);

            sf::VertexArray fill(sf::PrimitiveType::Triangles);

            for (const auto& vertex : triangles)
            {
                fill.append(vertex);
            }

            fills.push_back(std::move(fill));

            outlines.emplace_back(sf::PrimitiveType::Triangles);
        }

        updateOutlines();

        //---------------------------------------------------------
        // Calculate territory centre
        //---------------------------------------------------------

        // Calculate polygon area using the shoelace formula
        auto calculateArea = [](const std::vector<sf::Vector2f>& polygon)
        {
            float area = 0.0f;

            for (std::size_t i = 0; i < polygon.size(); ++i)
            {
                const auto& a = polygon[i];
                const auto& b = polygon[(i + 1) % polygon.size()];

                area += a.x * b.y - b.x * a.y;
            }

            return std::abs(area) / 2.0f;
        };

        // Select the largest polygon by area
        const auto& polygon =
            *std::max_element(vertices.begin(), vertices.end(), [&](const auto& a, const auto& b)
                              { return calculateArea(a) < calculateArea(b); });

        //---------------------------------------------------------
        // Calculate polygon centroid
        //---------------------------------------------------------

        float signedArea = 0.0f;
        float centroidX = 0.0f;
        float centroidY = 0.0f;

        for (std::size_t i = 0; i < polygon.size(); ++i)
        {
            const auto& a = polygon[i];
            const auto& b = polygon[(i + 1) % polygon.size()];

            float cross = a.x * b.y - b.x * a.y;

            signedArea += cross;

            centroidX += (a.x + b.x) * cross;
            centroidY += (a.y + b.y) * cross;
        }

        signedArea *= 0.5f;

        sf::Vector2f centre(centroidX / (6.0f * signedArea), centroidY / (6.0f * signedArea));

        // Apply territory-specific adjustments
        centre += getLabelOffset();

        //---------------------------------------------------------
        // Territory title
        //---------------------------------------------------------

        titleText.setString(title);
        titleText.setCharacterSize(titleCharacterSize);
        titleText.setFillColor(sf::Color::White);

        sf::FloatRect titleBounds = titleText.getLocalBounds();

        titleText.setOrigin({titleBounds.position.x + titleBounds.size.x / 2.0f,
                             titleBounds.position.y + titleBounds.size.y / 2.0f});

        titleText.setPosition({centre.x, centre.y - 10.0f});

        //---------------------------------------------------------
        // Troop count
        //---------------------------------------------------------

        troopCountText.setString("0");
        troopCountText.setCharacterSize(troopCharacterSize);
        troopCountText.setFillColor(sf::Color::White);

        sf::FloatRect troopBounds = troopCountText.getLocalBounds();

        troopCountText.setOrigin({troopBounds.position.x + troopBounds.size.x / 2.0f,
                                  troopBounds.position.y + troopBounds.size.y / 2.0f});

        troopCountText.setPosition({centre.x, centre.y + 10.0f});

        setPlayerID(playerID);
    }
    //-------------------------------------------------------------
    // Territory outline
    //-------------------------------------------------------------

        void TerritoryGraphics::updateOutlines()
        {
            float thickness = selected ? 5.0f : outlineThickness;
            sf::Color colour = selected ? sf::Color::White : sf::Color::Black;
            constexpr int circleSegments = 12;
            constexpr float pi = 3.14159265f;

            for (std::size_t polygonIndex = 0; polygonIndex < vertices.size(); ++polygonIndex)
            {
                const auto& polygon = vertices[polygonIndex];
                sf::VertexArray& outline = outlines[polygonIndex];
                outline.clear();

                if (polygon.size() < 2 || thickness <= 0.0f) continue;

                for (std::size_t i = 0; i < polygon.size(); ++i)
                {
                    const sf::Vector2f& a = polygon[i];
                    const sf::Vector2f& b = polygon[(i + 1) % polygon.size()];
                    sf::Vector2f direction = b - a;
                    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                    if (length == 0.0f) continue;

                    sf::Vector2f normal(-direction.y / length, direction.x / length);
                    sf::Vector2f offset = normal * (thickness / 2.0f);
                    sf::Vector2f p1 = a + offset;
                    sf::Vector2f p2 = b + offset;
                    sf::Vector2f p3 = b - offset;
                    sf::Vector2f p4 = a - offset;

                    outline.append(sf::Vertex{p1, colour});
                    outline.append(sf::Vertex{p2, colour});
                    outline.append(sf::Vertex{p3, colour});
                    outline.append(sf::Vertex{p1, colour});
                    outline.append(sf::Vertex{p3, colour});
                    outline.append(sf::Vertex{p4, colour});
                }

                // Rounded joins preserve the smooth coastlines from the last pass.
                float radius = thickness / 2.0f;
                for (const sf::Vector2f& centre : polygon)
                {
                    for (int j = 0; j < circleSegments; ++j)
                    {
                        float angle1 = 2.0f * pi * static_cast<float>(j) / circleSegments;
                        float angle2 = 2.0f * pi * static_cast<float>(j + 1) / circleSegments;
                        sf::Vector2f p1(centre.x + std::cos(angle1) * radius,
                                        centre.y + std::sin(angle1) * radius);
                        sf::Vector2f p2(centre.x + std::cos(angle2) * radius,
                                        centre.y + std::sin(angle2) * radius);
                        outline.append(sf::Vertex{centre, colour});
                        outline.append(sf::Vertex{p1, colour});
                        outline.append(sf::Vertex{p2, colour});
                    }
                }
            }
    }

    //-------------------------------------------------------------
    // Player colour
    //-------------------------------------------------------------

    void TerritoryGraphics::setPlayerID(int newPlayerID)
    {
        // Ownership and faction appearance are separate concerns.
        playerID = newPlayerID;
    }

    void TerritoryGraphics::setFactionColour(int avatarID)
    {
        constexpr std::uint8_t alpha = 205;
        sf::Color playerColour(100, 100, 100, alpha);

        switch (avatarID)
        {
            case 0:
                playerColour = sf::Color(41, 79, 120, alpha);
                break; // France

            case 1:
                playerColour = sf::Color(183, 71, 54, alpha);
                break; // Britain

            case 2:
                playerColour = sf::Color(69, 65, 58, alpha);
                break; // Prussia

            case 3:
                playerColour = sf::Color(228, 212, 173, alpha);
                break; // Austria

            case 4:
                playerColour = sf::Color(214, 160, 56, alpha);
                break; // Spain

            case 5:
                playerColour = sf::Color(115, 139, 89, alpha);
                break; // Russia

            default:
                break;
        }

        for (auto& fill : fills)
        {
            for (std::size_t i = 0; i < fill.getVertexCount(); ++i)
            {
                fill[i].color = playerColour;
            }
        }
    }

    //-------------------------------------------------------------
    // Troop count
    //-------------------------------------------------------------

    void TerritoryGraphics::setTroopCount(int troopCount)
    {
        troopCountText.setString(std::to_string(troopCount));
    }

    //-------------------------------------------------------------
    // Selection
    //-------------------------------------------------------------

    void TerritoryGraphics::setSelected(bool isSelected)
    {
        selected = isSelected;

        updateOutlines();
    }

    sf::Vector2f TerritoryGraphics::getLabelOffset() const
    {
        switch (territoryID)
        {
            case TerritoryID::England:
                return {13.f, -2.f};

            case TerritoryID::Scotland:
                return {-2.f, 3.f};

            case TerritoryID::Wales:
                return {3.f, 0.f};

            case TerritoryID::Norway:
                return {-30.f,30.f};

            case TerritoryID::Sweden:
                return {-30.f, 50.f};

            case TerritoryID::Finland:
                return {0.f, 15.f};

            case TerritoryID::Sicily:
                return {5.f, 2.f};

            case TerritoryID::Bulgaria:
                return {5.f, 7.f};

            case TerritoryID::Tuscany:
                return {2.f, 5.f};
            default:
                return {0.f, 0.f};
        }
    }
    //-------------------------------------------------------------
    // Draw
    //-------------------------------------------------------------

    void TerritoryGraphics::draw(sf::RenderWindow& window) const
    {
        sf::RenderStates states;
        states.transform.translate({0.f, 15.f});

        for (const auto& fill : fills)
        {
            window.draw(fill, states);
        }

        for (const auto& outline : outlines)
        {
            window.draw(outline, states);
        }

        window.draw(titleText, states);
        window.draw(troopCountText, states);
    }

    //-------------------------------------------------------------
    // Territory ID
    //-------------------------------------------------------------

    TerritoryID TerritoryGraphics::getTerritoryID() const { return territoryID; }

    //-------------------------------------------------------------
    // Player ID
    //-------------------------------------------------------------

    int TerritoryGraphics::getPlayerID() const { return playerID; }

    //-------------------------------------------------------------
    // Bounds
    //-------------------------------------------------------------

    sf::FloatRect TerritoryGraphics::getBounds() const
    {
        bool hasPoint = false;

        float left = 0.0f;
        float top = 0.0f;
        float right = 0.0f;
        float bottom = 0.0f;

        for (const auto& polygon : vertices)
        {
            for (const auto& point : polygon)
            {
                if (!hasPoint)
                {
                    left = right = point.x;
                    top = bottom = point.y;
                    hasPoint = true;
                }
                else
                {
                    left = std::min(left, point.x);
                    top = std::min(top, point.y);

                    right = std::max(right, point.x);
                    bottom = std::max(bottom, point.y);
                }
            }
        }

        if (!hasPoint)
        {
            return {};
        }

        return sf::FloatRect({left, top}, {right - left, bottom - top});
    }

    //-------------------------------------------------------------
    // Point inside territory
    //-------------------------------------------------------------

    bool TerritoryGraphics::contains(sf::Vector2f point) const
    {
        for (const auto& polygon : vertices)
        {
            std::size_t pointCount = polygon.size();

            if (pointCount < 3)
            {
                continue;
            }

            //-----------------------------------------------------
            // Quick rejection
            //-----------------------------------------------------

            float left = polygon[0].x;
            float right = polygon[0].x;
            float top = polygon[0].y;
            float bottom = polygon[0].y;

            for (const auto& vertex : polygon)
            {
                left = std::min(left, vertex.x);
                right = std::max(right, vertex.x);

                top = std::min(top, vertex.y);
                bottom = std::max(bottom, vertex.y);
            }

            if (point.x < left || point.x > right || point.y < top || point.y > bottom)
            {
                continue;
            }

            //-----------------------------------------------------
            // Point-in-polygon test
            //-----------------------------------------------------

            bool inside = false;

            for (std::size_t i = 0, j = pointCount - 1; i < pointCount; j = i++)
            {
                const sf::Vector2f& pointI = polygon[i];

                const sf::Vector2f& pointJ = polygon[j];

                bool intersects =
                    ((pointI.y > point.y) != (pointJ.y > point.y)) &&
                    (point.x <
                     (pointJ.x - pointI.x) * (point.y - pointI.y) / (pointJ.y - pointI.y) + pointI.x);

                if (intersects)
                {
                    inside = !inside;
                }
            }

            //-----------------------------------------------------
            // Any polygon belonging to this territory counts
            //-----------------------------------------------------

            if (inside)
            {
                return true;
            }
        }

        return false;
    }

    //-------------------------------------------------------------
    // Original vertices
    //-------------------------------------------------------------

    const std::vector<std::vector<sf::Vector2f>>& TerritoryGraphics::getVertices() const
    {
        return vertices;
    }

    //-------------------------------------------------------------
    // Title
    //-------------------------------------------------------------

    std::string TerritoryGraphics::getTitle() const { return title; }

}  // namespace risk
