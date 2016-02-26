#include <iostream>
#include <algorithm>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "defs.hpp"
#include "game.hpp"
#include "world.hpp"
#include "entitymanager.hpp"


void DisplaySystem::update(Entity&) { return; }

void DisplaySystem::draw(Entity& entity) {  
     auto display = entity.cmgr.getComponent<Display>();
     auto position = entity.cmgr.getComponent<Position>();
     getWorld()->game->te.createObject(display->sprite_name, position->x, position->y);
     getWorld()->game->te.centerCamera(position->x * 5, position->y * 5);
}

void MovementSystem::update(Entity& entity, int dx, int dy)
{
    auto position = entity.cmgr.getComponent<Position>();
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

bool CollisionSystem::check(Entity& , uint x, uint y)
{
    std::cout << "MOVED -> " << x << " " << y << std::endl;
    auto tile = getWorld()->at(x,y);
    if ( !tile.occupied ) { 
        return tile.passable;    
    } else {
        return false;
    }
}


void InventorySystem::take(Entity& entity, uint object)
{
  if ( !entity.haveTrait("canPick") ) {
    return;
  }
  
  if ( !getWorld()->emgr.getComponentFromEntity<Item>(object)->pickable ) { 
    return;
  }
  
  auto pos = entity.cmgr.getComponent<Position>();
  auto& objects = getWorld()->at(pos->x, pos->y).objects;
  auto obj_it = std::find(objects.begin(), objects.end(), object);
  entity.cmgr.getComponent<Storage>()->items.push_back(*obj_it);
  objects.erase(obj_it);
  std::cout << "Object taken!" << std::endl;
  
  return;
}

