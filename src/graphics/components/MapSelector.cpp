#include "risk/graphics/components/MapSelector.h"

namespace risk {

    MapSelector::MapSelector(
        const sf::Font& font)
        : mapTitleClassicText(font)
    {
        //=========================================================
        // Colours
        //=========================================================

        const sf::Color brass(
            128,
            105,
            65);

        const sf::Color parchment(
            235,
            220,
            185,
            100);

        const sf::Color textColour(
            55,
            47,
            38);

        //=========================================================
        // Map preview box
        //=========================================================

        mapImageBox.setSize({
            380.f,
            160.f
            });

        mapImageBox.setPosition({
            770.f,
            325.f
            });

        mapImageBox.setFillColor(
            sf::Color::Transparent);

        mapImageBox.setOutlineColor(
            brass);

        mapImageBox.setOutlineThickness(
            2.f);

        //=========================================================
        // Map preview image
        //=========================================================

        if (mapTexture.loadFromFile(
            "data/graphics/components/ClassicMapPreview.png"))
        {
            mapTexture.setSmooth(true);

            mapSprite.emplace(
                mapTexture);

            sf::Vector2u textureSize =
                mapTexture.getSize();

            mapSprite->setScale({
                380.f /
                    static_cast<float>(textureSize.x),

                160.f /
                    static_cast<float>(textureSize.y)
                });

            mapSprite->setPosition({
                770.f,
                325.f
                });
        }

        //=========================================================
        // Map title box
        //=========================================================

        mapTitleBox.setSize({
            220.f,
            40.f
            });

        mapTitleBox.setPosition({
            850.f,
            435.f
            });

        mapTitleBox.setFillColor(
            parchment);

        mapTitleBox.setOutlineColor(
            brass);

        mapTitleBox.setOutlineThickness(
            2.f);

        //=========================================================
        // Classic map title
        //=========================================================

        mapTitleClassicText.setString(
            "CLASSIC");

        mapTitleClassicText.setCharacterSize(
            24);

        mapTitleClassicText.setFillColor(
            textColour);

        sf::FloatRect titleBounds =
            mapTitleClassicText.getLocalBounds();

        mapTitleClassicText.setOrigin({
            titleBounds.position.x +
                titleBounds.size.x / 2.f,

            titleBounds.position.y +
                titleBounds.size.y / 2.f
            });

        mapTitleClassicText.setPosition({
            960.f,
            455.f
            });

        //=========================================================
        // Left arrow box
        //=========================================================

        leftArrowBox.setSize({
            55.f,
            55.f
            });

        leftArrowBox.setPosition({
            690.f,
            375.f
            });

        leftArrowBox.setFillColor(
            parchment);

        leftArrowBox.setOutlineColor(
            brass);

        leftArrowBox.setOutlineThickness(
            2.f);

        //=========================================================
        // Left arrow
        //=========================================================

        leftArrow.setPointCount(3);

        leftArrow.setPoint(
            0,
            { 0.f, 15.f });

        leftArrow.setPoint(
            1,
            { 22.f, 0.f });

        leftArrow.setPoint(
            2,
            { 22.f, 30.f });

        leftArrow.setFillColor(
            brass);

        leftArrow.setPosition({
            706.f,
            387.f
            });

        //=========================================================
        // Right arrow box
        //=========================================================

        rightArrowBox.setSize({
            55.f,
            55.f
            });

        rightArrowBox.setPosition({
            1175.f,
            375.f
            });

        rightArrowBox.setFillColor(
            parchment);

        rightArrowBox.setOutlineColor(
            brass);

        rightArrowBox.setOutlineThickness(
            2.f);

        //=========================================================
        // Right arrow
        //=========================================================

        rightArrow.setPointCount(3);

        rightArrow.setPoint(
            0,
            { 0.f, 0.f });

        rightArrow.setPoint(
            1,
            { 22.f, 15.f });

        rightArrow.setPoint(
            2,
            { 0.f, 30.f });

        rightArrow.setFillColor(
            brass);

        rightArrow.setPosition({
            1192.f,
            387.f
            });
    }

    //=========================================================
    // Draw
    //=========================================================

    void MapSelector::draw(
        sf::RenderWindow& window)
    {
        // Map preview backing / border
        window.draw(mapImageBox);

        // Map preview image
        if (mapSprite)
        {
            window.draw(*mapSprite);
        }

        // Map title overlays the preview image
        window.draw(mapTitleBox);
        window.draw(mapTitleClassicText);

        // Selection arrows
        window.draw(leftArrowBox);
        window.draw(leftArrow);

        window.draw(rightArrowBox);
        window.draw(rightArrow);
    }

    //=========================================================
    // Getters
    //=========================================================

    const sf::RectangleShape&
        MapSelector::getLeftArrowBox() const
    {
        return leftArrowBox;
    }

    const sf::RectangleShape&
        MapSelector::getRightArrowBox() const
    {
        return rightArrowBox;
    }

} // namespace risk