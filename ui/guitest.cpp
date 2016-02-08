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
    
    GuiStyle defStyle{&font, 18, 20, 2, sf::Color(128,128,128)};
    MapBox map(10,10,100,100, defStyle);
    StatusBox status{0,window.getSize().y - 100,window.getSize().x,100, defStyle};
    for ( auto i = 0; i < 10; i++) {
        for ( auto j = 0; j < 10; j++) {
            if ( i % 3 >= 1 || j % 3 >= 1 ) {
                map.at(i,j).setAll(sf::Color::Black, sf::Color::Yellow,' ');
            } else {
                map.at(i,j).setAll(sf::Color::Green,sf::Color::Black,' ');
            }
        }
    }
    status.showMsg(L"Ala ma kota, pies miał ale... Bardzo wiele ale ", sf::Color::Red);
    sf::View view(sf::FloatRect(0.f, 0.f,window.getSize().x, window.getSize().y-200));
    view.setViewport(sf::FloatRect(0,0,0.75,0.75));
    while ( window.isOpen() ) {
        sf::Event ev;
        while ( window.pollEvent(ev) ) {
            if ( ev.type == sf::Event::Closed ) {
                window.close();
            } else if ( ev.type == sf::Event::KeyPressed ) {
                if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ) {
                    view.move(0,-20);   
                } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ) {
                    view.move(0,20);
                } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ) {
                    view.move(-20,0);
                } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ) {
                    view.move(20,0);
                }
             }
        }
        window.setView(view);
        map.render(window);
        window.setView(window.getDefaultView());
        status.render(window);
        window.display();
        window.clear(sf::Color::Black);         
    }
    return 0;
}