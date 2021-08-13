#pragma once
#include <vector>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include "Matrix.hpp"

class DrawableMatrix
    : public sf::Drawable, public sf::Transformable
{
private:
    std::vector<std::vector<float>> m_rows;

public:
    DrawableMatrix(const std::vector<std::vector<float>>& rows);
    DrawableMatrix(const Matrix2f& matrix);


protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};