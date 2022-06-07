#include "play.h"

void Player::Get_combination(Card* table_cards)
{
    char suit;
    char value;
    bool five[5] = { false, false, false, false, false };

    // Royal-flush
    for (short i = 0; i < 4; ++i)
    {
        if (i == 0)
            suit = 'H';
        else if (i == 1)
            suit = 'D';
        else if (i == 2)
            suit = 'S';
        else
            suit = 'C';

        for (short k = 0; k < 5; k++)
        {
            if (k == 0)
                value = 'T';
            else if (k == 1)
                value = 'J';
            else if (k == 2)
                value = 'Q';
            else if (k == 3)
                value = 'K';
            else
                value = 'A';

            if (this->card1.value == value && this->card1.suit == suit)
            {
                five[k] = true;
                continue;
            }
            if (this->card2.value == value && this->card2.suit == suit)
            {
                five[k] = true;
                continue;
            }
            for (short j = 0; j < 5; ++j)
            {
                if (table_cards[j].value == value && table_cards[j].suit == suit)
                {
                    five[k] = true;
                    break;
                }
            }
        }

        if (five[0] && five[1] && five[2] && five[3] && five[4])
        {
            this->combination = ROYAL_FLASH;
            return;
        }

        for (short i = 0; i < 5; ++i)
            five[i] = false;
    }

    // Straight-flush
    for (short i = 0; i < 4; ++i)
    {
        if (i == 0)
            suit = 'H';
        else if (i == 1)
            suit = 'D';
        else if (i == 2)
            suit = 'S';
        else
            suit = 'C';

        for (short n = 0; n < 9; ++n)
        {
            for (short k = 0; k < 5; k++)
            {
                if (n == 0)
                {
                    if (k == 0)
                        value = 'A';
                    else if (k == 1)
                        value = '2';
                    else if (k == 2)
                        value = '3';
                    else if (k == 3)
                        value = '4';
                    else
                        value = '5';
                }
                else if (n == 1)
                {
                    if (k == 0)
                        value = '2';
                    else if (k == 1)
                        value = '3';
                    else if (k == 2)
                        value = '4';
                    else if (k == 3)
                        value = '5';
                    else
                        value = '6';
                }
                else if (n == 2)
                {
                    if (k == 0)
                        value = '3';
                    else if (k == 1)
                        value = '4';
                    else if (k == 2)
                        value = '5';
                    else if (k == 3)
                        value = '6';
                    else
                        value = '7';
                }
                else if (n == 3)
                {
                    if (k == 0)
                        value = '4';
                    else if (k == 1)
                        value = '5';
                    else if (k == 2)
                        value = '6';
                    else if (k == 3)
                        value = '7';
                    else
                        value = '8';
                }
                else if (n == 4)
                {
                    if (k == 0)
                        value = '5';
                    else if (k == 1)
                        value = '6';
                    else if (k == 2)
                        value = '7';
                    else if (k == 3)
                        value = '8';
                    else
                        value = '9';
                }
                else if (n == 5)
                {
                    if (k == 0)
                        value = '6';
                    else if (k == 1)
                        value = '7';
                    else if (k == 2)
                        value = '8';
                    else if (k == 3)
                        value = '9';
                    else
                        value = 'T';
                }
                else if (n == 6)
                {
                    if (k == 0)
                        value = '7';
                    else if (k == 1)
                        value = '8';
                    else if (k == 2)
                        value = '9';
                    else if (k == 3)
                        value = 'T';
                    else
                        value = 'J';
                }
                else if (n == 7)
                {
                    if (k == 0)
                        value = '8';
                    else if (k == 1)
                        value = '9';
                    else if (k == 2)
                        value = 'T';
                    else if (k == 3)
                        value = 'J';
                    else
                        value = 'Q';
                }
                else if (n == 8)
                {
                    if (k == 0)
                        value = '9';
                    else if (k == 1)
                        value = 'T';
                    else if (k == 2)
                        value = 'J';
                    else if (k == 3)
                        value = 'Q';
                    else
                        value = 'K';
                }

                if (this->card1.value == value && this->card1.suit == suit)
                {
                    five[k] = true;
                    continue;
                }
                if (this->card2.value == value && this->card2.suit == suit)
                {
                    five[k] = true;
                    continue;
                }
                for (short j = 0; j < 5; ++j)
                {
                    if (table_cards[j].value == value && table_cards[j].suit == suit)
                    {
                        five[k] = true;
                        break;
                    }
                }
            }

            if (five[0] && five[1] && five[2] && five[3] && five[4])
            {
                this->combination = STRAIGHT_FLASH;

                if (n == 0)
                    this->higt_card_combination = '5';

                else if (n == 1)
                    this->higt_card_combination = '6';
                
                else if (n == 2)
                    this->higt_card_combination = '7';
                
                else if (n == 3)
                    this->higt_card_combination = '8';
                
                else if (n == 4)
                    this->higt_card_combination = '9';
                
                else if (n == 5)
                    this->higt_card_combination = 'T';
                
                else if (n == 6)
                    this->higt_card_combination = 'J';
                
                else if (n == 7)
                    this->higt_card_combination = 'Q';
                
                else if (n == 8)
                    this->higt_card_combination = 'K';
                
                return;
            }

            for (short i = 0; i < 5; ++i)
                five[i] = false;
        }
    }

    // Kare
    for (short j = 0; j < 13; ++j)
    {
        if (j == 0)
            value = '2';
        else if (j == 1)
            value = '3';
        else if (j == 2)
            value = '4';
        else if (j == 3)
            value = '5';
        else if (j == 4)
            value = '6';
        else if (j == 5)
            value = '7';
        else if (j == 6)
            value = '8';
        else if (j == 7)
            value = '9';
        else if (j == 8)
            value = 'T';
        else if (j == 9)
            value = 'J';
        else if (j == 10)
            value = 'Q';
        else if (j == 11)
            value = 'K';
        else
            value = 'A';

        for (short i = 0; i < 4; i++)
        {
            if (i == 0)
                suit = 'H';
            else if (i == 1)
                suit = 'D';
            else if (i == 2)
                suit = 'S';
            else
                suit = 'C';

            if (this->card1.value == value && this->card1.suit == suit)
            {
                five[i] = true;
                continue;
            }
            if (this->card2.value == value && this->card2.suit == suit)
            {
                five[i] = true;
                continue;
            }
            for (short j = 0; j < 5; ++j)
            {
                if (table_cards[j].value == value && table_cards[j].suit == suit)
                {
                    five[i] = true;
                    break;
                }
            }
        }

        if (five[0] && five[1] && five[2] && five[3])
        {
            this->combination = KARE;
            this->higt_card_combination = value;
            return;
        }

        for (short i = 0; i < 5; ++i)
            five[i] = false;
    }

    // Full-house
    for (short j = 0; j < 13; ++j)
    {
        if (j == 0)
            value = 'A';
        else if (j == 1)
            value = 'K';
        else if (j == 2)
            value = 'Q';
        else if (j == 3)
            value = 'J';
        else if (j == 4)
            value = 'T';
        else if (j == 5)
            value = '9';
        else if (j == 6)
            value = '8';
        else if (j == 7)
            value = '7';
        else if (j == 8)
            value = '6';
        else if (j == 9)
            value = '5';
        else if (j == 10)
            value = '4';
        else if (j == 11)
            value = '3';
        else
            value = '2';

        for (short i = 0; i < 4; i++)
        {
            if (i == 0)
                suit = 'H';
            else if (i == 1)
                suit = 'D';
            else if (i == 2)
                suit = 'S';
            else
                suit = 'C';

            if (this->card1.value == value && this->card1.suit == suit)
            {
                five[i] = true;
                continue;
            }
            if (this->card2.value == value && this->card2.suit == suit)
            {
                five[i] = true;
                continue;
            }
            for (short k = 0; k < 5; ++k)
            {
                if (table_cards[k].value == value && table_cards[k].suit == suit)
                {
                    five[i] = true;
                    break;
                }
            }
        }

        if (!five[0] && five[1] && five[2] && five[3] || five[0] && !five[1] && five[2] && five[3] || five[0] && five[1] && !five[2] && five[3] || five[0] && five[1] && five[2] && !five[3])
        {
            this->higt_card_combination = value;
            for (short n = 0; n < 5; ++n)
                five[n] = false;
            char pare_value;
            for (short n = 0; n < 13; ++n)
            {
                if (n == 0 && value != 'A')
                    pare_value = 'A';
                else if (n == 1 && value != 'K')
                    pare_value = 'K';
                else if (n == 2 && value != 'Q')
                    pare_value = 'Q';
                else if (n == 3 && value != 'J')
                    pare_value = 'J';
                else if (n == 4 && value != 'T')
                    pare_value = 'T';
                else if (n == 5 && value != '9')
                    pare_value = '9';
                else if (n == 6 && value != '8')
                    pare_value = '8';
                else if (n == 7 && value != '7')
                    pare_value = '7';
                else if (n == 8 && value != '6')
                    pare_value = '6';
                else if (n == 9 && value != '5')
                    pare_value = '5';
                else if (n == 10 && value != '4')
                    pare_value = '4';
                else if (n == 11 && value != '3')
                    pare_value = '3';
                else if (n == 12 && value != '2')
                    pare_value = '2';
                else
                    continue;
                for (short m = 0; m < 4; m++)
                {
                    if (m == 0)
                        suit = 'H';
                    else if (m == 1)
                        suit = 'D';
                    else if (m == 2)
                        suit = 'S';
                    else
                        suit = 'C';


                    if (this->card1.value == pare_value && this->card1.suit == suit)
                    {
                        five[m] = true;
                        continue;
                    }
                    if (this->card2.value == pare_value && this->card2.suit == suit)
                    {
                        five[m] = true;
                        continue;
                    }
                    for (short k = 0; k < 5; ++k)
                    {
                        if (table_cards[k].value == pare_value && table_cards[k].suit == suit)
                        {
                            five[m] = true;
                            break;
                        }
                    }

                }

                if (five[0] && five[1] && !five[2] && !five[3] || five[0] && !five[1] && five[2] && !five[3] || five[0] && !five[1] && !five[2] && five[3] || !five[0] && five[1] && five[2] && !five[3] || !five[0] && five[1] && !five[2] && five[3] || !five[0] && !five[1] && five[2] && five[3])
                {
                    this->combination = FULL_HOUSE;
                    return;
                }

                for (short i = 0; i < 5; ++i)
                    five[i] = false;
            }
        }

        for (short n = 0; n < 5; ++n)
            five[n] = false;
    }

    // Flush
    for (short i = 0; i < 4; i++)
    {
        if (i == 0)
            suit = 'H';
        else if (i == 1)
            suit = 'D';
        else if (i == 2)
            suit = 'S';
        else
            suit = 'C';

        short t = 0;
        if (this->card1.suit == suit)
        {
            five[t] = true;
            t++;
        }
        if (this->card2.suit == suit)
        {
            five[t] = true;
            t++;
        }
        for (short j = 0; j < 5; ++j)
        {
            if (table_cards[j].suit == suit)
            {
                five[t] = true;
                t++;
            }
        }

        if (five[0] && five[1] && five[2] && five[3] && five[4])
        {
            this->combination = FLUSH;
            this->higt_card_combination = '2';
            for (short j = 0; j < 5; ++j)
            {
                if (table_cards[j].value > this->higt_card_combination)
                    this->higt_card_combination = table_cards[j].value;
            }
            if (this->card1.value > this->higt_card_combination)
                this->higt_card_combination = this->card1.value;
            if (this->card2.value > this->higt_card_combination)
                this->higt_card_combination = this->card2.value;
            return;
        }

        for (short i = 0; i < 5; ++i)
            five[i] = false;
    }

    // Straight
    for (short n = 0; n < 10; ++n)
    {
        for (short k = 0; k < 5; k++)
        {
            if (n == 0)
            {
                if (k == 0)
                    value = 'A';
                else if (k == 1)
                    value = '2';
                else if (k == 2)
                    value = '3';
                else if (k == 3)
                    value = '4';
                else
                    value = '5';
            }
            else if (n == 1)
            {
                if (k == 0)
                    value = '2';
                else if (k == 1)
                    value = '3';
                else if (k == 2)
                    value = '4';
                else if (k == 3)
                    value = '5';
                else
                    value = '6';
            }
            else if (n == 2)
            {
                if (k == 0)
                    value = '3';
                else if (k == 1)
                    value = '4';
                else if (k == 2)
                    value = '5';
                else if (k == 3)
                    value = '6';
                else
                    value = '7';
            }
            else if (n == 3)
            {
                if (k == 0)
                    value = '4';
                else if (k == 1)
                    value = '5';
                else if (k == 2)
                    value = '6';
                else if (k == 3)
                    value = '7';
                else
                    value = '8';
            }
            else if (n == 4)
            {
                if (k == 0)
                    value = '5';
                else if (k == 1)
                    value = '6';
                else if (k == 2)
                    value = '7';
                else if (k == 3)
                    value = '8';
                else
                    value = '9';
            }
            else if (n == 5)
            {
                if (k == 0)
                    value = '6';
                else if (k == 1)
                    value = '7';
                else if (k == 2)
                    value = '8';
                else if (k == 3)
                    value = '9';
                else
                    value = 'T';
            }
            else if (n == 6)
            {
                if (k == 0)
                    value = '7';
                else if (k == 1)
                    value = '8';
                else if (k == 2)
                    value = '9';
                else if (k == 3)
                    value = 'T';
                else
                    value = 'J';
            }
            else if (n == 7)
            {
                if (k == 0)
                    value = '8';
                else if (k == 1)
                    value = '9';
                else if (k == 2)
                    value = 'T';
                else if (k == 3)
                    value = 'J';
                else
                    value = 'Q';
            }
            else if (n == 8)
            {
                if (k == 0)
                    value = '9';
                else if (k == 1)
                    value = 'T';
                else if (k == 2)
                    value = 'J';
                else if (k == 3)
                    value = 'Q';
                else
                    value = 'K';
            }
            else if (n == 9)
            {
                if (k == 0)
                    value = 'T';
                else if (k == 1)
                    value = 'J';
                else if (k == 2)
                    value = 'Q';
                else if (k == 3)
                    value = 'K';
                else
                    value = 'A';
            }

            if (this->card1.value == value)
            {
                five[k] = true;
                continue;
            }
            if (this->card2.value == value)
            {
                five[k] = true;
                continue;
            }
            for (short j = 0; j < 5; ++j)
            {
                if (table_cards[j].value == value)
                {
                    five[k] = true;
                    break;
                }
            }
        }

        if (five[0] && five[1] && five[2] && five[3] && five[4])
        {
            this->combination = STRAIGHT;

            if (n == 0)
                this->higt_card_combination = '5';

            else if (n == 1)
                this->higt_card_combination = '6';

            else if (n == 2)
                this->higt_card_combination = '7';

            else if (n == 3)
                this->higt_card_combination = '8';

            else if (n == 4)
                this->higt_card_combination = '9';

            else if (n == 5)
                this->higt_card_combination = 'T';

            else if (n == 6)
                this->higt_card_combination = 'J';

            else if (n == 7)
                this->higt_card_combination = 'Q';

            else if (n == 8)
                this->higt_card_combination = 'K';

            else if (n == 9)
                this->higt_card_combination = 'A';
            return;
        }

        for (short i = 0; i < 5; ++i)
            five[i] = false;
    }

    // Set
    for (short j = 0; j < 13; ++j)
    {
        if (j == 0)
            value = 'A';
        else if (j == 1)
            value = 'K';
        else if (j == 2)
            value = 'Q';
        else if (j == 3)
            value = 'J';
        else if (j == 4)
            value = 'T';
        else if (j == 5)
            value = '9';
        else if (j == 6)
            value = '8';
        else if (j == 7)
            value = '7';
        else if (j == 8)
            value = '6';
        else if (j == 9)
            value = '5';
        else if (j == 10)
            value = '4';
        else if (j == 11)
            value = '3';
        else
            value = '2';

        for (short i = 0; i < 4; i++)
        {
            if (i == 0)
                suit = 'H';
            else if (i == 1)
                suit = 'D';
            else if (i == 2)
                suit = 'S';
            else
                suit = 'C';

            if (this->card1.value == value && this->card1.suit == suit)
            {
                five[i] = true;
                continue;
            }
            if (this->card2.value == value && this->card2.suit == suit)
            {
                five[i] = true;
                continue;
            }
            for (short j = 0; j < 5; ++j)
            {
                if (table_cards[j].value == value && table_cards[j].suit == suit)
                {
                    five[i] = true;
                    break;
                }
            }
        }

        if (!five[0] && five[1] && five[2] && five[3] || five[0] && !five[1] && five[2] && five[3] || five[0] && five[1] && !five[2] && five[3] || five[0] && five[1] && five[2] && !five[3])
        {
            this->combination = SET;
            this->higt_card_combination = value;
            return;
        }

        for (short i = 0; i < 5; ++i)
            five[i] = false;
    }

    // Two-pairs
    for (short j = 0; j < 13; ++j)
    {
        if (j == 0)
            value = 'A';
        else if (j == 1)
            value = 'K';
        else if (j == 2)
            value = 'Q';
        else if (j == 3)
            value = 'J';
        else if (j == 4)
            value = 'T';
        else if (j == 5)
            value = '9';
        else if (j == 6)
            value = '8';
        else if (j == 7)
            value = '7';
        else if (j == 8)
            value = '6';
        else if (j == 9)
            value = '5';
        else if (j == 10)
            value = '4';
        else if (j == 11)
            value = '3';
        else
            value = '2';

        for (short i = 0; i < 4; i++)
        {
            if (i == 0)
                suit = 'H';
            else if (i == 1)
                suit = 'D';
            else if (i == 2)
                suit = 'S';
            else
                suit = 'C';

            if (this->card1.value == value && this->card1.suit == suit)
            {
                five[i] = true;
                continue;
            }
            if (this->card2.value == value && this->card2.suit == suit)
            {
                five[i] = true;
                continue;
            }
            for (short j = 0; j < 5; ++j)
            {
                if (table_cards[j].value == value && table_cards[j].suit == suit)
                {
                    five[i] = true;
                    break;
                }
            }
        }

        if (five[0] && five[1] && !five[2] && !five[3] || five[0] && !five[1] && five[2] && !five[3] || five[0] && !five[1] && !five[2] && five[3] || !five[0] && five[1] && five[2] && !five[3] || !five[0] && five[1] && !five[2] && five[3] || !five[0] && !five[1] && five[2] && five[3])
        {
            this->higt_card_combination = value;

            for (short i = 0; i < 5; ++i)
                five[i] = false;
            char pare_value;
            for (short n = 0; n < 13; ++n)
            {
                if (n == 0 && value != 'A')
                    pare_value = 'A';
                else if (n == 1 && value != 'K')
                    pare_value = 'K';
                else if (n == 2 && value != 'Q')
                    pare_value = 'Q';
                else if (n == 3 && value != 'J')
                    pare_value = 'J';
                else if (n == 4 && value != 'T')
                    pare_value = 'T';
                else if (n == 5 && value != '9')
                    pare_value = '9';
                else if (n == 6 && value != '8')
                    pare_value = '8';
                else if (n == 7 && value != '7')
                    pare_value = '7';
                else if (n == 8 && value != '6')
                    pare_value = '6';
                else if (n == 9 && value != '5')
                    pare_value = '5';
                else if (n == 10 && value != '4')
                    pare_value = '4';
                else if (n == 11 && value != '3')
                    pare_value = '3';
                else if (n == 12 && value != '2')
                    pare_value = '2';
                else
                    continue;
                for (short m = 0; m < 4; m++)
                {
                    if (m == 0)
                        suit = 'H';
                    else if (m == 1)
                        suit = 'D';
                    else if (m == 2)
                        suit = 'S';
                    else
                        suit = 'C';

                    if (this->card1.value == pare_value && this->card1.suit == suit)
                    {
                        five[m] = true;
                        continue;
                    }
                    if (this->card2.value == pare_value && this->card2.suit == suit)
                    {
                        five[m] = true;
                        continue;
                    }
                    for (short j = 0; j < 5; ++j)
                    {
                        if (table_cards[j].value == pare_value && table_cards[j].suit == suit)
                        {
                            five[m] = true;
                            break;
                        }
                    }

                }

                if (five[0] && five[1] && !five[2] && !five[3] || five[0] && !five[1] && five[2] && !five[3] || five[0] && !five[1] && !five[2] && five[3] || !five[0] && five[1] && five[2] && !five[3] || !five[0] && five[1] && !five[2] && five[3] || !five[0] && !five[1] && five[2] && five[3])
                {
                    this->combination = TWO_PAIR;
                    if (pare_value > this->higt_card_combination)
                        this->higt_card_combination = pare_value;
                    return;
                }

                for (short i = 0; i < 5; ++i)
                    five[i] = false;
            }
        }

        for (short i = 0; i < 5; ++i)
            five[i] = false;
    }

    // Pair
    for (short j = 0; j < 13; ++j)
    {
        if (j == 0)
            value = 'A';
        else if (j == 1)
            value = 'K';
        else if (j == 2)
            value = 'Q';
        else if (j == 3)
            value = 'J';
        else if (j == 4)
            value = 'T';
        else if (j == 5)
            value = '9';
        else if (j == 6)
            value = '8';
        else if (j == 7)
            value = '7';
        else if (j == 8)
            value = '6';
        else if (j == 9)
            value = '5';
        else if (j == 10)
            value = '4';
        else if (j == 11)
            value = '3';
        else
            value = '2';

        for (short i = 0; i < 4; i++)
        {
            if (i == 0)
                suit = 'H';
            else if (i == 1)
                suit = 'D';
            else if (i == 2)
                suit = 'S';
            else
                suit = 'C';

            if (this->card1.value == value && this->card1.suit == suit)
            {
                five[i] = true;
                continue;
            }
            if (this->card2.value == value && this->card2.suit == suit)
            {
                five[i] = true;
                continue;
            }
            for (short j = 0; j < 5; ++j)
            {
                if (table_cards[j].value == value && table_cards[j].suit == suit)
                {
                    five[i] = true;
                    break;
                }
            }
        }

        if (five[0] && five[1] && !five[2] && !five[3] || five[0] && !five[1] && five[2] && !five[3] || five[0] && !five[1] && !five[2] && five[3] || !five[0] && five[1] && five[2] && !five[3] || !five[0] && five[1] && !five[2] && five[3] || !five[0] && !five[1] && five[2] && five[3])
        {
            this->higt_card_combination = value;
            this->combination = PAIR;
            return;
        }

        for (short i = 0; i < 5; ++i)
            five[i] = false;
    }

    // High card
    for (short j = 0; j < 13; ++j)
    {
        if (j == 0)
            value = 'A';
        else if (j == 1)
            value = 'K';
        else if (j == 2)
            value = 'Q';
        else if (j == 3)
            value = 'J';
        else if (j == 4)
            value = 'T';
        else if (j == 5)
            value = '9';
        else if (j == 6)
            value = '8';
        else if (j == 7)
            value = '7';
        else if (j == 8)
            value = '6';
        else if (j == 9)
            value = '5';
        else if (j == 10)
            value = '4';
        else if (j == 11)
            value = '3';
        else
            value = '2';

        if (this->card1.value == value)
        {
            this->combination = HIGH_CARD;
            return;
        }
        if (this->card2.value == value)
        {
            this->combination = HIGH_CARD;
            return;
        }
        for (short j = 0; j < 5; ++j)
        {
            if (table_cards[j].value == value)
            {
                this->combination = HIGH_CARD;
                return;
            }
        }
    }
}

