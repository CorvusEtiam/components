#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "game.hpp"
#include "world.hpp"
#include "defs.hpp"
#include "entitycreator.hpp"


bool World::loadMapFile(const std::string& path)
{
    std::cout << "PATH: " <<  path << std::endl;
    std::ifstream file(path);
    if ( !file.good()) { std::cout << "FILE DOESNT EXIST!" << std::endl; return false; }
    std::string line;
    std::getline(file, line);
    auto header = split(line, ';');
    width = std::stoi(header[0]);
    height = std::stoi(header[1]);
    map.resize(height*width);
    game->te.setSize(sf::Vector2i(width, height));
    uint y = 0;
    while ( std::getline(file, line) ) {
        if ( line[0] == '@' || line['#'] ) { continue; }
        auto data = split(line, ';');
        for ( uint x = 0; x < data.size(); ++x ) {
            int val = std::stoi(data[x]);
            std::cout << val << " | ";
            switch(val) {
                case 2:
                    createFloorTile(this, Types::WATER, {x,y});
                    break;
                case 1:
                    createFloorTile(this, Types::STONE, {x,y});
                    break;
                case 0:
                default:
                    createFloorTile(this, Types::GRASS, {x,y});
                    break;
            }
            
        }
        std::cout << std::endl;
        y++;
    }    
    createPlayer(this, "M", {0,0});
    return true;
    
}

void World::draw() {
//    std::cout << "[LOG] Draw started" << std::endl;
    
    game->te.createMap(map);
    
    for ( auto& entity : emgr.entities ) {
        displaySys.draw(entity.second); 
    }
}

void World::update() {
//    std::cout << "[LOG] Update start" << std::endl;
    if ( left ) {
        movementSys.update(emgr.getPlayer(), -1, 0);
    } else if ( right ) {
        movementSys.update(emgr.getPlayer(), 1, 0);
    } else if ( top ) {
        movementSys.update(emgr.getPlayer(), 0, -1);
    } else if ( down ) {
        movementSys.update(emgr.getPlayer(), 0, 1);
    }
    
     for ( auto& entity : emgr.entities ) {
        displaySys.update(entity.second); 
     }
     left = right = top = down = false;
}

void World::input(sf::Event& ev) {
    if ( ev.type == sf::Event::Closed || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::Escape ) ) {
        game->exit();
        return;
        } 
    if ( ev.type == sf::Event::KeyPressed ) {
        game->waiting = false;
    }
    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W) ) {
        top = true;
        left = right = down = false;
        //  game->gui.moveCamera(0, 20);
        game->waiting = false;
    } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) ) {
        down = true;
        left = right = top = game->waiting =  false;
        //    game->gui.moveCamera(0, -20);
    } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::A) ) {
        left = true;
        top = right = down = game->waiting =  false;
        //    game->gui.moveCamera(-20, 0);
    } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D) ) {
        right = true;
        left = top = down = game->waiting =  false;
        //    game->gui.moveCamera(20, 0);
    } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::E) ) {
        Position * pos = emgr.getComponentFromEntity<Position>(emgr.getPlayer());
        std::cout << this->at(pos->x, pos->y) << std::endl;
    }

}

