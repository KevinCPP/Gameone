#include "RoomBuilder.h"
#include "Materials.h"
#include "Engine.h"
#include <string>
#include <iostream>


RoomBuilder::RoomBuilder(){
    for(int i = 0; i < Materials::numMaterials; i++){

        std::wstring title = std::wstring(Materials::materials[i].begin(), Materials::materials[i].end());

        TextButton t(sf::Vector2f(5, (i+1)*24), sf::Color::Cyan, sf::Color::Red, title.c_str(), 20);
        tileButtons.push_back(t);
    }

    for(int i = 0; i < Materials::numItems; i++){
        std::wstring title = std::wstring(Materials::itemNames[i].begin(), Materials::itemNames[i].end());
        TextButton t(sf::Vector2f(1200, (i+1)*24), sf::Color::Cyan, sf::Color::Red, title.c_str(), 20);
        itemButtons.push_back(t);
    }

    menuVisible = true;
    currentBlock = 0;
    currentItem = 0;
    currentRoomIndex = 0;

    Room r;
    rooms.push_back(r);
}

void RoomBuilder::ChangeCurrentBlock(uint32_t i){
    currentBlock = i;
}

void RoomBuilder::changeCurrentItem(uint32_t i){
    currentItem = i;
}

void RoomBuilder::ChangeCurrentRoom(uint32_t i){
    if(i < 0 || i >= rooms.size())
        return;
    else
        currentRoomIndex = i;
}

void RoomBuilder::CreateNewRoom(){
    Room r;
    rooms.push_back(r);
}

void RoomBuilder::placeBlock(){
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !menuVisible){
        sf::Vector2i tile = getCursorTile();
        rooms[currentRoomIndex].setTile(tile.x, tile.y, currentBlock);
    }
}

void RoomBuilder::placeItem(){
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && !menuVisible){
        Item I = *Materials::getItem(currentItem);
        I.setPosition(Engine::getMousePos());
        rooms[currentRoomIndex].addItem(I);
    }
}

void RoomBuilder::menu(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Insert))
        menuVisible = true;
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Delete))
        menuVisible = false;

    if(menuVisible){
        for(uint32_t i = 0; i < tileButtons.size(); i++){
            tileButtons[i].draw();

            if(tileButtons[i].pollClicked()){
                ChangeCurrentBlock(i);
                std::cout << i << "\n";
            }
        }

        for(uint32_t i = 0; i < itemButtons.size(); i++){
            itemButtons[i].draw();
            if(itemButtons[i].pollClicked()){
                changeCurrentItem(i);
                std::cout << "Item: " << i << "\n";
            }
        }
    }
}

sf::Vector2i RoomBuilder::getCursorTile(){
    return sf::Vector2i(Engine::getMousePos().x/40,
                        Engine::getMousePos().y/40);
}

Room* RoomBuilder::getCurrentRoom(){
    return &rooms.at(currentRoomIndex);
}

void RoomBuilder::draw(){
    rooms[currentRoomIndex].draw();
    menu();
}
