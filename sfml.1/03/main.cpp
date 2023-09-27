#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({2, 300}), "title");

    window.clear();

    sf::CircleShape greenLight(40);
    greenLight.setPosition({10, 10});
    greenLight.setFillColor(sf::Color::Green);
    window.draw(greenLight);

    sf::CircleShape yellowLight(40);
    yellowLight.setPosition({10, 110});
    yellowLight.setFillColor(sf::Color::Yellow);
    window.draw(yellowLight);

    sf::CircleShape redLight(40);
    redLight.setPosition({10, 210});
    redLight.setFillColor(sf::Color::Red);
    window.draw(redLight);

    window.display();

    sf::sleep(sf::seconds(5));
}