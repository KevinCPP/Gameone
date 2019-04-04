#include "Engine.h"
#include "HeadsUpDisplay.h"

namespace Engine{
    std::unique_ptr<sf::Clock>          gpFramerateClock;
    std::unique_ptr<sf::RenderWindow>   gpWindow;
    std::unique_ptr<sf::Font>           gpFont;

    const uint16_t tilesX = 32; //number of tiles horizontally in each room
    const uint16_t tilesY = 18; //number of tiles vertically in each room

    unsigned int xResolution, yResolution;

    void initialize(const sf::VideoMode& videoMode, const wchar_t* title){
        gpWindow = std::make_unique<sf::RenderWindow>(videoMode, title, sf::Style::Close | sf::Style::Titlebar);
        gpFramerateClock = std::make_unique<sf::Clock>();
        gpFont = std::make_unique<sf::Font>();

        gpFont->loadFromFile("arial.ttf");

        xResolution = videoMode.width;
        yResolution = videoMode.height;
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
