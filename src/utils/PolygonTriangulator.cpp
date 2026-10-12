
#include "risk/utils/PolygonTriangulator.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

namespace risk
{

std::vector<sf::Vertex> polyTri(const std::vector<sf::Vector2f>& vertices)
{
    std::vector<sf::Vertex> triangles;

    if (vertices.size() < 3)
    {
        return triangles;
    }

    //-----------------------------------------------------
    // Remove consecutive duplicate vertices
    //-----------------------------------------------------

    std::vector<sf::Vector2f> points;

    for (const auto& point : vertices)
    {
        if (points.empty() || points.back() != point)
        {
            points.push_back(point);
        }
    }

    if (points.size() > 1)
    {
        if (points.front() == points.back())
        {
            points.pop_back();
        }
    }

    if (points.size() < 3)
    {
        return triangles;
    }

    //-----------------------------------------------------
    // Determine polygon winding (signed area)
    //-----------------------------------------------------

    double signedArea = 0.0;

    for (std::size_t i = 0; i < points.size(); i++)
    {
        const auto& a = points[i];
        const auto& b = points[(i + 1) % points.size()];

        signedArea += static_cast<double>(a.x) * b.y - static_cast<double>(b.x) * a.y;
    }

    if (std::abs(signedArea) < 0.00000001)
    {
        throw std::runtime_error("polyTri: polygon has no area");
    }

    //-----------------------------------------------------
    // Create vertex indices in positive winding order
    //-----------------------------------------------------

    std::vector<std::size_t> indices(points.size());

    for (std::size_t i = 0; i < points.size(); i++)
    {
        indices[i] = i;
    }

    if (signedArea < 0.0)
    {
        std::reverse(indices.begin(), indices.end());
    }

    //-----------------------------------------------------
    // Cross product
    //-----------------------------------------------------

    auto cross = [](
        const sf::Vector2f& a, 
        const sf::Vector2f& b, 
        const sf::Vector2f& c) -> double
    {
        return static_cast<double>(b.x - a.x) * (c.y - a.y) -
               static_cast<double>(b.y - a.y) * (c.x - a.x);
    };

    //-----------------------------------------------------
    // Check whether a point lies inside a triangle
    //-----------------------------------------------------

    auto pointInTriangle = [&](const sf::Vector2f& p, const sf::Vector2f& a, const sf::Vector2f& b,
                               const sf::Vector2f& c) -> bool
    { return cross(a, b, p) >= 0.0 && cross(b, c, p) >= 0.0 && cross(c, a, p) >= 0.0; };

    //-----------------------------------------------------
    // Clip ears until only three vertices remain
    //-----------------------------------------------------

    while (indices.size() > 3)
    {
        bool earFound = false;

        for (std::size_t i = 0; i < indices.size(); ++i)
        {
            //-----------------------------------------------------
            // Select three consecutive vertices
            //-----------------------------------------------------

            std::size_t prev = (i + indices.size() - 1) % indices.size();

            std::size_t curr = i;

            std::size_t next = (i + 1) % indices.size();

            const sf::Vector2f& a = points[indices[prev]];

            const sf::Vector2f& b = points[indices[curr]];

            const sf::Vector2f& c = points[indices[next]];

            //-----------------------------------------------------
            // Check whether B is a convex corner
            //-----------------------------------------------------

            if (cross(a, b, c) <= 0.0)
            {
                continue;
            }

            //-----------------------------------------------------
            // Check whether another vertex is inside ABC
            //-----------------------------------------------------

            bool containsVertex = false;

            for (std::size_t j = 0; j < indices.size(); ++j)
            {
                if (j == prev || j == curr || j == next)
                {
                    continue;
                }

                const sf::Vector2f& p = points[indices[j]];

                if (pointInTriangle(p, a, b, c))
                {
                    containsVertex = true;
                    break;
                }
            }

            if (containsVertex)
            {
                continue;
            }

            //-----------------------------------------------------
            // Valid ear: add triangle to output
            //-----------------------------------------------------

            triangles.push_back(sf::Vertex{a, sf::Color::White});

            triangles.push_back(sf::Vertex{b, sf::Color::White});

            triangles.push_back(sf::Vertex{c, sf::Color::White});

            //-----------------------------------------------------
            // Remove B from the remaining polygon
            //-----------------------------------------------------

            indices.erase(indices.begin() + curr);

            earFound = true;
            break;
        }

        //-----------------------------------------------------
        // No valid ear found - diagnostic output
        //-----------------------------------------------------

        if (!earFound)
        {
            std::cerr << "\n[polyTri] Failed with " << indices.size() << " vertices remaining:\n";

            for (std::size_t i = 0; i < indices.size(); ++i)
            {
                const sf::Vector2f& p = points[indices[i]];

                std::cerr << i << ": (" << p.x << ", " << p.y << ")\n";
            }

            throw std::runtime_error("polyTri: unable to find a valid ear");
        }
    }

    //-----------------------------------------------------
    // Add the final remaining triangle
    //-----------------------------------------------------

    const sf::Vector2f& a = points[indices[0]];

    const sf::Vector2f& b = points[indices[1]];

    const sf::Vector2f& c = points[indices[2]];

    triangles.push_back(sf::Vertex{a, sf::Color::White});

    triangles.push_back(sf::Vertex{b, sf::Color::White});

    triangles.push_back(sf::Vertex{c, sf::Color::White});

    return triangles;
}

}  // namespace risk
