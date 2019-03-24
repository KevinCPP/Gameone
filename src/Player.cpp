#include "Player.h"
#include "Engine.h"
#include "Materials.h"
#include "Tile.h"


#include <cmath>
#include <sstream>
#include <algorithm>

Player::Player(int maxhp, int maxsp, sf::Vector2f position){
    player.setPosition(position);
    pos = player.getPosition();

    money = 0;
    speed = 4;
    maxHP = maxhp;
    maxSP = maxsp;
    HP = maxhp;
    SP = maxsp;

    menuOpen = false;
    MenuControl.setButton(sf::Keyboard::E);

    player.setFillColor(sf::Color::Red);
    player.setSize(sf::Vector2f(40 , 40));
}

void Player::control(Room* r){

    if(MenuControl.pollKey())
        menuOpen = !menuOpen;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        pos.y -= speed;
        player.setPosition(pos);

        if(testCollision(r)){
            pos.y += speed;
            player.setPosition(pos);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        pos.x -= speed;
        player.setPosition(pos);

        if(testCollision(r)){
            pos.x += speed;
            player.setPosition(pos);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        pos.x += speed;
        player.setPosition(pos);

        if(testCollision(r)){
            pos.x -= speed;
            player.setPosition(pos);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        pos.y += speed;
        player.setPosition(pos);

        if(testCollision(r)){
            pos.y -= speed;
            player.setPosition(pos);
        }
    }

    if(menuOpen)
        menu();

    checkForItems(r);
}

void Player::menu(){
    sf::Text t;
    t.setCharacterSize(18);
    t.setFont(*Engine::gpFont);
    t.setFillColor(sf::Color::Magenta);
    t.setOutlineColor(sf::Color::Black);
    t.setOutlineThickness(1);

    t.setPosition(300, 150);

    for(auto &i : ItemsList){
        t.setString(i.first + "\tx" + std::to_string(i.second));
        Engine::gpWindow->draw(t);
    }
}

bool Player::testCollision(Room* r){
    for(int x = 0; x < 32; x++){
        for(int y = 0; y < 18; y++){
            sf::FloatRect tile = sf::FloatRect(sf::Vector2f(x*40, y*40), sf::Vector2f(40, 40));
            sf::FloatRect p = player.getGlobalBounds();

            if(tile.intersects(p) && Materials::getTile(r->getTile(x, y))->hasCollision()){
                return true;
            }
        }
    }
    return false;
}

bool Player::checkForItems(Room* r){
    int itemIndex = r->checkForItemCollision(player.getGlobalBounds());

    if(itemIndex >= 0){
        int itemID = r->getItem(itemIndex).collect();
        r->removeItem(itemIndex);
        ItemInventory.push_back(itemID);

        if(ItemsList.count(Materials::itemNames[itemID])){
            ItemsList.at(Materials::itemNames[itemID]) += 1;
        } else {
            ItemsList.insert(std::make_pair(Materials::itemNames[itemID], 1));
        }

        return true;
    }
    return false;
}

int Player::getHP(){
    return HP;
}

int Player::getSP(){
    return SP;
}

int Player::getMoney(){
    return money;
}

void Player::setMoney(int amount){
    money = amount;
}

void Player::setHP(int hp){
    HP = hp;
}
void Player::setSP(int sp){
    SP = sp;
}

void Player::draw(){
    Engine::gpWindow->draw(player);
}
