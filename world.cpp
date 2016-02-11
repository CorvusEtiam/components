#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "globals.hpp"
#include "game.hpp"
#include "world.hpp"
#include "defs.hpp"
#include "entitycreator.hpp"

bool World::loadMapFile(const std::string& path)
{
    std::ifstream file(path);
    if ( !file.good()) { std::cout << "FILE DOESNT EXIST!" << std::endl; return false; }
    std::string line;
    std::getline(file, line);
    auto header = split(line, ';');
    width = std::stoi(header[0]);
    height = std::stoi(header[1]);
    map.resize(height);
    for ( auto& m : map ) m.resize(width);
    uint y = 0;
    while ( std::getline(file, line) ) {
        if ( line[0] == '@' || line['#'] ) { continue; }
        auto data = split(line, ';');
        for ( uint x = 0; x < data.size(); ++x ) {
            int val = std::stoi(data[x]);
            std::cout << val << " | ";
            switch(val) {
                case 2:
                    createFloorTile(this, Types::MAGMA, {x,y});
                    break;
                case 1:
                    createObstacle(this, Types::WALL, {x,y});
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
    createPlayer(this, "M", {0,1});
    return true;
}



#define DEBUG 
#ifdef DEBUG 

void showEntities(EntityManager& emgr) {
    for ( auto ent : emgr.entities ) {
        auto pos = ent.second.cmgr.getComponent<Position>();
        std::cout << ent.second.id << " => X:"  << pos->x << "Y: " << pos->y;
        if ( ent.second.cmgr.hasComponent<Floor>() ) {
            std::cout << "P: " << (ent.second.cmgr.getComponent<Floor>()->passable ? 1 : 0) << std::endl;
        } else {
            std::cout << std::endl;
        }
    }
}

void World::displayMap() {
    for ( uint y = 0; y < height; ++y ) {
        for ( uint x = 0; x < width; ++x ) {
            std::cout << map[y][x].floor << " " << (map[y][x].haveActor ? map[y][x].actor : 0) << " P: " 
            << (emgr.getCompManager(map[y][x].floor).getComponent<Floor>()->passable ? 1 : 0) << " | "; 
        }
        std::cout << std::endl;
    }
}
#endif /* DEBUG */

void World::draw()
{      
    for ( uint y = 0; y < height; ++y ) {
        for ( uint x = 0; x < width; ++x ) {
            auto& tile = this->at(x,y);
            if ( !tile.visible) {
                continue;
            }
            if ( tile.occupied) {
                displaySys.draw(emgr.getEntity(tile.actor));
            } else if ( tile.taken ) {
                if ( tile.objects.size() > 1 ) {
                   displaySys.draw("wall");
                } else {
                   displaySys.draw(tile.objects[0]);
                } 
            } else {
                displaySys.draw(tile.floor_tile);
            }
        }
    }
}

void World::update()
{
    if ( left ) {
        movementSys.update(emgr.getPlayer(), -1, 0);
    } else if ( right ) {
        movementSys.update(emgr.getPlayer(), 1, 0);
    } else if ( top ) {
        movementSys.update(emgr.getPlayer(), 0, -1);
    } else if ( down ) {
        movementSys.update(emgr.getPlayer(), 0, 1);
    }
    
    for ( auto tile : map  ) {
       displaySys.update(emgr.getEntity(tile.floor_tile));
       if ( tile.occupied) {
           displaySys.update(emgr.getEntity(tile.actor));
       }
       for ( auto id : tile->objects ) {
           displaySys.update(emgr.getEntity(id));
       }
    }
           
}

GameState World::input(sf::Event& ev) {
      if ( ev.type == sf::Event::Closed || 
           sf::Keyboard::isKeyPressed(sf::Keyboard::Escape ) ) {
            game->exit();
            return GameState::PAUSE;
      } 
      if ( ev.type == sf::Event::KeyPressed ) {
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W) ) {
            top = true; left = right = down = false;
            game->gui.moveCamera(0, 20);
            game->waiting = false;
        } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) ) {
            down = true; left = right = top = game->waiting =  false;
            game->gui.moveCamera(0, -20);
        } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::A) ) {
            left = true; top = right = down = game->waiting =  false;
            game->gui.moveCamera(-20, 0);
        } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D) ) {
            right = true; left = top = down = game->waiting =  false;
            game->gui.moveCamera(20, 0);
        } 
        return GameState::MAP;
}
    return GameState::MAP;
}

