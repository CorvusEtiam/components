#ifndef ENTITY_CREATORS_HPP
#define ENTITY_CREATORS_HPP
#include <string>
#include <SFML/Graphics.hpp>
/*
    TODO: Proper creation of entity types;
 */

struct Coord {
    uint x;
    uint y;
};

namespace Types {
    enum FloorType {
        MAGMA,
        WATER,
        STONE,
        GRASS,
    };
    
    enum ObstacleType {
        WALL,
        HEDGE
    };
    
    enum StaticType {
        STATUE,
        WELL
    };
}

class World;

void createPlayer(World * world, std::string name, Coord cord);
void createFloorTile(World * world, Types::FloorType type , Coord cord);
void createObstacle(World * world, Types::ObstacleType type, Coord cord );
void createItem(
  World * world, 
  std::string item_name, 
  std::string item_tile, 
  sf::Color color, 
  Coord cord,
  bool pickable = true, 
  bool buyable = true, 
  uint price = 100 );
#endif /* ENTITY_CREATORS_HPP */
