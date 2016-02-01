#include <iostream>
#include <sstream>

#include "gui.hpp"

namespace Gui {

W linebreak(W entry, uint width) {
    std::istringstream iss(entry);
    std::ostringstream oss;
    W word;
    
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

    
    
void MapBox::render(sf::RenderTarget& target) const
{
    for ( auto x = 0; x < width; ++x ) {
        for ( auto y = 0; y < height; ++y ) {
            if ( plane[y][x].visible && plane[y][x].rect != nullptr && plane[y][x].text != nullptr ) {
                target.draw(*plane[y][x].rect);
                target.draw(*plane[y][x].text);
            }  
        }
        
    }
}
    
void StatusBox::render(sf::RenderTarget& target) const
{
    target.draw(*(this->textbox));
}


}


