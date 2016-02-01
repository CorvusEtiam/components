#include <iostream>
#include "gui.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using namespace Gui;
int main() {
    
    sf::RenderWindow window(sf::VideoMode(800.f, 600.f), "Gui Window");
    sf::Font font;
    if ( ! font.loadFromFile("../media/COURIER.TTF") ) {
        return -1;
    }
    
    GuiStyle guiStyle(sf::Color::Green, sf::Color::White, &font, 15, 20);
    MapBox map(10,10,10,10,20);
    StatusBox status(0,500,window.getSize().x,100,20);
    
    for ( auto i = 0; i < 4; i++) {
        for ( auto j = 0; j < 5; j++) {
            if ( i * j % 3 == 0) {
                map.setTile(i,j,&guiStyle,'#');
            } else {
                map.setTile(i,j,&guiStyle,'.');
            }
        }
    }
    
    status.showMsg("Ala ma kota\nKot chcialby psa", guiStyle);
      
    while ( window.isOpen() ) {
        sf::Event ev;
        while ( window.pollEvent(ev) ) {
            if ( ev.type == sf::Event::Closed ) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        map.render(window);
        status.render(window);
        
        window.display();
    }
    return 0;
}