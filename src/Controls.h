#ifndef CONTROLS_H_INCLUDED
#define CONTROLS_H_INCLUDED

#include <SFML/Graphics.hpp>

class Control{
private:

    //union that can store either a key or a mouse button
    union ControlTypes{
        sf::Keyboard::Key key;
        sf::Mouse::Button button;
    } btn;

    //enum for which variable is stored in the union
    enum buttonType{
        keyboard,
        mouse
    } btnType;

    //is true when the button is pressed,
    //allows the button to only get registered once
    //until it is released again
    bool wasPressed;
public:
    //default constructor, does nothing.
    Control();

    //constructor with keyboard key parameter, sets btnType to keyboard.
    Control(sf::Keyboard::Key k);

    //constructor with mouse button parameter, sets btnType to mouse.
    Control(sf::Mouse::Button b);

    //returns true when the button is pressed
    bool pollKey();

    //stores the key and sets btnType to keyboard.
    void setButton(sf::Keyboard::Key k);

    //stores the button and sets btnType to mouse.
    void setButton(sf::Mouse::Button b);
};

#endif // CONTROLS_H_INCLUDED
