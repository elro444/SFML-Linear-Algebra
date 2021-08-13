#include "DrawableMatrix.hpp"

#include <vector>
#include <sstream>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Util.h"


static sf::Font loadFont()
{
    sf::Font font;
    // font.loadFromMemory(consolaFontArray, consolaFontArraySize);
    font.loadFromFile("res\\cambria.ttc");
    return font;
}

template<typename T>
static std::string to_string(T t, unsigned precision = 2)
{
    std::ostringstream out;
    out.precision(precision);
    out << t;
    return out.str();
}

DrawableMatrix::DrawableMatrix(const std::vector<std::vector<float>>& rows)
    : m_rows(rows)
{
}

DrawableMatrix::DrawableMatrix(const Matrix2f& matrix)
    : DrawableMatrix(std::vector<std::vector<float>>{
        {matrix.iHat.x, matrix.jHat.x}, 
        {matrix.iHat.y, matrix.jHat.y}
    })
{
}

void DrawableMatrix::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    const float padding = 30.f;
    const float bracketsThickness = 3.f;
    const float bracketsArms = padding/2.f; // How much the tips of the brackets hang
    static sf::Font font = loadFont();

    /* Cell: Text and it's position in the matrix */
    using Cell = std::tuple<sf::Text, sf::Vector2i>;
    std::vector<Cell> cells;
    sf::Vector2f biggestCellSize(-1, -1);

    size_t columns = 0;
    size_t rows = m_rows.size();
    for (unsigned y = 0; y < m_rows.size(); ++y) {
        columns = std::max(m_rows[y].size(), columns);
        for (unsigned x = 0; x < m_rows[y].size(); ++x) {
            sf::Text text(to_string(m_rows[y][x]), font);
            sf::FloatRect bounds = text.getGlobalBounds();
            if (bounds.width > biggestCellSize.x) {
                biggestCellSize.x = bounds.width;
            }
            if (bounds.height > biggestCellSize.y) {
                biggestCellSize.y = bounds.height;
            }
            // text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
            cells.push_back({std::move(text), sf::Vector2i(x, y)});
        }
    }

    for (auto [text, index] : cells) {
        // Move the text to it's cell
        sf::Vector2f centeredPos = sf::Vector2f(index) - 0.5f * sf::Vector2f(columns - 1, rows - 1);
        sf::Vector2f cellScale = biggestCellSize + sf::Vector2f(padding, padding);
        sf::Vector2f scaledCenteredPos = util::scaleVector<2>(centeredPos, cellScale);
        text.setPosition(scaledCenteredPos);

        // Center text on itself:
        sf::FloatRect lbounds = text.getLocalBounds();
        text.setOrigin(lbounds.left + lbounds.width / 2, lbounds.top + lbounds.height / 2);
        
        target.draw(text, states);
    }

    float bracketsOffset = 0.5f * columns * (biggestCellSize.x + padding);
    float bracketsHeight = (rows - 0.5f) * (biggestCellSize.y + padding);

    sf::RectangleShape brackets(
        sf::Vector2f(
            bracketsThickness,
            bracketsHeight
        )
    );
    brackets.setOrigin(brackets.getSize() / 2.f);

    brackets.setPosition(-bracketsOffset, 0);
    target.draw(brackets, states);

    brackets.setPosition(bracketsOffset, 0);
    target.draw(brackets, states);

    // The little handles of the brackets
    sf::RectangleShape handles = brackets;
    handles.setSize(sf::Vector2f(0.25f * padding, bracketsThickness));

    handles.setOrigin(0, 0); // Bottom left
    handles.setPosition(-bracketsOffset, -bracketsHeight / 2.f);
    target.draw(handles, states);

    handles.setOrigin(0, handles.getSize().y); // Top left
    handles.setPosition(-bracketsOffset, bracketsHeight / 2.f);
    target.draw(handles, states);

    handles.setOrigin(handles.getSize().x, 0); // Bottom right    
    handles.setPosition(bracketsOffset, -bracketsHeight / 2.f);
    target.draw(handles, states);
    
    handles.setOrigin(handles.getSize()); // Top right    
    handles.setPosition(bracketsOffset, bracketsHeight / 2.f);
    target.draw(handles, states);
}