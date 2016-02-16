#pragma once
#include "gui.hpp"
namespace Gui {

enum class WidgetType {
    TextField,
    Button
};

class IWidget  {
public:
    virtual void draw(sf::RenderTarget& target) const = 0;
    WidgetType type;
    virtual ~IWidget() {}
    
};

template<typename T, typename... Args>
T * create_widget(Args&&... args) {
    static_assert(std::is_base_of<IWidget, T>(), "T have to be Subclass of IWidget!");
    return new T(std::forward<Args>(args)...);
}

class TextFieldWidget : public IWidget {
private:
    sf::Text * text;
    sf::RectangleShape * box;
public:
    void draw(const Box * box, sf::RenderTarget& target) const override  {
        target.draw(*box);
        target.draw(*text);
    }
    
    TextFieldWidget(
                    const std::string _text, 
                    GuiStyle _style, 
                    sf::Vector2f _size, 
                    sf::Vector2i _position ) {
        type = WidgetType::TextField;
        text = new sf::Text();
        box = new sf::RectangleShape();
        text->setString(linebreak(_text, 11));
        text->setFont(*_style.font);
        text->setCharacterSize(_style.fontsize);
        text->setColor(_style.foreground);
        text->setPosition(_position.x + 3, _position.y - 3);
        box->setPosition(_position.x, _position.y);
        box->setSize(_size + sf::Vector2f(_style.border, _style.border));
        box->setFillColor(_style.background);
        box->setOutlineThickness(_style.border);
        box->setOutlineColor(sf::Color(128,128,128));
    }
    
    ~TextFieldWidget() {
        delete box;
        delete text;
    }
};

class Button : public IWidget {
private:
    sf::Text * text;
    sf::RectangleShape * box;
public:
    virtual void draw(sf::RenderTarget& target) const {
        target.draw(*box);
        target.draw(*text);        
    }
    
    Button( const std::string _text, 
            GuiStyle  _style, 
            sf::Vector2f _size, 
            sf::Vector2i _position ) {
        
        type = WidgetType::Button;
        text = new sf::Text();
        box = new sf::RectangleShape();
        text->setString(_text);
        text->setFont(*_style.font);
        text->setCharacterSize(_style.fontsize);
        text->setColor(_style.foreground);
        text->setPosition(_position.x + 3, _position.y - 3);
        float width = (_style.fontsize * _text.size()) + _style.border * 2;
        float half_height = ( _style.fontsize + _style.border );
        text->move(half_height , _style.fontsize / 2);
        box->setPosition(_position.x, _position.y);
        box->setSize(sf::Vector2f(width, half_height * 2));
        box->setFillColor(_style.background);
        box->setOutlineThickness(_style.border);
        box->setOutlineColor(sf::Color(128,128,128));
            }
};


    
/*
 * O#########
 * #H:......#
 * #S:......# 
 * #........#
 * #********#
 * #1.      #
 * #2.      #
 * #3.      #
 * #        #
 * ##########
 * */

    

}
