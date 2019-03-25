#include "Player.h"
#include "Engine.h"
#include "Materials.h"
#include "Tile.h"

#include <cmath>
#include <string>
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
    openMenu.setButton(sf::Keyboard::E);
    menuCursorDown.setButton(sf::Keyboard::Down);
    menuCursorUp.setButton(sf::Keyboard::Up);

    player.setFillColor(sf::Color::Red);
    player.setSize(sf::Vector2f(40 , 40));
}

void Player::control(Room* r){

    if(openMenu.pollKey())
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

    int weaponY = 150;
    int usableY = 150;
    int collectibleY = 150;
    int moneyY = 150;

    for(auto &i : ItemsList){
        Item* itm = Materials::getItemFromName(i.first);

        std::wstring wideName = std::wstring(i.first.begin(), i.first.end());

        int indBtn = ItemButtonsTextSearch(wideName);

        std::cout << indBtn;

        switch(itm->getType()){
            case Item::Weapon:
                weaponY += 20;
                itemButtons.at(indBtn).setPosition(100, weaponY);
                break;
            case Item::Usable:
                usableY += 20;
                itemButtons.at(indBtn).setPosition(375, usableY);
                break;
            case Item::Collectible:
                collectibleY += 20;
                itemButtons.at(indBtn).setPosition(650, collectibleY);
                break;
            case Item::Money:
                moneyY += 20;
                itemButtons.at(indBtn).setPosition(925, moneyY);
                break;
        }

        //minGW has a bug where std::to_wstring does not work? fix:
        std::string s = std::to_string(i.second);
        std::wstring ws = std::wstring(s.begin(), s.end());

        itemButtons.at(indBtn).setText((wideName + L"\tx" + ws).c_str());
        itemButtons.at(indBtn).draw();
        itemButtons.at(indBtn).setText(wideName.c_str());
    }
}

int Player::ItemButtonsTextSearch(const std::wstring& text){
    for(int i = 0; i < itemButtons.size(); i++){
        if(itemButtons.at(i).getText() == text)
            return i;
    }
    return -1;
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

            std::wstring wname;
            wname = std::wstring(Materials::itemNames[itemID].begin(),
                                 Materials::itemNames[itemID].end() );

            itemButtons.push_back( TextButton(sf::Vector2f(0, 0),
                                              sf::Color::Magenta,
                                              sf::Color::White,
                                              wname.c_str(),
                                              18) );
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
