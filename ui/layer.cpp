#include "layer.hpp"
#include "engine.hpp"

void Layer::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    state.transform *= getTransform();
    for ( auto& sprite : *m_sprites ) {
        sprite.move(getPosition());
        target.draw(sprite);
    }
    m_sprites->clear();
}

