#include "risk/graphics/components/FineMesh.h"

namespace risk {

    FineMesh::FineMesh()
        : minorLines(sf::PrimitiveType::Lines),
        majorLines(sf::PrimitiveType::Lines)
    {
        //---------------------------------------------------------
        // Vertical Lines
        //---------------------------------------------------------

        for (float x = 0.f;
            x <= canvasWidth;
            x += minorSpacing)
        {
            bool isMajor =
                static_cast<int>(x) %
                static_cast<int>(majorSpacing) == 0;

            sf::VertexArray& lines =
                isMajor ? majorLines : minorLines;

            sf::Vertex top;
            top.position = { x, 0.f };

            sf::Vertex bottom;
            bottom.position = { x, canvasHeight };

            if (isMajor)
            {
                top.color =
                    sf::Color(0, 0, 0, 100);

                bottom.color =
                    sf::Color(0, 0, 0, 100);
            }
            else
            {
                top.color =
                    sf::Color(0, 0, 0, 40);

                bottom.color =
                    sf::Color(0, 0, 0, 40);
            }

            lines.append(top);
            lines.append(bottom);
        }

        //---------------------------------------------------------
        // Horizontal Lines
        //---------------------------------------------------------

        for (float y = 0.f;
            y <= canvasHeight;
            y += minorSpacing)
        {
            bool isMajor =
                static_cast<int>(y) %
                static_cast<int>(majorSpacing) == 0;

           sf::VertexArray& lines =
                isMajor ? majorLines : minorLines;

            sf::Vertex left;
            left.position = { 0.f, y };

            sf::Vertex right;
            right.position = { canvasWidth, y };

            if (isMajor)
            {
                left.color =
                    sf::Color(0, 0, 0, 100);

                right.color =
                    sf::Color(0, 0, 0, 100);
            }
            else
            {
                left.color =
                    sf::Color(0, 0, 0, 40);

                right.color =
                    sf::Color(0, 0, 0, 40);
            }

            lines.append(left);
            lines.append(right);
        }
    }


    void FineMesh::draw(
        sf::RenderWindow& window) const
    {
        window.draw(minorLines);
        window.draw(majorLines);
    }

} // namespace risk