#include "Player.h"
#include "Engine.h"
#include "Materials.h"
#include "Tile.h"
#include "Item.h"

#include <cmath>
#include <string>
#include <sstream>
#include <algorithm>

///constructor:
Player::Player(int maxhp, int maxsp, sf::Vector2f position){
    player.setPosition(position);
    pos = player.getPosition();
    playerTextureU.loadFromFile("Textures\\playerModelU.png");
    playerTextureD.loadFromFile("Textures\\playerModelD.png");
    playerTextureL.loadFromFile("Textures\\playerModelL.png");
    playerTextureR.loadFromFile("Textures\\playerModelR.png");
    player.setTexture(playerTextureU);

    money = 0;
    speed = 4;
    maxHP = maxhp;
    maxSP = maxsp;
    HP = maxhp;
    SP = maxsp;
    currentDirection = up;
    EquipedWeapon = nullptr;

    menuOpen = false;
    openMenu.setButton(sf::Keyboard::E);
}

/**
* handles all keyboard input related
* to the player in any way (controlling
* the player's movement, opening and
* closing the menu, etc).
**/
void Player::control(Room* r){
    if(openMenu.pollKey())
        menuOpen = !menuOpen;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        pos.y -= speed;
        player.setPosition(pos);
        currentDirection = up;

        if(testCollision(r)){
            pos.y += speed;
            player.setPosition(pos);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        pos.y += speed;
        player.setPosition(pos);
        currentDirection = down;

        if(testCollision(r)){
            pos.y -= speed;
            player.setPosition(pos);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        pos.x -= speed;
        player.setPosition(pos);
        currentDirection = left;

        if(testCollision(r)){
            pos.x += speed;
            player.setPosition(pos);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        pos.x += speed;
        player.setPosition(pos);
        currentDirection = right;

        if(testCollision(r)){
            pos.x -= speed;
            player.setPosition(pos);
        }
    }

    if(menuOpen)
        menu();

    checkForItems(r);
    checkNextRoom();
}

/**
* this method takes a room pointer, and checks that room
* to see if the player's position will intersect with any
* solid tiles, if the player intersects it returns true,
* otherwise it returns false
**/
bool Player::testCollision(Room* r){
    for(int x = 0; x < Engine::tilesX; x++){
        for(int y = 0; y < Engine::tilesY; y++){
            sf::FloatRect tile = sf::FloatRect(sf::Vector2f(x*40, y*40), sf::Vector2f(40, 40));
            sf::FloatRect p = player.getGlobalBounds();

            if(tile.intersects(p) && Materials::getTile(r->getTile(x, y))->hasCollision()){
                return true;
            }
        }
    }
    return false;
}

/**
* this method get's the player's position and checks if their rectangle
* is going off screen, if it is going off screen to the right, it changes
* nextRoom to roomRight, if it's going off screen to the left, it changes nextRoom
* to roomLeft, if it's going off screen at the top, it changes nextRoom to roomUp,
* if it's going off screen at the bottom, it changes nextRoom to roomBottom
**/
void Player::checkNextRoom(){
    sf::FloatRect p = player.getGlobalBounds();
    nextRoom = noNext;

    if(p.left < 0){
        nextRoom = roomLeft;
        player.setPosition(Engine::xResolution-p.width, player.getPosition().y);
        pos = player.getPosition();
    }
    if((p.left + p.width) > Engine::xResolution){
        nextRoom = roomRight;
        player.setPosition(0, player.getPosition().y);
        pos = player.getPosition();
    }
    if(p.top < 0){
        nextRoom = roomUp;
        player.setPosition(player.getPosition().x, Engine::yResolution-p.height);
        pos = player.getPosition();
    }
    if((p.top + p.height) > Engine::yResolution){
        nextRoom = roomDown;
        player.setPosition(player.getPosition().x, 0);
        pos = player.getPosition();
    }
}

void Player::menu(){

    //default button Y values to 150, we need a separate Y for each one
    //because there are 4 columns of buttons for each type of item
    float weaponY = 150, usableY = 150, collectibleY = 150, moneyY = 150;

    //iterate through all the items listed in itemsList:
    for(auto it = ItemsList.begin(); it != ItemsList.end();){

        //We do this because in order to delete items
        //from a container using an iterator, you must go
        //past it, then delete the previous element (the one
        //you want to delete has to be the previous element):
        auto &p = *it;
        ++it;

        //get a pointer to the item by it's name:
        Item* item = Materials::getItemFromName(p.first);

        //convert the item's name to a wstring for easier use in parameters:
        std::wstring wItemName = std::wstring(p.first.begin(), p.first.end());

        //get the index of the item's corresponding button
        //by searching the itemButtons vector for a button
        //whose text matches this item's name:
        int bIndex = ItemButtonsTextSearch(wItemName);

        if(bIndex != -1){
            //store the button's position:
            sf::Vector2f buttonPosition = itemButtons.at(bIndex).getPosition();

            //switch statement to determine the position of the button:
            switch(item->getType()){
                case Item::Weapon:
                    buttonPosition.x = 100;
                    buttonPosition.y = weaponY;

                    //increment by 20 to give space between buttons:
                    weaponY += 20.0f;
                    break;
                case Item::Usable:
                    buttonPosition.x = 375;
                    buttonPosition.y = usableY;

                    //increment by 20 to give space between buttons:
                    usableY += 20.0f;
                    break;
                case Item::Collectible:
                    buttonPosition.x = 650;
                    buttonPosition.y = collectibleY;

                    //increment by 20 to give space between buttons:
                    collectibleY += 20.0f;
                    break;
                case Item::Money:
                    buttonPosition.x = 925;
                    buttonPosition.y = moneyY;

                    //increment by 20 to give space between buttons:
                    moneyY += 20.0f;
                    break;
            }

            //set the button's position now that it's X has been determined:
            itemButtons.at(bIndex).setPosition(buttonPosition);

            /*
            * below we will set the button's text to represent
            * it's corresponding item's name as well as it's
            * quantity then draw the button to the screen so
            * that the client can see how many of each item
            * they have, but then we change it back so that it
            * doesn't break any comparisons with the button's
            * Text (ItemButtonsTextSearch for example):
            */

            //text representing item's quantity to append to the end of the the item's name:
            std::string QuantityText = "\tx" + std::to_string(p.second);

            //wide string that will be the button's text:
            std::wstring wQText = wItemName + std::wstring(QuantityText.begin(), QuantityText.end());

            //set the button's text (it takes wchar_t* so we call .c_str() on wQText):
            itemButtons.at(bIndex).setText(wQText.c_str());

            //draw the button with the temporary text to the screen:
            itemButtons.at(bIndex).draw();

            //poll if the button was clicked, and if it was,
            //we will call useItem on it's corresponding Item:
            if(itemButtons.at(bIndex).pollClicked()){
                useItem(item);
            }

            //change the button's text back to what it was, note: there
            //is a possibility of the button being removed after calling
            //useItem() because when an item's quantity hits 0, the
            //button corresponding with that item is removed, therefore
            //we need a check after the useItem() call to make sure that
            //we don't get an index out of bounds error:
            if(ItemButtonsTextSearch(wQText) != -1)
                itemButtons.at(bIndex).setText(wItemName.c_str());
        }
    }
}

/**
* this function takes an item pointer from menu() and
* get it's ID then call ItemAttributes with that for
* the item to get used; the Parameter will always be
* an item the player has because in the menu() method
* it only loops through items in the player's inventory
* and passes those as parameters, therefore an item the
* player does not have will never be used with this
* function.
**/
void Player::useItem(Item* it){
    int itemID = it->getItemID();
    ItemAttributes(itemID);
}

/**
* this function will actually have an effect based on
* what item just got used; for example, if the player
* just used a potion of healing, this function will
* be the one that actually adds to the player's HP
* whereas most of the other ones just handle removing
* the item from the player's inventory and updating
* the inventory menu it's self
**/
void Player::ItemAttributes(int id){
    switch(id){
        case 0: //sword
            EquipedWeapon = Materials::getItem(id);
            break;
        case 1: //ultra potion of healing
            healHP(50);
            removeItem(id);
            break;
        case 2: //super potion of healing
            healHP(25);
            removeItem(id);
            break;
        case 3: //potion of healing
            healHP(10);
            removeItem(id);
            break;
        case 4: //ultra potion of mana
            healSP(50);
            removeItem(id);
            break;
        case 5: //super potion of mana
            healSP(25);
            removeItem(id);
            break;
        case 6: //potion of mana
            healSP(10);
            removeItem(id);
            break;
    }
}

/**
* method to remove one instance of an item from the player's inventory,
* it removes the first occurance of the item's ID from the itemInventory
* vector, then decrements it's quantity in the itemsList, and if the
* quantity in itemsList is 0 or less, it will remove the item's listing
* all together. After this it calls updateButtons():
**/
bool Player::removeItem(int id){
    //this will be set to true as soon as we find the item:
    bool found = false;

    //loop through ItemInventory and remove the first occurance of id
    //if it exists, otherwise found will remain false:
    for(int i = 0; i < ItemInventory.size(); i++){
        if(ItemInventory.at(i) == id){
            ItemInventory.erase(ItemInventory.begin() + i);
            found = true;
            break;
        }
    }

    //if the item was not found in the inventory, there is no need to
    //continue, we can just return false because we know that it isn't
    //in the player's inventory so it can't be removed in the first place:
    if(!found)
        return false;

    //get an iterator for the item ID's corresponding name in itemsList:
    auto itr = ItemsList.find(Materials::itemNames[id]);

    //check to make sure the item is actually listed; it will be
    //but this is a safeguard in case something breaks:
    if(itr != ItemsList.end()){
        //decrement the item's quantity:
        itr->second--;

        //if there are none remaining, we remove it from the itemsList entirely:
        if(itr->second <= 0)
            ItemsList.erase(itr);
    }

    //update the buttons based on the new changes:
    updateButtons();

    //return true because if it got to this point,
    //the item was found and removed:
    return true;
}

/**
* this method loops through all of the buttons in itemButtons
* and compares each one's text to the parameter and returns
* the index of the first one that *CONTAINS* text, if none match it
* just returns -1:
**/
///IMPORTANT: THIS CHECKS IF THE BUTTON *CONTAINS* THE TEXT
//int Player::ItemButtonsTextSearchC(const std::wstring& text){
//    if(itemButtons.size() > 0){
//        for(int i = 0; i < itemButtons.size(); i++){
//            std::wstring bTxt = itemButtons.at(i).getText();
//            if(bTxt.find(text) != std::string::npos)
//                return i;
//        }
//    }
//
//    return -1;
//}

/**
* this method loops through all of the buttons in itemButtons
* and compares each one's text to the parameter and returns
* the index of the first one that exactly matches text, if none
* match it, it just returns -1.
**/
int Player::ItemButtonsTextSearch(const std::wstring& text){
    if(itemButtons.size() > 0){
        for(int i = 0; i < itemButtons.size(); i++){
            std::wstring bTxt = itemButtons.at(i).getText();
            if(bTxt == text)
                return i;
        }
    }

    return -1;
}

/**
* Method to check if the player is touching any items in *r and
* if they are, it removes that item from the room, adds it to the player's
* inventory as well as updating itemsList
**/
bool Player::checkForItems(Room* r){
    //itemIndex will == the ID of any item we collided with, if there
    //was no item it returns -1
    int itemIndex = r->checkForItemCollision(player.getGlobalBounds());

    if(itemIndex >= 0){
        //get item ID from the item we just collided with:
        int itemID = r->getItem(itemIndex).collect();

        //remove the item from the room and add it's ID to ItemInventory:
        r->removeItem(itemIndex);
        ItemInventory.push_back(itemID);

        //get the item's name and add it to itemsList if it doesn't exist.
        std::string itemName = Materials::itemNames[itemID];

        //if the item's name is listed in itemsList, we increment it's
        //quantity, else we add it and initialize it's quantity to 1:
        if(ItemsList.count(itemName) != 0){
            ItemsList.at(itemName)++;
        } else {
            ItemsList.insert(std::make_pair(itemName, 1));
        }

        //update the buttons in case a new item was obtained:
        updateButtons();

        //return true because item was found:
        return true;
    }

    //return false, item wasn't found:
    return false;
}

///Method to update all of the buttons to represent our current inventory:
void Player::updateButtons(){
    //first we clear the vector of itemButton:
    itemButtons.clear();

    //loop to go through each unique item in ItemsList map
    //and make a button for each one:
    for(auto& p : ItemsList){
        //convert the item's name into a wstring (textbutton constructor takes wchar_t*, wstring is easier to work with):
        std::wstring wName = std::wstring(p.first.begin(), p.first.end());

        //add the new button to itemButtons
        TextButton btn(sf::Vector2f(0, 0), sf::Color::Magenta, sf::Color::White, wName.c_str(), 18);

        /* TextButtons have a bool variable that
        * is true when the mouse1 button is being
        * pressed, and this prevents them from being
        * registered as clicked again every frame,
        * I default this to true so that when the
        * buttons are cleared and this variable is
        * reset to false, this will go back to true
        * so that the user doesn't use one item each
        * frame the button is pressed and instead just
        * uses one item each time the button is clicked
        */
        btn.setWasClicked(true);

        //add the button to the itemButtons vector:
        itemButtons.push_back(btn);
    }
}

/**
* this method heals the player's hp and
* range checks it, if it exceeds maxHP
* then HP = maxHP, if HP < 0, HP = 0.
**/
void Player::healHP(int h){
    HP += h;

    if(HP > maxHP)
        HP = maxHP;
    if(HP < 0)
        HP = 0;
}

/**
* this method restores the player's sp and
* range checks it, if it exceeds maxSP
* then SP = maxSP, if SP < 0, SP = 0.
**/
void Player::healSP(int s){
    SP += s;

    if(SP > maxSP)
        SP = maxSP;
    if(SP < 0)
        SP = 0;
}

///getters:
int Player::getHP(){
    return HP;
}

int Player::getSP(){
    return SP;
}

int Player::getMoney(){
    return money;
}

///setters:
void Player::setMoney(int amount){
    money = amount;
}

/**
* doesn't care about range checking HP,
* when using this method HP will equal
* the parameter no matter what
**/
void Player::setHP(int hp){
    HP = hp;
}

/**
* doesn't care about range checking SP,
* when using this method SP will equal
* the parameter no matter what
**/
void Player::setSP(int sp){
    SP = sp;
}

///rotate the player based on the direction they're facing:
void Player::setRotation(){
    switch(currentDirection){
        case up:
            player.setTexture(playerTextureU);
            break;
        case down:
            player.setTexture(playerTextureD);
            break;
        case left:
            player.setTexture(playerTextureL);
            break;
        case right:
            player.setTexture(playerTextureR);
            break;
    }
}

/**
* call setRotation() to ensure that the player is facing in the correct
* direction before drawing, then draw the player to the window
**/
void Player::draw(){
    setRotation();
    Engine::gpWindow->draw(player);
}
