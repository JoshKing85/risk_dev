#include "risk/graphics/game_elements/FeatureGraphics.h"

#include <algorithm>
#include <cmath>
#include <utility>

namespace risk
{

//---------------------------------------------------------
// Constructor
//---------------------------------------------------------

FeatureGraphics::FeatureGraphics(const std::vector<Feature>& features)
{
    const sf::Color mountainColour(42, 43, 40, 220);
    const sf::Color forestColour(35, 55, 40, 210);

    //---------------------------------------------------------
    // Helper: thick line segment
    //---------------------------------------------------------

    auto addThickLine = [&](sf::VertexArray& shape, sf::Vector2f start, sf::Vector2f end,
                            float thickness, sf::Color colour)
    {
        sf::Vector2f direction = end - start;

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length == 0.0f) return;

        sf::Vector2f normal(-direction.y / length, direction.x / length);

        normal *= thickness / 2.0f;

        sf::Vector2f a = start + normal;
        sf::Vector2f b = start - normal;
        sf::Vector2f c = end + normal;
        sf::Vector2f d = end - normal;

        shape.append(sf::Vertex{a, colour});
        shape.append(sf::Vertex{b, colour});
        shape.append(sf::Vertex{c, colour});

        shape.append(sf::Vertex{c, colour});
        shape.append(sf::Vertex{b, colour});
        shape.append(sf::Vertex{d, colour});
    };

    //---------------------------------------------------------
    // Helper: mountain peak
    //---------------------------------------------------------

    auto addMountain = [&](sf::VertexArray& shape, sf::Vector2f centre, float width, float height)
    {
        sf::Vector2f left(centre.x - width / 2.0f, centre.y + height / 2.0f);

        sf::Vector2f right(centre.x + width / 2.0f, centre.y + height / 2.0f);

        sf::Vector2f peak(centre.x, centre.y - height / 2.0f);

        addThickLine(shape, left, peak, 1.8f, mountainColour);
        addThickLine(shape, peak, right, 1.8f, mountainColour);

        addThickLine(shape, peak, {centre.x + width * 0.12f, centre.y + height * 0.32f}, 1.2f,
                     mountainColour);
    };

    //---------------------------------------------------------
    // Helper: tree symbol
    //---------------------------------------------------------

    auto addTree = [&](sf::VertexArray& shape, sf::Vector2f centre, float size)
    {
        sf::Vector2f top(centre.x, centre.y - size);

        sf::Vector2f left(centre.x - size * 0.55f, centre.y + size * 0.35f);

        sf::Vector2f right(centre.x + size * 0.55f, centre.y + size * 0.35f);

        shape.append(sf::Vertex{top, forestColour});
        shape.append(sf::Vertex{left, forestColour});
        shape.append(sf::Vertex{right, forestColour});

        addThickLine(shape, {centre.x, centre.y + size * 0.25f},
                     {centre.x, centre.y + size * 0.75f}, 1.2f, forestColour);
    };

    //---------------------------------------------------------
    // Generate feature geometry
    //---------------------------------------------------------

    for (const auto& feature : features)
    {
        if (feature.featureType == FeatureType::River)
        {
            createRiver(feature);
            continue;
        }

        sf::VertexArray shape(sf::PrimitiveType::Triangles);

        //-----------------------------------------------------
        // Mountains
        //-----------------------------------------------------

        if (feature.featureType == FeatureType::Mountain)
        {
            for (std::size_t i = 0; i + 1 < feature.vertices.size(); ++i)
            {
                sf::Vector2f start = feature.vertices[i];
                sf::Vector2f end = feature.vertices[i + 1];

                sf::Vector2f direction = end - start;

                float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

                if (length == 0.0f) continue;

                const float spacing = 12.0f;

                for (float distance = 0.0f; distance < length; distance += spacing)
                {
                    float t = distance / length;

                    sf::Vector2f position = start + direction * t;

                    addMountain(shape, position, 11.0f, 9.0f);
                }
            }
        }

        //-----------------------------------------------------
        // Forests
        //-----------------------------------------------------

        else if (feature.featureType == FeatureType::Forest)
        {
            for (const auto& point : feature.vertices)
            {
                addTree(shape, point, 6.0f);

                addTree(shape, {point.x - 8.0f, point.y + 7.0f}, 5.0f);

                addTree(shape, {point.x + 8.0f, point.y + 6.0f}, 5.5f);
            }
        }

        featureShapes.push_back(std::move(shape));
    }
}

