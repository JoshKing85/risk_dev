#include "risk/graphics/ui/LoadingUI.h"

namespace risk {

    LoadingUI::LoadingUI()
        : loadingText(font)
    {
        font.openFromFile("C:/Windows/Fonts/arial.ttf");

        // Loading box
        loadingBox.setSize({ 400.f, 150.f });
        loadingBox.setPosition({ 400.f, 285.f });
        loadingBox.setFillColor(sf::Color(50, 50, 50));
        loadingBox.setOutlineColor(sf::Color::White);
        loadingBox.setOutlineThickness(2.f);

        // Loading text
        loadingText.setString("Loading...");
        loadingText.setCharacterSize(32);
        loadingText.setFillColor(sf::Color::White);
        loadingText.setPosition({ 525.f, 335.f });
    }

    void LoadingUI::draw(sf::RenderWindow& window)
    {
        window.draw(loadingBox);
        window.draw(loadingText);
    }

} // namespace risk