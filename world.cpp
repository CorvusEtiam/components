#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "game.hpp"
#include "world.hpp"
#include "defs.hpp"
#include "entitycreator.hpp"

using Vector2d = std::vector< std::vector < uint > >;

Entity& World::getPlayer() {
    return emgr.getEntity(emgr.kinds[Kind::Player][0]);
}

std::vector<std::string> split(std::string str, char sep) {
    std::stringstream ss(str);
    std::string item;
    std::vector<std::string> vec;
    while ( std::getline(ss, item, sep ) ) {
        if ( !item.empty() ) vec.push_back(item);
    }
    return vec;  
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
            switch(val) {
                case 2:
                    createFloorTile(this, Types::MAGMA, {x,y});
                    break;
                case 1:
                    break;
                    createObstacle(this, Types::WALL, {x,y});
                case 0:
                default:
                    createFloorTile(this, Types::GRASS, {x,y});
                    break;
            }
        }
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
    for ( uint y = 0; y < height; ++y ) {
        for ( uint x = 0; x < width; ++x ) {
            if ( map[y][x].haveActor ) {
                displaySys.draw(emgr.getEntity(map[y][x].actor));
            } else if( ( !map[y][x].haveActor ) && map[y][x].objects.size() == 0 ) {
                displaySys.draw(emgr.getEntity(map[y][x].floor));
            } else if ( !map[y][x].haveActor && map[y][x].objects.size() == 1 ) {
                displaySys.draw(emgr.getEntity(map[y][x].objects[0]));
            } else if ( !map[y][x].haveActor && map[y][x].objects.size() > 1 ) {
                displaySys.draw(emgr.getEntity(map[y][x].floor), '*');
            }
        }
    }
}

void World::update()
{
    for ( uint y = 0; y < height; ++y ) {
        for ( uint x = 0; x < width; ++x ) {
            auto entity = emgr.getEntity(map[y][x].floor);
            displaySys.update(entity);
            if ( map[y][x].haveActor ) {
                auto entity = emgr.getEntity(map[y][x].actor);
                displaySys.update(entity);
            }
            for ( uint handle = 0; handle < map[y][x].objects.size(); ++handle ) {
                auto entity = emgr.getEntity(map[y][x].objects[handle]);
                displaySys.update(entity);
            }
        }
    }
}


