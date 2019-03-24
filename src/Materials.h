#ifndef MATERIALS_H_INCLUDED
#define MATERIALS_H_INCLUDED

#include <string>

class Tile;
class Item;

namespace Materials{

    extern const std::string materials[];   //array of tile names (array index corresponds with tile's unique item ID)
    extern const std::string itemNames[];   //array of item names (array index corresponds with item's unique item ID)
    extern const int numMaterials;          //total number of different tiles in the game.
    extern const int numItems;              //total number of different items in the game.
    extern Tile* tiles[];                   //array to store the different tiles.
    extern Item* items[];                   //array to store the different items.

    Tile* getTile(int i); //returns any tile pointer in the tiles array.
    Item* getItem(int i); //returns any item pointer in the items array.

    //loads all of the different tiles into the tiles array,
    //it initializes their texture, interactibility, collision,
    //and their names:
    void loadMaterials();

    //deletes and nullifies all of the pointers in the tiles array
    //to clean up that memory space:
    void unloadMaterials();
}

#endif // MATERIALS_H_INCLUDED
