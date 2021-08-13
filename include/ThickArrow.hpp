#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

class ThickArrow
    : public sf::Drawable
{
private:
    mutable sf::RectangleShape m_line;
    mutable sf::ConvexShape m_tip;
    sf::Vector2f m_head;
    sf::Vector2f m_tail;
    sf::Color m_color;
    float m_thickness;
    float m_tipRadius;
    bool m_should_invalidate;

public:
    ThickArrow(float thickness, float tipRadius);
    ThickArrow(sf::Vector2f tail, sf::Vector2f head, float thickness, sf::Color color, float tipRadius);
    void setHeadPos(sf::Vector2f pos);
    void setTailPos(sf::Vector2f pos);
    void setColor(sf::Color color);
    
protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    void invalidate() const;
};
