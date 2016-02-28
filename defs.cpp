#include <iostream>
#include <algorithm>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "defs.hpp"
#include "game.hpp"
#include "world.hpp"
#include "entitymanager.hpp"


void DisplaySystem::update(Entity*) { return; }

void DisplaySystem::draw(Entity * entity) {  
     if (entity->cmgr.hasComponent<Position>()) {
        auto display = entity->cmgr.getComponent<Display>();
        auto position = entity->cmgr.getComponent<Position>();
        std::cout << position->x << " <:POSITION:> " << position->y << std::endl;
        getWorld()->game->te.createObject(display->sprite_name, position->x, position->y);
        getWorld()->game->te.centerCamera(position->x * 5, position->y * 5);
     }
}

void MovementSystem::update(Entity * entity, int dx, int dy)
{
    auto position = entity->cmgr.getComponent<Position>();
    std::cout << position->x << " + " << dx << " " << 
        position->y << " + " << dy << std::endl;


    if ( position->x + dx < 0 || position->x + dx >= int(getWorld()->width) ) 
        return;
    if ( position->y + dy < 0 || position->y + dy >= int(getWorld()->height) )  
        return;
    if ( !getWorld()->collisionSys.check(entity, position->x+dx, position->y+dy))
        return;

        getWorld()->at(position->x, position->y).occupied = false;
        getWorld()->at(position->x+dx, position->y+dy).actor = getWorld()->at(position->x, position->y).actor;
        getWorld()->at(position->x+dx, position->y+dy).occupied = true;
        position->x += dx;
        position->y += dy;
}

bool CollisionSystem::check(Entity * , uint x, uint y)
{
    std::cout << "MOVED -> " << x << " " << y << std::endl;
    auto tile = getWorld()->at(x,y);
    if ( !tile.occupied ) { 
        return tile.passable;    
    } else {
        return false;
    }
}


void InventorySystem::take(Entity * entity, Entity * object, sf::Vector2i coord)
{
  
  if ( !entity->haveTrait("canPick") ) {
    return;
  }
  
  std::cout << object->cmgr.getComponent<Item>()->price << std::endl;
  if ( !object->cmgr.getComponent<Item>()->pickable ) { 
    return;
  }
  std::vector<uint>& o = getWorld()->at(coord.x,coord.y).objects;
  o.erase(std::remove(o.begin(), o.end(), object->id), o.end());
  std::cout << "TAKEN OBJECT ID: " << object->id << std::endl;
  entity->cmgr.getComponent<Storage>()->items.push_back(object->id);
  object->cmgr.removeComponent<Position>();
}

void InventorySystem::drop(Entity * entity, Entity * object, sf::Vector2i coord) 
{
  if ( !entity->haveTrait("canDrop") ) {
    return;
  }
  
  if ( !object->cmgr.getComponent<Item>()->dropable ) { 
    return;
  }
  std::vector<uint>& s = entity->cmgr.getComponent<Storage>()->items;
  std::vector<uint>& t = getWorld()->at(coord.x, coord.y).objects;
  s.erase(std::remove(s.begin(), s.end(), object->id), s.end());
  object->cmgr.createComponent<Position>(coord.x, coord.y);
  t.push_back(object->id);
}
