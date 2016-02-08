#ifndef GUI_SYSTEM
#define GUI_SYSTEM
#include <type_traits>
#include <vector>
#include <cstdint>
#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace Gui {

typedef uint32_t uint;


std::string linebreak(std::string entry, uint width); 
std::wstring linebreak(std::wstring entry, uint width);


struct GuiStyle {
    sf::Font * font;
    uint tilesize;
    uint fontsize;
    uint border;
    sf::Color bordercolor;
    GuiStyle(sf::Font * _font, uint _fontsize,  uint _tilesize, uint _border, sf::Color _bordercolor ) :
       font(_font), fontsize(_fontsize), border(_border), bordercolor(_bordercolor), tilesize(_tilesize)
    {
        ////////////////////////
        /// \param _font pointer to Font 
        /// \param _fontsize font size
        /// \param _border thickness 
        /// \param _bordercolor 
        ////////////////////////
    }

    GuiStyle() {
        font = nullptr;
    }
};

class BaseBox {
public:
    uint width;
    uint height;
    uint x;
    uint y;
    GuiStyle style;
    BaseBox(uint _x, uint _y, uint _width, uint _height, GuiStyle _style) :
        width(_width),
        height(_height),
        x(_x),
        y(_y)
        {
            style = _style;
            
        }
};

struct Tile {
private:
    sf::RectangleShape * rect;
    sf::Text * text;
public:
    
    Tile() {
        rect = new sf::RectangleShape();
        text = new sf::Text();
       
    }
    
    Tile(uint x, uint y, const GuiStyle& style) {
        rect = new sf::RectangleShape();
        rect->setSize(sf::Vector2f(style.tilesize,style.tilesize));
        rect->setOutlineThickness(style.border);
        rect->setOutlineColor(style.bordercolor);
        rect->setPosition(x*style.tilesize,y*style.tilesize);
        text = new sf::Text();
        text->setPosition(x*style.tilesize,y*style.tilesize);
        text->setCharacterSize(style.fontsize);
        text->setFont(*style.font);
    }
    
    void setTile(uint x, uint y, const GuiStyle& style) {
        rect->setSize(sf::Vector2f(style.tilesize,style.tilesize));
        rect->setOutlineThickness(style.border);
        rect->setOutlineColor(style.bordercolor);
        rect->setPosition(x*style.tilesize,y*style.tilesize);
        
        text->setPosition(x*style.tilesize,y*style.tilesize);
        text->setCharacterSize(style.fontsize);
        text->setFont(*style.font);
        
    }
    
    
    void draw(sf::RenderTarget& target) const {
        target.draw(*rect);
        target.draw(*text);
    }
    
    
    void setBackground(sf::Color color) {
        rect->setFillColor(color);
    }
    
    void setForeground(sf::Color color) {
        text->setColor(color);
    }
    
    void setCharacter(const wchar_t wc) {
        text->setString(wc);
    }
    
    void setAll(sf::Color back, sf::Color fore, const wchar_t wc) {
        this->setBackground(back);
        this->setForeground(fore);
        this->setCharacter(wc);
    }
    
};


inline sf::Vector2f mapCoordsToNormal(float x, float y, uint tilesize = 20) {
    return sf::Vector2f(x + tilesize , y + tilesize );
}


template<typename T>
using Map2D = std::vector<std::vector<T>>;

class MapBox : public Gui::BaseBox {
private:
    std::vector<Tile> tilemap;
    // sf::View view;
    
public:
    MapBox(uint _x, uint _y, uint _width, uint _height, GuiStyle& _style) :
        BaseBox(_x, _y, _width, _height, _style)  
        {
            tilemap.resize(_width*_height);
            for ( auto i = 0; i < height; i++ ) {
                for ( auto j = 0; j < width; j++ ) {
                    tilemap[i*height + j].setTile(i, j, style);
                }      
            }    
        }
        
    
    
    Tile& at(uint x, uint y) {
        return tilemap[height*y + x];
    }
    
    const Tile& at(uint x, uint y) const {
        return tilemap[height*y + x];
    }
    
    void render(sf::RenderTarget& target) const;
};

class StatusBox : public BaseBox {
    sf::Text * textbox;
    sf::RectangleShape * blackbox;
public:
    
    StatusBox(uint _x, uint _y, float _width, float _height, const GuiStyle& _style) :
        BaseBox(_x, _y, _width, _height, _style)
    {
        blackbox = new sf::RectangleShape();
        blackbox->setFillColor(sf::Color::Black);
        blackbox->setSize({_width, _height});
        blackbox->setPosition(sf::Vector2f(_x, _y));
        
        textbox = new sf::Text;
        textbox->setPosition(_x, _y);
        textbox->setFont(*style.font);
        textbox->setCharacterSize(style.fontsize);
    }

    void showMsg(std::wstring msg, sf::Color foreground) {
        if ( (msg.size() * style.fontsize ) > width ) {
            msg = linebreak(msg, int(width / style.tilesize));
        }
        textbox->setString(msg);
        textbox->setColor(foreground);
    }
    
    /*
     void createButton();
     void createTextBox();
     void 
     */
    
    void render(sf::RenderTarget& target) const;
};


// class SideBar : public BaseBox {};
// class InventoryBox {};
// class Messanger {}; // take care of popups, messanges
// class MapBox : public Box {};
// class StatusBarBox : public Box {};
// class GuiToolbarBox : public Box {};

class Gui {
public:
    sf::RenderWindow window;
    MapBox * map;
    StatusBox * box;

    Gui(float window_width, float window_height, const std::string& title) {
        window.create(sf::Vector2f{window_width, window_height}, title);
    }
    
    void clear() {
        window.clear(sf::Color::Black);
    }
    
    void display() {
        window.display();
    }
    
    void close() {
        window.close();
    }
    
    void draw(sf::Drawable * _draw) {
        window.draw(_draw);
    }
    
    //    ResourceManager rmgr;
};

}    /* Gui */
#endif
