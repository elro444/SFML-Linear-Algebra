#include "Scene.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

Scene::Scene(std::vector<InitializerFunc> initializers)
    : m_segments()
    , m_currentSegment(0)
    , m_currentSegmentStartTime(sf::Time::Zero)
{
    // With default constructors..
    m_segments.resize(initializers.size());

    for (unsigned i = 0; i < initializers.size(); ++i) {
        initializers[i](m_segments[i]);
    }
}

bool Scene::advance(const sf::Time& currentTime)
{
    if (!hasNext()) {
        return false;
    }

    ++m_currentSegment;
    m_currentSegmentStartTime = currentTime;
    return true;
}

void Scene::update(const sf::Time& elapsed)
{
    if (m_currentSegment >= m_segments.size()) {
        return;
    }

    for (auto& animation : m_segments[m_currentSegment].animations) {
        animation.update(elapsed - m_currentSegmentStartTime);
    }

    if (hasNext() && m_segments[m_currentSegment + 1].should_autoplay && hasCurrentSegmentEnded()) {
        advance(elapsed);
    }
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (m_currentSegment >= m_segments.size()) {
        return;
    }

    for (const auto& element : m_segments[m_currentSegment].elements) {
        target.draw(*element, states);
    }
}

bool Scene::hasCurrentSegmentEnded() const
{
    if (m_currentSegment >= m_segments.size()) {
        return false; // Maybe a bad fallback? shouldn't happen anyway..
    }
    const auto& animations = m_segments[m_currentSegment].animations;
    return std::all_of(animations.begin(), animations.end(), [](const auto& x){return x.hasEnded();});
}

bool Scene::hasNext() const
{
    return m_currentSegment + 1 < m_segments.size();
}

sf::Time Scene::Segment::getDuration() const
{
    auto compByDuration = [](const auto& a, const auto& b) {
        return a.getDuration() < b.getDuration();
    };
    return std::max_element(animations.begin(), animations.end(), compByDuration)->getDuration();
}
