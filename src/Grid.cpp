#include "Grid.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "Util.h"
#include "ThickArrow.hpp"


const sf::Color thinLineColor(52, 160, 198);
const sf::Color thickLineColor(sf::Color::White);
// constexpr float gridSpacing = 1.f;
// constexpr float outsidePadding = 5.f;
// constexpr float lineThickness = 1.5f;
// constexpr float thickLineThickness = 2.5f;


/***
 * Create a grid, with a line per cell.
 * Axis have a thicker line.
 * :param size: The area that the grid should cover (with line every 'spacing')?
 ***/
Grid::Grid(float spacing, const sf::Vector2f& size)
    : m_gridLines()
    , m_spacing(spacing)
{

    for (float x = 0; x < size.x / 2.f; x += spacing) {
        sf::Color color(thinLineColor);
        if (x == 0) {
            color = thickLineColor;
        }
        for (float offset : {x, -x}) {
            m_gridLines.push_back(
                sf::Vertex(
                    {offset, -size.y/2.f},
                    color)
                );
            m_gridLines.push_back(
                sf::Vertex(
                    {offset, size.y/2.f},
                    color)
                );
            if (x == 0) {
                break;
            }
        }
    }
    for (float y = 0; y < size.y / 2.f; y += spacing) {
        sf::Color color(thinLineColor);
        if (y == 0) {
            color = thickLineColor;
        }
        for (float offset : {y, -y}) {
            m_gridLines.push_back(
                sf::Vertex(
                    {-size.x/2.f, offset},
                    color)
                );
            m_gridLines.push_back(
                sf::Vertex(
                    {size.x/2.f, offset},
                    color)
                );
            if (y == 0) {
                break;
            }
        }
    }
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.transform.scale(sf::Vector2f(1, -1)); // Flip on y axis to have positive go up

    target.draw(m_gridLines.data(), m_gridLines.size(), sf::PrimitiveType::Lines, states);
    float arrowsThickness = m_spacing / 50.f;
    float arrowsTipRadius = arrowsThickness * 4.f;

    sf::Vector2f iHat(0, m_spacing), jHat(m_spacing, 0);
    sf::Vector2f origin(states.transform.transformPoint(0, 0));
    ThickArrow iHatDrawable(origin, states.transform.transformPoint(iHat), arrowsThickness, sf::Color(255, 110, 102), arrowsTipRadius);
    target.draw(iHatDrawable);
    ThickArrow jHatDrawable(origin, states.transform.transformPoint(jHat), arrowsThickness, sf::Color(172, 245, 168), arrowsTipRadius);
    target.draw(jHatDrawable);
}
