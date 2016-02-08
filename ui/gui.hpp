#ifndef GUI_SYSTEM
#define GUI_SYSTEM
#include <type_traits>
#include <exception>
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
    GuiStyle(
            sf::Font * _font, 
            uint _fontsize,  
            uint _tilesize, 
            uint _border, 
            sf::Color _bordercolor ) :
                
        font(_font), 
        tilesize(_tilesize), 
        fontsize(_fontsize), 
        border(_border),  
        bordercolor(_bordercolor) {
        
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
    
    
    void setBackground(sf::Color color) {
        rect->setFillColor(color);
    }
    
    void setForeground(sf::Color color) {
        text->setColor(color);
    }
   
   
    void setColor(sf::Color back, sf::Color fore) {
        this->setBackground(back);
        this->setForeground(fore);
    }
    
    
    void setCharacter(const wchar_t wc) {
        text->setString(wc);
    }
        
    void draw(sf::RenderTarget& target) const {
        target.draw(*rect);
        target.draw(*text);
    }
    
    void setSize(float width, float height) {
        rect->setSize(sf::Vector2f{width, height});
    }
    
    void setPosition(uint x, uint y) {
        rect->setPosition(x,y);
        text->setPosition(x+3, y-3);
    }
};


struct Atlas {
    std::map<std::string, Tile> atlas;
    
    void emplace(const std::string& key, wchar_t chr, sf::Color back, sf::Color fore) {
        atlas[key] = Tile{};
        atlas[key].setBackground(back);
        atlas[key].setForeground(fore);
        atlas[key].setCharacter(chr);
    }
    
    Tile& get(const std::string& key) {
        return atlas[key];
    }
};

template<typename T>
using Map2D = std::vector<std::vector<T>>;

class MapBox : public Gui::BaseBox {
private:
    std::vector<Tile> tilemap;
    Gui::Atlas atlas;
    // sf::View view;
    
public:
    MapBox(uint _x, uint _y, uint _width, uint _height, GuiStyle& _style) :
        BaseBox(_x, _y, _width, _height, _style)  
        {
            tilemap.resize(_width*_height);
            atlas.emplace("wall", L'#', sf::Color::Black, sf::Color::White);
            atlas.emplace("floor", L'.',sf::Color::Black, sf::Color::White);
            atlas.emplace("grass", L'.',sf::Color::Green, sf::Color::Black); 
        }
    
    
    
    void setTile(uint x, uint y, std::string s) {
        tilemap[height*y + x] = atlas.get(s);
        tilemap[height*y + x].setPosition(this->x + style.tilesize*x, this->y + style.tilesize * y);
    }
    
    Tile& getTile(uint x, uint y) {
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

class Gui {
private:
    sf::Font font;
    sf::View view;
public:
    MapBox * map;
    StatusBox * box;
    sf::RenderWindow window;
    
    Gui(uint window_width, uint window_height, std::string title) {
        window.create(sf::VideoMode{window_width, window_height}, title);
        if ( ! font.loadFromFile("../media/COURIER.TTF") ) {
            throw std::logic_error("Couldnt load font file -- COURIER from ../media");
        }
        GuiStyle style{&font,20,18,2,sf::Color(128,128,128)};
        map = new MapBox(1,1, window_width - 200, window_height - 200, style);
        box = new StatusBox(0,200, window_width, 200, style);
        view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y-200));
        view.setCenter(sf::Vector2f(0.f,0.f));
        view.setViewport(sf::FloatRect(0,0,0.75,0.75));
    }
    
    void moveCamera(float x, float y) {
        view.move(x,y);
    }
    
    void clear() {
    }
    
    void close() {
        window.close();
    }
    
    void display() {
        window.setView(view);
        map->render(window);
        window.setView(window.getDefaultView());
        box->render(window);
        window.display();
        window.clear(sf::Color::Black);
    }
   
    
    ~Gui() {
        delete map;
        delete box;
    }
    //    ResourceManager rmgr;
};

}    /* Gui */
#endif
