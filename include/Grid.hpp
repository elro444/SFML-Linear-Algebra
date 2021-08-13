#pragma once
#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Grid
    : public sf::Drawable, public sf::Transformable
{
private:
    float m_spacing;
    std::vector<sf::Vertex> m_gridLines;
    

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    Grid(float spacing, const sf::Vector2f& size);
};