#include "engine.hpp"
#include <iostream>
#include "../tile.hpp"
void TileEngine::init(StrTuple textures, StrTuple tiles, StrTuple fonts, sf::Vector2i tilesize, uint fontsize)
{
    texturemgr.load(textures.first, textures.second);
    spritemgr.load(tiles.first, tiles.second, tilesize);
    fontmgr.load(fonts.first, fonts.second);
    fontmgr.setSize(fontsize);
 
}

void TileEngine::createMap(std::vector< Tile > _map)    
{
    map->populate(_map);
}

void TileEngine::createObject(std::string name, uint x, uint y)
{
    sf::Sprite sprite = texturemgr.getSprite(name);
    sprite.setPosition(x*20,y*20);
    objects->placeSprite(sprite);
}

void TileEngine::render(sf::RenderWindow& target)
{
    target.draw(*map);
    target.draw(*objects);
}

