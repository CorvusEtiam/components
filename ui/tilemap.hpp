#ifndef TILEMAP_HPP
#define TILEMAP_HPP
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>
#include <fstream>
#include <vector>
#include "resourcemanager.hpp"
#include "../tile.hpp"


class TileEngine;
class TileMap : public sf::Drawable, public sf::Transformable {
public:
    TileMap(TileEngine * engine) {
        m_engine = engine;
    }
    void init();
    void populate(std::vector<Tile> _map);
    void setSize(sf::Vector2i size) { 
        m_size = size;
    }
    sf::Vector2i getSize() const { return m_size; }
    
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setTileAt(uint x, uint y, std::string tilename);
    sf::VertexArray m_vertices;
    TileEngine * m_engine;
    sf::Vector2i m_size;
        
};


#endif /* TILEMAP_HPP */