#pragma once
#include <vector>

#include "TimedAnimation.hpp"

/**
 * Create an "animation" that does nothing, to create delays between animations.
 **/
TimedAnimation Delay(const sf::Time& duration);

/**
 * Chain animations together, one after the other.
 **/
TimedAnimation Chain(std::vector<TimedAnimation> animations);
