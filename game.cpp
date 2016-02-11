#include "game.hpp"

void Game::mainloop() {
    waiting = true;
    while ( running ) {
        input();
        if ( !waiting ) {
            update();
        }
        draw();
        gui.display();
    }
}

void Game::draw() {
   if ( state == GameState::MAP ) {
       world.draw();
   }
}

void Game::input() {
  sf::Event ev;
  while ( window.pollEvent(ev) ) {
      if ( state == GameState::MAP ) {
        state = world.input(ev);
      }
  }
}

void Game::update() {
    if ( state == GameState::MAP ) {
        world.update();
    }
    waiting = true;
}

