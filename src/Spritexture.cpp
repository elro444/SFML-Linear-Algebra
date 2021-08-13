#include "Spritexture.hpp"

Spritexture::Spritexture(const sf::Texture& texture)
    : m_texture(texture), Sprite(m_texture)
{
}
