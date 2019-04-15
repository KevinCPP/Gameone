#include "Engine.h"
#include "HeadsUpDisplay.h"
#include "Room.h"

namespace Engine{
    std::unique_ptr<sf::Clock>          gpFramerateClock;
    std::unique_ptr<sf::RenderWindow>   gpWindow;
    std::unique_ptr<sf::Font>           gpFont;

    const unsigned int xResolution = 1600, yResolution = 900;

    const uint32_t TILE_SIZE_X = calc_tile_size_x();
    const uint32_t TILE_SIZE_Y = calc_tile_size_y();

    const std::string TextureFilePath = "Textures\\";
    const std::string GameDataFilePath = "GameData\\";

    void initialize(const wchar_t* title){
        gpWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(xResolution, yResolution), title, sf::Style::Close | sf::Style::Titlebar);
        gpFramerateClock = std::make_unique<sf::Clock>();
        gpFont = std::make_unique<sf::Font>();

        gpFont->loadFromFile("arial.ttf");
    }

    constexpr uint32_t calc_tile_size_x(){
        return Engine::xResolution/Room::tilesX;
    }

    constexpr uint32_t calc_tile_size_y(){
        return Engine::yResolution/Room::tilesY;
    }

    inline double getFramerate(){
        double T = gpFramerateClock->getElapsedTime().asMicroseconds();
        double framerate = 1000000/T;
        gpFramerateClock->restart();
        return framerate;
    }

    sf::Vector2f getMousePos(){
        sf::Vector2i mousePos2i = sf::Mouse::getPosition(*gpWindow);
        sf::Vector2f mousePos2f;
        mousePos2f.x = (float)mousePos2i.x;
        mousePos2f.y = (float)mousePos2i.y;
        return mousePos2f;
    }
}
