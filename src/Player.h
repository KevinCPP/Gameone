#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <map>

#include "Room.h"
#include "RoomBuilder.h"
#include "TextButton.h"
#include "Controls.h"

class Player{
private:
    sf::Sprite player;          //sprite that represents the player
    sf::Texture playerTextureR; //texture for the player's sprite facing right
    sf::Texture playerTextureL; //texture for the player's sprite facing left
    sf::Texture playerTextureD; //texture for the player's sprite facing down
    sf::Texture playerTextureU; //texture for the player's sprite facing up

    int HP;     //player's Health Points
    int SP;     //player's Special Points
    int maxHP;  //maximum value for the player's health points
    int maxSP;  //maximum value for the player's special points
    uint32_t money; //how much money the player has

    float speed; //speed the player will move at (pixels per frame)

    bool menuOpen;  //boolean which is true when the inventory Menu is open

    sf::Vector2f pos; //player's position

    //tests the player's collision in the room that is
    //passed, accepts the memory address of the room:
    bool testCollision(Room* r);

    //tests if the player is colliding with any items
    //in the room, accepts the memory address of the room
    bool checkForItems(Room* r);

    std::vector<int> ItemInventory;         //the player's inventory of items.
    std::vector<TextButton> itemButtons;    //vector of TextButtons that correspond with each unique item in the player's inventory
    std::map<std::string, int> ItemsList;   //map that stores each unique item's name and it's quantity

    Control openMenu;           //control to open the menu

    void ItemAttributes(int id);        //makes the items do something depending on what was passed
    bool removeItem(int id);            //removes an item from the player's inventory
    void useItem(Item* it);             //takes an Item* and passes it's ID to ItemAttributes
    void updateButtons();               //updates the buttons based on the player's inventory

    Item* EquipedWeapon;    //stores the player's currently equipped weapon

    //enum to store the player's direction for rotations
    enum direction {
        up,
        down,
        left,
        right
    } currentDirection;

    void setRotation();
public:
    //constructor for the player, initializes maxHP, maxSP, and their position:
    Player(int maxhp, int maxsp, sf::Vector2f position);

    //allows the keyboard to control the player's actions, the
    //room variable is passed to be used with testCollision so
    //that the player cannot move inside of a tile that has
    //collision:
    void control(Room* r);

    //adds the parameter to the player's HP and then checks to make sure the HP is still
    //under maxHP, if HP > maxHP, HP = maxHP:
    void healHP(int h);

    //adds the parameter to the player's SP and then checks to make sure the SP is still
    //under maxSP, if SP > maxSP, SP = maxSP:
    void healSP(int s);

    //getters:
    int ItemButtonsTextSearchC(const std::wstring& text);   //returns the index in itemButtons for a TextButton which *contains* the text parameter
    int ItemButtonsTextSearch(const std::wstring& text);   //returns the index in itemButtons for a TextButton which equals the text parameter
    int getMoney();                                         //returns the money variable
    int getHP();                                            //returns the HP variable
    int getSP();                                            //returns the SP variable

    //setters:
    void setMoney(int amount);  //sets the money variable
    void setHP(int hp);         //sets the HP variable
    void setSP(int sp);         //sets the SP variable

    void menu();    //inventory menu, handles all things related to the player's inventory
    void draw();    //draws the player to the screen
};

#endif // PLAYER_H_INCLUDED
