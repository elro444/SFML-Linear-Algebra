#include "TimedInterpolation.hpp"

TimedInterpolation::TimedInterpolation(const sf::Time& duration)
    : m_duration(duration)
    , m_elapsed()
{   
}

void TimedInterpolation::update(const sf::Time& deltaTime)
{
    m_elapsed += deltaTime;
    updateFunc(get());
}

bool TimedInterpolation::hasEnded() const
{
    return m_elapsed >= m_duration;
}

TimedInterpolation& TimedInterpolation::setUpdateFunc(UpdateFunc func)
{
    updateFunc = func;
    return *this;
}
