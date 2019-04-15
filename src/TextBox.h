#ifndef TEXTBOX_H_INCLUDED
#define TEXTBOX_H_INCLUDED

#include "main.h"

class TextBox{
private:
    sf::Text text;                  //text to be drawn
    sf::RectangleShape background;  //drawable rectangle for the background

    sf::FloatRect textBounds;       //will be the background's bounds but with space from the boarder;

    std::string rawTextData;            //all of the text that the TextBox contains as a raw string.
    std::vector<std::string> pagesText; //the text split up into strings that will fit in textBounds.

    //stores the font size of sf::Text:
    uint16_t fontSize;

    //this function will insert newlines to make text
    //fit in the width of background if text's width is
    //greater than textBound's width:
    void wrapLines();

    //this function will split the string up to make it fit on
    //multiple pages if text's height exceeds textBound's height:
    void splitIntoPages();
public:

    //default constructor, will
    //initialize the color, dimensions,
    //and text to a default value:
    TextBox();

    //constructor, takes dimensions for the background and a font size
    TextBox(const sf::FloatRect& dimensions, const uint16_t& fontsize);

    //this will set the raw text data string,
    //and call wrapLines() and splitIntoPages():
    void setString(const std::string& str);

    void draw(); //draws the textbox to the screen and polls interaction
};

#endif // TEXTBOX_H_INCLUDED
