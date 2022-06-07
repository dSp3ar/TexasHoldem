#include "menu.h"

void Menu(sf::RenderWindow& window)
{
    sf::Music music;
    std::string filename;
    sf::Font font;

    music.openFromFile("menu_song.wav");
    music.play();
    music.setLoop(true);

    font.loadFromFile("font.ttf");
    sf::Text Play("", font, 80);
    sf::Text Rules("", font, 80);
    sf::Text Exit("", font, 80);

    char temp[4];
    short i = 1;
    for (; i < 110; ++i)
    {
        filename = ".\\frames\\f (";
        sf::Texture intro_texture;

        _itoa(i, temp, 10);
        filename += temp;
        filename += ").jpg";
        intro_texture.loadFromFile(filename);

        sf::Sprite intro_sprite(intro_texture);

        window.draw(intro_sprite);
        window.display();
    }

    i = 100;
    while (true)
    {
        filename = ".\\frames\\f (";
        sf::Texture intro_texture;

        _itoa(i, temp, 10);
        filename += temp;
        filename += ").jpg";
        intro_texture.loadFromFile(filename);

        sf::Sprite intro_sprite(intro_texture);

        Play.setString("PLAY");
        Play.setPosition(850, 350);
        Play.setFillColor(sf::Color::Black);

        Rules.setString("RULES");
        Rules.setPosition(850, 550);
        Rules.setFillColor(sf::Color::Black);

        Exit.setString("EXIT");
        Exit.setPosition(850, 750);
        Exit.setFillColor(sf::Color::Black);

        window.draw(intro_sprite);
        window.draw(Play);
        window.draw(Rules);
        window.draw(Exit);
        window.display();

        if (sf::IntRect(850, 350, 200, 85).contains(sf::Mouse::getPosition(window)))
        {
            Play.setFillColor(sf::Color::Blue);
            window.draw(Play);
            window.display();
        }

        if (sf::IntRect(850, 550, 250, 85).contains(sf::Mouse::getPosition(window)))
        {
            Rules.setFillColor(sf::Color::Blue);
            window.draw(Rules);
            window.display();
        }

        if (sf::IntRect(850, 750, 200, 85).contains(sf::Mouse::getPosition(window)))
        {
            Exit.setFillColor(sf::Color::Blue);
            window.draw(Exit);
            window.display();
        }

        if (sf::IntRect(850, 350, 200, 85).contains(sf::Mouse::getPosition(window)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            for (i = 1; i < 40; i++)
            {
                filename = ".\\end_frames\\e (";
                sf::Texture end_texture;

                _itoa(i, temp, 10);
                filename += temp;
                filename += ").jpg";
                end_texture.loadFromFile(filename);

                sf::Sprite end_sprite(end_texture);
                window.draw(end_sprite);
                window.display();
            }
            music.stop();
            Play_game(window);
            music.play();
            for (i = 39; i > 0; i--)
            {
                filename = ".\\end_frames\\e (";
                sf::Texture end_texture;

                _itoa(i, temp, 10);
                filename += temp;
                filename += ").jpg";
                end_texture.loadFromFile(filename);

                sf::Sprite end_sprite(end_texture);
                window.draw(end_sprite);
                window.display();
            }
            i = 120;
        }

        if (sf::IntRect(850, 750, 200, 85).contains(sf::Mouse::getPosition(window)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            for (i = 1; i < 40; i++)
            {
                filename = ".\\end_frames\\e (";
                sf::Texture end_texture;

                _itoa(i, temp, 10);
                filename += temp;
                filename += ").jpg";
                end_texture.loadFromFile(filename);

                sf::Sprite end_sprite(end_texture);
                window.draw(end_sprite);
                window.display();
            }
            music.stop();
            sf::Music quit;

            quit.openFromFile("end.wav");
            quit.play();
            for (i = 1; i < 181; i++)
            {
                filename = ".\\close\\q (";
                sf::Texture close_texture;

                _itoa(i, temp, 10);
                filename += temp;
                filename += ").jpg";
                close_texture.loadFromFile(filename);

                sf::Sprite close_sprite(close_texture);
                window.draw(close_sprite);
                window.display();

                if (i > 24)
                {
                    sf::Text end_text("", font, 100);
                    end_text.setString("THE END");
                    end_text.setPosition(800, 450);
                    end_text.setFillColor(sf::Color::Red);
                    window.draw(end_text);
                    window.display();
                }
            }
            window.close();
            exit(EXIT_SUCCESS);
        }

        if (sf::IntRect(850, 550, 250, 85).contains(sf::Mouse::getPosition(window)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            for (short j = 1; j < 40; j++)
            {
                filename = ".\\end_frames\\e (";
                sf::Texture end_texture;

                _itoa(j, temp, 10);
                filename += temp;
                filename += ").jpg";
                end_texture.loadFromFile(filename);

                sf::Sprite end_sprite(end_texture);
                window.draw(end_sprite);
                window.display();
            }

            while (true)
            {
                sf::Texture rules_back_texture;
                rules_back_texture.loadFromFile("rules_back.jpg");
                sf::Sprite rules_back_sprite(rules_back_texture);

                sf::Texture rules_texture;
                rules_texture.loadFromFile("rules.jpg");
                sf::Sprite rules_sprite(rules_texture);

                sf::Text back("", font, 40);
                back.setString("GO BACK");
                back.setPosition(1600, 50);
                back.setFillColor(sf::Color::White);

                window.draw(rules_back_sprite);
                window.draw(rules_sprite);
                window.draw(back);

                if (sf::IntRect(1600, 50, 180, 50).contains(sf::Mouse::getPosition(window)))
                {
                    back.setFillColor(sf::Color::Blue);
                    window.draw(back);
                }
                window.display();

                if (sf::IntRect(1600, 50, 180, 50).contains(sf::Mouse::getPosition(window)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    for (short j = 39; j > 0; j--)
                    {
                        filename = ".\\end_frames\\e (";
                        sf::Texture end_texture;

                        _itoa(j, temp, 10);
                        filename += temp;
                        filename += ").jpg";
                        end_texture.loadFromFile(filename);

                        sf::Sprite end_sprite(end_texture);
                        window.draw(end_sprite);
                        window.display();
                    }
                    break;
                }
            }

        }

        if (i < 115)
            i++;
        else i = 100;
    }

}



