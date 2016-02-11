#include <iostream>
#include <SFML/Graphics.hpp>
#include "entitycreator.hpp"
#include "entitymanager.hpp"
#include "entity.hpp"
#include "world.hpp"


void createPlayer(World * world, std::string name, Coord cord)
{
    auto id = world->emgr.createEntity(Kind::Player);
    world->emgr.getCompManager(id).createComponent<Display>(sf::Color::Black, sf::Color::Blue, '@')
               .createComponent<Description>(name)
               .createComponent<Position>(cord.x, cord.y);
    world->at(cord.x, cord.y).actor = id;
    world->at(cord.x, cord.y).occupied = true;
}

void createFloorTile(World * world, Types::FloorType type, Coord cord)
{
    auto id = world->emgr.createEntity(Kind::Floor);
    std::cout << "FLOOR CREATED " << id << "X: " << cord.y << "Y: " << cord.y << std::endl;
    using namespace Types;
    switch ( type ) {
        case MAGMA:
            world->emgr.getCompManager(id).createComponent<Display>(sf::Color::Red, sf::Color::Black, '~')
                                          .createComponent<Floor>(false)
                                          .createComponent<Position>(cord.x, cord.y);
            break;
        case WATER:
            world->emgr.getCompManager(id).createComponent<Display>(sf::Color::Blue, sf::Color::Black, '~')
                                          .createComponent<Floor>(false)
                                          .createComponent<Position>(cord.x, cord.y);
            break;
        case GRASS:
            world->emgr.getCompManager(id).createComponent<Display>(sf::Color::Green, sf::Color::Yellow, '.')
                                          .createComponent<Floor>(true)
                                          .createComponent<Position>(cord.x, cord.y);
            break;
        case STONE:
            world->emgr.getCompManager(id).createComponent<Display>(sf::Color::Black, sf::Color::Color(128,128,128), '.')
                                          .createComponent<Floor>(true)
                                          .createComponent<Position>(cord.x, cord.y);
            break;
            
    }
    world->at(cord.x, cord.y).floor_tile = id;
}

void createObstacle(World * world, Types::ObstacleType type, Coord cord)
{
    auto id = world->emgr.createEntity(Kind::Obstacle);
    std::cout << "OBSTACLE CREATED " << id << "X: " << cord.y << "Y: " << cord.y << std::endl;
    using namespace Types;
    switch ( type ) {
        case WALL:
            world->emgr.getCompManager(id).createComponent<Display>(sf::Color::Black, sf::Color::White, '#')
                                          .createComponent<Floor>(false)
                                          .createComponent<Position>(cord.x, cord.y);
            break;
        case HEDGE:
            world->emgr.getCompManager(id).createComponent<Display>(sf::Color::Black, sf::Color::Green, '~')
                                          .createComponent<Floor>(false)
                                          .createComponent<Position>(cord.x, cord.y);
            break;
    }
    world->at(cord.x, cord.y).floor_tile = id;
    world->at(cord.x, cord.y).passable = false; 
}



