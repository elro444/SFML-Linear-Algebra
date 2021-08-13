#pragma once
#include <functional>
#include <memory>

#include <SFML/System/Time.hpp>
#include <polymorphic_value.h>

#include "Pacer.hpp"

class TimedAnimation
{
public:
    using UpdateCallback = std::function<void(float)>;

private:

protected:
    const sf::Time m_duration;
    sf::Time m_elapsed;
    const UpdateCallback m_callback;
    const jbcoe::polymorphic_value<Pacer> m_pacer;
    // std::unique_ptr<Pacer> m_pacer;

public:
    TimedAnimation(const sf::Time& duration, UpdateCallback callback, jbcoe::polymorphic_value<Pacer> pacer);

    /* Life cycle of the interpolation */
    void update(const sf::Time& deltaTime);
    bool hasEnded() const;
};
