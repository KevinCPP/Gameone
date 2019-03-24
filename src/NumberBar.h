#ifndef NUMBERBAR_H_INCLUDED
#define NUMBERBAR_H_INCLUDED

#include <SFML/Graphics.hpp>

template <typename T>
class NumberBar{
private:

    sf::RectangleShape numberBarOutline;
    sf::RectangleShape numberBar;

    sf::Color primaryOutlineColor;
    sf::Color secondaryOutlineColor;
    sf::Color primaryBarColor;
    sf::Color secondaryBarColor;

    T* variablePtr;
    T minimumValue;
    T maximumValue;

    float width;
    float height;
    float Xpos;
    float Ypos;

public:
    NumberBar(T* var, T minimum, T maximum);
    NumberBar(T* var, T minimum, T maximum, const sf::Vector2f& WH, const sf::Vector2f& pos);

    void draw();

    void setVariable(T* var, T minimum, T maximum);

    void setPosition(const sf::Vector2f& xy);
    void setPosition(const float& x, const float& y);

    void setSizeWidthHeight(const sf::Vector2f& WH);
    void setSizeWidthHeight(const float& w, const float& h);

    void setSecondaryOutlineColor(const sf::Color& clr);
    void setPrimaryOutlineColor(const sf::Color& clr);
    void setSecondaryBarColor(const sf::Color& clr);
    void setPrimaryBarColor(const sf::Color& clr);
};

#endif // NUMBERBAR_H_INCLUDED
