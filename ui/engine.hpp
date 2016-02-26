#ifndef TILE_ENGINE_HPP
#define TILE_ENGINE_HPP
#include <utility>
#include "tilemap.hpp"
#include "layer.hpp"
#include "resourcemanager.hpp"
#include "../tile.hpp"
  
enum class ResourceType {
    Font,
    Texture,
    Coords,
    Sprite
};
  

typedef std::pair<std::string, std::string> StrTuple;

class TileEngine {
    uint m_center_x;
    uint m_center_y;
    TileMap * map;
    Layer * objects; // Layer abstact away all drawable sprites on map;
public:
    SpriteManager spritemgr;
    TextureManager texturemgr;
    FontManager fontmgr;
    
    TileEngine() {
        objects = new Layer(this);
        map = new TileMap(this);    
    }
    
    
    TileEngine(StrTuple textures, StrTuple tiles, StrTuple fonts, sf::Vector2i tilesize, uint fontsize) {
        objects = new Layer(this);
        map = new TileMap(this);
        init(textures,tiles,fonts,tilesize, fontsize);
    }
    
    void setPosition(sf::Vector2f pos) {
        map->setPosition(pos);
        objects->setPosition(pos);
    }
        
    void setSize(sf::Vector2i vec) {
        map->setSize(vec); 
        map->init();
    }
    void init(StrTuple textures, StrTuple tiles, StrTuple fonts, sf::Vector2i tilesize, uint fontsize);
    void render(sf::RenderWindow& window);
    void createObject(std::string name, uint x, uint y);
    void createMap(std::vector<Tile> _map);
    void centerCamera(uint x, uint y) {
      m_center_x = x;
      m_center_y = y;
    }
};

#endif /* TILE_ENGINE_HPP */
