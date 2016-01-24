#include <iostream>
#include <algorithm>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "defs.hpp"
#include "game.hpp"
#include "world.hpp"
#include "entitymanager.hpp"

void DisplaySystem::update(Entity&) { return; }

void DisplaySystem::draw(Entity& entity, char alter_code) {  
      auto display = entity.cmgr.getComponent<Display>();
      auto position = entity.cmgr.getComponent<Position>();
      sf::RectangleShape rect;
      sf::Text text;      
      rect.setPosition({position->x * 20.f, position->y * 20.f});
      rect.setSize({20.f, 20.f});
      rect.setFillColor(display->background);
      text.setFont(getWorld()->game->font);
      text.setString(alter_code);
      text.setPosition(position->x * 20.f+ 3, position->y * 20.f - 3);
      text.setCharacterSize(18);
      getWorld()->game->window.draw(rect);
      getWorld()->game->window.draw(text);
}

void DisplaySystem::draw(Entity& entity) {  
      auto position = entity.cmgr.getComponent<Position>();
      auto display = entity.cmgr.getComponent<Display>();
      sf::RectangleShape rect;
      sf::Text text;
      rect.setPosition(sf::Vector2f(position->x * 20.f, position->y * 20.f));
      rect.setSize({20.f, 20.f});
      text.setPosition(position->x * 20.f + 3, position->y * 20.f - 3);
      text.setCharacterSize(18);
      text.setFont(getWorld()->game->font);
      text.setString(sf::String(display->code));
      
      
      if ( entity.cmgr.hasComponent<Floor>() ) {
        rect.setFillColor(display->background);
        text.setColor(display->foreground);  
      } else {
        auto backtile = getWorld()->map[position->y][position->x].floor;
        auto backdisp = getWorld()->emgr.getCompManager(backtile).getComponent<Display>();
        rect.setFillColor(backdisp->background);
        text.setColor(display->foreground);
      }
      
      getWorld()->game->window.draw(rect);
      getWorld()->game->window.draw(text);

}

/*
 
#####
#####
###0#
#####
 
*/

void MovementSystem::update(Entity& entity, int dx, int dy)
{
    auto position = entity.cmgr.getComponent<Position>();
<<<<<<< HEAD
    std::cout << position->x << " + " << dx << " " << position->y << " + " << dy << std::endl;
    if ( ( position->x + dx < 0 || position->x + dx >= getWorld()->width ) ||
         ( position->y + dy < 0 || position->y + dy > getWorld()->height ) ) {
            return;
        }
    auto floor = getWorld()->emgr.getCompManager(getWorld()->map[position->x+dx][position->y+dy].floor).getComponent<Floor>();
    if ( floor->passable ) {
        getWorld()->map[position->x][position->y].haveActor = false;
        getWorld()->map[position->x+dx][position->y+dy].actor = getWorld()->map[position->x][position->y].actor;
        getWorld()->map[position->x+dx][position->y+dy].haveActor = true;
=======
    std::cout << position->x << " + " << dx << " " << 
        position->y << " + " << dy << std::endl;


    if ( position->x + dx < 0 || position->x + dx >= int(getWorld()->width) ) 
        return;
    if ( position->y + dy < 0 || position->y + dy >= int(getWorld()->height) )  
        return;
    if ( !getWorld()->collisionSys.check(entity, position->x+dx, position->y+dy))
        return;

        getWorld()->map[position->y][position->x].haveActor = false;
        getWorld()->map[position->y+dy][position->x+dx].actor = getWorld()->map[position->y][position->x].actor;
        getWorld()->map[position->y+dy][position->x+dx].haveActor = true;
>>>>>>> maploader
        position->x += dx;
        position->y += dy;
}



bool CollisionSystem::check(Entity& , uint x, uint y)
{
    std::cout << "MOVED -> " << x << " " << y << std::endl;
    EntityList list = getWorld()->map[y][x];
    if ( list.haveFloor && !list.haveActor ) {
        return getWorld()->emgr.getComponentFromEntity<Floor>(list.floor)->passable;
    } else {
        return false;
    }
}

