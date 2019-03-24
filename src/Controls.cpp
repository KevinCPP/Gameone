#include "Controls.h"

Control::Control(){}

Control::Control(sf::Keyboard::Key k){
    btn.key = k;
    btnType = keyboard;
    wasPressed = false;
}

Control::Control(sf::Mouse::Button b){
    btn.button = b;
    btnType = mouse;
    wasPressed = false;
}

bool Control::pollKey(){
    switch(btnType){
        case keyboard:
        {
            if(!sf::Keyboard::isKeyPressed(btn.key)){
                wasPressed = false;
                return false;
            }
            if(sf::Keyboard::isKeyPressed(btn.key) && !wasPressed){
                wasPressed = true;
                return true;
            }
            break;
        }
        case mouse:
        {
            if(!sf::Mouse::isButtonPressed(btn.button)){
                wasPressed = false;
                return false;
            }
            if(sf::Mouse::isButtonPressed(btn.button) && !wasPressed){
                wasPressed = true;
                return true;
            }
            break;
        }
    }

    return false;
}

void Control::setButton(sf::Keyboard::Key k){
    btn.key = k;
    btnType = keyboard;
}

void Control::setButton(sf::Mouse::Button b){
    btn.button = b;
    btnType = mouse;
}
