#pragma once
#include <memory>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Spritexture
    : public sf::Sprite
{
private:
    sf::Texture m_texture;
public:
    explicit Spritexture(const sf::Texture& texture);
};
