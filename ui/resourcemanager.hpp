#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include <utility>

class TextureManager {
private:
    sf::Texture texture;
    std::map<std::string, sf::Vector2f> sheet;
public:
    void load(const std::string& texture_file, const std::string& texture_descr);
    const sf::Vector2f& get(const std::string& name) const;
    sf::Texture& getTexture() {
        return texture;
    }
    sf::Sprite getSprite(const std::string name) {
        sf::Sprite sprite; 
        sprite.setTexture(getTexture());
        auto tleft = get(name);
        sprite.setTextureRect(sf::IntRect(tleft.x*20, tleft.y*20, 20, 20));
        return sprite;
    }
    
};


class FontManager {
private:
    std::map<std::string, sf::Font> fonts;
    uint m_fontsize;
public:
    void load(const std::string& font_name, const std::string& font_file);
    uint getSize() const { return m_fontsize; }
    void setSize(uint fontsize) { m_fontsize = fontsize; }
    sf::Font * get(const std::string& name);
};

class SpriteManager {
private:
    sf::Vector2i tilesize;
    sf::Texture texture;
    std::map<std::string, sf::Sprite> sprites;
public:
    void load(const std::string& sprite_file, const std::string& sprite_descr, sf::Vector2i _tilesize);
    sf::Sprite get(const std::string& name); 
    
    void setTilesize(sf::Vector2i _tilesize) { tilesize = _tilesize; }
    sf::Vector2i getTilesize() const { return tilesize; }
};

class ResourceManager {
    SpriteManager spritemgr;
    TextureManager texturemgr;
    FontManager fontmgr;
public:
    
};

#endif /* RESOURCE_MANAGER_HPP */
