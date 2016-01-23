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
    if ( ev.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape ) ) {
      window.close();
      running = false;
    } else if ( ev.type == sf::Event::KeyPressed ) {
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W) ) {
            top = true; left = right = down = waiting = false;
        } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) ) {
            down = true; left = right = top = waiting =  false;
        } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::A) ) {
            left = true; top = right = down = waiting =  false;
        } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D) ) {
            right = true; left = top = down = waiting =  false;
        } 
    }   
    }
}

void Game::update() {
    if ( left ) {
        world.movementSys.update(world.getPlayer(), -1, 0);
    } else if ( right ) {
        world.movementSys.update(world.getPlayer(), 1, 0);
    } else if ( top ) {
        world.movementSys.update(world.getPlayer(), 0, -1);
    } else if ( down ) {
        world.movementSys.update(world.getPlayer(), 0, 1);
    }
    world.update();
    waiting = true;
}

