#ifndef PLAY_H_
#define PLAY_H_
    
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
#include <cstdlib>
#include <string>
#include <ctime>
#include <iostream>

#define SMALL_BLIND 5
#define BIG_BLIND 10

struct Card
{
    char value;
    char suit;
    bool available;
};

enum
{
    HIGH_CARD,
    PAIR,
    TWO_PAIR,
    SET,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    KARE,
    STRAIGHT_FLASH,
    ROYAL_FLASH
};

class Human
{
public:
    std::string name;
    Human(const char*);
    ~Human();
};

class Player : public Human
{
protected:
    Card card1;
    Card card2;
public:
    short rate;
    short chips;
    bool in_the_game;
    bool in_the_round;
    bool dealer;
    bool big_blind;
    bool small_blind;
    short combination;
    char higt_card_combination;
    Player* next;

    Player(const char*);
    void Show_player(float, float, float, float, const char*, sf::RenderWindow&);
    void Show_dealer(float, float, sf::RenderWindow&);
    void Show_big_blind(float, float, sf::RenderWindow&);
    void Show_small_blind(float, float, sf::RenderWindow&);
    void Show_chips(float, float, sf::RenderWindow&);
    void Show_rate(float, float, sf::RenderWindow&);
    void Get_cards();
    short Rate_making(short&);
    short Make_small_blind();
    short Make_big_blind();
    void Get_combination(Card*);
    void Show_cards(float, float, float, float, sf::RenderWindow&);
    ~Player();
};

class MyPlayer : public Player
{
public:
    MyPlayer(const char*);
    void Show_name(float, float, sf::RenderWindow&);
    short Player_makes_rate(Player*, sf::RenderWindow&, sf::Sprite&, sf::Sprite&, sf::Text&, sf::Sprite&, short, short = 0);
    ~MyPlayer();
};

void Play_game(sf::RenderWindow&);
void Set_cards();
void Nullify_dealers(MyPlayer&, Player*);
void Nullify_small_blinds(MyPlayer&, Player*);
void Nullify_big_blinds(MyPlayer&, Player*);
void Make_available_all_cards();
void Reshow(MyPlayer&, Player*, sf::RenderWindow&, sf::Sprite&, sf::Sprite&, sf::Text&, sf::Sprite&, bool, short = 0);
void Rate_refresh(MyPlayer&, Player*);
void Show_table_card(sf::RenderWindow&, float, float, short);
Player* Get_winner(Player*, short);

#endif


