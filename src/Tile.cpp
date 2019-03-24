#include "Tile.h"
#include "Engine.h"

//constructors:

Tile::Tile(const char* name, const uint32_t& ID, bool solid, bool interact){
    tileName = name;
    itemID = ID;
    collision = solid;
    interactable = interact;

    float tileWidth = Engine::xResolution/Engine::tilesX;
    float tileHeight = Engine::yResolution/Engine::tilesY;

    width = tileWidth;
    height = tileHeight;

    tile.setSize(sf::Vector2f(tileWidth, tileHeight));
}

Tile::Tile(const char* name, const uint32_t& ID, bool solid, bool interact, const sf::Texture* tx){
    tileName = name;
    itemID = ID;
    collision = solid;
    interactable = interact;

    float tileWidth = Engine::xResolution/Engine::tilesX;
    float tileHeight = Engine::yResolution/Engine::tilesY;

    tile.setSize(sf::Vector2f(tileWidth, tileHeight));
    texture = *tx;
    tile.setTexture(&texture);
}

//setter methods:

void Tile::setRoomCoordinates(const uint16_t& x, const uint16_t& y){
    tile.setPosition(sf::Vector2f(x*width, y*height));
}

void Tile::setTexture(const sf::Texture* tx){
    texture = *tx;
    tile.setTexture(&texture);
}

void Tile::setInteractable(bool interact){
    interactable = interact;
}

void Tile::setCollision(bool solid){
    collision = solid;
}

//getter methods:

uint32_t Tile::getItemID(){
    return itemID;
}

bool Tile::isInteractable(){
    return interactable;
}

bool Tile::hasCollision(){
    return collision;
}

//draws the tile to the window.

void Tile::draw(){
    Engine::gpWindow->draw(tile);
}
