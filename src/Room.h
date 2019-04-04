#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <stdint.h>
#include "main.h"
#include "Item.h"

class Room{
private:

    //number of tiles X and Y:
    static const int tilesX = 32, tilesY = 18;

    int tileGrid[tilesX][tilesY];    //grid of tiles, the tiles are stored by their unique item IDs.

    std::vector<Item> items; //vector of items in the room.
public:


    Room(); //default constructor for a Room

    friend std::ostream& operator<< (std::ostream& o, const Room& room);
    friend std::istream& operator>> (std::istream& i, Room& room);

    //sets the tile at a certain position in the room,
    //x and y are room coordinates not actual coordinates.
    //rooms are 32x18 tiles:
    void setTile(uint32_t x, uint32_t y, int tileID);

    //returns whatever tile ID is at the x and y passed,
    //x and y are room coordinates not actual coordinates.
    int getTile(uint32_t x, uint32_t y) const;

    //adds an Item object to the items vector.
    void addItem(const Item& i);

    //removes an Item object from the index in the items vector.
    void removeItem(const int& index);

    //gets an item from the vector by index.
    Item getItem(const int& index) const;

    //loops through the vector of items and returns the index
    //of any item that intersects with collision, if there are
    //no items that intersect, it returns -1.
    int checkForItemCollision(sf::FloatRect collision) const;

    void draw(); //draws every tile in the room to the screen.
};

#endif // ROOM_H_INCLUDED
