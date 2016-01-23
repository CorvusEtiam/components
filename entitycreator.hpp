#ifndef ENTITY_CREATORS_HPP
#define ENTITY_CREATORS_HPP
#include <string>
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

#endif /* ENTITY_CREATORS_HPP */
