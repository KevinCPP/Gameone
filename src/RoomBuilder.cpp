#include "RoomBuilder.h"
#include "Materials.h"
#include "Engine.h"
#include "Controls.h"
#include "Player.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iterator>
#include <fstream>

RoomBuilder::RoomBuilder(const std::string& saveFile){
    for(int i = 0; i < Materials::numMaterials; i++){
        std::wstring title = std::wstring(Materials::materials[i].begin(), Materials::materials[i].end());

        TextButton t(sf::Vector2f(5, (i+1)*24), sf::Color::Cyan, sf::Color::Red, title.c_str(), 20);
        tileButtons.push_back(t);
    }

    for(int i = 0; i < Materials::numItems; i++){
        std::wstring title = std::wstring(Materials::itemNames[i].begin(), Materials::itemNames[i].end());
        TextButton t(sf::Vector2f(Engine::xResolution - 250, (i+1)*24), sf::Color::Cyan, sf::Color::Red, title.c_str(), 20);
        itemButtons.push_back(t);
    }

    menuVisible = true;
    currentBlock = 0;
    currentItem = 0;

    rX = 0;
    rY = 0;

    c.setButton(sf::Mouse::Right);

    saveFileName = saveFile;
}

void RoomBuilder::ChangeCurrentBlock(uint32_t i){
    currentBlock = i;
}

void RoomBuilder::changeCurrentItem(uint32_t i){
    currentItem = i;
}

void RoomBuilder::ChangeCurrentRoom(uint32_t x, uint32_t y){
    if(x >= roomsX || y >= roomsY){
        std::cerr << "Invalid room coordinates - x: " << x << " y: " << y << std::endl
                << "Accepted x ranges from 0 - " << roomsX-1 << std::endl
                << "Accepted y ranges from 0 - " << roomsY-1 << std::endl;
    } else {
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
                ChangeCurrentRoom(rX-1, rY);

            std::cout << "going left: " << rX << " " << rY;

            p->nextRoom = Player::noNext;

            break;
        case Player::roomRight:
            if(rX+1 < roomsX)
                ChangeCurrentRoom(rX+1, rY);

            std::cout << "going right: " << rX << " " << rY;

            p->nextRoom = Player::noNext;

            break;
        case Player::roomDown:
            if(rY+1 < roomsY)
                ChangeCurrentRoom(rX, rY+1);

            std::cout << "going down: " << rX << " " << rY;

            p->nextRoom = Player::noNext;

            break;
        case Player::roomUp:
            if(rY-1 >= 0)
                ChangeCurrentRoom(rX, rY-1);

            std::cout << "going up: " << rX << " " << rY;

            p->nextRoom = Player::noNext;

            break;
    }
}

sf::Vector2i RoomBuilder::getCursorTile(){
    return sf::Vector2i(Engine::getMousePos().x/Engine::TILE_SIZE_X,
                        Engine::getMousePos().y/Engine::TILE_SIZE_Y);
}

Room* RoomBuilder::getCurrentRoom(){
    return &rooms[rX][rY];
}

//this will generate a file that stores the matrix of tiles for
//each room and every single item in them as well:
bool RoomBuilder::saveRooms(){
    //open the output file to save the rooms to:
    std::ofstream out(saveFileName);

    //loop through columns of rooms:
    for(int x = 0; x < roomsX; x++){
        //loop through rows of rooms:
        for(int y = 0; y < roomsY; y++){
            //save the room to the file:
            out << rooms[x][y];
        }
    }

    //close the file now that all the rooms have been saved:
    out.close();
}

bool RoomBuilder::loadRooms(){
    std::ifstream in(saveFileName);

    //convert the ifstream into a stringstream
    //so that it can be split up at each occurance
    //of "END_OF_ROOM":
    std::ostringstream ss;
    std::copy(std::istreambuf_iterator<char>(in),
              std::istreambuf_iterator<char>(),
              std::ostreambuf_iterator<char>(ss));

    //convert the stringstream into a string:
    std::string ssStr = ss.str();

    //vector that will store a string containing each
    //room's info, split at every occurrence of the
    //delimiter, "END_OF_ROOM"
    std::vector<std::string> split;

    //delimiter definition:
    std::string delimiter = "END_OF_ROOM";

    //token to store the current string that
    //just got split:
    std::string token;

    //stores the position of the delimiter:
    size_t pos = 0;

    //loop through the string that contains the entire stringstream
    //until the delimiter is not found anymore, and set pos equal
    //to the first occurrence of the delimiter:
    while((pos = ssStr.find(delimiter)) != std::string::npos){
        //make a substring from the beginning of the split until the delimiter
        //is found, and store that in token:
        token = ssStr.substr(0, pos);

        //add token the the split vector:
        split.push_back(token);

        //erase the delimiter from that position so that we don't
        //keep getting the same split every time, this makes it find the
        //NEXT delimiter, because now the next one will be the first occurrence:
        ssStr.erase(0, pos+delimiter.length());
    }

    //print the size of the split vector, AKA how many
    //delimiters were found, or how many room's info
    //were in the file:
    std::cout << "size split: " << split.size();

    ///map each room's info in the split vector to a room in the matrix:

    //store the current index of split:
    int splitIndex = 0;

    //loop through rooms matrix columns:
    for(int x = 0; x < roomsX; x++){
        //loop through rooms matrix rows:
        for(int y = 0; y < roomsY; y++){
            //make sure that there is room data to
            //be loaded:
            if(splitIndex < split.size()){
                //convert the string in split at splitIndex to
                //a stringstream so that a room can be extracted
                //from it:
                std::stringstream strstr(split.at(splitIndex));

                //use the room's extraction operator to extract
                //it's information from strstr:
                strstr >> rooms[x][y];

                //increment splitindex to move on to the next room's info now
                //that this room has been loaded:
                splitIndex++;
            } else {
                std::cerr << "Error: no room data to be loaded at split index: " << splitIndex
                        << " for room: " << "x - " << x << " | " << "y - " << y << "\n";
            }
        }
    }

    //close the file now that the rooms have all been loaded:
    in.close();
}

void RoomBuilder::draw(){
    rooms[rX][rY].draw();
}
