#include <iostream>
#include <cmath>
#include <filesystem>
#include <memory>
#include <SFML/Graphics.hpp>
#include <ctime> 

_CMATH_

class Player {
public:
    Player()
        : sprite(texture), position(500.f, 500.f), angle(sf::degrees(180))
    {
        // Load texture from file
        if (!texture.loadFromFile("../sprites/blueship1.png")) {
            // Handle error (e.g., log or throw)
        }
        // Assign texture to sprite
        sprite = sf::Sprite(texture);
        // Optionally, set origin, scale, or other properties
        sprite.setPosition(position);
    }
    
    void Draw(sf::RenderWindow& window, float deltaTime) {
        sf::Transform transform;
        static sf::Clock clock;

        float currentTime = clock.getElapsedTime().asSeconds();
        float sinus = sin(static_cast<float>(currentTime));
        std::cout << sinus << std::endl;

        transform.scale(sf::Vector2f(1.1, 1.1)).rotate(sf::Angle(sf::degrees(deltaTime * 10)));
        sprite.setPosition(position+=sf::Vector2f(sinus * deltaTime * 100, sinus * deltaTime * 100));

        window.draw(sprite, transform);
    }

private:
    sf::Texture texture;  // Must be a member variable!
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Angle angle;
};

namespace fs = std::filesystem;


int main()
{
    
    sf::RenderWindow window(sf::VideoMode({ 2000, 1800 }), "Astroids Game",
        sf::Style::Close | sf::Style::Titlebar);
    sf::Clock clock;

    //code to test shape transforms
    sf::Transform transform;
    transform.translate(sf::Vector2f(300,300)).rotate(sf::Angle(sf::degrees(0)));

    sf::Texture texture;
    if (!texture.loadFromFile("../sprites/blueship1.png")) {
        return 0;
    }
    sf::Sprite sprite(texture);


    // Create a graphical text to display
    //const sf::Font font("arial.ttf");
    //sf::Text text(font, "Hello SFML", 50);

    Player player;

    while (window.isOpen())
    {

        //restart() returns a time object which ahve asSeconds as member
        float deltaTime = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        transform.rotate(sf::Angle(sf::degrees(deltaTime * 10)));
        window.clear();
        player.Draw(window, deltaTime);
        //draw the test shape that is moving to know the update is working
        window.draw(sprite, transform);
        // end draw test shape
        window.display();
    }

    std::cout << "Hello World!\n";
}
