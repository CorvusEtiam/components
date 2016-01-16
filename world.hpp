#pragma once
#include <vector>
#include "entitymanager.hpp"
#include "defs.hpp"

using EntityList = std::vector<uint>;
using TileMap    = std::vector<std::vector< EntityList > >;
using Vector2D =  std::vector<std::vector<uint>>;    

class Game;
class World {
public:
    TileMap map;
    EntityManager emgr;
    DisplaySystem displaySys;
    MovementSystem movementSys;
    CollisionSystem collisionSys;
    Game * game;

    World() {}

    void init(Game * _game) {
        displaySys.setWorld(this);
        movementSys.setWorld(this);
        collisionSys.setWorld(this);
        game = _game; 
        this->loadMapFile("media/simplemap.csv");
    }
    Entity& getPlayer();
    void loadMapFile(const std::string& path); 
    void loadMap(std::vector<std::vector<uint> > _map );
    void draw();
    void update();
    uint width;
    uint height;
};

