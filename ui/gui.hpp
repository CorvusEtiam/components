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
#include "resourcemanager.hpp"
#include "tilemap.hpp"
namespace Gui {


    
typedef uint32_t uint;
std::string linebreak(std::string entry, uint width); 
std::wstring linebreak(std::wstring entry, uint width);



struct GuiStyle {
    sf::Font * font;
    /////////////
    /// \todo Rewrite this class to use unique_ptr
    /////////////
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


class Gui {
private:
    sf::View view;
public:
    TileMap * map;
    std::vector<std::string> plane;
    StatusBox * box;
    sf::RenderWindow window;
    FontManager fontmgr;
    SpriteManager spritemgr;
    // map.drawTile(this, x,y,"wall")
    Gui() {
        
    }
    
    
    
    void init(uint window_width, uint window_height, std::string title) {
        window.create(sf::VideoMode{window_width, window_height}, title);
        fontmgr.load("courier", "../media/COURIER.TTF");
        GuiStyle style{fontmgr.get("courier"),20,18,2,sf::Color(128,128,128)};
        map = new TileMap();
        map->load("../media/sprite.png", "../media/sprite.txt");
        map->setPosition(20,20);
    //    box = new StatusBox(0,200, window_width, 200, style);
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
        window.draw(*map);
        window.setView(window.getDefaultView());
     //   box->render(window);
        window.display();
        window.clear(sf::Color::Black);
    }
   
    
    ~Gui() {
        delete map;
        delete box;
    }
    
};





// class SideBar : public BaseBox {};
// class InventoryBox {};
// class Messanger {}; // take care of popups, messanges


}    /* Gui */
#endif
