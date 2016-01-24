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
    world->map[cord.y][cord.x].actor = id;
    world->map[cord.y][cord.x].haveActor = true;
}

void createFloorTile(World * world, Types::FloorType type, Coord cord)
{
    auto id = world->emgr.createEntity(Kind::Floor);
    std::cout << "FLOOR CREATED " << id << std::endl;
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
    world->map[cord.y][cord.x].floor = id;
    world->map[cord.y][cord.x].haveFloor = true;
}

void createObstacle(World * world, Types::ObstacleType type, Coord cord)
{
    auto id = world->emgr.createEntity(Kind::Obstacle);
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
    world->map[cord.y][cord.x].floor = id;
    world->map[cord.y][cord.x].haveFloor = true;
}



