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
      auto display = entity.cmgr.getComponent<Display>();
      auto position = entity.cmgr.getComponent<Position>();
      sf::RectangleShape rect;
      sf::Text text;
      rect.setPosition(sf::Vector2f(position->x * 20.f, position->y * 20.f));
      rect.setSize({20.f, 20.f});
      rect.setFillColor(display->background);
      text.setFont(getWorld()->game->font);
      text.setString(sf::String(display->code));
      text.setColor(display->foreground);
      text.setPosition(position->x * 20.f + 3, position->y * 20.f - 3);
      text.setCharacterSize(18);
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
    std::cout << position->x << " + " << dx << " " << position->y << " + " << dy << std::endl;
    if ( ( position->x + dx < 0 || position->x + dx >= getWorld()->width ) ||
         ( position->y + dy < 0 || position->y + dy >= getWorld()->height ) ) {
            return;
        }
    auto floor = getWorld()->emgr.getCompManager(getWorld()->map[position->x+dx][position->y+dy].floor).getComponent<Floor>();
    if ( floor->passable ) {
        getWorld()->map[position->x][position->y].haveActor = false;
        getWorld()->map[position->x+dx][position->y+dy].actor = getWorld()->map[position->x][position->y].actor;
        getWorld()->map[position->x+dx][position->y+dy].haveActor = true;
        position->x += dx;
        position->y += dy;
    }
}



bool CollisionSystem::check(Entity& entity, uint x, uint y)
{
    std::cout << "MOVED -> " << x << " " << y << std::endl;
    EntityList list = getWorld()->map[x][y];
    if ( list.haveFloor && !list.haveActor ) {
        Floor * f = getWorld()->emgr.getComponentFromEntity<Floor>(list.floor);
        return f->passable;
    } else {
        return false;
    }
}

