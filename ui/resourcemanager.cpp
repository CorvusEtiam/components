#include "resourcemanager.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include "../util.hpp"

sf::Sprite SpriteManager::get(const std::string& name) {
   if ( sprites.find(name) != sprites.end() ) {
        return sprites[name];
    } else {
        throw std::out_of_range("Sprite not found");
    }
}

void SpriteManager::load(const std::string& sprite_file, const std::string& sprite_descr, sf::Vector2i _tilesize)
{
    setTilesize(_tilesize);
    if ( !texture.loadFromFile(sprite_file)) {
        throw std::runtime_error("Problem with sprites loading");
    } 
    
    std::ifstream sfile(sprite_descr);
    std::string line;
    while ( std::getline(sfile, line) ) {
        std::cout << line << std::endl;
        auto vec = split(line, ';');
        sf::Sprite s;
        s.setTexture(texture);
        s.setTextureRect(sf::IntRect(std::stoi(vec[1])*20, std::stoi(vec[2])*20, getTilesize().x, getTilesize().y ));
        sprites.insert(std::make_pair(vec[0], s));
    }
}

void FontManager::load(const std::string& font_name, const std::string& font_file)
{
    sf::Font font;
    if ( !font.loadFromFile(font_file)) {
        throw std::runtime_error("Font-file not found");
    }
    fonts.insert({font_name, font});
}

sf::Font* FontManager::get(const std::string& name)
{
    return &fonts[name];
}


void TextureManager::load(const std::string& texture_file, const std::string& texture_descr)
{
    if ( !texture.loadFromFile(texture_file)) {
        throw std::runtime_error("Problem with texture loading");
    } 
    
    std::ifstream sfile(texture_descr);
    std::string line;
    while ( std::getline(sfile, line) ) {
        auto vec = split(line, ';');
        std::cout << "TEXTURE: " << vec[0] << " : X: " << vec[1] << " Y: "<< vec[2] << std::endl;
        sheet.insert(std::make_pair(vec[0], sf::Vector2f(float(std::stoi(vec[1])), float(std::stoi(vec[2])))));
    }
}


const sf::Vector2f& TextureManager::get(const std::string& name) const
{
    if ( sheet.find(name) != sheet.end() ) {
        return sheet.at(name);
    } else {
        std::cerr << "!!! " << name << std::endl; 
        throw std::out_of_range("Texture not found");
    }
}



