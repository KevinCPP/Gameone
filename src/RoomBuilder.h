#ifndef ROOMBUILDER_H_INCLUDED
#define ROOMBUILDER_H_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>
#include "Controls.h"
#include "Room.h"
#include "TextButton.h"

/* The RoomBuilder Class stores a vector of rooms,
 * it allows me, the developer, to create new rooms easily
 * in the game instead of hard coding each room, then it
 * will have the functionality to store each room in a
 * file and when the player opens the game, it will load
 * all of these rooms that I made. This simplifies the
 * room building process because there is a user interface
 * for the room builder in game, that allows you to place
 * tiles and items anywhere on the map. this will not be
 * accessible to the players, but makes development far
 * easier.
*/
class RoomBuilder{
private:
    std::vector<TextButton> tileButtons; //vector of buttons, one button for each different tile.
    std::vector<TextButton> itemButtons; //vector of buttons, one button for each different item.
    std::vector<Room> rooms;             //vector that stores the room.
    int currentRoomIndex;                //index in the rooms vector (which room are you on)
    int currentBlock;                    //current block you are placing (changed with tileButtons)
    int currentItem;                     //current item you are placing (changed with itemButtons)
    bool menuVisible;                    //boolean to determine if the menu for changing tiles is visible.
    Control c;                           //control for the right mouse which can be polled (for placing items)
public:

    RoomBuilder(); //default constructor

    bool saveRooms(); //will save the rooms vector to a file.
    bool loadRooms(); //will load the rooms vector from a file.

    void ChangeCurrentBlock(uint32_t i); //method to change the current tile you are placing (uses tile's unique item ID)
    void changeCurrentItem(uint32_t i);  //method to change the current item you are placing (uses item's ID)
    void ChangeCurrentRoom(uint32_t i);  //method to change the current room you are in (changes currentRoomIndex)
    void CreateNewRoom();                //adds a new room to the rooms vector.
    void placeBlock();                   //places a block where the mouse is positioned.
    void placeItem();                    //places an item where the mouse is positioned.
    void restart();                      //will reset all of the tiles in the room to AIR (item id: 0)
    void menu();                         //draws the menu to the screen.

    sf::Vector2i getCursorTile();   //converts the cursor coordinates to room coordinates.

    Room* getCurrentRoom();         //returns a pointer to the current room object that is being drawn.

    void draw(); //draws the current room to the screen.

    /* NOT CURRENTLY IMPLEMENTED:
     * bool saveRooms()
     * bool loadRooms()
     * void restart()
    */
};

#endif // ROOMBUILDER_H_INCLUDED
