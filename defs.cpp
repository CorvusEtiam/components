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
    if ( !tile.occupied ) 
        return tile.passable;    
    
}



/*
void InventorySystem::_displayMsg(std::vector<uint> data, uint x, uint y)
{
    std::string line;
    uint width = 0;
    for ( uint handle = 0; handle < data.size(); ++handle ) {
        auto name = getWorld()->emgr.getCompManager(data[handle]).getComponent<Description>()->name;
        if ( name.size() + 10 > width ) width = name.size();
        line += name + " \n";
    }
    uint height = data.size()*20 + 10;
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::Black);
    rect.setPosition(x,y);
    rect.setSize(width, height);
    sf::Text text;
    text.setCharacterSize(18);
    text.setFont(getWorld()->game->font);
    text.setColor(sf::Color::Color(128,128,128));
    text.setString(line);
    getWorld()->game->window.draw(rect);
    getWorld()->game->window.draw(text);
}



void InventorySystem::draw(Entity& entity)
{
    
    
     * Leave it for better time. Turn into proper Gui subsystem; connect with main;
     * For now console output have to be enough!!
    sf::RectangleShape outer;
    sf::RectangleShape rect;
    outer.setSize(22*inv->items.size()+50, 350);
    outer.setPosition({20.f,20.f});
    outer.setFillColor(sf::Color::Black);
    rect.setSize(22*inv->items.size(), 300);
    rect.setFillColor(sf::Color::Black);
    rect.setPosition({45.f, 45.f});
    rect.setOutlineThickness(2);
    rect.setOutlineColor(sf::Color::White);
    sf::Text text;
    text.setCharacterSize(18);
    text.setFont(getWorld()->game->font);
    text.setColor(sf::Color::Color(128,128,128));
    for ( uint handle = 0; handle < inv->items.size(); ++handle ) {
        text.setString(getWorld()->emgr.getCompManager(inv->items[handle]).getComponent<Description>()->name);
        text.setPosition(50.f, 50.f+handle*20);
        getWorld()->game->window.draw(text);
    }
    getWorld()->game->window.draw(outer);
    getWorld()->game->window.draw(rect);
    
    
}


void InventorySystem::take(Entity& entity, uint object)
{
    auto position = entity.cmgr.getComponent<Position>();
    this->_displayMsg(entity.cmgr.getComponent<Storage>()->items, 20, 20);
    
}
*/
