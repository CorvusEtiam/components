#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "gui.hpp"
#include "tilemap.hpp"

int main() {
    Gui::Gui gui(800, 600, "Title");
    gui.map->populate({
        "water", "wall","wall","grass",
        "water", "wall","wall","grass",
        "water","water","wall","grass",
        "grass", "wall","wall","grass"
    },4,4,{20.f, 20.f});
    gui.map->setPosition(20,20);
    while ( gui.window.isOpen() ) {
        sf::Event ev;
        while ( gui.window.pollEvent(ev) ) {
            if ( ev.type == sf::Event::Closed ) {
                gui.close();
            } 
        }
        gui.display();      
    }
    return 0;
}