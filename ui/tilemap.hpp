#ifndef TILEMAP_HPP
#define TILEMAP_HPP
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>
#include <fstream>
#include <vector>
#include "resourcemanager.hpp"

class TileMap : public sf::Drawable, public sf::Transformable {
public:
    void load(std::string texture_path, std::string texture_descr );
    
    void populate(std::vector<std::string> _map, uint width, uint height, sf::Vector2f tilesize); 
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    sf::VertexArray m_vertices;
    TextureManager m_tileset;
};


#endif /* TILEMAP_HPP */