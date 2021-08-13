#pragma once
#include <cmath>

class Pacer
{
public:
    virtual ~Pacer() = default;
    /**
     * Change the pace of some advancing percentage.
     * I.e form linear to logarithmic.
     * Input assumed to be [0,1].
     * Output should be [0,1].
     **/
    virtual float get(float percentage) const = 0;
};

class LinearPacer
    : public Pacer
{
public:
    virtual float get(float percentage) const override
    {
        return percentage;
    }
};

class SigmoidPacer
    : public Pacer
{
private:
    float p, s;

    static float f(float x, float n, float c)
    {
        return pow(x, c) / pow(n, c - 1);
    }
public:
    SigmoidPacer(float p=0.5f, float s=0.5f)
        : p(p), s(s) {}
    
    virtual float get(float percentage) const override
    {
        float c = 2 / (1 - s) - 1;
        if (percentage < p)
            return f(percentage, p, c);
        else
            return 1 - f(1 - percentage, 1 - p, c);
    }
};
