#include "TimedAnimation.hpp"

#include "Util.h"

TimedAnimation::TimedAnimation(const sf::Time& duration, UpdateCallback callback, jbcoe::polymorphic_value<Pacer> pacer)
    : m_duration(duration)
    , m_elapsed()
    , m_callback(callback)
    , m_pacer(std::move(pacer))
{   
}

void TimedAnimation::update(const sf::Time& elapsed)
{
    m_elapsed = util::clamp(elapsed, sf::Time::Zero, m_duration);
    float percentage = m_elapsed / m_duration;
    m_callback(m_pacer->get(percentage));
}

bool TimedAnimation::hasEnded() const
{
    return m_elapsed >= m_duration;
}

sf::Time TimedAnimation::getDuration() const
{
    return m_duration;
}
