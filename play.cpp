#include "play.h"

Card cards[52];
Card table_cards[5];
short bank;

void Play_game(sf::RenderWindow& window)
{
    sf::Music music;
    music.openFromFile("play_song.ogg");
    music.play();
    music.setLoop(true);

    while (true)
    {
        sf::Texture background_texture;
        background_texture.loadFromFile("game_back.jpg");
        sf::Sprite background_sprite(background_texture);

        sf::Texture table_texture;
        table_texture.loadFromFile("table.png");
        sf::Sprite table_sprite(table_texture);
        table_sprite.setPosition(280, 100);

        sf::Texture piece_texture;
        piece_texture.loadFromFile("piece.jpg");
        sf::Sprite piece_sprite(piece_texture);
        piece_sprite.setPosition(492, 650);

        sf::Font font;
        font.loadFromFile("font.ttf");
        sf::Text go_menu("", font, 40);
        go_menu.setString("GO MENU");
        go_menu.setPosition(1700, 50);
        go_menu.setFillColor(sf::Color::White);

        Set_cards();
        MyPlayer player("player");
        Player players[5]
        {
            Player("Pierce Brosnan"),
            Player("Sean Connery"),
            Player("Daniel Craig"),
            Player("Le Chiffre"),
            Player("Franz Oberhauser")
        };

        player.next = &players[0];
        for (short i = 0; i < 4; ++i)
            players[i].next = &players[i + 1];
        players[4].next = &player;

        players[4].dealer = true;
        player.small_blind = true;
        players[0].big_blind = true;

        Player* auxiliary = &players[0];

        while (players[0].in_the_game || players[1].in_the_game || players[2].in_the_game || players[3].in_the_game || players[4].in_the_game)
        {
            window.draw(background_sprite);
            window.draw(table_sprite);
            window.draw(go_menu);
            window.draw(piece_sprite);

            player.Show_player(880, 700, 0.4f, 0.4f, "Player.png", window);
            player.Show_name(890, 940, window);

            if (players[0].in_the_game)
                players[0].Show_player(330, 660, 0.12f, 0.12f, "Pierce_Brosnan.png", window);
            if (players[1].in_the_game)
                players[1].Show_player(360, 60, 0.2f, 0.2f, "Sean_Connery.png", window);
            if (players[2].in_the_game)
                players[2].Show_player(860, 30, 0.13f, 0.13f, "Daniel_Craig.png", window);
            if (players[3].in_the_game)
                players[3].Show_player(1430, 60, 0.4f, 0.4f, "Le_Chiffre.png", window);
            if (players[4].in_the_game)
                players[4].Show_player(1410, 640, 0.33f, 0.33f, "Franz_Oberhauser.png", window);

            window.display();
            sf::SoundBuffer sound_buffer;
            sound_buffer.loadFromFile("shuffle.ogg");
            sf::Sound shuffle(sound_buffer);
            shuffle.play();
            Sleep(6000);

            short number = 1;
            for (short i = 0; i < 5; ++i)
                if (players[i].in_the_game)
                    number++;

            while (!auxiliary->dealer)
                auxiliary = auxiliary->next;
            auxiliary = auxiliary->next;
            while (!auxiliary->in_the_game)
                auxiliary = auxiliary->next;
            Nullify_dealers(player, players);
            auxiliary->dealer = true;


            if (player.dealer)
                player.Show_dealer(930, 650, window);
            else if (players[0].dealer)
                players[0].Show_dealer(480, 660, window);
            else if (players[1].dealer)
                players[1].Show_dealer(500, 280, window);
            else if (players[2].dealer)
                players[2].Show_dealer(950, 250, window);
            else if (players[3].dealer)
                players[3].Show_dealer(1350, 280, window);
            else if (players[4].dealer)
                players[4].Show_dealer(1390, 660, window);

            if (number > 2)
            {
                while (!auxiliary->small_blind)
                    auxiliary = auxiliary->next;
                auxiliary = auxiliary->next;
                while (!auxiliary->in_the_game || auxiliary->dealer)
                    auxiliary = auxiliary->next;
                Nullify_small_blinds(player, players);
                auxiliary->small_blind = true;
            }
            else
            {
                Nullify_small_blinds(player, players);
                auxiliary->small_blind = true;
            }

            if (player.small_blind)
                player.Show_small_blind(930, 580, window);
            else if (players[0].small_blind)
                players[0].Show_small_blind(550, 660, window);
            else if (players[1].small_blind)
                players[1].Show_small_blind(550, 280, window);
            else if (players[2].small_blind)
                players[2].Show_small_blind(1000, 250, window);
            else if (players[3].small_blind)
                players[3].Show_small_blind(1400, 310, window);
            else if (players[4].small_blind)
                players[4].Show_small_blind(1440, 600, window);


            while (!auxiliary->big_blind)
                auxiliary = auxiliary->next;
            auxiliary = auxiliary->next;
            while (!auxiliary->in_the_game || auxiliary->small_blind || auxiliary->dealer)
                auxiliary = auxiliary->next;
            Nullify_big_blinds(player, players);
            auxiliary->big_blind = true;


            if (player.big_blind)
                player.Show_big_blind(930, 580, window);
            else if (players[0].big_blind)
                players[0].Show_big_blind(550, 660, window);
            else if (players[1].big_blind)
                players[1].Show_big_blind(550, 280, window);
            else if (players[2].big_blind)
                players[2].Show_big_blind(1000, 250, window);
            else if (players[3].big_blind)
                players[3].Show_big_blind(1400, 310, window);
            else if (players[4].big_blind)
                players[4].Show_big_blind(1440, 600, window);


            for (short i = 0; i < 6; ++i)
            {
                std::cout << auxiliary->name << " " << auxiliary->dealer << " " << auxiliary->small_blind << " " << auxiliary->big_blind << std::endl;
                auxiliary = auxiliary->next;
            }
            std::cout << "\n\n\n";

            Make_available_all_cards();

            player.Get_cards();
            for (short i = 0; i < 5; ++i)
                if (players[i].in_the_game)
                    players[i].Get_cards();

            player.Show_cards(820, 630, 1000, 630, window);
            player.Show_chips(1050, 850, window);


            if (players[0].in_the_game)
                players[0].Show_chips(450, 800, window);

            if (players[1].in_the_game)
                players[1].Show_chips(510, 150, window);

            if (players[2].in_the_game)
                players[2].Show_chips(1050, 130, window);

            if (players[3].in_the_game)
                players[3].Show_chips(1570, 200, window);

            if (players[4].in_the_game)
                players[4].Show_chips(1630, 800, window);

            window.display();

            bank = 0;
            short max_rate = 0;
            while (!auxiliary->small_blind)
                auxiliary = auxiliary->next;
            max_rate = auxiliary->Make_small_blind();
            bank += max_rate;

            Reshow(player, players, window, background_sprite, table_sprite, go_menu, piece_sprite, true);
            Sleep(3000);

            while (!auxiliary->big_blind)
                auxiliary = auxiliary->next;
            max_rate = auxiliary->Make_big_blind();
            bank += max_rate;

            Reshow(player, players, window, background_sprite, table_sprite, go_menu, piece_sprite, true);
            Sleep(3000);

            auxiliary = auxiliary->next;
            max_rate = BIG_BLIND;
            short player_rate = 0;

            bool next_round = false;
            for (short i = 0; i < 6; ++i)
            {
                if (auxiliary == &player && player.chips > 0 && player.in_the_round)
                {
                    player_rate = player.Player_makes_rate(players, window, background_sprite, table_sprite, go_menu, piece_sprite, max_rate);
                    if (player_rate == -1)
                        return;
                    bank += player_rate;
                    if (player.rate > max_rate)
                    {
                        max_rate = player.rate;
                        i = 0;
                        Sleep(2000);
                    }
                }
                else if (auxiliary->in_the_round && auxiliary->chips > 0)
                {
                    player_rate = auxiliary->Rate_making(max_rate);
                    bank += player_rate;
                    if (auxiliary->rate > max_rate)
                    {
                        max_rate = auxiliary->rate;
                        i = 0;
                        Sleep(2000);
                    }
                }

                Reshow(player, players, window, background_sprite, table_sprite, go_menu, piece_sprite, true);

                short who_play = 0;
                for (short j = 0; j < 6; j++)
                {
                    if (auxiliary->in_the_round)
                        who_play++;
                    auxiliary = auxiliary->next;
                }

                if (who_play < 2)
                {
                    for (short j = 0; j < 6; j++)
                    {
                        if (auxiliary->in_the_round)
                            break;
                        auxiliary = auxiliary->next;
                    }
                    auxiliary->chips += bank;
                    next_round = true;
                    break;
                }

                auxiliary = auxiliary->next;
            }

            if (next_round)
            {
                bank = 0;
                max_rate = 0;
                for (short i = 0; i < 6; ++i)
                {
                    if (auxiliary->chips <= 0)
                        auxiliary->in_the_game = false;
                    auxiliary->in_the_round = true;
                    auxiliary->rate = 0;
                    auxiliary->combination = 0;
                    auxiliary = auxiliary->next;
                }
                continue;
            }

            std::cout << std::endl << "BANK-> " << bank << std::endl;
            //window.display();



            for (short index = 0; index < 5; ++index)
            {
                short result = 0;
                do
                {
                    result = rand() % 51;
                    table_cards[index] = cards[result];
                } while (!cards[result].available);
                cards[result].available = false;
            }

            short cards_number = 3;
            for (short j = 0; j < 3; j++)
            {
                Rate_refresh(player, players);
                max_rate = 0;

                Reshow(player, players, window, background_sprite, table_sprite, go_menu, piece_sprite, true, cards_number);

                while (!auxiliary->dealer)
                    auxiliary = auxiliary->next;
                auxiliary = auxiliary->next;
                while (!auxiliary->in_the_round)
                    auxiliary = auxiliary->next;

                next_round = false;
                for (short i = 0; i < 6; ++i)
                {
                    if (auxiliary == &player && player.chips > 0 && player.in_the_round)
                    {
                        player_rate = player.Player_makes_rate(players, window, background_sprite, table_sprite, go_menu, piece_sprite, max_rate, cards_number);
                        if (player_rate == -1)
                            return;
                        bank += player_rate;
                        if (player.rate > max_rate)
                        {
                            max_rate = player.rate;
                            i = 0;
                            Sleep(2000);
                        }
                    }
                    else if (auxiliary->in_the_round && auxiliary->chips > 0)
                    {
                        player_rate = auxiliary->Rate_making(max_rate);
                        bank += player_rate;
                        if (auxiliary->rate > max_rate)
                        {
                            max_rate = auxiliary->rate;
                            i = 0;
                            Sleep(2000);
                        }
                    }

                    Reshow(player, players, window, background_sprite, table_sprite, go_menu, piece_sprite, true, cards_number);
                    Sleep(1000);
                    auxiliary = auxiliary->next;
                }

                short who_play = 0;
                for (short j = 0; j < 6; j++)
                {
                    if (auxiliary->in_the_round)
                        who_play++;
                    auxiliary = auxiliary->next;
                }

                if (who_play < 2)
                {
                    for (short j = 0; j < 6; j++)
                    {
                        if (auxiliary->in_the_round)
                            break;
                        auxiliary = auxiliary->next;
                    }
                    auxiliary->chips += bank;
                    next_round = true;
                    break;
                }

                std::cout << std::endl << "BANK-> " << bank << std::endl;
                window.display();
                cards_number++;
            }

            if (next_round)
            {
                bank = 0;
                max_rate = 0;
                for (short i = 0; i < 6; ++i)
                {
                    if (auxiliary->chips <= 0)
                        auxiliary->in_the_game = false;
                    auxiliary->in_the_round = true;
                    auxiliary->rate = 0;
                    auxiliary->combination = 0;
                    auxiliary = auxiliary->next;
                }
                continue;
            }

            players[0].Show_cards(470, 550, 590, 550, window);
            players[1].Show_cards(470, 370, 590, 370, window);
            players[2].Show_cards(900, 280, 1020, 280, window);
            players[3].Show_cards(1300, 350, 1420, 350, window);
            players[4].Show_cards(1300, 580, 1420, 580, window);
            window.display();

            for (short i = 0; i < 6; ++i)
            {
                auxiliary->Get_combination(table_cards);
                std::cout << auxiliary->name << "\t" << auxiliary->combination << std::endl;
                auxiliary = auxiliary->next;
            }

            Player* winner = NULL;

            for (short i = 0; i < 6; ++i)
            {
                if (auxiliary->in_the_round && auxiliary->combination == ROYAL_FLASH)
                {
                    winner = auxiliary;
                    winner->chips += bank;
                    bank = 0;
                    max_rate = 0;
                    for (short i = 0; i < 6; ++i)
                    {
                        if (auxiliary->chips <= 0)
                            auxiliary->in_the_game = false;
                        auxiliary->in_the_round = true;
                        auxiliary->rate = 0;
                        auxiliary->combination = 0;
                        auxiliary = auxiliary->next;
                    }
                }
                auxiliary = auxiliary->next;
            }

            if ((winner = Get_winner(auxiliary, STRAIGHT_FLASH)) != NULL)
            {
                winner->chips += bank;
                bank = 0;
                max_rate = 0;
                for (short i = 0; i < 6; ++i)
                {
                    if (auxiliary->chips <= 0)
                        auxiliary->in_the_game = false;
                    auxiliary->in_the_round = true;
                    auxiliary->rate = 0;
                    auxiliary->combination = 0;
                    auxiliary = auxiliary->next;
                }
            }

            for (short i = 0; i < 6; ++i)
            {
                if (auxiliary->in_the_round && auxiliary->combination == KARE)
                {
                    winner = auxiliary;
                    winner->chips += bank;
                    bank = 0;
                    max_rate = 0;
                    for (short i = 0; i < 6; ++i)
                    {
                        if (auxiliary->chips <= 0)
                            auxiliary->in_the_game = false;
                        auxiliary->in_the_round = true;
                        auxiliary->rate = 0;
                        auxiliary->combination = 0;
                        auxiliary = auxiliary->next;
                    }
                }
            }

            if ((winner = Get_winner(auxiliary, FULL_HOUSE)) != NULL)
            {
                winner->chips += bank;
                bank = 0;
                max_rate = 0;
                for (short i = 0; i < 6; ++i)
                {
                    if (auxiliary->chips <= 0)
                        auxiliary->in_the_game = false;
                    auxiliary->in_the_round = true;
                    auxiliary->rate = 0;
                    auxiliary->combination = 0;
                    auxiliary = auxiliary->next;
                }
            }

            if ((winner = Get_winner(auxiliary, FLUSH)) != NULL)
            {
                winner->chips += bank;
                bank = 0;
                max_rate = 0;
                for (short i = 0; i < 6; ++i)
                {
                    if (auxiliary->chips <= 0)
                        auxiliary->in_the_game = false;
                    auxiliary->in_the_round = true;
                    auxiliary->rate = 0;
                    auxiliary->combination = 0;
                    auxiliary = auxiliary->next;
                }
            }

            if ((winner = Get_winner(auxiliary, STRAIGHT)) != NULL)
            {
                winner->chips += bank;
                bank = 0;
                max_rate = 0;
                for (short i = 0; i < 6; ++i)
                {
                    if (auxiliary->chips <= 0)
                        auxiliary->in_the_game = false;
                    auxiliary->in_the_round = true;
                    auxiliary->rate = 0;
                    auxiliary->combination = 0;
                    auxiliary = auxiliary->next;
                }
            }

            if ((winner = Get_winner(auxiliary, SET)) != NULL)
            {
                winner->chips += bank;
                bank = 0;
                max_rate = 0;
                for (short i = 0; i < 6; ++i)
                {
                    if (auxiliary->chips <= 0)
                        auxiliary->in_the_game = false;
                    auxiliary->in_the_round = true;
                    auxiliary->rate = 0;
                    auxiliary->combination = 0;
                    auxiliary = auxiliary->next;
                }
            }

            if ((winner = Get_winner(auxiliary, TWO_PAIR)) != NULL)
            {
                winner->chips += bank;
                bank = 0;
                max_rate = 0;
                for (short i = 0; i < 6; ++i)
                {
                    if (auxiliary->chips <= 0)
                        auxiliary->in_the_game = false;
                    auxiliary->in_the_round = true;
                    auxiliary->rate = 0;
                    auxiliary->combination = 0;
                    auxiliary = auxiliary->next;
                }
            }

            if ((winner = Get_winner(auxiliary, PAIR)) != NULL)
            {
                winner->chips += bank;
                bank = 0;
                max_rate = 0;
                for (short i = 0; i < 6; ++i)
                {
                    if (auxiliary->chips <= 0)
                        auxiliary->in_the_game = false;
                    auxiliary->in_the_round = true;
                    auxiliary->rate = 0;
                    auxiliary->combination = 0;
                    auxiliary = auxiliary->next;
                }
            }

            if ((winner = Get_winner(auxiliary, HIGH_CARD)) != NULL)
            {
                winner->chips += bank;
                bank = 0;
                max_rate = 0;
                for (short i = 0; i < 6; ++i)
                {
                    if (auxiliary->chips <= 0)
                        auxiliary->in_the_game = false;
                    auxiliary->in_the_round = true;
                    auxiliary->rate = 0;
                    auxiliary->combination = 0;
                    auxiliary = auxiliary->next;
                }
            }



            Sleep(7000);


        }


    }
}

