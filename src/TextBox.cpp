#include "TextBox.h"
#include "Engine.h"
#include <cmath>
#include <string>

TextBox::TextBox(){
    background.setSize(sf::Vector2f(100, 50));
    background.setPosition(300, 300);
    background.setFillColor(sf::Color(40, 40, 40));

    sf::Color outlineclr;
    outlineclr.r = 255 - background.getFillColor().r;
    outlineclr.g = 255 - background.getFillColor().g;
    outlineclr.b = 255 - background.getFillColor().b;

    background.setOutlineColor(outlineclr);
    background.setOutlineThickness(1);

    fontSize = 12;

    text.setFont(*Engine::gpFont);
    text.setCharacterSize(fontSize);
    text.setFillColor(outlineclr);

    sf::FloatRect d = background.getGlobalBounds();

    textBounds.top = d.top + 2;
    textBounds.left = d.left + 2;
    textBounds.width = d.width - 4;
    textBounds.height = d.height - 4;

    text.setPosition(sf::Vector2f(textBounds.top, textBounds.left));

    rawTextData = "sample text";
    text.setString(rawTextData);
}

TextBox::TextBox(const sf::FloatRect& dimensions, const uint16_t& fontsize){
    background.setSize(sf::Vector2f(dimensions.width, dimensions.height));
    background.setPosition(sf::Vector2f(dimensions.top, dimensions.left));
    background.setFillColor(sf::Color(40, 40, 40));

    sf::Color outlineclr;
    outlineclr.r = 255 - background.getFillColor().r;
    outlineclr.g = 255 - background.getFillColor().g;
    outlineclr.b = 255 - background.getFillColor().b;

    background.setOutlineColor(outlineclr);
    background.setOutlineThickness(1);

    fontSize = fontsize;

    text.setFont(*Engine::gpFont);
    text.setCharacterSize(fontSize);
    text.setFillColor(outlineclr);

    textBounds.top = dimensions.top-2;
    textBounds.left = dimensions.left+2;
    textBounds.width = dimensions.width-4;
    textBounds.height = dimensions.height-4;

    text.setPosition(sf::Vector2f(textBounds.top, textBounds.left));

    rawTextData = "sample text";
    text.setString(rawTextData);
}

void TextBox::wrapLines(){
    for(int i = 0; i < text.getString().getSize(); i++){
        if(text.findCharacterPos(i).x > (textBounds.left + textBounds.width)){
            rawTextData.insert(i-1, "\n");
            text.setString(rawTextData);
        }
    }
}

void TextBox::setString(const std::string& str){
    rawTextData = str;
    text.setString(rawTextData);
    wrapLines();

}

void TextBox::draw(){
    Engine::gpWindow->draw(background);
    Engine::gpWindow->draw(text);
}
