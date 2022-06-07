#include "introduction.h"

void Introdaction(sf::RenderWindow& window)
{
    std::string filename;
    sf::Music music;
    sf::Font font;

    music.openFromFile("song.wav");
    music.play();

    font.loadFromFile("font.ttf");
    sf::Text text("", font, 50);

    char temp[4];
    for (short i = 1; i < 117; ++i)
    {
        filename = ".\\fps\\c (";
        sf::Texture intro_texture;

        _itoa(i, temp, 10);
        filename += temp;
        filename += ").jpg";
        intro_texture.loadFromFile(filename);

        sf::Sprite intro_sprite(intro_texture);

        window.draw(intro_sprite);
        window.display();
    }
    sf::Texture texture_scale;
    texture_scale.loadFromFile("start.jpg");
    sf::Sprite scale(texture_scale);
    window.draw(scale);

    text.setString("TEXAS HOLDEM POKER\n\tCREATED\n\t\tBY DENYS SPYS\n\t\t\t227 GROUP\n\t\t\t\t2020\n\n\n\n\t\tPRESS ENTER TO CONTINUE...");
    text.setPosition(250, 300);
    while (!(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)))
    {
        window.draw(scale);
        window.draw(text);
        window.display();
        window.clear(sf::Color(0, 0, 0, 0));
    }
}

