#include "entitymanager.hpp"

struct Counter {
    static uint get() { return id++; }
private:
    static uint id;
};

uint Counter::id = 0;

uint EntityManager::createEntity(Kind kind)
{
    auto entity = Entity();
    entity.world = world;
    uint id = Counter::get();
    entity.id = id;
    entities[id] = entity;
    if ( kinds.find(kind) != kinds.end() ) {
        kinds[kind].push_back(id);
    } else {
        kinds.insert( {kind, Group()});
        kinds[kind].push_back(id);
    }
    return id;
}

uint EntityManager::setEntity(Kind kind, Entity entity)
{
    auto id = Counter::get();
    entity.id = id;
    entities[id] = entity;
    if ( kinds.find(kind) != kinds.end() ) {
        kinds[kind].push_back(id);
    } else {
        kinds.insert( {kind, Group()});
        kinds[kind].push_back(id);
    }
    return id;
}
