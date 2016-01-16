#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>



#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::Font font;
    font.loadFromFile("media/COURIER.TTF");
    sf::Text text;
    text.setString("TEST");
    text.setFont(font);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(text);
        window.display();
    }
}
    