#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "main.h"

namespace Engine{

    extern std::unique_ptr<sf::Clock>           gpFramerateClock;
    extern std::unique_ptr<sf::RenderWindow>    gpWindow;
    extern std::unique_ptr<sf::Font>            gpFont;
    extern const unsigned int xResolution, yResolution;

    extern const uint32_t TILE_SIZE_Y;
    extern const uint32_t TILE_SIZE_X;

    extern const std::string TextureFilePath;
    extern const std::string GameDataFilePath;

    /*
    * initializes the engine, the engine will
    * not work unless this function is called
    * first, should be called at the beginning
    * of main.cpp.
    */
    void initialize(const wchar_t* title);

    constexpr uint32_t calc_tile_size_x();
    constexpr uint32_t calc_tile_size_y();

    //returns the frame rate in gpWindow.
    inline double getFramerate();

    //returns the local mouse position relative to gpWindow.
    sf::Vector2f getMousePos();
}

#endif // ENGINE_H_INCLUDED
