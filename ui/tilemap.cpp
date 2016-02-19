#include "tilemap.hpp"
#include "engine.hpp" 
#include <iostream>



void TileMap::init() {
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(m_size.x*m_size.y*4);
}

void TileMap::setTileAt(uint x, uint y, std::string tilename)
{
    sf::Vector2i size = getSize();
    sf::Vector2i tilesize = m_engine->spritemgr.getTilesize();
    sf::Vertex* quad = &m_vertices[(x + (y * size.x)) * 4];
    sf::Vector2f tex_pos = m_engine->texturemgr.get(tilename);
#define COORD(X,Y) sf::Vector2f((X)*tilesize.x, (Y)*tilesize.y)
    quad[0].position = COORD(x,y);
    quad[1].position = COORD(x+1, y);
    quad[2].position = COORD(x+1, y+1);
    quad[3].position = COORD(x,y+1);
    // define its 4 texture coordinates
    quad[0].texCoords = COORD(tex_pos.x, tex_pos.y);
    quad[1].texCoords = COORD(tex_pos.x+1, tex_pos.y); 
    quad[2].texCoords = COORD(tex_pos.x+1, tex_pos.y+1);
    quad[3].texCoords = COORD(tex_pos.x, tex_pos.y+1);
#undef COORD        
}

void TileMap::populate(std::vector< Tile > _map)
{
    for (  const Tile& tile : _map) {
        if (tile.visible) {
//            std::cout << tile.x << " " << tile.y << std::endl;
            setTileAt(tile.x, tile.y, tile.floor_tile);
        } else {
            setTileAt(tile.x, tile.y,  "wall");
        }
    }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &m_engine->texturemgr.getTexture();
    target.draw(m_vertices, states);
}