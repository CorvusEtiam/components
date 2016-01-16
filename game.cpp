#include "game.hpp"

void Game::mainloop() {
    waiting = true;
    while ( running ) {
        window.clear(sf::Color::Black);
        input();
        draw();
        if ( ! waiting ) { // -- turn based -- 
            window.clear(sf::Color::Black);
            update();
            draw();
        }
         window.display();
    }
    
}

void Game::draw() {
   world.draw();
}

void Game::input() {
  sf::Event ev;
  while ( window.pollEvent(ev) ) {
    if ( ev.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape ) ) {
      window.close();
      running = false;
    } else if ( ev.type == sf::Event::KeyPressed ) {
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W) ) {
            world.movementSys.update(world.getPlayer(), 0, -1);
        } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) ) {
            world.movementSys.update(world.getPlayer(), 0, 1);
        } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::A) ) {
            world.movementSys.update(world.getPlayer(), -1, 0);
        } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D) ) {
            world.movementSys.update(world.getPlayer(), 1, 0);
        }
        waiting = false;
    }
        
    }
}

void Game::update() {
    world.update();
}

