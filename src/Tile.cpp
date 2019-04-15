#include "Tile.h"
#include "Engine.h"
#include "Room.h"

//constructors:
Tile::Tile(const char* name, const uint32_t& ID, bool solid, bool interact){
    tileName = name;
    itemID = ID;
    collision = solid;
    interactable = interact;

    tile.setSize(sf::Vector2f(Engine::TILE_SIZE_X, Engine::TILE_SIZE_Y));
}

Tile::Tile(const char* name, const uint32_t& ID, bool solid, bool interact, const sf::Texture* tx){
    tileName = name;
    itemID = ID;
    collision = solid;
    interactable = interact;

    tile.setSize(sf::Vector2f(Engine::TILE_SIZE_X, Engine::TILE_SIZE_Y));
    texture = *tx;
    tile.setTexture(&texture);
}

//setter methods:

void Tile::setRoomCoordinates(const uint16_t& x, const uint16_t& y){
    tile.setPosition(sf::Vector2f(x*Engine::TILE_SIZE_X, y*Engine::TILE_SIZE_Y));
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
