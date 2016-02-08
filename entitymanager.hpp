#pragma once
#include <vector>
#include <map>
#include <queue>
#include <type_traits>
#include "entity.hpp"
#include "system.hpp"
class World;


enum class Kind {
    Item,
    Actor,
    Obstacle,
    Player,
    Floor
};

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
      return entities[id];
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

