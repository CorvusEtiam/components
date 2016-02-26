#pragma once
#include <vector>
#include "entitymanager.hpp"
#include "defs.hpp"
#include "util.hpp"
#include "gamestates.hpp"
#include "tile.hpp"


class Game;
class World {
    private:
        bool m_drawn = false;
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
    InventorySystem inventorySys;
    Game * game;

    Tile& at(uint x, uint y) {
        return map[y*width + x];
    }
    
    

    
    World() {}

    void init(Game * _game) {
        displaySys.setWorld(this);
        movementSys.setWorld(this);
        collisionSys.setWorld(this);
        game = _game; 
        if ( !this->loadMapFile("/home/misiek/Projekt/cpp/tile/media/simplemap.csv")) {
            std::logic_error("Cannot load simplemap.csv");
        }
    }
    void displayMap();
    bool loadMapFile(const std::string& path); 
    // GameState input(sf::Event& ev);
    void input(sf::Event& ev);
    void draw();
    void update();
    uint width;
    uint height;
};

