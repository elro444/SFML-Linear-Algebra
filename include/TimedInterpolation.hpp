#pragma once
#include <functional>

#include <SFML/System/Time.hpp>

class TimedInterpolation
{
public:
    using UpdateFunc = std::function<void(float)>;
    UpdateFunc updateFunc;

private:
    static void stubUpdateFunc(float x)
    {
        UNUSED(x);
    }

protected:
    sf::Time m_elapsed;
    const sf::Time m_duration;

public:
    TimedInterpolation(const sf::Time& duration);

    /* Life cycle of the interpolation */
    void update(const sf::Time& deltaTime);
    bool hasEnded() const;

    TimedInterpolation& setUpdateFunc(UpdateFunc func);

    /* Get the current interpolated value */
    virtual float get() const = 0;
};
