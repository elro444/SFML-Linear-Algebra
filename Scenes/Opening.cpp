#include <SFML/Graphics/Font.hpp>

#include "Helpers.hpp"
#include "Scene.hpp"

#include "ThickArrow.hpp"
#include "Grid.hpp"
#include "DrawableMatrix.hpp"

sf::Font g_mathFont;
const std::string CDOT = "⋅";
const std::string I_HAT = "i ̂";

bool segment1(Scene::Segment& segment)
{
    std::shared_ptr<ThickArrow> arrow = std::make_shared<ThickArrow>(5.f, 15.f);
    // sf::Vector2f iHat(1, 0);
    // sf::Vector2f jHat(0, 1);
    std::shared_ptr<Grid> grid = std::make_shared<Grid>(100, 2.f * sf::Vector2f(1920, 1080));
    grid->setPosition(sf::Vector2f(1920, 1080) / 2.f);

    MAKE_INTERPOLATION_FUNC(sf::Vector2f, headPos, (300, 300), (500, 300), CALL_SETTER(arrow, setHeadPos));
    MAKE_INTERPOLATION_FUNC(sf::Vector2f, tailPos, (300, 500), (300, 300), CALL_SETTER(arrow, setTailPos));
    MAKE_INTERPOLATION_FUNC(sf::Vector3f, color, (0, 0, 255), (0, 255, 0), [arrow](auto x){arrow->setColor(sf::Color(x.x, x.y, x.z));});

    sf::Time duration(sf::seconds(3));
    jbcoe::polymorphic_value<Pacer> sigmoid(new SigmoidPacer());
    jbcoe::polymorphic_value<Pacer> linear(new LinearPacer());

    segment.animations.push_back(TimedAnimation(duration, headPos_interpolator, sigmoid));
    segment.animations.push_back(TimedAnimation(duration, tailPos_interpolator, sigmoid));
    segment.animations.push_back(TimedAnimation(duration, color_interpolator, sigmoid));
    segment.elements.push_back(grid);
    segment.elements.push_back(arrow);
    
}

static bool makeScene()
{
    g_mathFont.loadFromFile("res\\cambria.ttc");
    g_scenes.insert(std::make_pair(0, Scene(
        {
            segment1
        }
    )));
    return true;
}

static bool _unused = makeScene();
