#include "NumberBar.h"
#include "Engine.h"

template <typename T>
NumberBar<T>::NumberBar(T* var, T minimum, T maximum){
    variablePtr = var;
    minimumValue = minimum;
    maximumValue = maximum;
}

template <typename T>
NumberBar<T>::NumberBar(T* var, T minimum, T maximum, const sf::Vector2f& WH, const sf::Vector2f& pos){
    variablePtr = var;
    minimumValue = minimum;
    maximumValue = maximum;
    width = WH.x;
    height = WH.y;
    Xpos = pos.x;
    Ypos = pos.y;
}

template <typename T>
void NumberBar<T>::setPosition(const sf::Vector2f& xy){
    Xpos = xy.x;
    Ypos = xy.y;
}

template <typename T>
void NumberBar<T>::setPosition(const float& x, const float& y){
    Xpos = x;
    Ypos = y;
}

template <typename T>
void NumberBar<T>::draw(){

    numberBarOutline.setFillColor(primaryOutlineColor);
    numberBarOutline.setSize(sf::Vector2f(width, height));
    numberBarOutline.setPosition(Xpos, Ypos);

    float numberBarWidth = width-2;
    T value = *variablePtr;
    float percentWidth = (value-minimumValue)/maximumValue;
    numberBarWidth *= percentWidth;

    if(value > maximumValue)
        numberBarWidth = width-2;
    if(value < minimumValue)
        numberBarWidth = 0;

    numberBar.setFillColor(primaryBarColor);
    numberBar.setSize(sf::Vector2f(numberBarWidth, height-2));
    numberBar.setPosition(Xpos+1, Ypos+1);

    Engine::gpWindow->draw(numberBarOutline);
    Engine::gpWindow->draw(numberBar);
}

template <typename T>
void NumberBar<T>::setVariable(T* var, T minimum, T maximum){
    variablePtr = var;
    minimumValue = minimum;
    maximumValue = maximum;
}

template <typename T>
void NumberBar<T>::setSizeWidthHeight(const float& w, const float& h){
    width = w;
    height = h;
}

template <typename T>
void NumberBar<T>::setSizeWidthHeight(const sf::Vector2f& WH){
    width = WH.x;
    height = WH.y;
}

template <typename T>
void NumberBar<T>::setPrimaryBarColor(const sf::Color& clr){
    primaryBarColor = clr;
}

template <typename T>
void NumberBar<T>::setSecondaryBarColor(const sf::Color& clr){
    secondaryBarColor = clr;
}

template <typename T>
void NumberBar<T>::setPrimaryOutlineColor(const sf::Color& clr){
    primaryOutlineColor = clr;
}

template <typename T>
void NumberBar<T>::setSecondaryOutlineColor(const sf::Color& clr){
    secondaryOutlineColor = clr;
}

template class NumberBar<signed char>;
template class NumberBar<short int>;
template class NumberBar<long int>;
template class NumberBar<uint32_t>;
template class NumberBar<double>;
template class NumberBar<float>;
template class NumberBar<char>;
template class NumberBar<int>;
