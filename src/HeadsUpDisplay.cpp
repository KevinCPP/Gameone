#include "HeadsUpDisplay.h"
#include "Engine.h"
#include <string>

namespace HeadsUpDisplay{

    uint32_t    Health;
    uint32_t    Special;
    uint32_t    healthCap;
    uint32_t    specialCap;
    uint32_t    money;

    sf::Text    hpText;
    sf::Text    spText;
    sf::Text    moneyText;

    std::unique_ptr< NumberBar<uint32_t> > healthBar;
    std::unique_ptr< NumberBar<uint32_t> > specialBar;

    void initialize(uint32_t hp, uint32_t sp, const uint32_t& hpCap, const uint32_t& spCap){
        Health = hp;
        Special = sp;
        healthCap = hpCap;
        specialCap = spCap;

        std::string HPstr = "HP: " + std::to_string(Health) + " / " + std::to_string(healthCap);
        std::string SPstr = "SP: " + std::to_string(Special) + " / " + std::to_string(specialCap);
        std::string Mstr  = "$" + std::to_string(money);

        hpText.setString(HPstr);
        hpText.setFont(*Engine::gpFont);
        hpText.setCharacterSize(14);
        hpText.setFillColor(sf::Color(255, 96, 96));
        hpText.setPosition(sf::Vector2f(5.f, 4.f));
        hpText.setOutlineColor(sf::Color(64, 64, 64));
        hpText.setOutlineThickness(1);

        spText.setString(SPstr);
        spText.setFont(*Engine::gpFont);
        spText.setCharacterSize(14);
        spText.setFillColor(sf::Color(96, 96, 255));
        spText.setPosition(sf::Vector2f(350.f, 4.f));
        spText.setOutlineColor(sf::Color(64, 64, 64));
        spText.setOutlineThickness(1);

        moneyText.setString(Mstr);
        moneyText.setFont(*Engine::gpFont);
        moneyText.setCharacterSize(20);
        moneyText.setFillColor(sf::Color::Green);
        moneyText.setPosition(sf::Vector2f(700.f, 10.f));
        moneyText.setOutlineColor(sf::Color(64, 64, 64));
        moneyText.setOutlineThickness(1);

        healthBar = std::make_unique< NumberBar<uint32_t> >(&Health, 0, healthCap, sf::Vector2f(300, 10), sf::Vector2f(5, 20));
        specialBar = std::make_unique< NumberBar<uint32_t> >(&Special, 0, specialCap, sf::Vector2f(300, 10), sf::Vector2f(350, 20));

        healthBar->setPrimaryBarColor(sf::Color(255, 96, 96));
        healthBar->setPrimaryOutlineColor(sf::Color(64, 64, 64));
        specialBar->setPrimaryBarColor(sf::Color(96, 96, 255));
        specialBar->setPrimaryOutlineColor(sf::Color(64, 64, 64));
    }

    void draw(uint32_t hp, uint32_t sp, uint32_t m){
        Health = hp;
        Special = sp;
        money = m;

        hpText.setString("HP: " + std::to_string(Health) + " / " + std::to_string(healthCap));
        spText.setString("SP: " + std::to_string(Special) + " / " + std::to_string(specialCap));
        moneyText.setString("$" + std::to_string(money));

        healthBar->draw();
        specialBar->draw();
        Engine::gpWindow->draw(hpText);
        Engine::gpWindow->draw(spText);
        Engine::gpWindow->draw(moneyText);
    }

}
