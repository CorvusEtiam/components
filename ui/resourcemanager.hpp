#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <memory>


class TextureManager {
private:
    sf::Texture texture;
    std::map<std::string, sf::Vector2f> sheet;
public:
    void load(const std::string& texture_file, const std::string& texture_descr);
    const sf::Vector2f& get(const std::string& name) const;
    const sf::Texture* getTexture() const {
        return &texture;
    }
};


class FontManager {
private:
    std::map<std::string, sf::Font> fonts;
public:
    void load(const std::string& font_name, const std::string& font_file);
    
    sf::Font * get(const std::string& name);
};

class SpriteManager {
private:
    sf::Texture texture;
    std::map<std::string, sf::Sprite> sprites;
public:
    void load(const std::string& sprite_file, const std::string& sprite_descr);
    sf::Sprite * get(const std::string& name); 
};



#endif /* RESOURCE_MANAGER_HPP */