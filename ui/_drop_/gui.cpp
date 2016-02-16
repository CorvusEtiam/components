#include <iostream>
#include <sstream>
#include <locale>
#include "objects.hpp"

namespace Gui {

using std::string;
string linebreak(string entry, uint width) {
    std::istringstream iss(entry);
    std::ostringstream oss;
    string word;
    
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

using std::wstring;
wstring linebreak(wstring entry, uint width) {
    std::wistringstream iss(entry);
    iss.imbue(std::locale(""));
    std::wostringstream oss;
    wstring word;
    
    if ( iss >> word ) {
        oss << word;
        uint space_left = width - word.length();
        while ( std::getline(iss, word, L' ') ) {
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

    
void StatusBox::render(sf::RenderTarget& target) const
{
    target.draw(*this->blackbox);
    target.draw(*this->textbox);
}


}


