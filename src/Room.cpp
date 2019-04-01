#include "Room.h"
#include "Tile.h"
#include "Materials.h"
#include "Engine.h"

Room::Room(){
    Materials::loadMaterials();
    for(int i = 0; i < Engine::tilesX; i++){
        for(int k = 0; k < Engine::tilesY; k++){
            tileGrid[i][k] = 2; //initialize all tiles to sand floor
        }
    }
}

void Room::setTile(uint32_t x, uint32_t y, int tileID){
    if(x < Engine::tilesX && y < Engine::tilesY)
        tileGrid[x][y] = tileID;
}

int Room::getTile(uint32_t x, uint32_t y){
    if(x < Engine::tilesX && y < Engine::tilesY){
        return tileGrid[x][y];
    } else {
        return 0;
    }
}

void Room::addItem(const Item& i){
    items.push_back(i);
}

void Room::removeItem(const int& index){
    items.erase(items.begin() + index);
}

Item Room::getItem(const int& index){
    return items.at(index);
}

int Room::checkForItemCollision(sf::FloatRect collision){
    for(int i = 0; i < items.size(); i++){
        if(collision.intersects(items[i].getCollision())){
            return i;
        }
    }
    return -1;
}

void Room::draw(){
    for(int i = 0; i < Engine::tilesX; i++){
        for(int k = 0; k < Engine::tilesY; k++){
            Tile* t = Materials::getTile(tileGrid[i][k]);
            t->setRoomCoordinates(i, k);
            t->draw();
        }
    }

    for(int i = 0; i < items.size(); i++){
        items[i].draw();
    }
}
