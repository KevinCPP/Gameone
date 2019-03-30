#include "Materials.h"
#include "Tile.h"
#include "Item.h"
#include <string>

namespace Materials{

    const int numMaterials = 14; //total number of different tiles in the game
    const int numItems = 4;

    Tile* tiles[numMaterials];   //array to store the different tile
    Item* items[numItems];

    //array of tile names (array index corresponds with tile's unique item ID):
    const std::string materials[numMaterials] = {
        "Air",
        "Rock_Wall",
        "Sand_Floor",
        "Bush",
        "Water",
        "Gray_Brick",
        "Red_Brick",
        "Green_Brick",
        "Blue_Brick",
        "Gray_Brick_Floor",
        "Red_Brick_Floor",
        "Green_Brick_Floor",
        "Blue_Brick_Floor",
        "Wooden_Stairs"
    };

    const std::string itemNames[numItems] = {
        "Item_Sword",
        "Ultra_Potion_Of_Healing",
        "Super_Potion_Of_Healing",
        "Potion_Of_Healing"
    };

    const int itemValues[numItems] = {
        50,
        2500,
        750,
        100
    };

    const Item::Item_Type itemTypes[numItems] = {
        Item::Weapon,
        Item::Usable,
        Item::Usable,
        Item::Usable
    };

    const int numNoCollisionItems = 6; //number of tiles that have no collision

    //array that stores all of the Tile Item IDs that have no collision.
    const int noCollision[numNoCollisionItems] = {2, 9, 10, 11, 12, 13};

    //loads all of the different tiles into the tiles array,
    //it initializes their texture, interactibility, collision,
    //and their names:
    void loadMaterials(){
        for(int i = 0; i < numMaterials; i++){

            bool collision = true;

            for(int k = 0; k < numNoCollisionItems; k++)
                if(i == noCollision[k])
                    collision = false;

            tiles[i] = new Tile(materials[i].c_str(), i, collision, 0);

            sf::Texture tx;
            if(!tx.loadFromFile("Textures\\" + materials[i] + ".png"))
                tx.loadFromFile("Textures\\missingTexture.png");

            tiles[i]->setTexture(&tx);
        }

        for(int i = 0; i < numItems; i++){
            items[i] = new Item(i);

            items[i]->setValue(itemValues[i]);
            items[i]->setItemType(itemTypes[i]);

            sf::Texture tx;
            if(!tx.loadFromFile("Textures\\" + itemNames[i] + ".png"))
                tx.loadFromFile("Textures\\missingTexture.png");

            items[i]->setTexture(&tx);
        }
    }

    //returns any tile pointer in the tiles array:
    Tile* getTile(int i){
        return tiles[i];
    }

    Item* getItem(int i){
        return items[i];
    }

    Item* getItemFromName(std::string n){
        for(int i = 0; i < numItems; i++){
            if(n == itemNames[i])
                return items[i];
        }
        return nullptr;
    }

    //deletes and nullifies all of the pointers in the tiles array
    //to clean up that memory space:
    void unloadMaterials(){
        for(int i = 0; i < numMaterials; i++){
            delete tiles[i];
            tiles[i] = nullptr;
        }
    }
}
