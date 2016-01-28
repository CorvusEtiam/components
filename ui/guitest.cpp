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
    GuiStyle guiStyle(sf::Color::Black, sf::Color::Red, &font, 15, 2);
    Box box(create_widget<TextFieldWidget>( 
            "Something! is going to happen", guiStyle, sf::Vector2f( 120.f, 100.f ), sf::Vector2i(20,20)));
    box.emplaceBox(create_widget<TextFieldWidget>("Maybe now?", guiStyle,sf::Vector2f( 120.f, 100.f ), sf::Vector2i(20,80)));
    while ( window.isOpen() ) {
        sf::Event ev;
        while ( window.pollEvent(ev) ) {
            if ( ev.type == sf::Event::Closed ) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        box.render(window);
        window.display();
    }
    return 0;
}