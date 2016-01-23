#pragma once
#include <vector>
#include "entitymanager.hpp"
#include "defs.hpp"

struct EntityList {
    uint floor;
    uint actor;
    std::vector<uint> objects;
    EntityList() {
        haveActor = haveFloor = haveObjects = false;
        floor = actor = 0;
    }
    
    bool haveFloor;
    bool haveActor;
    bool haveObjects;
};

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
        if ( !this->loadMapFile("media/simplemap.csv")) {
            std::logic_error("Cannot load simplemap.csv");
        }
    }
    Entity& getPlayer();
    void displayMap();
    bool loadMapFile(const std::string& path); 
    void loadMap(Vector2D& _map );
    void draw();
    void update();
    uint width;
    uint height;
};

