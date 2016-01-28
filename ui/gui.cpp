#include <iostream>
#include <sstream>
#include "gui.hpp"
namespace Gui {
#if 0
Layer::Layer() : sf::Drawable(), std::vector<sf::Drawable*>() {

}

Layer::~Layer() {
    for ( auto it = begin(); it != end(); ++it ) {
        delete *it;
    }
}

void Layer::render(sf::RenderTarget& target) const {
    for ( std::vector<sf::Drawable*>::iterator it = begin(); it != end(); ++it ) {
        target.draw(*it);
    }
}
#endif

void Box::render(sf::RenderTarget& target) const  { 
    if ( widget->type == WidgetType::TextField ) {
        auto _widget = static_cast<TextFieldWidget*>(widget);
        _widget->draw(target);
    } else if ( widget->type == WidgetType::Button ) {
        auto _widget = static_cast<Button*>(widget);
        _widget->draw(target);
    }
    
    for ( auto& b : children ) {
        b->render(target);
    }
}



std::string linebreak(std::string entry, uint width) {  
    std::istringstream iss(entry);
    std::ostringstream oss;
    std::string word;
    
    if ( iss >> word ) {
        oss << word;
        uint space_left = width - word.length();
        while ( std::getline(iss, word, ' ') ) {
            if ( space_left < word.length() + 1 ) {
                oss << '\n' << word;
                space_left = width - word.length();
            } else {
                oss << ' ' << word;
                space_left -= word.length() + 1;
            }
        }
    }
    return oss.str();
}
    
    
}


