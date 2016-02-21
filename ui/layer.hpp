#ifndef LAYER_ENGINE_HPP
#define LAYER_ENGINE_HPP
#include <SFML/Graphics.hpp>
#include <vector>

class TileEngine;
class Layer : public sf::Drawable, public sf::Transformable {
private:
    std::vector<sf::Sprite> * m_sprites;
    TileEngine * m_engine;    
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
public:
    Layer(TileEngine * engine) { 
        m_engine = engine; 
        m_sprites = new std::vector<sf::Sprite>();
    }
    void placeSprite(sf::Sprite s) { 
        m_sprites->push_back(s); 
    };        
};
  


#endif /* LAYER_ENGINE_HPP */