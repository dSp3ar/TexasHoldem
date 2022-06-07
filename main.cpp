#include "main.h"

int main(void)
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "TEXAS HOLDEM POKER", sf::Style::Fullscreen);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        Sleep(7000);
        static bool intro = true;
        if (intro)
            Introdaction(window);
        intro = false;
        
        static bool menu = true;
        if (menu)
            Menu(window);
        menu = false;

        window.display();
    }

    return 0;
}