Player* Get_winner(Player* auxiliary, short COMBINATION)
{
    Player* winner = NULL;
    short number = 0;

    for (short i = 0; i < 6; ++i)
    {
        if (auxiliary->in_the_round && auxiliary->combination == COMBINATION)
        {
            if (number == 0)
            {
                winner = auxiliary;
                number++;
            }
            else
                if (auxiliary->higt_card_combination > winner->higt_card_combination)
                {
                    winner = auxiliary;
                    number++;
                }
        }
        auxiliary = auxiliary->next;
    }

    return winner;
}

void Show_table_card(sf::RenderWindow& window, float x, float y, short index)
{
    sf::Texture card_texture;
    sf::Sprite card_sprite;
    char image_name[14] = "cards\\";

    if (table_cards[index].value == 'T')
    {
        image_name[6] = '1';
        image_name[7] = '0';
        image_name[8] = table_cards[index].suit;
        strcat(image_name, ".png");
    }
    else
    {
        image_name[6] = table_cards[index].value;
        image_name[7] = table_cards[index].suit;
        strcat(image_name, ".png");
    }
    card_texture.loadFromFile(image_name);
    card_sprite.setTexture(card_texture);
    card_sprite.scale(0.13f, 0.13f);
    card_sprite.setPosition(x, y);
    window.draw(card_sprite);
}

