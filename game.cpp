#include <iostream>
#include "game.hpp"

Game::Game()
{
      std::string home_dir = "/home/misiek/Projekt/cpp/tile/";
      running = true; 
      waiting = true;
      window.create(sf::VideoMode(800,600), "Start");
      te.init(
          std::make_pair(home_dir+"media/sprite.png", home_dir+"media/sprite.txt"),
          std::make_pair(home_dir+"media/sprite.png", home_dir+"media/sprite.txt"),
          std::make_pair("courier", home_dir+"media/COURIER.TTF"),
          sf::Vector2i{20,20},
          18
         );
//      te.setPosition(sf::Vector2f(0.f,0.f));
//      te.centerCamera(0,0);
      world.init(this);  
      
}

void Game::mainloop() {
    waiting = true;
    std::cout << "MAIN LOOP: " << std::endl;
    while ( running ) {
   
        input();
        if ( !waiting ) {
            update();
        }
            
        window.clear(sf::Color::Black);
        
        draw();
        window.display();
    }
}

void Game::draw() {
    world.draw();
    te.render(window);
}

void Game::input() {
  sf::Event ev;
  while ( window.pollEvent(ev) ) {
      world.input(ev); // -> GameState -> [gui,world]
  }
}

void Game::update() {
    world.update();
    waiting = true;
}

