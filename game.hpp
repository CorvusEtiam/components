#pragma once
#include <SFML/Graphics.hpp>
#include "./ui/engine.hpp"
#include "entity.hpp"
#include "system.hpp"
#include "component.hpp"
#include "world.hpp"
#include "gamestates.hpp"


class Game {
public:
  bool running;
  bool waiting; 
//  GameState state = GameState::MAP;
  World world;
  sf::RenderWindow window;
  TileEngine te;
  Game();
  
  void exit() {
      running = false;
  }
  
  void mainloop();
  void draw();
  void input();
  void update();
private:
  bool left;
  bool right;
  bool top;
  bool down;
};


