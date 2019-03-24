#include "main.h"
#include "Engine.h"
#include "Materials.h"
#include "Room.h"
#include "Tile.h"
#include "RoomBuilder.h"
#include "Player.h"
#include "HeadsUpDisplay.h"
#include "Item.h"
#include "Controls.h"

/******************************************
 * THIS GAME WAS DEVELOPED BY KEVIN COSBY *
 ******************************************/

//entry point of the application:
int main(){

    using namespace Engine;

    initialize(sf::VideoMode(1280, 720), L"test"); //initializes the engine.

    Materials::loadMaterials();
    HeadsUpDisplay::initialize(10, 5, 10, 5);

    RoomBuilder r;
    Player p(10, 5, sf::Vector2f(480, 400));
    p.setMoney(1000);

    sf::Texture tex;
    tex.loadFromFile("Textures\\Item_Sword.png");

    Item I(&tex, sf::Vector2f(400, 400), 0, Item::Weapon, 100);
    r.getCurrentRoom()->addItem(I);

    gpWindow->setFramerateLimit(60);

    while(gpWindow->isOpen()){
        sf::Event event;

        while(gpWindow->pollEvent(event))
            if(event.type == sf::Event::Closed)
                gpWindow->close();

        gpWindow->clear();

        r.placeBlock();
        r.placeItem();
        r.draw();

        p.draw();
        p.control(r.getCurrentRoom());

        HeadsUpDisplay::draw(p.getHP(), p.getSP(), p.getMoney());

        gpWindow->display();
    }

    Materials::unloadMaterials();
}
