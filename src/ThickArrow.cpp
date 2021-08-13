#include "ThickArrow.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "Util.h"

ThickArrow::ThickArrow(float thickness, float tipRadius)
    : ThickArrow(sf::Vector2f(), sf::Vector2f(), thickness, sf::Color(), tipRadius)
{
}

ThickArrow::ThickArrow(sf::Vector2f tail, sf::Vector2f head, float thickness, sf::Color color, float tipRadius)
    : m_line()
    , m_tip(3)
    , m_head(head)
    , m_tail(tail)
    , m_color(color)
    , m_thickness(thickness)
    , m_tipRadius(tipRadius)
    , m_should_invalidate(true)
{
}

void ThickArrow::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_should_invalidate) {
        invalidate();
    }
    target.draw(m_line, states);
    target.draw(m_tip, states);
}

void ThickArrow::setHeadPos(sf::Vector2f pos)
{
    m_head = pos;
    m_should_invalidate = true;
}

void ThickArrow::setTailPos(sf::Vector2f pos)
{
    m_tail = pos;
    m_should_invalidate = true;
}

void ThickArrow::setColor(sf::Color color)
{
    m_color = color;
    m_should_invalidate = true;
}

void ThickArrow::invalidate() const
{
    float angle = util::angle(m_head - m_tail) * util::rad2deg;
    float length = util::abs(m_head - m_tail);
    m_line.setSize(sf::Vector2f(length - m_tipRadius, m_thickness));
    m_line.setFillColor(m_color);
    m_line.setOrigin(0, m_thickness/2.f);
    m_line.setRotation(angle);
    m_line.setPosition(m_tail);

    for (unsigned i = 0; i < 3; ++i) {
        const float angle = util::PI * 2.f / 3.f * static_cast<float>(i);
        m_tip.setPoint(i, m_tipRadius * util::normalize(angle));
    }
    m_tip.setOrigin(m_tipRadius, 0);
    m_tip.setRotation(angle);
    m_tip.setPosition(m_head);
    m_tip.setFillColor(m_color);
}