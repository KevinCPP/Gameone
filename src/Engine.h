#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "main.h"

namespace Engine{

    extern std::unique_ptr<sf::Clock>           gpFramerateClock;
    extern std::unique_ptr<sf::RenderWindow>    gpWindow;
    extern std::unique_ptr<sf::Font>            gpFont;
    extern unsigned int xResolution, yResolution;

    extern const uint16_t tilesX, tilesY;

    /*
    * initializes the engine, the engine will
    * not work unless this function is called
    * first, should be called at the beginning
    * of main.cpp.
    */
    void initialize(const sf::VideoMode& videoMode, const wchar_t* title);

    //returns the framerate in gpWindow.
    double getFramerate();

    //returns the local mouse position relative to gpWindow.
    sf::Vector2f getMousePos();
}

#endif // ENGINE_H_INCLUDED
