#include "RoomBuilder.h"
#include "Materials.h"
#include "Engine.h"
#include "Controls.h"
#include "Player.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <ios>

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

    rX = 0;
    rY = 0;

    c.setButton(sf::Mouse::Right);
}

void RoomBuilder::ChangeCurrentBlock(uint32_t i){
    currentBlock = i;
}

void RoomBuilder::changeCurrentItem(uint32_t i){
    currentItem = i;
}

void RoomBuilder::ChangeCurrentRoom(uint32_t x, uint32_t y){
    if(x >= roomsX || y >= roomsY)
        return;
    else{
        rX = x;
        rY = y;
    }
}

void RoomBuilder::placeBlock(){
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !menuVisible){
        sf::Vector2i tile = getCursorTile();
        rooms[rX][rY].setTile(tile.x, tile.y, currentBlock);
    }
}

void RoomBuilder::placeItem(){
    if(c.pollKey() && !menuVisible){
        Item I = *Materials::getItem(currentItem);
        I.setPosition(Engine::getMousePos());
        rooms[rX][rY].addItem(I);
    }
}

void RoomBuilder::menu(Player* p){
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

    switch(p->nextRoom){
        case Player::roomLeft:
            if(rX-1 >= 0)
                rX--;

            std::cout << "going left: " << rX << " " << rY;

            p->nextRoom = Player::noNext;

            break;
        case Player::roomRight:
            if(rX+1 < roomsX)
                rX++;

            std::cout << "going right: " << rX << " " << rY;

            p->nextRoom = Player::noNext;

            break;
        case Player::roomDown:
            if(rY+1 < roomsY)
                rY++;

            std::cout << "going down: " << rX << " " << rY;

            p->nextRoom = Player::noNext;

            break;
        case Player::roomUp:
            if(rY-1 >= 0)
                rY--;

            std::cout << "going up: " << rX << " " << rY;

            p->nextRoom = Player::noNext;

            break;
    }
}

sf::Vector2i RoomBuilder::getCursorTile(){
    return sf::Vector2i(Engine::getMousePos().x/40,
                        Engine::getMousePos().y/40);
}

Room* RoomBuilder::getCurrentRoom(){
    return &rooms[rX][rY];
}

//this will generate a file that stores the matrix of tiles for
//each room and every single item in them as well:
bool RoomBuilder::saveRooms(){
    //open the output file to save the rooms to:
    std::ofstream out("GameData\\DefaultMapRoomBuilder.klvl");

    for(int x = 0; x < roomsX; x++){
        for(int y = 0; y < roomsY; y++){

            out << "Tiles: ";
            for(int j = 0; j < 32; j++){
                for(int k = 0; k < 18; k++){
                    out << rooms[x][y].getTile(j, k) << " ";
                }
            }
            out << "\n";

            //save the items and their positions to the room:

            for(int j = 0; j < rooms[x][y].items.size(); j++){
                int itemID = rooms[x][y].items.at(j).getItemID();
                float xPos = rooms[x][y].items.at(j).getPosition().x;
                float yPos = rooms[x][y].items.at(j).getPosition().y;

                out << "ID: " << itemID << " " << xPos << " " << yPos << std::endl;
            }

            //text to signify the end of the room:
            out << "\nEND_OF_ROOM\n";
        }
    }
    return true;
}

bool RoomBuilder::loadRooms(){
    std::ifstream in("GameData\\DefaultMapRoomBuilder.klvl");

    std::vector<std::string> lines;

    //only happens if input stream is open:
    if(in.is_open()){
        //string to store the current line we're on:
        std::string line;

        //while loop to loop through each line:
        while(std::getline(in, line)){
            //add each line to the lines vector:
            lines.push_back(line);
        }
        //close the file now that we no longer need it:
        in.close();
    }

    int cX = 0, cY = 0;

    for(int i = 0; i < lines.size(); i++){
        std::cout << lines.at(i) << std::endl;

        if(lines.at(i).find("END_OF_ROOM") != std::string::npos){



            if(cY+1 < roomsY)
                cY++;
            else if(cX+1 < roomsX)
                cX++;

            std::cout << "loaded room at iteration: " << i << std::endl;
        }
        else if(lines.at(i).find("Tiles:") != std::string::npos){
            std::vector<int> tiles = parseIntsFromString(lines.at(i));
            std::cout << "got here";

            int tIndex = 0;
            for(int x = 0; x < 32; x++){
                for(int y = 0; y < 18; y++){
                    rooms[cX][cY].setTile(x, y, tiles[tIndex]);
                    tIndex++;
                }
            }
            std::cout << "got here" << " cx: " << cX << " cy: " << cY << std::endl;
        }
        else if(lines.at(i).find("ID:") != std::string::npos){
            std::vector<int> itemInfo = parseIntsFromString(lines.at(i));

            Item I = *Materials::getItem(itemInfo[0]);
            I.setPosition(sf::Vector2f(itemInfo[1], itemInfo[2]));

            rooms[cX][cY].addItem(I);

            std::cout << "added item at iteration: " << i << std::endl;
        }
    }
    return true;
}

std::vector<int> RoomBuilder::parseIntsFromString(const std::string& str){
    std::vector<int> ints;

    std::stringstream ss;
    ss << str;

    std::string temp;
    int found;

    while(!ss.eof()){
        ss >> temp;

        if(std::stringstream(temp) >> found)
            ints.push_back(found);

        temp = "";
    }

    return ints;
}

void RoomBuilder::draw(){
    rooms[rX][rY].draw();
    //menu();
}
