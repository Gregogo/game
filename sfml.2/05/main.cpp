#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>

int main()
{
    constexpr int pointCount = 200;
    const sf::Vector2f ellipseRadius = {1.f, 1.f};
    sf::Clock clock;
    float roseAngle = 0;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}), "Elipse",
        sf::Style::Default, settings);

    sf::ConvexShape ellipse;
    ellipse.setPosition({400, 320});
    ellipse.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; pointNo++)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        float radius = float(200 * sin(6 * float(angle)));
        sf::Vector2f point = {
            radius * std::sin(angle),
            radius * std::cos(angle)};
        ellipse.setPoint(pointNo, point);
    };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();

        const float deltaTime = clock.restart().asSeconds();
        roseAngle = roseAngle + deltaTime * 1;
        ellipse.setPosition({400 + 50 * std::sin(roseAngle),
                             320 + 50 * std::cos(roseAngle)});

        window.draw(ellipse);
        window.display();
    }
}