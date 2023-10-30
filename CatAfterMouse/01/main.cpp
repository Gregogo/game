#include <SFML/Graphics.hpp>
#include <cmath>
#include <math.h>
#include <iostream>

struct Arrow
{
    sf::ConvexShape body;
    sf::Vector2f position;
    float rotation = 0;
};

float toDegrees(float radians)
{
    return radians * 180.0 / float(M_PI);
}

float toPi(float degrees)
{
    return degrees / 180.0 * float(M_PI);
}

void updateArrowElements(Arrow &arrow)
{
    arrow.body.setPosition(arrow.position);
    arrow.body.setRotation(arrow.rotation);
}

// Инициализирует фигуру-стрелку
void initArrow(Arrow &arrow)
{
    arrow.position = {400, 300};

    arrow.body.setPointCount(7);
    arrow.body.setPoint(0, {30, 0});
    arrow.body.setPoint(1, {0, -20});
    arrow.body.setPoint(2, {0, -7});
    arrow.body.setPoint(3, {-40, -7});
    arrow.body.setPoint(4, {-40, 7});
    arrow.body.setPoint(5, {0, 7});
    arrow.body.setPoint(6, {0, 20});
    arrow.body.setFillColor(sf::Color(252, 186, 3));
    arrow.body.setOutlineColor(sf::Color(0, 0, 0));
    arrow.body.setOutlineThickness(2.0);

    updateArrowElements(arrow);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;

    mousePosition = {float(event.x),
                     float(event.y)};
}

// Опрашивает и обрабатывает доступные события в цикле.
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

// Обновляет фигуру, указывающую на мышь
void update(const sf::Vector2f &mousePosition, Arrow &arrow, float deltaTime)
{
    const sf::Vector2f delta = mousePosition - arrow.position;
    const float speed = 5;
    const float rotateSpeed = 200;
    const float calculatedSpeed = sqrt((delta.x) * (delta.x) + (delta.y) * (delta.y) * speed);

    const float rotationDelta = (toPi(arrow.rotation) - atan2(delta.y, delta.x));
    float angle = arrow.rotation;
    const float neededAngle = toDegrees(atan2(delta.y, delta.x)) + 180;
    const float opositeAngle = std::fmod((angle + 180), 360.0);
    if (angle > opositeAngle)
    {
        if ((angle > neededAngle) && (opositeAngle < neededAngle))
        {
            angle = angle + deltaTime * rotateSpeed;
        }
        else
        {
            angle = angle - deltaTime * rotateSpeed;
        }
    }
    else
    {
        if ((angle < neededAngle) && (opositeAngle > neededAngle))
        {
            angle = angle - deltaTime * rotateSpeed;
        }
        else
        {
            angle = angle + deltaTime * rotateSpeed;
        }
    }
    angle = std::fmod(angle + 360.0, 360.0);
    arrow.rotation = angle;
    arrow.position = {
        x : arrow.position.x + calculatedSpeed * deltaTime * cos(toPi(arrow.rotation)),
        y : arrow.position.y + calculatedSpeed * deltaTime * sin(toPi(arrow.rotation))
    };
    updateArrowElements(arrow);
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, Arrow &arrow)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(arrow.body);
    window.display();
}

// Программа рисует в окне стрелку, которая поворачивается вслед за курсором мыши.
int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow follows mouse", sf::Style::Default, settings);

    Arrow arrow;
    sf::Vector2f mousePosition;

    initArrow(arrow);

    sf::Clock clock;
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        const float deltaTime = clock.restart().asSeconds();
        update(mousePosition, arrow, deltaTime);
        redrawFrame(window, arrow);
    }
}