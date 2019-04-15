#include "Room.h"
#include "Tile.h"
#include "Materials.h"
#include "Engine.h"
#include "Utility.h"
#include <sstream>

Room::Room(){
    Materials::loadMaterials();
    for(int i = 0; i < Room::tilesX; i++){
        for(int k = 0; k < Room::tilesY; k++){
            tileGrid[i][k] = 2; //initialize all tiles to sand floor
        }
    }
}

std::ostream& operator<< (std::ostream& o, const Room& room){
    o << "\nTiles: ";
    for(int x = 0; x < Room::tilesX; x++){
        for(int y = 0; y < Room::tilesY; y++){
            o << room.getTile(x, y) << " ";
        }
    }
    o << std::endl;

    for(int i = 0; i < room.items.size(); i++){
        o << room.items.at(i);
    }
    o << "\nEND_OF_ROOM";

    return o;
}

std::istream& operator>> (std::istream& i, Room& room){
    //loop through each line in the istream:
    for(std::string line; std::getline(i, line); ){
        //if the line contains "Tiles:" we parse all
        //of the ints out which are the tileIDs for
        //the room's tiles:
        if(line.find("Tiles:") != std::string::npos){

            //parse ints from the line into the tileIDs vector:
            std::vector<int> tileIDs;
            Util::parseIntsFromString(line, tileIDs);

            //map the vector to the matrix,
            //looping through the rows of each columns:
            int tIndex = 0;

            //loops through columns:
            for(int x = 0; x < Room::tilesX; x++){
                //loop through rows:
                for(int y = 0; y < Room::tilesY; y++){
                    //check to make sure there are enough ints in the
                    //vector to fill up all of the tiles:
                    if(tIndex < tileIDs.size()){
                        room.tileGrid[x][y] = tileIDs.at(tIndex);
                        tIndex++;
                    } else {
                        //print an error message if there were not enough ints
                        //to fill in all of the tileIDs in the tilegrid matrix
                        //and fill the remaining tiles with the default tileID,
                        //2, which is sand_floor:
                        std::cerr << "Error loading room tiles: "
                                << "tileIDs vector not large enough "
                                << "to fill all tiles, the remaining "
                                << "tiles will be filled with sand_floor "
                                << " by default.";

                        room.tileGrid[x][y] = 2; //2 is the item ID for sand_floor.
                    }
                }
            }

        }
        else if(line.find("ID:") != std::string::npos){
            std::vector<int> itemInfo;
            Util::parseIntsFromString(line, itemInfo);

            //since we are setting the item's ID, and it's x/y coordinate,
            //we check to make sure there are 3 values in the itemInfo vector,
            //if not this error message is printed:
            if(itemInfo.size() != 3){
                std::cerr << "Error loading room item, itemInfo"
                    << "vector size invalid, itemInfo vector size: "
                    << itemInfo.size() << "\nline text: " << line;
            } else {
                //the first value will be the item's ID, so we make
                //an Item with the itemID:
                Item I = *Materials::getItem(itemInfo.at(0));

                //the second value will be the item's X, and the third
                //will be the item's Y, so we set the position accordingly:
                I.setPosition(sf::Vector2f(itemInfo.at(1), itemInfo.at(2)));

                //add the item to the room's items vector:
                room.items.push_back(I);
            }
        }
    }

    //return the istream once finished:
    return i;
}

void Room::setTile(uint32_t x, uint32_t y, int tileID){
    if(x < Room::tilesX && y < Room::tilesY)
        tileGrid[x][y] = tileID;
}

int Room::getTile(uint32_t x, uint32_t y) const{
    if(x < tilesX && y < tilesY){
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

Item Room::getItem(const int& index) const {
    return items.at(index);
}

int Room::checkForItemCollision(sf::FloatRect collision) const {
    for(int i = 0; i < items.size(); i++){
        if(collision.intersects(items[i].getCollision())){
            return i;
        }
    }
    return -1;
}

/**
* this function takes a FloatRect, and checks every tile
* in the room to see if the test FloatRect intersects with
* any that have collision, if it does then it returns true,
* otherwise it returns false.
**/
bool Room::checkForTileCollision(sf::FloatRect test) const {
    for(int x = 0; x < Room::tilesX; x++){
        for(int y = 0; y < Room::tilesY; y++){
            sf::FloatRect tile = sf::FloatRect(sf::Vector2f(x*Engine::TILE_SIZE_X, y*Engine::TILE_SIZE_Y),
                                               sf::Vector2f(Engine::TILE_SIZE_X, Engine::TILE_SIZE_Y));

            if(tile.intersects(test) && Materials::getTile(tileGrid[x][y])->hasCollision()){
                return true;
            }
        }
    }
    return false;
}

void Room::draw(){
    for(int i = 0; i < tilesX; i++){
        for(int k = 0; k < tilesY; k++){
            Tile* t = Materials::getTile(tileGrid[i][k]);
            t->setRoomCoordinates(i, k);
            t->draw();
        }
    }

    for(int i = 0; i < items.size(); i++){
        items[i].draw();
    }
}
