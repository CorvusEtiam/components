#pragma once
#include <SFML/Graphics.hpp>

#include "entity.hpp"
#include "system.hpp"
#include "component.hpp"
#include "world.hpp"
class Game {
public:
  bool running;
  bool waiting;
  
  World world;
  sf::RenderWindow window;
  sf::Font font;
  
  
  
  Game() : running(true), waiting(true) {
    
    window.create(sf::VideoMode(800.f, 600.f), "Test");
    if ( !font.loadFromFile("media/COURIER.TTF")) {
      auto error = "RESOURCE CANNOT BE LOADED :: FONT -- COURIER.TTF";
      throw std::logic_error(error);
    }
    
    world.init(this);
  }
  
  void mainloop();
  void draw();
  void input();
  void update();
  
};
