#include "tilemap.hpp"
#include <iostream>
void TileMap::load(std::string texture_path, std::string texture_descr)
{
    m_tileset.load(texture_path, texture_descr);
}

void TileMap::populate(std::vector< std::string > _map, uint width, uint height, sf::Vector2f tilesize)
{
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width*height*4);
    for ( uint x = 0; x < width; ++x )  {
        for ( uint y = 0; y < height; ++y )  {
            sf::Vertex* quad = &m_vertices[(x + y * width) * 4];
            sf::Vector2f tex_pos = m_tileset.get(_map[y + x * width]);
            // define its 4 corners
            std::cout << _map[y + x * width] << " " << tex_pos.x << " " << tex_pos.y << " " << x << " " << y <<  std::endl;

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
    }
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply the transform

    states.transform *= getTransform();
    // apply the tileset texture
    states.texture = m_tileset.getTexture();

    // draw the vertex array
    target.draw(m_vertices, states);
}