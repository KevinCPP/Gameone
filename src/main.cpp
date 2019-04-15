#include <ostream>
#include <fstream>
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
#include "TextBox.h"

/******************************************
 * THIS GAME WAS DEVELOPED BY KEVIN COSBY *
 ******************************************/

//entry point of the application:
int main(){

    using namespace Engine;

    initialize(L"test"); //initializes the engine.

    Materials::loadMaterials();
    HeadsUpDisplay::initialize(10, 5, 10, 5);

    RoomBuilder r(Engine::GameDataFilePath + "DefaultMapRoomBuilder.klvl");
    r.loadRooms();
    Player p(10, 5, sf::Vector2f(480, 400));

    gpWindow->setFramerateLimit(60);

    TextBox t;
    t.setString("WWWWWWWWWWWWWWWWWWWWWWWW.");

    while(gpWindow->isOpen()){
        sf::Event event;

        while(gpWindow->pollEvent(event))
            if(event.type == sf::Event::Closed)
                gpWindow->close();

        gpWindow->clear();

        r.placeBlock();
        r.placeItem();
        r.draw();
        r.menu(&p);

        t.draw();

        p.draw();
        p.control(r.getCurrentRoom());

        HeadsUpDisplay::draw(p.HP, p.SP, p.money);

        gpWindow->display();
    }

    r.saveRooms();

    Materials::unloadMaterials();
}
