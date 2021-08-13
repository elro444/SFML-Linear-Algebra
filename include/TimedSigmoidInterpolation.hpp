#pragma once
#include "Util.h"

#include "TimedInterpolation.hpp"

class TimedSigmoidInterpolation
    : public TimedInterpolation
{
protected:
    /* Sigmoid function params */
    float p, s;

public:
    inline TimedSigmoidInterpolation(const sf::Time& duration, float p=.5f, float s=.5f)
        : TimedInterpolation(duration), p(p), s(s) {}

    virtual inline float get() const
    {
        float linearPercentage = std::min(1.f, m_elapsed / m_duration);
        return util::interpolation::sigmoid(linearPercentage, p, s);
    }
};