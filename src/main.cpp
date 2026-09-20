#include <iostream>
#include "risk/graphics/ui/GameWindow.h"

int main()
{
    risk::GameWindow window(
        sf::VideoMode({ 1920, 1080 }),
        "Risk"
    );

    window.run();

    return 0;
}