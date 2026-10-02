#include "risk/graphics/components/DebugGrid.h"

#include <stdexcept>
#include <string>

namespace risk {

    DebugGrid::DebugGrid()
        : gridLines(sf::PrimitiveType::Lines)
    {
        const float width = 1920.f;
        const float height = 1080.f;
        const float spacing = 50.f;

        const sf::Color gridColour(
            0,
            100,
            255,
            65);

        //=====================================================
        // Font
        //=====================================================

        if (!font.openFromFile(
            "C:/Windows/Fonts/arial.ttf"))
        {
            throw std::runtime_error(
                "Could not load debug grid font");
        }

        //=====================================================
        // Vertical lines
        //=====================================================

        for (float x = 0.f;
            x <= width;
            x += spacing)
        {
            sf::Vertex topVertex;
            topVertex.position = {
                x,
                0.f
            };
            topVertex.color = gridColour;

            sf::Vertex bottomVertex;
            bottomVertex.position = {
                x,
                height
            };
            bottomVertex.color = gridColour;

            gridLines.append(
                topVertex);

            gridLines.append(
                bottomVertex);
        }

        //=====================================================
        // Horizontal lines
        //=====================================================

        for (float y = 0.f;
            y <= height;
            y += spacing)
        {
            sf::Vertex leftVertex;
            leftVertex.position = {
                0.f,
                y
            };
            leftVertex.color = gridColour;

            sf::Vertex rightVertex;
            rightVertex.position = {
                width,
                y
            };
            rightVertex.color = gridColour;

            gridLines.append(
                leftVertex);

            gridLines.append(
                rightVertex);
        }

        //=====================================================
        // Column labels
        //=====================================================

        for (int x = 500;
            x < static_cast<int>(width);
            x += 500)
        {
            labels.emplace_back(
                font,
                std::to_string(x),
                18);

            labels.back().setFillColor(
                sf::Color::Blue);

            labels.back().setPosition({
                static_cast<float>(x) + 5.f,
                5.f
                });
        }

        //=====================================================
        // Row labels
        //=====================================================

        for (int y = 500;
            y < static_cast<int>(height);
            y += 500)
        {
            labels.emplace_back(
                font,
                std::to_string(y),
                18);

            labels.back().setFillColor(
                sf::Color::Blue);

            labels.back().setPosition({
                5.f,
                static_cast<float>(y) + 5.f
                });
        }
    }

    void DebugGrid::draw(
        sf::RenderWindow& window) const
    {
        window.draw(
            gridLines);

        for (const auto& label : labels)
        {
            window.draw(
                label);
        }
    }

} // namespace risk