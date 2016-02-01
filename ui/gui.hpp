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

using W = std::string;
W linebreak(W entry, uint width); 

struct GuiStyle {
    sf::Color background;
    sf::Color foreground;
    sf::Font * font;
    uint fontsize;
    uint border;
    GuiStyle(sf::Color _back, sf::Color _fore, sf::Font * _font, uint _fontsize, uint _border) :
        background(_back), foreground(_fore), font(_font), fontsize(_fontsize), border(_border)
    {}

    GuiStyle() {}
};

class BaseBox {
public:
    uint width;
    uint height;
    uint x;
    uint y;
    float tilesize;

    BaseBox(uint _x, uint _y, uint _width, uint _height, float _tilesize) :
        width(_width),
        height(_height),
        x(_x),
        y(_y),
        tilesize(_tilesize) 
        {}
};

struct Tile {
    sf::RectangleShape* rect = nullptr;
    sf::Text* text = nullptr;
    bool changed = false;
    bool visible = true;
    Tile() {}
    Tile(sf::RectangleShape * r, sf::Text * t) {
        rect = r;
        text = t;
    }
};



using Map = std::vector<std::vector<Tile>>;

inline sf::Vector2f mapCoordsToNormal(float x, float y, uint tilesize = 20) {
    return sf::Vector2f(x + tilesize , y + tilesize );
}

class MapBox : public Gui::BaseBox {
private:
    std::vector<std::vector<Tile>> plane;
//    sf::View view;
public:
    MapBox(uint _x, uint _y, uint _width, uint _height, float _tilesize) :
        BaseBox(_x, _y, _width, _height, _tilesize)
    {
        plane.resize(height);
        for ( auto y = 0; y < height; ++y ) {
            plane[y] = std::vector<Tile>();
            plane[y].resize(this->width);
            for ( auto x = 0; x < width; ++x ) {
                std::cout << x << " " << y << std::endl;
                auto rect = new sf::RectangleShape();
                rect->setSize(sf::Vector2f(tilesize, tilesize));
                rect->setPosition(this->x + x*tilesize, this->y + y*tilesize);
                rect->setOutlineThickness(2.0);
                rect->setOutlineColor(sf::Color::Blue);
                auto text = new sf::Text;
                text->setCharacterSize(tilesize - 4);
                text->setPosition(this->x + x*tilesize + 3, this->y + y*tilesize - 3);
                plane[y][x] = Tile(rect, text);
            }
        }
    }
    
    void setTile(uint x, uint y, char str) {
        plane[y][x].text->setString(str);
    }
#define DEBUG_PRINT(STR) std::cout << "[" << __LINE__  << "]" << STR << std::endl;    
    void setTile(uint x, uint y, GuiStyle * style, char str) {
        plane[y][x].rect->setFillColor(style->background);
        plane[y][x].text->setString(str);
        plane[y][x].text->setFont(*(style->font));
        plane[y][x].text->setColor(sf::Color::White);
        plane[y][x].visible = true;
        plane[y][x].changed = true;
    }
    
    void hidden(uint x, uint y) {
        plane[y][x].visible = false;
    }
    
    void render(sf::RenderTarget& target) const;
};

class StatusBox : public BaseBox {
    sf::Text * textbox;
public:
    StatusBox(uint _x, uint _y, uint _width, uint _height, float _tilesize) :
        BaseBox(_x, _y, _width, _height, _tilesize)
    {
        textbox = new sf::Text;
        textbox->setPosition(_x, _y);
    }

    void showMsg(std::string msg, Gui::GuiStyle& msgStyle) {
        if ( tilesize * msg.size() > width ) {
            msg = linebreak(msg, int(width / tilesize));
        }
        textbox->setString(msg);
        textbox->setColor(msgStyle.foreground);
        textbox->setFont(*(msgStyle.font));
        textbox->setCharacterSize(msgStyle.fontsize);
    }
    
    void render(sf::RenderTarget& target) const;
};

// class SideBar : public BaseBox {};
// class InventoryBox {};
// class Messanger {}; // take care of popups, messanges
// class MapBox : public Box {};
// class StatusBarBox : public Box {};
// class GuiToolbarBox : public Box {};
class Gui {
    MapBox * map;
    StatusBox * box;
    // SideBar * left;
    // MenuBar * menu;
};

}    /* Gui */
#endif