void Rate_refresh(MyPlayer& player, Player* players)
{
    player.rate = 0;
    for (short i = 0; i < 5; ++i)
        players[i].rate = 0;
}

void Reshow(MyPlayer& player, Player* players, sf::RenderWindow& window, sf::Sprite& background_sprite, sf::Sprite& table_sprite, sf::Text& go_menu, sf::Sprite& piece_sprite, bool show_rate, short number)
{
    window.draw(background_sprite);
    window.draw(table_sprite);
    window.draw(go_menu);
    window.draw(piece_sprite);

    player.Show_player(880, 700, 0.4f, 0.4f, "Player.png", window);
    player.Show_name(890, 940, window);

    if (players[0].in_the_game)
        players[0].Show_player(330, 660, 0.12f, 0.12f, "Pierce_Brosnan.png", window);
    if (players[1].in_the_game)
        players[1].Show_player(360, 60, 0.2f, 0.2f, "Sean_Connery.png", window);
    if (players[2].in_the_game)
        players[2].Show_player(860, 30, 0.13f, 0.13f, "Daniel_Craig.png", window);
    if (players[3].in_the_game)
        players[3].Show_player(1430, 60, 0.4f, 0.4f, "Le_Chiffre.png", window);
    if (players[4].in_the_game)
        players[4].Show_player(1410, 640, 0.33f, 0.33f, "Franz_Oberhauser.png", window);

    if (player.dealer)
        player.Show_dealer(930, 650, window);
    else if (players[0].dealer)
        players[0].Show_dealer(480, 660, window);
    else if (players[1].dealer)
        players[1].Show_dealer(500, 280, window);
    else if (players[2].dealer)
        players[2].Show_dealer(950, 250, window);
    else if (players[3].dealer)
        players[3].Show_dealer(1350, 280, window);
    else if (players[4].dealer)
        players[4].Show_dealer(1390, 660, window);

    if (player.small_blind)
        player.Show_small_blind(930, 580, window);
    else if (players[0].small_blind)
        players[0].Show_small_blind(550, 660, window);
    else if (players[1].small_blind)
        players[1].Show_small_blind(550, 280, window);
    else if (players[2].small_blind)
        players[2].Show_small_blind(1000, 250, window);
    else if (players[3].small_blind)
        players[3].Show_small_blind(1400, 310, window);
    else if (players[4].small_blind)
        players[4].Show_small_blind(1440, 600, window);

    if (player.big_blind)
        player.Show_big_blind(930, 580, window);
    else if (players[0].big_blind)
        players[0].Show_big_blind(550, 660, window);
    else if (players[1].big_blind)
        players[1].Show_big_blind(550, 280, window);
    else if (players[2].big_blind)
        players[2].Show_big_blind(1000, 250, window);
    else if (players[3].big_blind)
        players[3].Show_big_blind(1400, 310, window);
    else if (players[4].big_blind)
        players[4].Show_big_blind(1440, 600, window);

    if (player.in_the_round)
        player.Show_cards(820, 630, 1000, 630, window);
    player.Show_chips(1050, 850, window);

    if (players[0].in_the_game)
        players[0].Show_chips(450, 800, window);

    if (players[1].in_the_game)
        players[1].Show_chips(510, 150, window);

    if (players[2].in_the_game)
        players[2].Show_chips(1050, 130, window);

    if (players[3].in_the_game)
        players[3].Show_chips(1570, 200, window);

    if (players[4].in_the_game)
        players[4].Show_chips(1630, 800, window);

    if (show_rate)
    {
        if (player.in_the_round && player.rate > 0)
            player.Show_rate(940, 620, window);
        if (players[0].in_the_round && players[0].rate > 0)
            players[0].Show_rate(500, 690, window);
        if (players[1].in_the_round && players[1].rate > 0)
            players[1].Show_rate(500, 290, window);
        if (players[2].in_the_round && players[2].rate > 0)
            players[2].Show_rate(940, 250, window);
        if (players[3].in_the_round && players[3].rate > 0)
            players[3].Show_rate(1400, 300, window);
        if (players[4].in_the_round && players[4].rate > 0)
            players[4].Show_rate(1410, 690, window);
    }

    if (number == 1)
        Show_table_card(window, 700, 400, 0);
    else if (number == 2)
    {
        Show_table_card(window, 700, 400, 0);
        Show_table_card(window, 810, 400, 1);
    }
    else if (number == 3)
    {
        Show_table_card(window, 700, 400, 0);
        Show_table_card(window, 810, 400, 1);
        Show_table_card(window, 920, 400, 2);
    }
    else if (number == 4)
    {
        Show_table_card(window, 700, 400, 0);
        Show_table_card(window, 810, 400, 1);
        Show_table_card(window, 920, 400, 2);
        Show_table_card(window, 1030, 400, 3);
    }
    else if (number == 5)
    {
        Show_table_card(window, 700, 400, 0);
        Show_table_card(window, 810, 400, 1);
        Show_table_card(window, 920, 400, 2);
        Show_table_card(window, 1030, 400, 3);
        Show_table_card(window, 1140, 400, 4);
    }

    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Text bank_text("", font, 30);
    char bank_str[12];
    sprintf(bank_str, "BANK: %hd", bank);
    bank_text.setString(bank_str);
    bank_text.setPosition(100, 50);
    bank_text.setFillColor(sf::Color::White);
    window.draw(bank_text);

    window.display();
}

