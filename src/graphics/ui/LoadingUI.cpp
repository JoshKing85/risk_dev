#include "risk/graphics/ui/LoadingUI.h"

#include <stdexcept>

namespace risk {

    //=========================================================
    // CONSTRUCTOR
    //=========================================================

    LoadingUI::LoadingUI()
        : loadingText(font)
    {
        //-----------------------------------------------------
        // Font
        //-----------------------------------------------------

        if (!font.openFromFile(
            "C:/Windows/Fonts/georgia.ttf"))
        {
            throw std::runtime_error(
                "Could not load loading screen font");
        }

        //-----------------------------------------------------
        // Background
        //-----------------------------------------------------

        if (!backgroundTexture.loadFromFile(
            "data/graphics/components/CuirassierWaterloo.png"))
        {
            throw std::runtime_error(
                "Could not load loading screen background");
        }

        backgroundTexture.setSmooth(true);

        backgroundSprite.emplace(
            backgroundTexture);

        const sf::Vector2u textureSize =
            backgroundTexture.getSize();

        const float scaleX =
            1920.0f /
            static_cast<float>(textureSize.x);

        const float scaleY =
            1080.0f /
            static_cast<float>(textureSize.y);

        backgroundSprite->setScale({
            scaleX,
            scaleY
            });

        //-----------------------------------------------------
        // Background dampener
        //-----------------------------------------------------

        backgroundDampener.setPrimitiveType(
            sf::PrimitiveType::TriangleStrip);

        backgroundDampener.resize(4);

        backgroundDampener[0].position =
        { 0.f, 350.f };

        backgroundDampener[0].color =
            sf::Color(225, 215, 195, 64);

        backgroundDampener[1].position =
        { 0.f, 1080.f };

        backgroundDampener[1].color =
            sf::Color(225, 215, 195, 64);

        backgroundDampener[2].position =
        { 700.f, 350.f };

        backgroundDampener[2].color =
            sf::Color(225, 215, 195, 0);

        backgroundDampener[3].position =
        { 700.f, 1080.f };

        backgroundDampener[3].color =
            sf::Color(225, 215, 195, 0);

        //-----------------------------------------------------
        // Loading banner
        //-----------------------------------------------------

        loadingBanner.setSize({
            620.f,
            110.f
            });

        loadingBanner.setPosition({
            650.f,
            485.f
            });

        loadingBanner.setFillColor(
            sf::Color(232, 216, 177, 235));

        loadingBanner.setOutlineColor(
            sf::Color(128, 105, 65));

        loadingBanner.setOutlineThickness(
            2.f);

        //-----------------------------------------------------
        // Decorative lines
        //-----------------------------------------------------

        topLine.setSize({
            560.f,
            1.f
            });

        topLine.setPosition({
            680.f,
            500.f
            });

        topLine.setFillColor(
            sf::Color(128, 105, 65));

        bottomLine.setSize({
            560.f,
            1.f
            });

        bottomLine.setPosition({
            680.f,
            579.f
            });

        bottomLine.setFillColor(
            sf::Color(128, 105, 65));

        //-----------------------------------------------------
        // Loading text
        //-----------------------------------------------------

        loadingText.setString(
            "FORMING THE LINES...");

        loadingText.setCharacterSize(
            28);

        loadingText.setStyle(
            sf::Text::Bold);

        loadingText.setFillColor(
            sf::Color(55, 47, 38));
    }


    //=========================================================
    // LOADING TEXT
    //=========================================================

    void LoadingUI::updateLoadingText(
        float elapsedSeconds)
    {
        if (elapsedSeconds < 1.2f)
        {
            loadingText.setString(
                "FORMING THE LINES...");
        }
        else if (elapsedSeconds < 2.4f)
        {
            loadingText.setString(
                "POSITIONING THE CANNONS...");
        }
        else
        {
            loadingText.setString(
                "MUSTERING THE CAVALRY...");
        }

        const sf::FloatRect bounds =
            loadingText.getLocalBounds();

        loadingText.setOrigin({
            bounds.position.x +
                bounds.size.x / 2.0f,
            bounds.position.y +
                bounds.size.y / 2.0f
            });

        loadingText.setPosition({
            960.f,
            540.f
            });
    }


    //=========================================================
    // DRAW
    //=========================================================

    void LoadingUI::draw(
        sf::RenderWindow& window,
        float elapsedSeconds)
    {
        updateLoadingText(
            elapsedSeconds);

        //-----------------------------------------------------
        // Background
        //-----------------------------------------------------

        if (backgroundSprite.has_value())
        {
            window.draw(
                *backgroundSprite);
        }

        window.draw(
            backgroundDampener);

        //-----------------------------------------------------
        // Banner
        //-----------------------------------------------------

        window.draw(
            loadingBanner);

        window.draw(
            topLine);

        window.draw(
            bottomLine);

        window.draw(
            loadingText);
    }

} // namespace risk