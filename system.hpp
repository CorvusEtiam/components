#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include "util.hpp"

class World;
struct Entity;
/*
    @abstract 
*/
struct IDraw {
   virtual void draw(Entity& entity) = 0;
};


/*
    @abstract 
*/
struct ISystem {
private:
    World * world;
public:
    void setWorld(World * world) {
        this->world = world;
    }
    
    World * getWorld() { return world; }
    
    virtual void update(Entity& entity) = 0;
    
};

#endif