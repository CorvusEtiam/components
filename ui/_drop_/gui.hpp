#ifndef GUI_SYSTEM
#define GUI_SYSTEM
#include <type_traits>
#include <exception>
#include <vector>
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "resourcemanager.hpp"
#include "tilemap.hpp"

namespace Gui {
    




class Gui {
private:
    sf::View view;
public:
    // TileEngine engine;
    TileMap * map;
    std::vector<std::string> plane;
    // StatusBox * box;
    sf::RenderWindow window;
    FontManager fontmgr;
    // map.drawTile(this, x,y,"wall")
    Gui() {
        
    }
        
    void init(uint window_width, uint window_height, std::string title) {
        window.create(sf::VideoMode{window_width, window_height}, title);
        fontmgr.load("courier", "../media/COURIER.TTF");
        map = new TileMap();
        map->load("../media/sprite.png", "../media/sprite.txt");
        map->setPosition(20,20);
        view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y-200));
        view.setCenter(sf::Vector2f(0.f,0.f));
        view.setViewport(sf::FloatRect(0,0,0.75,0.75));
    }
    
    void moveCamera(float x, float y) {
        view.move(x,y);
    }
    
    void clear() {
    }
    
    void close() {
        window.close();
    }
    
    void display() {
        window.setView(view);
        window.draw(*map);
        window.setView(window.getDefaultView());
        window.display();
        window.clear(sf::Color::Black);
    }
   
    
    ~Gui() {
        delete map;
       
    }
    
};




}    /* Gui */
#endif
