#ifndef HEADSUPDISPLAY_H_INCLUDED
#define HEADSUPDISPLAY_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "NumberBar.h"

namespace HeadsUpDisplay{
    extern uint32_t    Health;
    extern uint32_t    Special;
    extern uint32_t    Money;
    extern uint32_t    healthCap;
    extern uint32_t    specialCap;

    extern sf::Text    hpText;
    extern sf::Text    spText;
    extern sf::Text    moneyText;

    extern std::unique_ptr< NumberBar<uint32_t> > healthBar;
    extern std::unique_ptr< NumberBar<uint32_t> > specialBar;

    void draw(uint32_t hp, uint32_t sp, uint32_t m);
    void updateHealthCap(uint32_t cap);
    void updateSpecialCap(uint32_t cap);
    void initialize(uint32_t hp, uint32_t sp, const uint32_t& hpCap, const uint32_t& spCap);
}

#endif // HEADSUPDISPLAY_H_INCLUDED
