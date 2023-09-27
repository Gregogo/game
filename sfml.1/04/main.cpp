#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({1500, 1000}), "title");

    window.clear();

    sf::RectangleShape vertLine;
    vertLine.setSize({20, 100});
    vertLine.setRotation(0);
    vertLine.setPosition({100, 100});
    vertLine.setFillColor(sf::Color(0xFF, 0x0, 0xFF));
    window.draw(vertLine);

    sf::RectangleShape gorLine;
    gorLine.setSize({50, 20});
    gorLine.setRotation(0);
    gorLine.setPosition({120, 100});
    gorLine.setFillColor(sf::Color(0xFF, 0x0, 0xFF));
    window.draw(gorLine);

    vertLine.setPosition({170, 100});
    window.draw(vertLine);

    vertLine.setPosition({210, 100});
    window.draw(vertLine);

    gorLine.setPosition({230, 100});
    window.draw(gorLine);

    vertLine.setPosition({300, 100});
    window.draw(vertLine);

    vertLine.setPosition({340, 100});
    window.draw(vertLine);

    vertLine.setRotation(20);
    window.draw(vertLine);

    window.display();

    sf::sleep(sf::seconds(5));
}