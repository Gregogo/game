#include <SFML/Graphics.hpp>
#include <cmath>
#include <math.h>
#include <iostream>

struct Sprite
{
    sf::Sprite body;
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

void updateSpriteElements(Sprite &sprite)
{
    sprite.body.setPosition(sprite.position);
    sprite.body.setRotation(sprite.rotation);
}

void onMousePress(const sf::Event::MouseButtonEvent &event, sf::Vector2f &mousePosition, Sprite &pointer)
{
    mousePosition = {float(event.x),
                     float(event.y)};
    pointer.position = mousePosition;
    updateSpriteElements(pointer);
}

// Опрашивает и обрабатывает доступные события в цикле.
void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, Sprite &pointer)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            onMousePress(event.mouseButton, mousePosition, pointer);
            break;
        default:
            break;
        }
    }
}

// Обновляет фигуру, указывающую на мышь
void update(const sf::Vector2f &mousePosition, Sprite &sprite, float deltaTime)
{
    const sf::Vector2f delta = mousePosition - sprite.position;
    const float speed = 5;
    const float rotateSpeed = 200;
    const float calculatedSpeed = sqrt((delta.x) * (delta.x) + (delta.y) * (delta.y) * speed);

    const float rotationDelta = (toPi(sprite.rotation) - atan2(delta.y, delta.x));
    float angle = sprite.rotation;
    const float neededAngle = toDegrees(atan2(delta.y, delta.x)) + 180;
    const float opositeAngle = std::fmod((angle + 180), 360.0);
    if (sprite.position.x < mousePosition.x)
    {
        sprite.body.setScale(sf::Vector2f(0.1, 0.1));
    }
    else
    {
        sprite.body.setScale(sf::Vector2f(-0.1, 0.1));
    }
    angle = std::fmod(neededAngle + 360.0, 360.0);
    sprite.position = {
        x : sprite.position.x - calculatedSpeed * deltaTime * cos(toPi(angle)),
        y : sprite.position.y - calculatedSpeed * deltaTime * sin(toPi(angle))
    };
    updateSpriteElements(sprite);
}

// Рисует и выводит один кадр
void redrawFrame(sf::RenderWindow &window, Sprite &sprite, Sprite &pointer)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(sprite.body);
    window.draw(pointer.body);
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
        "Sprite follows mouse", sf::Style::Default, settings);

    Sprite sprite;
    sf::Vector2f mousePosition;

    sf::Texture texture;
    texture.loadFromFile("png-transparent-among-us.png");
    texture.setSmooth(true);
    sprite.body.setTexture(texture);
    sprite.position.x = 0;
    sprite.position.y = 0;
    sprite.body.setOrigin(sf::Vector2f(460, 600));
    sprite.body.setScale(sf::Vector2f(0.1, 0.1));
    sprite.body.setPosition(sprite.position);
    updateSpriteElements(sprite);

    Sprite pointer;
    sf::Texture texture2;
    texture2.loadFromFile("red_pointer.png");
    texture2.setSmooth(true);
    pointer.body.setTexture(texture2);
    pointer.position.x = 0;
    pointer.position.y = 0;
    pointer.body.setOrigin(sf::Vector2f(16, 16));
    pointer.body.setPosition(pointer.position);
    updateSpriteElements(pointer);

    sf::Clock clock;
    while (window.isOpen())
    {
        pollEvents(window, mousePosition, pointer);
        const float deltaTime = clock.restart().asSeconds();
        update(mousePosition, sprite, deltaTime);
        redrawFrame(window, sprite, pointer);
    }
}