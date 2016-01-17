#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "game.hpp"
#include "world.hpp"
#include "defs.hpp"


using Vector2d = std::vector< std::vector < uint > >;

Entity& World::getPlayer() {
    return emgr.getEntity(emgr.kinds[Kind::Player][0]);
}

Entity createEntity(uint val) {
    Entity ent = Entity();
    switch(val) {
        case 0:
            ent.cmgr.createComponent<Floor>(false)
               .createComponent<Display>(sf::Color::Black, sf::Color::White, '#');
            return ent;
        case 1:
            ent.cmgr.createComponent<Floor>(true)
                     .createComponent<Display>(sf::Color::Black, sf::Color::White, '.');
            return ent;
        default:
        case 2:
            ent.cmgr.createComponent<Floor>(false)
                     .createComponent<Display>(sf::Color::Red, sf::Color::Yellow, '~');
            return ent;
        
    }
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
    Vector2D vec;
    std::ifstream file(path);
    if ( !file ) { return false; }
    std::string line;
    
    std::getline(file, line);
    auto header = split(line, ';');
    width = std::stoi(header[0]);
    height = std::stoi(header[1]);
    vec.resize(height);
    for ( auto& line : vec ) {
        line.resize(width);
    }
    
    int x = 0, y = 0;
    while ( std::getline(file, line) ) {
        if ( line[0] == '#' || line[1] == '@' ) { 
            /*
             *   # are comments
             *   @ are metadata -- metadata are useful for stuff like legend with all used symbols on map
             */

#ifdef DEBUG_MAP_DATA
            std::cout << line << std::endl;
#endif
            continue; 
        } 
        auto item = split(line, ';');
        for ( auto chr : item ) {
            vec[x++][y] = std::stoi(chr); 
        }
        x = 0;
        y++;
    }
    loadMap(vec);
    return true;
}

void World::loadMap(Vector2D& _map)
{
        map.resize(height);
        for ( auto& line : map ) {
            line.resize(width);
        }
        std::cout << width << " ::: " << height << std::endl;
        for ( uint y = 0; y < height; ++y ) {
            for ( uint x = 0; x < width; ++x ) {
                Entity entity = createEntity(_map[y][x]);
                entity.cmgr.createComponent<Position>(y,x);
                auto id = emgr.setEntity(Kind::Floor, entity);
                map[y][x].push_back(id);
           }
        }
        std::cout << "HERE" << std::endl;
        auto id = emgr.createEntity(Kind::Player);
        emgr.getCompManager(id).createComponent<Display>(sf::Color::Black, sf::Color::Blue, '@')
            .createComponent<Position>(2,2);
        map[2][2].push_back(id);
        std::cout << "DONE: " << id << std::endl;
}

void World::draw()
{       
    std::cout << "*DRAW*" << std::endl;
    uint y, x;
    for ( y = 0; y < width; ++y ) {
        for (  x = 0; x < height; ++x ) {
           
            if ( map[y][x].size() == 1 ) {
               auto entity = emgr.getEntity(map[y][x][0]);
                // std::cout << entity.id << std::endl;
                displaySys.draw(entity); 
            } else if ( map[y][x].size() == 2 ) {
                displaySys.draw(emgr.getEntity(map[y][x][1]));
            } else {
                displaySys.draw(emgr.getEntity(map[y][x][0]), '*');
            }
           
        
        }
    }
    std::cout << "*DRAW END*" << std::endl;
}

void World::update()
{
    std::cout << "*UPDATE*" << std::endl;
    uint y, x, handle;
    for ( y = 0; y < width; ++y ) {
        for (  x = 0; x < height; ++x ) {
             for ( handle = 0; handle < map[y][x].size(); ++handle ) {
                 std::cout << map[y][x][handle] << " ";       
                 displaySys.update(emgr.getEntity(map[y][x][handle]));
             }
             std::cout << std::endl;
        }
    }
    std::cout << "*UPDATE END*" << std::endl;
}


