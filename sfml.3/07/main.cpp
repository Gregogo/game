#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &firstPupil, sf::ConvexShape &secondPupil, sf::Vector2f ellipseRadius, sf::Vector2f pupilRadius)
{
    const sf::Vector2f socketOne = {x : 300,
                                    y : 300};
    const sf::Vector2f socketTwo = {x : 600,
                                    y : 300};
    const sf::Vector2f firstDelta = {x : socketOne.x - mousePosition.x,
                                     y : socketOne.y - mousePosition.y};
    const float firstDeltaLength = sqrt(firstDelta.x * firstDelta.x + firstDelta.y * firstDelta.y);
    const float firstAngle = atan2(firstDelta.y, firstDelta.x);
    const float firstCircleRadius = (ellipseRadius.x - pupilRadius.x * 1.5) * (cos(firstAngle)) * (cos(firstAngle)) + (ellipseRadius.y - pupilRadius.y * 2) * (sin(firstAngle)) * (sin(firstAngle));

    const sf::Vector2f secondDelta = {x : socketTwo.x - mousePosition.x,
                                      y : socketTwo.y - mousePosition.y};
    const float secondDeltaLength = sqrt(secondDelta.x * secondDelta.x + secondDelta.y * secondDelta.y);
    const float secondAngle = atan2(secondDelta.y, secondDelta.x);
    const float secondCircleRadius = (ellipseRadius.x - pupilRadius.x * 1.5) * (cos(secondAngle)) * (cos(secondAngle)) + (ellipseRadius.y - pupilRadius.y * 2) * (sin(secondAngle)) * (sin(secondAngle));

    float y;
    if (firstCircleRadius > firstDeltaLength)
    {
        y = ((socketTwo.y - sin(secondAngle) * secondCircleRadius) + (mousePosition.y)) / 2;
    }
    else
    {
        if (secondCircleRadius > secondDeltaLength)
        {
            y = ((mousePosition.y) + (socketOne.y - sin(firstAngle) * firstCircleRadius)) / 2;
        }
        else
        {
            y = ((socketTwo.y - sin(secondAngle) * secondCircleRadius) + (socketOne.y - sin(firstAngle) * firstCircleRadius)) / 2;
        }
    }

    if (firstCircleRadius > firstDeltaLength)
    {
        firstPupil.setPosition({mousePosition.x, y});
    }
    else
    {
        const float x = socketOne.x - cos(firstAngle) * firstCircleRadius;
        //const float y = socketOne.y - sin(firstAngle) * firstCircleRadius;
        firstPupil.setPosition({x, y});
    }

    if (secondCircleRadius > secondDeltaLength)
    {
        secondPupil.setPosition({mousePosition.x, y});
    }
    else
    {
        const float x = socketTwo.x - cos(secondAngle) * secondCircleRadius;
        //const float y = socketTwo.y - sin(secondAngle) * secondCircleRadius;
        secondPupil.setPosition({x, y});
    }
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{

    mousePosition = {float(event.x),
                     float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape firstEye, sf::ConvexShape secondEye, sf::ConvexShape firstPupil, sf::ConvexShape secondPupil)
{
    window.clear();
    window.draw(firstEye);
    window.draw(secondEye);
    window.draw(firstPupil);
    window.draw(secondPupil);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 1000;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "looking", sf::Style::Default, settings);

    sf::Vector2f mousePosition;

    constexpr int pointCount = 200;
    const sf::Vector2f ellipseRadius = {120.f, 200.f};
    const sf::Vector2f pupilRadius = {24.f, 40.f};

    sf::ConvexShape firstEye;
    firstEye.setPosition({300, 300});
    firstEye.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    firstEye.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; pointNo++)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            ellipseRadius.x * std::sin(angle),
            ellipseRadius.y * std::cos(angle)};
        firstEye.setPoint(pointNo, point);
    };

    sf::ConvexShape secondEye;
    secondEye.setPosition({600, 300});
    secondEye.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    secondEye.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; pointNo++)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            ellipseRadius.x * std::sin(angle),
            ellipseRadius.y * std::cos(angle)};
        secondEye.setPoint(pointNo, point);
    };

    sf::ConvexShape firstPupil;
    firstPupil.setPosition({300, 300});
    firstPupil.setFillColor(sf::Color(0x0, 0x0, 0x0));
    firstPupil.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; pointNo++)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            pupilRadius.x * std::sin(angle),
            pupilRadius.y * std::cos(angle)};
        firstPupil.setPoint(pointNo, point);
    };

    sf::ConvexShape secondPupil;
    secondPupil.setPosition({600, 300});
    secondPupil.setFillColor(sf::Color(0x0, 0x0, 0x0));
    secondPupil.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; pointNo++)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            pupilRadius.x * std::sin(angle),
            pupilRadius.y * std::cos(angle)};
        secondPupil.setPoint(pointNo, point);
    };

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, firstPupil, secondPupil, ellipseRadius, pupilRadius);
        redrawFrame(window, firstEye, secondEye, firstPupil, secondPupil);
    }
}