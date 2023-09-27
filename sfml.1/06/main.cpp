#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::ConvexShape roof;
    roof.setFillColor(sf::Color(sf::Color::Red));
    roof.setPosition({400, 300});
    roof.setPointCount(4);
    roof.setPoint(0, {-180, 0});
    roof.setPoint(1, {+180, 0});
    roof.setPoint(2, {+300, 100});
    roof.setPoint(3, {-300, 100});

    sf::RectangleShape houseBody;
    houseBody.setSize({500, 300});
    houseBody.setPosition({150, 400});
    houseBody.setFillColor(sf::Color(sf::Color::Yellow));

    sf::RectangleShape door;
    door.setSize({100, 200});
    door.setPosition({200, 500});
    door.setFillColor(sf::Color(153, 153, 153));

    sf::RectangleShape pipe1;
    pipe1.setSize({30, 60});
    pipe1.setPosition({500, 270});
    pipe1.setFillColor(sf::Color(153, 153, 153));

    sf::RectangleShape pipe2;
    pipe2.setSize({60, 30});
    pipe2.setPosition({485, 240});
    pipe2.setFillColor(sf::Color(153, 153, 153));

    sf::CircleShape smoke1(20);
    smoke1.setPosition({500, 200});
    smoke1.setFillColor(sf::Color(230, 230, 230));

    sf::CircleShape smoke2(25);
    smoke2.setPosition({520, 180});
    smoke2.setFillColor(sf::Color(230, 230, 230));

    sf::CircleShape smoke3(30);
    smoke3.setPosition({550, 150});
    smoke3.setFillColor(sf::Color(230, 230, 230));

    sf::CircleShape smoke4(35);
    smoke4.setPosition({590, 110});
    smoke4.setFillColor(sf::Color(230, 230, 230));

    sf::RenderWindow window(sf::VideoMode({1800, 1000}), "Convex Shapes");
    window.clear();
    window.draw(roof);
    window.draw(houseBody);
    window.draw(door);
    window.draw(smoke1);
    window.draw(smoke2);
    window.draw(smoke3);
    window.draw(smoke4);
    window.draw(pipe1);
    window.draw(pipe2);

    window.display();

    sf::sleep(sf::seconds(5));
}