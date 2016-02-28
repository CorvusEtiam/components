#ifndef SYSTEM_HPP
#define SYSTEM_HPP
#include "util.hpp"
#include <stdexcept>
class World;
struct Entity;
/*
    @abstract 
*/
struct IDraw {
   virtual void draw(Entity * entity) = 0;
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
    
    World * getWorld() { 
      if ( this->world != nullptr ) { 
	return world; 	
      } else { 
	throw std::runtime_error("World is NULL"); } 
    }
    
    virtual void update(Entity * entity) = 0;
    
};

#endif