#include <iostream>
#include <SFML/Graphics.hpp>
#include "entitycreator.hpp"
#include "entitymanager.hpp"
#include "entity.hpp"
#include "world.hpp"


void createPlayer(World * world, std::string name, Coord cord)
{
    auto id = world->emgr.createEntity(Kind::Player);
    world->emgr.getCompManager(id).createComponent<Display>(sf::Color::Black, sf::Color::Blue, "player")
               .createComponent<Description>(name)
               .createComponent<Position>(cord.x, cord.y);
    auto& tile = world->at(cord.x, cord.y);
    tile.actor = id;
    tile.occupied = true;
}

void createFloorTile(World * world, Types::FloorType type, Coord cord)
{
    auto& tile = world->at(cord.x, cord.y);
    tile.x = cord.x;
    tile.y = cord.y;
    tile.occupied = false;
    using namespace Types;
    switch ( type ) {
        case MAGMA:
            tile.visible = true;
            tile.passable = false;
            break;
        case WATER:
            tile.floor_tile = "water";
            tile.visible = true;
            tile.passable = false;
            break;
        case GRASS:
            tile.floor_tile = "grass";
            tile.visible = true;
            tile.passable = true;
            break;
        case STONE:
            tile.floor_tile = "wall";
            tile.visible = true;
            tile.passable = false;
            break;
            
    }
}

void createObstacle(World * world, Types::ObstacleType type, Coord cord)
{
    auto& tile = world->at(cord.x, cord.y);
    tile.x = cord.x;
    tile.y = cord.y;
    using namespace Types;
    switch ( type ) {
        case WALL:
            tile.floor_tile = "wall";
            tile.visible = true;
            tile.passable = false;
            break;
        case HEDGE:
            tile.floor_tile = "wall";
            tile.visible = true;
            tile.passable = false;
            break;
    }
}



