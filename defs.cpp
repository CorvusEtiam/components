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
//      std::cout << "SET DRAW" << std::endl;
      rect.setPosition(sf::Vector2f(position->x * 20.f, position->y * 20.f));
      rect.setSize({20.f, 20.f});
      rect.setFillColor(display->background);
//      std::cout << "*" << std::endl;
      text.setFont(getWorld()->game->font);
      text.setString(sf::String(display->code));
      text.setColor(display->foreground);
      text.setPosition(position->x * 20.f + 3, position->y * 20.f - 3);
      text.setCharacterSize(18);
//      std::cout << "**" << std::endl;
      getWorld()->game->window.draw(rect);
      getWorld()->game->window.draw(text);

}


void MovementSystem::update(Entity& entity, int dx, int dy)
{
    auto pos = entity.cmgr.getComponent<Position>();
    std::vector<uint>& vec = getWorld()->map[pos->x][pos->y];
    vec.erase(std::remove(std::begin(vec), std::end(vec), entity.id));
    if ( ( pos->x + dx >= 0 && pos->x + dx < getWorld()->width )  &&
         ( pos->y + dy >= 0 && pos->y + dy < getWorld()->height ) &&
         ( getWorld()->collisionSys.check(entity, pos->x+dx, pos->y+dy) ) ) {
        pos->x += dx;
        pos->y += dy; 
    }
    
    getWorld()->map[pos->x][pos->y].push_back(entity.id);
}

bool CollisionSystem::check(Entity& entity, float x, float y)
{
    EntityList list = getWorld()->map[x][y];
    if ( list.size() == 1 ) {
        return getWorld()->emgr.getComponentFromEntity<Floor>(list[0])->passable;
    } else {
        return false;
    }
}