void Make_available_all_cards()
{
    for (short i = 0; i < 52; ++i)
        cards[i].available = true;
}

void Nullify_dealers(MyPlayer& player, Player* players)
{
    for (short i = 0; i < 5; ++i)
        players[i].dealer = false;
    player.dealer = false;
}

void Nullify_small_blinds(MyPlayer& player, Player* players)
{
    for (short i = 0; i < 5; ++i)
        players[i].small_blind = false;
    player.small_blind = false;
}

void Nullify_big_blinds(MyPlayer& player, Player* players)
{
    for (short i = 0; i < 5; ++i)
        players[i].big_blind = false;
    player.big_blind = false;
}

void Set_cards()
{
    for (short i = 1; i <= 4; ++i)
        for (short j = 1; j <= 13; ++j)
        {
            cards[(i - 1) * 13 + (j - 1)].available = true;

            if (j < 9)
                cards[(i - 1) * 13 + (j - 1)].value = (j + 1) + 48;
            else if (j == 9)
                cards[(i - 1) * 13 + (j - 1)].value = 'T';
            else if (j == 10)
                cards[(i - 1) * 13 + (j - 1)].value = 'J';
            else if (j == 11)
                cards[(i - 1) * 13 + (j - 1)].value = 'Q';
            else if (j == 12)
                cards[(i - 1) * 13 + (j - 1)].value = 'K';
            else if (j == 13)
                cards[(i - 1) * 13 + (j - 1)].value = 'A';

            if (i == 1)
                cards[(i - 1) * 13 + (j - 1)].suit = 'H';
            else if (i == 2)
                cards[(i - 1) * 13 + (j - 1)].suit = 'D';
            else if (i == 3)
                cards[(i - 1) * 13 + (j - 1)].suit = 'S';
            else if (i == 4)
                cards[(i - 1) * 13 + (j - 1)].suit = 'C';
        }
}

