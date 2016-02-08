#pragma once
#include <vector>
#include "entitymanager.hpp"
#include "defs.hpp"
#include "util.hpp"
#include "gamestates.hpp"


struct Tile {
    const char * floor_tile;
    uint actor; 
    std::vector<uint> objects;
    std::bitset<32> flags; 
    bool isPassable() {
        return true;
    }
};





template<typename T>
using Plane2D =  std::vector<std::vector<T>>;    

class Game;
class World {
    private:
        bool left;
        bool right;
        bool top;
        bool down;
    public:
    std::vector<Tile> map;
    EntityManager emgr;
    DisplaySystem displaySys;
    MovementSystem movementSys;
    CollisionSystem collisionSys;
    Game * game;

    Tile& at(uint x, uint y) {
        return map[y*width + x];
    }
    
    const Tile& at(uint x, uint y) {
        return map[y*width + x];
    }
    

    
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
    GameState input(sf::Event& ev);
    void draw();
    void update();
    uint width;
    uint height;
};

