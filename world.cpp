#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "game.hpp"
#include "world.hpp"
#include "defs.hpp"
#include "entitycreator.hpp"


Entity& World::getPlayer() {
    return emgr.getEntity(emgr.kinds[Kind::Player][0]);
}

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
            std::cout << map[y][x].floor << " " << (map[y][x].haveActor ? map[y][x].actor : 0) << " P: " << (emgr.getCompManager(map[y][x].floor).getComponent<Floor>()->passable ? 1 : 0) << " | "; 
        }
        std::cout << std::endl;
    }
}

void World::draw()
{      
    int i = 0;
    for ( uint y = 0; y < height; ++y ) {
        for ( uint x = 0; x < width; ++x ) {
            i += 1;
            if ( map[y][x].haveActor ) {
                displaySys.draw(emgr.getEntity(map[y][x].actor));
            } else if( ( !map[y][x].haveActor ) && map[y][x].objects.size() == 0 ) {
                displaySys.draw(emgr.getEntity(map[y][x].floor));
            } else if ( !map[y][x].haveActor && map[y][x].objects.size() == 1 ) {
                displaySys.draw(emgr.getEntity(map[y][x].objects[0]));
            } else if ( !map[y][x].haveActor && map[y][x].objects.size() > 1 ) {
                displaySys.draw(emgr.getEntity(map[y][x].floor), '*');
            } else {
                displaySys.draw(emgr.getEntity(map[y][x].floor), 'X');
            }
        }
    }
    std::cout << "DRAWN: " << i << std::endl;
}

void World::update()
{
    if ( left ) {
        movementSys.update(getPlayer(), -1, 0);
    } else if ( right ) {
        movementSys.update(getPlayer(), 1, 0);
    } else if ( top ) {
        movementSys.update(getPlayer(), 0, -1);
    } else if ( down ) {
        movementSys.update(getPlayer(), 0, 1);
    }
    
    for ( uint y = 0; y < height; ++y ) {
        std::cout << y;
        for ( uint x = 0; x < width; ++x ) {
            
            auto entity = emgr.getEntity(map[y][x].floor);
            displaySys.update(entity);
            if ( map[y][x].haveActor ) {
                auto entity = emgr.getEntity(map[y][x].actor);
                displaySys.update(entity);
            }
            std::cout << entity.id << "  " << map[y][x].objects.size() << std::endl;
            for ( uint handle = 0; handle < map[y][x].objects.size(); ++handle ) {
                
                auto entity = emgr.getEntity(map[y][x].objects[handle]);
                displaySys.update(entity);
            }
            std::cout << std::endl;
        }
    }
}

GameState World::input(sf::Event& ev) {
      if ( ev.type == sf::Event::Closed || 
           sf::Keyboard::isKeyPressed(sf::Keyboard::Escape ) ) {
            game->running = false;
            game->window.close();
            return GameState::PAUSE;
      } 
      if ( ev.type == sf::Event::KeyPressed ) {
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W) ) {
            top = true; left = right = down = false;
            game->waiting = false;
        } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::S) ) {
            down = true; left = right = top = game->waiting =  false;
        } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::A) ) {
            left = true; top = right = down = game->waiting =  false;
        } else if ( sf::Keyboard::isKeyPressed(sf::Keyboard::D) ) {
            right = true; left = top = down = game->waiting =  false;
        } 
        return GameState::MAP;
}
    return GameState::MAP;
}

