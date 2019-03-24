#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <map>

#include "Room.h"
#include "RoomBuilder.h"
#include "Controls.h"

class Player{
private:
    sf::RectangleShape player;  //rectangle that represents the player (change to sprite later on)

    int HP;     //player's Health Points
    int SP;     //player's Special Points
    int maxHP;  //maximum value for the player's health points
    int maxSP;  //maximum value for the player's special points

    float speed; //speed the player will move at (pixels per frame)

    uint32_t money; //how much money the player has

    bool menuOpen;

    sf::Vector2f pos; //player's position

    //tests the player's collision in the room that is
    //passed, accepts the memory address of an already existing room:
    bool testCollision(Room* r);
    bool checkForItems(Room* r);

    std::vector<int> ItemInventory; //the player's inventory of items.
    std::map<std::string, int> ItemsList;

    Control MenuControl;
public:
    //constructor for the player, initializes maxHP, maxSP, and their position:
    Player(int maxhp, int maxsp, sf::Vector2f position);

    //allows the keyboard to control the player's actions, the
    //room variable is passed to be used with testCollision so
    //that the player cannot move inside of a tile that has
    //collision:
    void control(Room* r);

    //getters:
    int getMoney(); //returns the money variable
    int getHP();    //returns the HP variable
    int getSP();    //returns the SP variable

    //setters:
    void setMoney(int amount);  //sets the money variable
    void setHP(int hp);         //sets the HP variable
    void setSP(int sp);         //sets the SP variable

    void menu();
    void draw();    //draws the player to the screen
};

#endif // PLAYER_H_INCLUDED
