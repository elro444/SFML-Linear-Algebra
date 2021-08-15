#include "TimedAnimationVariants.hpp"

#include <numeric>

#include "Util.h"

TimedAnimation Delay(const sf::Time& duration)
{
    auto doNothing = [](float){/* Does nothing :) */};
    return TimedAnimation(duration, doNothing, jbcoe::polymorphic_value<Pacer>(new LinearPacer()));
}

TimedAnimation Chain(std::vector<TimedAnimation> animations)
{
    std::vector<sf::Time> durations;
    for (const auto& animation : animations) {
        durations.push_back(animation.getDuration());
    }

    sf::Time totalDuration = std::accumulate(durations.begin(), durations.end(), sf::Time::Zero);

    // The starting percentage for each animation, rational to it's duration.
    std::vector<sf::Time> subAnimationsStartTime;
    subAnimationsStartTime.resize(animations.size() + 1, sf::Time::Zero); // +1 for first startTime which is zero.
    std::partial_sum(durations.begin(), durations.end(), subAnimationsStartTime.begin() + 1,
        [](sf::Time currentStart, const sf::Time& duration){return currentStart + duration;});
    subAnimationsStartTime.resize(animations.size()); // Get rid of the unneeded last one.

    auto interpolateChain = [animations, totalDuration, subAnimationsStartTime](float x) mutable {
        sf::Time elapsed = totalDuration * x;
        for (unsigned i = 0; i < subAnimationsStartTime.size(); ++i) {
            animations[i].update(util::clamp(
                elapsed - subAnimationsStartTime[i],
                sf::Time::Zero,
                animations[i].getDuration()
            ));
        }
    };
    return TimedAnimation(totalDuration, interpolateChain, jbcoe::polymorphic_value<Pacer>(new LinearPacer()));
}