Human::Human(const char* name)
{
    this->name = name;
}

Human::~Human()
{

}

Player::Player(const char* name) : Human(name)
{
    chips = 1000;
    rate = 0;
    in_the_game = true;
    in_the_round = true;
    dealer = false;
    big_blind = false;
    small_blind = false;
    card1.available = 0;
    card1.suit = 0;
    card1.value = 0;
    card2.available = 0;
    card2.suit = 0;
    card2.value = 0;
    combination = 0;
    higt_card_combination = 0;
    next = NULL;
}

void Player::Show_player(float x1, float y1, float x2, float y2, const char* path, sf::RenderWindow& window)
{
    sf::Texture player_texture;
    player_texture.loadFromFile(path);
    sf::Sprite player_sprite(player_texture);
    player_sprite.setPosition(x1, y1);
    player_sprite.scale(x2, y2);
    if (!this->in_the_round)
        player_sprite.setColor(sf::Color::Red);
    window.draw(player_sprite);
}

void Player::Show_dealer(float x, float y, sf::RenderWindow& window)
{
    sf::Texture dealer_texture;
    sf::Sprite dealer_sprite;

    dealer_texture.loadFromFile("dealer.png");
    dealer_sprite.setTexture(dealer_texture);
    dealer_sprite.scale(0.05f, 0.05f);
    dealer_sprite.setPosition(x, y);
    window.draw(dealer_sprite);
}

