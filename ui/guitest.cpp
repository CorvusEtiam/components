#include <iostream>
#include "gui.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


int main() {
    Gui::Gui gui(800.f, 600.f, "Start");
    for ( auto i = 0; i < 10; i++) {
        for ( auto j = 0; j < 10; j++) {
            if ( i % 3 >= 1 || j % 3 >= 1 ) {
                gui.map->setTile(i, j, "wall");
            } else {
                gui.map->setTile(i,j, "floor");
            }
        }
    }
    
    gui.box->showMsg(L"Ala ma kota", sf::Color::Yellow);
    while ( gui.window.isOpen() ) {
        sf::Event ev;
        while ( gui.window.pollEvent(ev) ) {
            if ( ev.type == sf::Event::Closed ) {
                gui.close();
            } else if ( ev.type == sf::Event::KeyPressed ) {
                if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ) {
                    gui.moveCamera(0,-20);   
                } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ) {
                    gui.moveCamera(0,20);
                } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ) {
                    gui.moveCamera(-20,0);
                } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ) {
                    gui.moveCamera(20,0);
                }
             }
        }
        gui.display();      
    }
    return 0;
}