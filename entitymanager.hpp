#pragma once
#include <vector>
#include <map>
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

using Group = std::vector<uint>;

class EntityManager {
public:
    uint createEntity(Kind kind) {
      auto entity = Entity();
      entity.world = world; 
      entities[entity.id] = entity;
      if ( kinds.find(kind) != kinds.end() ) {
        kinds[kind].push_back(entity.id);
      } else {
        kinds.insert({kind, Group()});
        kinds[kind].push_back(entity.id);
      }
      return entity.id;
    }
    
    
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
    
    uint setEntity(Kind kind, Entity entity) {
        auto id = generator();
        entity.id = id;
        entities[id] = entity;
        if ( kinds.find(kind) != kinds.end() ) {
            kinds[kind].push_back(id);
        } else {
            kinds.insert({kind, Group()});
            kinds[kind].push_back(id);
        }
        return id;
    }
    
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