void Player::Show_big_blind(float x, float y, sf::RenderWindow& window)
{
    sf::Texture big_blind_texture;
    sf::Sprite big_blind_sprite;

    big_blind_texture.loadFromFile("big_blind.png");
    big_blind_sprite.setTexture(big_blind_texture);
    big_blind_sprite.scale(0.119f, 0.119f);
    big_blind_sprite.setPosition(x, y);
    window.draw(big_blind_sprite);
}

void Player::Show_small_blind(float x, float y, sf::RenderWindow& window)
{
    sf::Texture small_blind_texture;
    sf::Sprite small_blind_sprite;

    small_blind_texture.loadFromFile("small_blind.png");
    small_blind_sprite.setTexture(small_blind_texture);
    small_blind_sprite.scale(0.07f, 0.07f);
    small_blind_sprite.setPosition(x, y);
    window.draw(small_blind_sprite);
}

void Player::Show_chips(float x, float y, sf::RenderWindow& window)
{
    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Text text("", font, 30);
    char chips[5];
    sprintf(chips, "%hd", this->chips);

    text.setString(chips);
    text.setFillColor(sf::Color::White);
    text.setPosition(x, y);
    window.draw(text);
}

short Player::Make_small_blind()
{
    short rate;

    if (this->chips <= SMALL_BLIND)
    {
        rate = this->chips;
        this->rate += rate;
        this->chips = 0;
    }
    else
    {
        rate = SMALL_BLIND;
        this->rate += rate;
        this->chips -= rate;
    }
    return rate;
}

short Player::Make_big_blind()
{
    short rate;

    if (this->chips <= BIG_BLIND)
    {
        rate = this->chips;
        this->rate += rate;
        this->chips = 0;
    }
    else
    {
        rate = BIG_BLIND;
        this->rate += rate;
        this->chips -= rate;
    }
    return rate;
}

void Player::Show_rate(float x, float y, sf::RenderWindow& window)
{
    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Text text("", font, 20);
    char rate[5];
    sprintf(rate, "%hd", this->rate);
    text.setString(rate);
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(x, y);
    window.draw(text);
}

