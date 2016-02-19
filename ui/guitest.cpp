#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "engine.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode(800,600), "Test");
    TileEngine engine;
    engine.init(StrTuple{"../media/sprite.png", "../media/sprite.txt"},StrTuple{"../media/sprite.png", "../media/sprite.txt"},
                StrTuple{"courier", "../media/COURIER.TTF"},sf::Vector2i{20,20},18);
    engine.createMap({
        "water", "wall","wall","grass",
        "water", "wall","wall","grass",
        "water","water","wall","grass",
        "grass", "wall","wall","grass"
    });
    engine.createObject("wall",0,0);
    engine.setPosition({100.f,100.f});
    while ( window.isOpen() ) {
        sf::Event ev;
        while ( window.pollEvent(ev) ) {
            if ( ev.type == sf::Event::Closed ) {
                window.close();
            } 
        }
        engine.render(window);
        window.display();      
    }
    return 0;
}