#include "tilemap.hpp"
#include "engine.hpp"
#include <iostream>


void TileMap::init(sf::Vector2i size) {
    setSize(size);
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(size.x*size.y*4);
}

void TileMap::setTileAt(uint x, uint y, std::string tilename)
{
    sf::Vector2i size = getSize();
    sf::Vector2i tilesize = m_engine->spritemgr.getTilesize();
    sf::Vertex* quad = &m_vertices[(x + y * size.x) * 4];
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

void TileMap::populate(std::vector< std::string > _map)
{
    sf::Vector2i size = getSize();
    for ( uint x = 0; x < size.x; ++x )  {
        for ( uint y = 0; y < size.y; ++y )  {
            setTileAt(y,x,_map[x + y * size.x]);
        }
    }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform

    states.transform *= getTransform();
    // apply the tileset texture
    states.texture = m_engine->texturemgr.getTexture();

    // draw the vertex array
    target.draw(m_vertices, states);
}