short Player::Rate_making(short& max_rate)
{
    short rate = 0;
    sf::SoundBuffer sound_buffer;

    enum
    {
        FOLD,
        CHECK,
        CALL,
        RAISE
    };

    srand(unsigned(time(NULL)));

    char choice, fortuna;
    while (true)
    {
        if (max_rate == this->rate)
        {
            fortuna = rand() % 100 + 1; // 60% - check, 20% - fold, 20% - raise
            if (fortuna <= 60)
                choice = CHECK;
            else if (fortuna <= 80)
                choice = RAISE;
            else
                choice = FOLD;
        }
        else
        {
            fortuna = rand() % 100 + 1; // 60% - call, 20% - fold, 20% - raise
            if (fortuna <= 60)
                choice = CALL;
            else if (fortuna <= 80)
                choice = RAISE;
            else
                choice = FOLD;
        }

        if (choice == FOLD)
        {
            sound_buffer.loadFromFile("fold.wav");
            sf::Sound sound(sound_buffer);
            sound.play();
            Sleep(1000);
            this->in_the_round = false;
            break;
        }
        else if (choice == CALL && this->chips > 0)
        {
            if (this->chips <= max_rate)
            {
                rate = this->chips;
                chips = 0;
                this->rate += rate;
            }
            else
            {
                rate = max_rate - this->rate;
                chips -= (max_rate - this->rate);
                this->rate += (max_rate - this->rate);
            }
            sound_buffer.loadFromFile("call.wav");
            sf::Sound sound(sound_buffer);
            sound.play();
            Sleep(1000);
            break;
        }
        else if (choice == RAISE && this->chips + max_rate >= 20)
        {
            sound_buffer.loadFromFile("raise.wav");
            sf::Sound sound(sound_buffer);
            sound.play();
            Sleep(1000);
            rate = (20 + max_rate - this->rate);
            this->chips -= (20 + max_rate - this->rate);
            this->rate += (20 + max_rate - this->rate);
            break;
        }
        else if (max_rate == 0)
        {
            sound_buffer.loadFromFile("check.wav");
            sf::Sound sound(sound_buffer);
            sound.play();
            Sleep(1000);
            break;
        }
    }
    return rate;
}

void Player::Get_cards()
{
    short result = 0;

    do
    {
        result = rand() % 51;
        card1 = cards[result];
    } while (!cards[result].available);
    cards[result].available = false;

    do
    {
        result = rand() % 51;
        card2 = cards[result];
    } while (!cards[result].available);
    cards[result].available = false;
}

Player::~Player()
{

}

MyPlayer::MyPlayer(const char* name) : Player(name)
{

}

MyPlayer::~MyPlayer()
{


}

void MyPlayer::Show_name(float x, float y, sf::RenderWindow& window)
{
    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Text text("", font, 20);
    text.setString("YOUR PLAYER");
    text.setFillColor(sf::Color::Yellow);
    text.setPosition(x, y);
    window.draw(text);
}