//---------------------------------------------------------
// Create river
//---------------------------------------------------------

void FeatureGraphics::createRiver(const Feature& feature)
{
    const sf::Color riverColour(75, 115, 140, 230);
    const int subdivisions = 8;

    //---------------------------------------------------------
    // Catmull-Rom interpolation
    //---------------------------------------------------------

    auto interpolate =
        [](sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, float t)
    {
        float t2 = t * t;
        float t3 = t2 * t;

        return 0.5f * ((p1 * 2.0f) + (p2 - p0) * t + (p0 * 2.0f - p1 * 5.0f + p2 * 4.0f - p3) * t2 +
                       (p0 * -1.0f + p1 * 3.0f - p2 * 3.0f + p3) * t3);
    };

    //---------------------------------------------------------
    // Generate geometry for one river path
    //---------------------------------------------------------

    auto createPath = [&](const std::vector<sf::Vector2f>& points, float startWidth, float endWidth)
    {
        if (points.size() < 2) return;

        //-----------------------------------------------------
        // Generate smooth centreline
        //-----------------------------------------------------

        std::vector<sf::Vector2f> smoothPoints;

        for (std::size_t i = 0; i + 1 < points.size(); ++i)
        {
            sf::Vector2f p0 = (i == 0) ? points[i] : points[i - 1];

            sf::Vector2f p1 = points[i];
            sf::Vector2f p2 = points[i + 1];

            sf::Vector2f p3 = (i + 2 < points.size()) ? points[i + 2] : points[i + 1];

            for (int step = 0; step < subdivisions; ++step)
            {
                float t = static_cast<float>(step) / subdivisions;

                smoothPoints.push_back(interpolate(p0, p1, p2, p3, t));
            }
        }

        smoothPoints.push_back(points.back());

        //-----------------------------------------------------
        // Generate river triangles
        //-----------------------------------------------------

        sf::VertexArray river(sf::PrimitiveType::Triangles);

        for (std::size_t i = 0; i + 1 < smoothPoints.size(); ++i)
        {
            sf::Vector2f start = smoothPoints[i];
            sf::Vector2f end = smoothPoints[i + 1];

            sf::Vector2f direction = end - start;

            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if (length == 0.0f) continue;

            sf::Vector2f normal(-direction.y / length, direction.x / length);

            float progressStart =
                static_cast<float>(i) / static_cast<float>(smoothPoints.size() - 1);

            float progressEnd =
                static_cast<float>(i + 1) / static_cast<float>(smoothPoints.size() - 1);

            float widthStart = startWidth + (endWidth - startWidth) * progressStart;

            float widthEnd = startWidth + (endWidth - startWidth) * progressEnd;

            sf::Vector2f startNormal = normal * (widthStart / 2.0f);

            sf::Vector2f endNormal = normal * (widthEnd / 2.0f);

            sf::Vector2f a = start + startNormal;
            sf::Vector2f b = start - startNormal;
            sf::Vector2f c = end + endNormal;
            sf::Vector2f d = end - endNormal;

            river.append(sf::Vertex{a, riverColour});
            river.append(sf::Vertex{b, riverColour});
            river.append(sf::Vertex{c, riverColour});

            river.append(sf::Vertex{c, riverColour});
            river.append(sf::Vertex{b, riverColour});
            river.append(sf::Vertex{d, riverColour});
        }

        featureShapes.push_back(std::move(river));
    };

    //---------------------------------------------------------
    // Main river
    //---------------------------------------------------------

    createPath(feature.vertices, 1.5f, 4.5f);

    //---------------------------------------------------------
    // Tributaries
    //---------------------------------------------------------

    for (const auto& tributary : feature.tributaries)
    {
        createPath(tributary, 0.8f, 2.5f);
    }
}

//---------------------------------------------------------
// Draw
//---------------------------------------------------------

void FeatureGraphics::draw(sf::RenderWindow& window) const
{
    for (const auto& shape : featureShapes)
    {
        window.draw(shape);
    }
}

}  // namespace risk