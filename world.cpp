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
        if ( line[0] == '@' || line[0] == '#' ) { continue; }
        auto data = split(line, ';');
        for ( uint x = 0; x < data.size(); ++x ) {
            int val = std::stoi(data[x]);
	    std::cout << x << " " << y << std::endl;
            /// \todo Rewrite into something more pleasant and extensible
	    ///       index by number taken from csv file -> identifier from legend.file -> set proper tile
	    switch(val) {
                case 4:
                    createObstacle(this, Types::WALL, {x,y});
                    break;
                case 3:
                    createFloorTile(this, Types::MAGMA, {x,y});
                    break;
                case 2:
                    createFloorTile(this, Types::WATER, {x,y});
                    break;
                case 1:
                    createFloorTile(this, Types::STONE, {x,y});
                    break;
                case 0:
                    createFloorTile(this, Types::GRASS, {x,y});
                    break;
                default:
                    auto& tile = at(x,y);
                    tile.x = x;
                    tile.y = y;
                    tile.floor_tile = "void";
                    tile.passable = false;
                    tile.visible = true;
                    break;
            }
            
        }
        std::cout << std::endl;
        y++;
    }    
    createPlayer(this, "M", {0,0});
    createItem(this, "Sword", "magma", sf::Color::White, {0,1});
    return true;
    
}

void World::draw() {
//    std::cout << "[LOG] Draw started" << std::endl;
    if ( !this->m_drawn ) { 
        game->te.createMap(map);
        this->m_drawn = true;
    }
    
    for ( auto& entity : emgr.entities ) {
        displaySys.draw(entity.second); 
    }
    displaySys.draw(emgr.getPlayer());
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
        game->waiting = false;
    } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) ) {
        down = true;
        left = right = top = game->waiting =  false;
    } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::A) ) {
        left = true;
        top = right = down = game->waiting =  false;
    } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D) ) {
        right = true;
        left = top = down = game->waiting =  false;
    } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::E) ) {
        Position * pos = emgr.getComponentFromEntity<Position>(emgr.getPlayer());
        std::cout << at(pos->x, pos->y) << std::endl;
    } else if  ( sf::Keyboard::isKeyPressed(sf::Keyboard::T) ) {
	Position * pos = emgr.getComponentFromEntity<Position>(emgr.getPlayer());
	if ( at(pos->x, pos->y).objects.size() > 0 ) {
	  inventorySys.take(emgr.getPlayer(), at(pos->x, pos->y).objects[0] );
	}
      
    }
 
}

