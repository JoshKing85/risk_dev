#include "risk/graphics/game_elements/FeatureGraphics.h"

namespace risk {

    FeatureGraphics::FeatureGraphics(
        const std::vector<Feature>& features)
    {
        for (const auto& feature : features)
        {
            if (feature.featureType == FeatureType::River)
            {
                sf::VertexArray river(
                    sf::PrimitiveType::LineStrip);

                for (const auto& point : feature.vertices)
                {
                    river.append(
                        sf::Vertex{
                            point,
                            sf::Color(85, 115, 130)
                        }
                    );
                }

                featureShapes.push_back(std::move(river));
            }
        }
    }

    void FeatureGraphics::draw(
        sf::RenderWindow& window) const
    {
        for (const auto& shape : featureShapes)
        {
            window.draw(shape);
        }
    }

}