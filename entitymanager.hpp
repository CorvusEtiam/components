#pragma once
#include <vector>
#include <map>
#include <queue>
#include <stdexcept>
#include <iostream>
#include <type_traits>
#include "entity.hpp"
#include "system.hpp"
class World;



typedef uint uint32_t;

using Group = std::vector<uint>;

class EntityManager {
public:
    uint createEntity(Kind kind); 
    
    
    template<typename T>
    T * getComponentFromEntity(uint handle) {
      return getCompManager(handle).getComponent<T>();
    }
  
 
    template<typename T>
    T * getComponentFromEntity(Entity& entity) {
        return entity.cmgr.getComponent<T>();
    }
  
    
    Entity& getEntity(uint id) {
        if ( entities.find(id) != entities.end() ) 
        { return entities[id]; }
        else {
            std::cerr << "NUMBER: " << id << std::endl;
            throw std::out_of_range("entity not found");
        }
    }
    
    Entity& getPlayer() {
        return getEntity(kinds[Kind::Player][0]);
    }
    
    uint setEntity(Kind kind, Entity entity);
    
    void removeEntity(uint id) {
        entities.erase(entities.find(id));
    } 
    
    ComponentManager& getCompManager(uint id) {
      return getEntity(id).cmgr;
    }

    World * world;
    std::map<uint, Entity> entities;
    std::map<Kind, Group> kinds;
};

