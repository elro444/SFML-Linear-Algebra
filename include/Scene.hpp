#include <vector>
#include <string>
#include <memory>
#include <map>
#include <functional>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

#include "TimedAnimation.hpp"

class Scene
    : public sf::Drawable
{
public:
    using Elements = std::vector<std::shared_ptr<sf::Drawable>>;
    using Animations = std::vector<TimedAnimation>;
    struct Segment
    {
        Elements elements;
        Animations animations;
        bool should_autoplay = false;
        sf::Time getDuration() const; // Returns the duration of the longest animation.
    };
    using InitializerFunc = std::function<void(Segment&)>;

private:
    std::vector<Segment> m_segments;
    unsigned m_currentSegment;
    sf::Time m_currentSegmentStartTime;

    /**
     * Check if all the animations in the current segment have ended.
     **/
    bool hasCurrentSegmentEnded() const;

    /**
     * Check if there is another segment available.
     **/
    bool hasNext() const;

public:

    /**
     * Constructor.
     * Gets a vector of callbacks that will initialize the segments of the 
     * scene with drawable elements and animations to play.
     **/
    Scene(std::vector<InitializerFunc> initializers);

    /**
     * Trigger the next segment. 
     * Returnes false if there is no next segment.
     * :param currentTime: The time at the moment of advancement (for relative timestamps)
     **/
    bool advance(const sf::Time& currentTime);

    /**
     * Update the scene with the time passed since the last frame.
     **/
    void update(const sf::Time& deltaTime);

protected:
    /**
     * Draws all the elements in the scene. 
     **/
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

/**
 * The global map of the scenes in the show.
 * Register scenes to the show by adding them
 * to this map.
 * The key is the index of the scene, and should
 * be kept unique (otherwise will override other scenes)
 **/
extern std::map<int, Scene> g_scenes;