short MyPlayer::Player_makes_rate(Player* players, sf::RenderWindow& window, sf::Sprite& background_sprite, sf::Sprite& table_sprite, sf::Text& go_menu, sf::Sprite& piece_sprite, short max_rate, short number)
{
    sf::SoundBuffer sound_buffer;
    sound_buffer.loadFromFile("select.ogg");
    sf::Sound select(sound_buffer);
    select.play();

    Reshow(*this, players, window, background_sprite, table_sprite, go_menu, piece_sprite, true, number);


    sf::Texture check_texture;
    sf::Sprite check_sprite;
    check_texture.loadFromFile("check.png");
    check_sprite.setTexture(check_texture);
    check_sprite.setPosition(530, 1000);

    sf::Texture fold_texture;
    sf::Sprite fold_sprite;
    fold_texture.loadFromFile("fold.png");
    fold_sprite.setTexture(fold_texture);
    fold_sprite.setPosition(700, 1000);

    sf::Texture call_texture;
    sf::Sprite call_sprite;
    call_texture.loadFromFile("call.png");
    call_sprite.setTexture(call_texture);
    call_sprite.setPosition(860, 1000);

    sf::Texture raise_texture;
    sf::Sprite raise_sprite;
    raise_texture.loadFromFile("raise.png");
    raise_sprite.setTexture(raise_texture);
    raise_sprite.setPosition(1020, 1000);

    sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile("arrow.png");
    sprite.setTexture(texture);
    sprite.setPosition(1750, 200);

    short rate = 0;
    while (true)
    {
        window.draw(fold_sprite);
        window.draw(raise_sprite);
        window.display();

        if (sf::IntRect(700, 1000, 160, 80).contains(sf::Mouse::getPosition(window)))
        {
            fold_sprite.setColor(sf::Color::Blue);
            window.draw(fold_sprite);
            window.display();
        }
        else
            fold_sprite.setColor(sf::Color::Red);

        if (max_rate != 0)
        {
            if (sf::IntRect(860, 1000, 160, 80).contains(sf::Mouse::getPosition(window)))
            {
                call_sprite.setColor(sf::Color::Blue);
                window.draw(call_sprite);
                window.display();
            }
            else
            {
                call_sprite.setColor(sf::Color::Green);
                window.draw(call_sprite);
                window.display();
            }
        }

        if (sf::IntRect(1020, 1000, 170, 80).contains(sf::Mouse::getPosition(window)))
        {
            raise_sprite.setColor(sf::Color::Blue);
            window.draw(raise_sprite);
            window.display();
        }
        else
            raise_sprite.setColor(sf::Color::Green);

        if (max_rate == 0)
        {
            window.draw(check_sprite);

            if (sf::IntRect(550, 1000, 170, 80).contains(sf::Mouse::getPosition(window)))
            {
                check_sprite.setColor(sf::Color::Blue);
                window.draw(check_sprite);
            }
            else
                check_sprite.setColor(sf::Color::Green);

            if (sf::IntRect(550, 1000, 170, 80).contains(sf::Mouse::getPosition(window)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                break;
            }
            window.display();
        }


        if (sf::IntRect(700, 1000, 160, 80).contains(sf::Mouse::getPosition(window)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->in_the_round = false;
            break;
        }

        if (max_rate != 0)
        {
            if (sf::IntRect(860, 1000, 160, 80).contains(sf::Mouse::getPosition(window)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if (this->chips <= max_rate)
                {
                    rate = this->chips;
                    chips = 0;
                    this->rate += rate;
                }
                else
                {
                    rate = max_rate - this->rate;
                    chips -= (max_rate - this->rate);
                    this->rate += (max_rate - this->rate);
                }
                break;
            }
        }

        if (sf::IntRect(1020, 1000, 170, 80).contains(sf::Mouse::getPosition(window)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            bool is_raise = false;
            while (true)
            {
                window.draw(sprite);

                while (sf::IntRect(1750, 200, 150, 770).contains(sf::Mouse::getPosition(window)))
                {

                    Reshow(*this, players, window, background_sprite, table_sprite, go_menu, piece_sprite, true, number);

                    window.draw(sprite);

                    double base = 770;
                    double procent = (double)((sf::Mouse::getPosition(window)).y - 200.0) * 100.0 / base;
                    short bet = this->chips - short(procent / 100 * this->chips) + max_rate;
                    if (bet < max_rate)
                        bet = max_rate;
                    if (bet > this->chips)
                        bet = this->chips;

                    sf::Font font;
                    font.loadFromFile("font.ttf");
                    sf::Text text("", font, 40);
                    char temp[5];
                    sprintf(temp, "%hd", bet);
                    text.setString(temp);
                    text.setFillColor(sf::Color::Cyan);
                    text.setPosition(1650, 600);
                    window.draw(text);

                    if (sf::IntRect(1750, 200, 150, 770).contains(sf::Mouse::getPosition(window)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        rate = bet - this->rate;
                        this->chips -= (bet - this->rate);
                        this->rate = bet;
                        select.play();
                        is_raise = true;
                    }

                    window.display();
                }
                window.display();
                if (is_raise)
                    break;
            }

            if (is_raise)
                break;
        }

        if (sf::IntRect(1700, 50, 170, 40).contains(sf::Mouse::getPosition(window)))
        {
            go_menu.setFillColor(sf::Color::Blue);
            window.draw(go_menu);
        }
        else
        {
            go_menu.setFillColor(sf::Color::White);
            window.draw(go_menu);
        }

        if (sf::IntRect(1700, 50, 170, 40).contains(sf::Mouse::getPosition(window)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            return -1;
        }
    }

    Reshow(*this, players, window, background_sprite, table_sprite, go_menu, piece_sprite, true, number);
    return rate;
}

void Player::Show_cards(float x1, float y1, float x2, float y2, sf::RenderWindow& window)
{
    sf::Texture card1_texture, card2_texture;
    sf::Sprite card1_sprite, card2_sprite;
    char image_name[14] = "cards\\";

    if (card1.value == 'T')
    {
        image_name[6] = '1';
        image_name[7] = '0';
        image_name[8] = card1.suit;
        strcat(image_name, ".png");
    }
    else
    {
        image_name[6] = card1.value;
        image_name[7] = card1.suit;
        strcat(image_name, ".png");
    }
    card1_texture.loadFromFile(image_name);
    card1_sprite.setTexture(card1_texture);
    if (this->name == "player")
        card1_sprite.scale(0.13f, 0.13f);
    else
        card1_sprite.scale(0.1f, 0.1f);
    card1_sprite.setPosition(x1, y1);
    if (this->in_the_round)
        window.draw(card1_sprite);

    memset(image_name, 0, 14);
    strcpy(image_name, "cards\\");

    if (card2.value == 'T')
    {
        image_name[6] = '1';
        image_name[7] = '0';
        image_name[8] = card2.suit;
        strcat(image_name, ".png");
    }
    else
    {
        image_name[6] = card2.value;
        image_name[7] = card2.suit;
        strcat(image_name, ".png");
    }
    card2_texture.loadFromFile(image_name);
    card2_sprite.setTexture(card2_texture);
    if (this->name == "player")
        card2_sprite.scale(0.13f, 0.13f);
    else
        card2_sprite.scale(0.1f, 0.1f);
    card2_sprite.setPosition(x2, y2);
    if (this->in_the_round)
        window.draw(card2_sprite);
}


