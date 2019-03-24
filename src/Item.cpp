#include "Item.h"
#include "Engine.h"

Item::Item(const sf::Texture* tx, const sf::Vector2f& pos, const int& iID, Item_Type type, const int& v){
    itemTexture = *tx;
    position = pos;
    itemID = iID;
    itemType = type;
    collected = false;
    value = v;

    itemSprite.setTexture(*tx);
    itemSprite.setPosition(position);
}

Item::Item(const int& iID){
    itemID = iID;
    collected = false;
}

sf::FloatRect Item::getCollision(){
    return itemSprite.getGlobalBounds();
}

sf::Vector2f Item::getPosition(){
    return itemSprite.getPosition();
}

sf::Vector2f Item::getSize(){
    sf::FloatRect r = itemSprite.getGlobalBounds();
    return sf::Vector2f(r.width, r.height);
}

Item::Item_Type Item::getType(){
    return itemType;
}

int Item::getTypeInt(){
    return (int)itemType;
}

int Item::getItemID(){
    return itemID;
}

int Item::getValue(){
    return value;
}

void Item::setPosition(const sf::Vector2f& pos){
    position = pos;
    itemSprite.setPosition(position);
}

void Item::setTexture(const sf::Texture* tx){
    itemTexture = *tx;
    itemSprite.setTexture(itemTexture);
}

void Item::setSize(const sf::Vector2f& sz){
    sf::FloatRect r = getCollision();
    sf::Vector2f s(sz.x/r.width, sz.y/r.height);
    itemSprite.setScale(s);
    r = getCollision();
    Size = sf::Vector2f(r.width, r.height);
}

void Item::setValue(const uint32_t& v){
    value = v;
}

void Item::setItemType(Item::Item_Type type){
    itemType = type;
}

void Item::setItemType(int type){
    itemType = (Item_Type)type;
}

int Item::collect(){
    collected = true;
    return itemID;
}

void Item::draw(){
    Engine::gpWindow->draw(itemSprite);
}
