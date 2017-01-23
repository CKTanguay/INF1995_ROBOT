#include "FonctionDelai.h"

void delai1MS(uint8_t delai)
{
    for (int i = 0; i < delai; i++)
    {
        _delay_ms(1);
    }
}


void delai5MS(uint8_t delai)
{
    for (int i = 0; i < delai; i++)
    {
        _delay_ms(5);
    }
}


void delai25MS(uint8_t delai)
{
    for (int i = 0; i < delai; i++)
    {
        _delay_ms(25);
    }
}


void delai100MS(uint8_t delai)
{
    for (int i = 0; i < delai; i++)
    {
        _delay_ms(100);
    }
}


void delai250MS(uint8_t delai)
{
    for (int i = 0; i < delai; i++)
    {
        _delay_ms(250);
    }
}


void delai500MS(uint8_t delai)
{
    for (int i = 0; i < delai; i++)
    {
        _delay_ms(500);
    }
}


void delai1000MS(uint8_t delai)
{
    for (int i = 0; i < delai; i++)
    {
        _delay_ms(1000);
    }
}
