#include <SFML/Graphics.hpp>

    
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

