#include "game.hpp"

void Game::mainloop() {
    waiting = true;
    while ( running ) {
        window.clear(sf::Color::Black);
        input();
        if ( !waiting ) {
            update();
        }
        draw();
        window.display();
    }
}

void Game::draw() {
   world.draw();
}

void Game::input() {
  sf::Event ev;
  while ( window.pollEvent(ev) ) {
    if ( state == GameState::MAP ) {
         
    }
      
    }
}

void Game::update() {
    if ( state == GameState::MAP ) {
        world.update();
    }
    waiting = true;
}

