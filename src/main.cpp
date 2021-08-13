#include <functional>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Util.h"

#include "Scene.hpp"
#include "Matrix.hpp"
#include "DrawableMatrix.hpp"
#include "Grid.hpp"
// #include "TimedSigmoidInterpolation.hpp"
// #include "ThickArrow.hpp"

std::map<int, Scene> g_scenes;

int main()
{
    /* Consts */
    sf::Color background(0xD, 0xD, 0xD);
    sf::Color blue(30, 80, 230);
    sf::Color red(230, 30, 60);

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "LinearAlgebra", sf::Style::Fullscreen, sf::ContextSettings(0, 0, 8));
    sf::View guiView = window.getView();
    float viewScale = 1.5f;
    sf::View worldView(sf::Vector2f(), viewScale * sf::Vector2f(16, -9));
    
    // TimedSigmoidInterpolation ascend(sf::seconds(1.5));
    // Matrix2f identity(sf::Vector2f(1, 0), sf::Vector2f(0, 1));
    Matrix2f stretch(sf::Vector2f(2, 0), sf::Vector2f(2, 1));

    // Grid grid(sf::Vector2f(30, 30));

    sf::Vector2f headPos;
    sf::Vector2f tailPos;
    // std::vector<Interpolator> interpolators = {
    //     makeInterpolator(guiView.getCenter(), guiView.getCenter() + sf::Vector2f(300, 300), headPos),
    //     makeInterpolator(guiView.getCenter() + sf::Vector2f(-200, 200), guiView.getCenter(), tailPos)
    // };

    sf::Clock clock;
    sf::Time elapsed = sf::Time::Zero;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                }
                break;
            }
        }
        sf::Time deltaTime = clock.restart();
        elapsed += deltaTime;
        // ascend.update(deltaTime);

        window.clear(background);
        // DrawableMatrix matrix(stretch);
        // matrix.setPosition(window.getView().getCenter());
        // window.draw(matrix);
        
        g_scenes.at(0).update(deltaTime);
        window.draw(g_scenes.at(0));
        window.display();
    }
    
    return 0;
}

void f()
{
    /* Draw things scaled as 1 pixel */
    // window.setView(worldView);
    // sf::RectangleShape rect(sf::Vector2f(100, 100));
    // rect.setFillColor(blue);
    // if (ascend.hasEnded()) {
    //     rect.setFillColor(red);
    // }
    // rect.setPosition(window.getView().getCenter());
    // rect.setOrigin(rect.getSize() / 2.f);
    // // rect.setPosition(window.getView().getCenter() + sf::Vector2f(0, 300) + sf::Vector2f(0, -600) * ascend.get());
    // Matrix2f currentMatrix = util::interpolation::linear(identity, stretch, ascend.get());
    // window.draw(grid, static_cast<sf::Transform>(currentMatrix));

    // /* Draw things in the normal 1920x1080 view */
    // window.setView(guiView);
    // DrawableMatrix drawableMatrix(currentMatrix);
    // drawableMatrix.setPosition(300, 300);
    
    // window.draw(drawableMatrix);

    // for (const auto& f : interpolators) {
    //     f(ascend.get());
    // }
    // ThickArrow arrow(
    //     tailPos, headPos, 5.f, blue, 15.f
    // );
    // window.draw(arrow);
}